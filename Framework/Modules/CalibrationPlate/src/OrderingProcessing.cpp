#include "pch.h"
#include "TraceLogExporter.h"
#include "FrameworkDefine.h"
#include "..\include\OrderingProcessing.h"


OrderingProcessing::OrderingProcessing()
{
	__org_cnt__ = 0;
}

OrderingProcessing::~OrderingProcessing()
{
}

void 
OrderingProcessing::SetOriginPointNumber(_In_ UINT cnt)
{
	__org_cnt__ = cnt;
}

NTSTATUS
OrderingProcessing::SetSourcePoint(_In_ PFLOAT pSrcPoint)
{
	for(UINT i = 0; i < __org_cnt__; i++)
	{
		try
		{
			P2F point(pSrcPoint[2 * i], pSrcPoint[2 * i + 1]);
			__org_point_vec__.push_back(point);
		}
		catch(const std::exception& err) 
		{
			TraceLog << "access to list get an exception: \n " << err.what();
			return BUFFER_DISMATCHED_WITTH_NUM;
		}
	}

	return SUCCESSED;
}

NTSTATUS
OrderingProcessing::SetSourcePoint(_In_ SerialPoint2f SrcPoint)
{
	if(SrcPoint.size() < 10)
	{
		return POINTS_NUM_TOO_SMALL;
	}
	__org_point_vec__.swap(SerialPoint2f());
	__org_cnt__ = SrcPoint.size();
	__org_point_vec__.assign(SrcPoint.begin(), SrcPoint.end());

	return SUCCESSED;
}

NTSTATUS OrderingProcessing::OrderingPoints(_Out_ SerialPoint2f& result)
{
	NTSTATUS status = SUCCESSED;
	status = SegregationPointsGroup();
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = SetCenter1();
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = SetCenter2();
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = SeparatePoints();
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	OPRCI __oprci ;
	status = CalculateMinRegs(&__oprci);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	GenerateResultPoints(&__oprci, result);

	return status;
}
//
//SerialPoint2f OrderingProcessing::GetOrderedPoints()
//{
//	return __orderd_points__;
//}
// 
//void 
//OrderingProcessing::GetOrderedPoints(_Out_ SerialPoint2f& result)
//{
//	result.assign(__orderd_points__.begin(), __orderd_points__.end());
//}
//
//UINT OrderingProcessing::GetOrderedPointsCount()
//{
//	return __orderd_points__.size() * 2;
//}
//
//void OrderingProcessing::GetOrderedPointsCount(_Out_ UINT& len)
//{
//	len = __orderd_points__.size() * 2;
//}


NTSTATUS OrderingProcessing::SegregationPointsGroup()
{
	try
	{
		kmeans(__org_point_vec__, 2, __labels__,
			   cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0),
			   3, cv::KMEANS_PP_CENTERS, __center__);
	}
	catch(const std::exception& err) 
	{
		TraceError << "kmeans exception : " << err.what();
		return KMEANS_FALIED;
	}
	return SUCCESSED;
}

NTSTATUS
OrderingProcessing::SetCenter1()
{
	try 
	{
		__cluster_center_1__ = 
			cv::Point2f(__center__.at<FLOAT>(0), __center__.at<FLOAT>(1));
	}
	catch(const std::exception& err) 
	{
		TraceLog << "m_Center1 exception : " << err.what();
		return GROUP_POINTS_TOO_LESS;
	}

	return SUCCESSED;
}

NTSTATUS
OrderingProcessing::SetCenter2()
{
	try 
	{
		__cluster_center_2__ =
			cv::Point2f(__center__.at<FLOAT>(2), __center__.at<FLOAT>(3));
	}
	catch(const std::exception& err)
	{
		TraceLog << "m_Center2 exception : " << err.what();
		return GROUP_POINTS_TOO_LESS;
	}

	return SUCCESSED;
}

NTSTATUS
OrderingProcessing::SeparatePoints()
{
	for(int i = 0; i < __labels__.size(); i++) 
	{
		if(__labels__[i] == 0)__cluster_1__.push_back(__org_point_vec__[i]);
		else __cluster_2__.push_back(__org_point_vec__[i]);
	}
	return SUCCESSED;
}

SerialPoint2f OrderingProcessing::PointsExtract()
{
	SerialPoint2f StandardPoints;
	StandardPoints.push_back(P2F(1, 0));
	StandardPoints.push_back(P2F(1, 1));
	StandardPoints.push_back(P2F(2, 1));
	StandardPoints.push_back(P2F(1, 2));
	StandardPoints.push_back(P2F(2, 2));
	StandardPoints.push_back(P2F(3, 2));
	StandardPoints.push_back(P2F(1, 3));
	StandardPoints.push_back(P2F(2, 3));
	StandardPoints.push_back(P2F(3, 3));
	StandardPoints.push_back(P2F(4, 3));
	StandardPoints.push_back(P2F(1, 4));
	StandardPoints.push_back(P2F(2, 4));
	StandardPoints.push_back(P2F(3, 4));
	StandardPoints.push_back(P2F(4, 4));
	StandardPoints.push_back(P2F(1, 5));
	StandardPoints.push_back(P2F(2, 5));
	StandardPoints.push_back(P2F(3, 5));
	StandardPoints.push_back(P2F(4, 5));
	StandardPoints.push_back(P2F(1, 6));
	StandardPoints.push_back(P2F(2, 6));
	StandardPoints.push_back(P2F(3, 6));
	StandardPoints.push_back(P2F(4, 6));
	StandardPoints.push_back(P2F(1, 7));
	StandardPoints.push_back(P2F(2, 7));
	StandardPoints.push_back(P2F(3, 7));
	StandardPoints.push_back(P2F(4, 7));
	return StandardPoints;
}

void 
OrderingProcessing::GenerateResultPoints(_In_ POPRCI pInput, _Out_ SerialPoint2f& result)
{
	bool AddFlip = false;
	if(pInput->fit1 > pInput->fit1_f)
	{
		AddFlip = false;
	}
	else if(pInput->fit1 < pInput->fit1_f)
	{
		AddFlip = true;
	}
	else if(pInput->fit1 == pInput->fit1_f)
	{
		if(pInput->error1 < pInput->error1_f)AddFlip = false;
		else AddFlip = true;
	}

	FinalResult(pInput, AddFlip, result);
}

void
OrderingProcessing::FinalResult(
	_In_ POPRCI pInput, _In_ bool AddFlip, _In_ SerialPoint2f& result)
{
	if(AddFlip)
	{
		if((pInput->center2_f - pInput->center1_f).dot(pInput->drct1_f) > 0)
		{
			for(int i = 0; i < pInput->crspd1_f.size(); i++)
				result.push_back(pInput->crspd1_f[i]);
			for(int i = 0; i < pInput->crspd2_f.size(); i++)
				result.push_back(pInput->crspd2_f[i]);
		}
		else
		{
			for(int i = 0; i < pInput->crspd2_f.size(); i++)
				result.push_back(pInput->crspd2_f[i]);
			for(int i = 0; i < pInput->crspd1_f.size(); i++)
				result.push_back(pInput->crspd1_f[i]);
		}
	}
	else
	{
		if((__cluster_center_2__ - __cluster_center_1__).dot(pInput->drct1) > 0)
		{
			for(int i = 0; i < pInput->crspd1.size(); i++)
				result.push_back(pInput->crspd1[i]);
			for(int i = 0; i < pInput->crspd2.size(); i++)
				result.push_back(pInput->crspd2[i]);
		}
		else
		{
			for(int i = 0; i < pInput->crspd2.size(); i++)
				result.push_back(pInput->crspd2[i]);

			for(int i = 0; i < pInput->crspd1.size(); i++)
				result.push_back(pInput->crspd1[i]);
		}
	}
}

NTSTATUS OrderingProcessing::CalculateMinRegs(_Out_ POPRCI __p_oprci)
{
	NTSTATUS status = SUCCESSED;
	SerialPoint2f stdPoints = PointsExtract();
	status = CalculateMinReg(
		__cluster_1__, stdPoints, __p_oprci->crspd1, &__p_oprci->fit1,
		&__p_oprci->error1, __p_oprci->drct1, __cluster_center_1__);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	status = CalculateMinReg(
		__cluster_2__, stdPoints, __p_oprci->crspd2, &__p_oprci->fit2, 
		&__p_oprci->error1, __p_oprci->drct2, __cluster_center_2__);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	SerialPoint2f stdPoints_f;
	stdPoints_f.assign(stdPoints.begin(), stdPoints.end());
	for(int i = 0; i < stdPoints_f.size(); i++){
		stdPoints_f[i].x = -stdPoints_f[i].x;
	}

	status = CalculateMinReg(
		__cluster_1__, stdPoints_f, __p_oprci->crspd1_f, &__p_oprci->fit1_f, 
		&__p_oprci->error1_f, __p_oprci->drct1_f, __p_oprci->center1_f);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	status = CalculateMinReg(
		__cluster_2__, stdPoints_f, __p_oprci->crspd2_f, &__p_oprci->fit2_f,
		&__p_oprci->error2_f, __p_oprci->drct2_f, __p_oprci->center2_f);

	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	return status;
}

NTSTATUS
OrderingProcessing::CalculateMinReg(
	_In_ SerialPoint2f cluster1, _In_ SerialPoint2f cluster2,
	_Out_ SerialPoint2f &correspondence, _Out_ INT* fitNum,
	_Out_ DOUBLE* totalError, _Out_ P2F &direction,_Out_ P2F &center)
{
	P2F	center_cluster1, center_cluster2;
	CPDMatrix cpdCalib_1(cluster1.size(), 2);
	NTSTATUS status = RotatePrepare(
		cluster1, cluster2,center_cluster1,center_cluster2, cpdCalib_1);

	if(status != SUCCESSED)
	{
		*fitNum = 0;
		return status;
	}

	INT maxFit = 0; DOUBLE minError = DBL_MAX; SerialPoint2f kPoint;
	for(INT degree = 0; degree < 360; degree += 15)
	{
		RotationRunning(cluster1, cluster2, center_cluster2,
						degree, maxFit, minError, cpdCalib_1,kPoint);
		
	}
	center.x = center.y = 0;

	for(INT i = 0; i < kPoint.size(); i++)
	{
		FLOAT dist = FLT_MAX; INT index = 0;
		center += kPoint[i];
		for(INT j = 0; j < cluster1.size(); j++)
		{
			FLOAT ftemp = CalculatePointsDistance(kPoint[i], cluster1[j]);
			if(ftemp < dist) 
			{
				dist = ftemp;
				index = j;
			}
		}
		if(dist < ERROR_PIXEL)correspondence.push_back(cluster1[index]);
		else correspondence.push_back(P2F(-1, -1));
	}

	size_t size = kPoint.size();
	center = (size == 0) ? center : center * ((FLOAT)1 / size);
	direction = (size < 3) ? P2F(-1, -1) : kPoint[2] - kPoint[1];
	*fitNum = maxFit; *totalError = minError;

	return SUCCESSED;
}

NTSTATUS 
OrderingProcessing::RotatePrepare(
	_In_ SerialPoint2f cluster1, _Out_ SerialPoint2f& cluster2,
	_Out_ P2F&	clustrt1Center, _Out_ P2F&	clustrt2Center,
	_Out_ CPDMatrix& cpdCalib_1)
{
	if((cluster1.size() < 5)|| (cluster2.size() < 5))
	{
		return CLUSTER_POINTS_TOO_LESS;
	}

	FLOAT scale1 = CalcClusterScale(cluster1);
	FLOAT scale2 = CalcClusterScale(cluster2);
	clustrt1Center = CalcClusterCenter(cluster1);
	clustrt2Center = CalcClusterCenter(cluster2);

	if(scale2 == 0)
	{
		PRINT_DBG("cluster 2 scale is 0 ");
		return CLUSTER_2_SCALE_IS_ZERO;
	}
	FLOAT scale2to1 = scale1 / scale2;

	for(INT i = 0; i < cluster2.size(); i++)
	{
		cluster2[i] - clustrt2Center;
		cluster2[i] * scale2to1 * 0.9;
		cluster2[i] + clustrt1Center;
	}
	clustrt2Center = clustrt1Center;
	for(INT i = 0; i < cluster1.size(); i++)
	{
		cpdCalib_1(i, 0) = cluster1[i].x;
		cpdCalib_1(i, 1) = cluster1[i].y;
	}

	return SUCCESSED;
}

void OrderingProcessing::RotationRunning(
	_In_ SerialPoint2f cluster1,_In_ SerialPoint2f cluster2,
	_In_ P2F center, _In_ INT degree, _In_ INT maxFit,
	_In_ DOUBLE minError, _In_ CPDMatrix cpdCalib_1,
	_Out_ SerialPoint2f& minKRT)
{
	SerialPoint2f pointsCalibRotate_2;
	pointsCalibRotate_2.assign(cluster2.begin(), cluster2.end());
	RotatePoints(center, degree, pointsCalibRotate_2);

	CPDMatrix cpdCalib_2(pointsCalibRotate_2.size(), 2);
	for(int i = 0; i < pointsCalibRotate_2.size(); i++)
	{
		cpdCalib_2(i, 0) = pointsCalibRotate_2[i].x;
		cpdCalib_2(i, 1) = pointsCalibRotate_2[i].y;
	}

	CPDNonrigid nonrigid;
	nonrigid.correspondence(true);
	nonrigid.max_iterations(20000);
	nonrigid.outliers(0.85);

	SerialPoint2f keypoints_2Transfer;
	CPDNonrigidResult result_affine = nonrigid.run(cpdCalib_1, cpdCalib_2);
	for(int i = 0; i < result_affine.points.rows(); i++)
	{
		P2F key;
		key.x = (float)result_affine.points(i, 0);
		key.y = (float)result_affine.points(i, 1);
		keypoints_2Transfer.push_back(key);
	}

	double totalError = 0;
	int fitNum = 0;
	findKeyPointsError(keypoints_2Transfer, cluster1, &fitNum, &totalError);
	if(fitNum > maxFit) {
		minError = totalError;
		maxFit = fitNum;
		minKRT.assign(keypoints_2Transfer.begin(), keypoints_2Transfer.end());
	}
	else if(fitNum > maxFit) 
	{
		if(totalError < minError) 
		{
			minError = totalError;
			maxFit = fitNum;
			minKRT.assign(keypoints_2Transfer.begin(), keypoints_2Transfer.end());
		}
	}
}

FLOAT
OrderingProcessing::CalcClusterScale(_In_ SerialPoint2f cluster)
{
	FLOAT scale = FLT_MAX;
	FLOAT maxDistance = FLT_MIN;
	SerialFloat cluster_distance =
		PairDistance(cluster, maxDistance);

	SerialFloat cluster_distance_list;
	SerialInt cluster_distance_num;
	for(INT i = 0; i < cluster_distance.size(); i++)
	{
		GetClusterDistanceList(
			cluster_distance[i],
			maxDistance, 
			cluster_distance_num,
			cluster_distance_list
		);
	}

	for(INT i = 0; i < cluster_distance_list.size(); i++) 
	{
		if(cluster_distance_list[i] < scale && cluster_distance_num[i] >= 20) 
		{
			scale = cluster_distance_list[i];
		}
	}
	return scale;
}

P2F
OrderingProcessing::CalcClusterCenter(_In_ SerialPoint2f cluster)
{
	if(cluster.size() == 0)return P2F(-1, -1);

	P2F center_cluster;
	for(INT i = 0; i < cluster.size(); i++) {
		center_cluster.x += cluster[i].x;
		center_cluster.y += cluster[i].y;
	}
	center_cluster *= 1 / (FLOAT)cluster.size();
	return center_cluster;
}

void
OrderingProcessing::GetClusterDistanceList(_In_ FLOAT dist, _In_ FLOAT maxDist,
										   _Out_ SerialInt& distCnt,
										   _Out_ SerialFloat& clsDistList)
{
	bool shouldAdd = true;
	INT similarIndex = 0;
	for(INT j = 0; j < clsDistList.size(); j++)
	{
		if(abs(dist - clsDistList[j]) <
		   MIN_DISTANCE_ERROR * maxDist / STANDARD_SIZE)
		{
			shouldAdd = false;
			similarIndex = j;
			break;
		}
	}
	if(shouldAdd)
	{
		clsDistList.push_back(dist);
		distCnt.push_back(1);
	}
	else
	{
		clsDistList[similarIndex] =
			(distCnt[similarIndex] * clsDistList[similarIndex] +
			 dist) / (distCnt[similarIndex] + 1);
		distCnt[similarIndex]++;
	}
}

SerialFloat OrderingProcessing::PairDistance(
	_In_ SerialPoint2f cluster, _Out_ FLOAT& maxDistance)
{
	maxDistance = FLT_MIN;
	SerialFloat cluster_distance;
	for(INT i = 0; i < cluster.size(); i++) {
		for(INT j = i + 1; j < cluster.size(); j++) {
			FLOAT f = CalculatePointsDistance(cluster[i], cluster[j]);
			if(f > maxDistance) maxDistance = f;
			cluster_distance.push_back(f);
		}
	}

	return cluster_distance;
}

FLOAT 
OrderingProcessing::CalculatePointsDistance(_In_ P2F p1, _In_ P2F p2)
{
	P2F p = p1 - p2;
	return sqrt(p.x * p.x + p.y * p.y);
}

void
OrderingProcessing::RotatePoints(
	_In_ P2F center, _In_ INT degree,_Out_ SerialPoint2f &OriginalKeyPoints)
{
	DOUBLE angle = degree * CV_PI / 180.;
	for(INT i = 0; i < OriginalKeyPoints.size(); i++)
	{
		FLOAT x = OriginalKeyPoints[i].x;
		FLOAT y = OriginalKeyPoints[i].y;
		OriginalKeyPoints[i].x = (x - center.x) * (FLOAT)std::cos(angle) -
			(y - center.y) * (FLOAT)std::sin(angle) + center.x;
		OriginalKeyPoints[i].y = (x - center.x) * (FLOAT)std::sin(angle) +
			(y - center.y) * (FLOAT)std::cos(angle) + center.y;
	}
}

void
OrderingProcessing::findKeyPointsError(
	_In_ SerialPoint2f p1List, _In_ SerialPoint2f p2List,
	_Out_ INT* num, _Out_ DOUBLE* totalError)
{
	*num = 0;
	*totalError = 0.0;

	for(INT i = 0; i < p1List.size(); i++) 
	{
		DOUBLE mindis = DBL_MAX;
		for(INT j = 0; j < p2List.size(); j++)
		{
			DOUBLE x = p1List[i].x - p2List[j].x;
			DOUBLE y = p1List[i].y - p2List[j].y;
			DOUBLE dis = x * x + y * y;
			if(dis < mindis)mindis = dis;
		}
		if(mindis < MIN_DISTANCE_ERROR * MIN_DISTANCE_ERROR * 1 * 1) 
		{
			*totalError += mindis;
			(*num)++;
		}
	}
}
