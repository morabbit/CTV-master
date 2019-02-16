#include "pch.h"
#include "TraceLogExporter.h"
#include "FrameworkDefine.h"
#include "..\include\CalibrationController.h"
#include "..\include\DisplayMessage.h"

CalibrationController::CalibrationController()
{
	__Initialize();
}

CalibrationController::~CalibrationController()
{
	if(nullptr != __calibrator__)
	{
		delete __calibrator__;
	}

	if(nullptr != __orderring__)
	{
		delete __orderring__;
	}	

	if(nullptr != __clearing__)
	{
		delete __clearing__;
	}

	if(nullptr != __extener__)
	{
		delete __extener__;
	}
}


PCalibration & CalibrationController::GetCalibration(void)
{
	return __calibrator__;
}

DF & CalibrationController::GetDevationParm()
{
	return __calibrator__->m_dvt;
}

SP & CalibrationController::GetSobelParm()
{
	return __calibrator__->m_sobel;
}

TP & CalibrationController::GetThresholdParm()
{
	return __calibrator__->m_thresh;
}

HC & CalibrationController::GetHullSizeParm()
{
	return __calibrator__->m_hull;
}

void CalibrationController::SetDebug(bool dbg)
{
	__dbg__ = dbg;
}

void CalibrationController::SetPath(CPCHAR path)
{
	__path = path;
}

NTSTATUS CalibrationController::FindImagePoints()
{
	if(__dbg__ == true)
	{
		__WriteParameter2File();
	}
	
	NTSTATUS status = SUCCESSED;

	CMat __thresh_img;
	status = __BasicImageProcessing(__thresh_img);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	SerialPoints contours;
	status = processer->FindImageContours(__thresh_img, contours);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	
	__ReInitializeResultContainer();
	status = processer->ExtractImagePoints(contours, __infos__, __points_vec__);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	__DisplayFinalCycleMessage();
	__p_cnt__ = (UINT)__points_vec__.size();

	return status;
}

UINT 
CalibrationController::GetOutterMatrixSize(void)
{
	return (UINT)__ext_outter__.cols * (UINT)__ext_outter__.rows;
}

void 
CalibrationController::GetOutterMatrixSize(UINT& len)
{
	len = (UINT)__ext_outter__.cols * (UINT)__ext_outter__.rows;
}

FLOAT
CalibrationController::GetMeanSquaredError(void)
{
	return __error__;
}

void 
CalibrationController::GetMeanSquaredError(FLOAT & err)
{
	err = __error__;
}

PDOUBLE CalibrationController::GetOutterMatrixArray(void)
{
	UINT size = (UINT)__ext_outter__.cols * (UINT)__ext_outter__.rows;
	PDOUBLE result = (PDOUBLE)MallocMemroy(sizeof(DOUBLE) * size);
	ZeroMemory(result, size * sizeof(DOUBLE));

	for(INT i = 0; i < __ext_outter__.rows; i++)
	{
		for(INT j = 0; j < __ext_outter__.cols; j++)
		{
			DOUBLE piexl = __ext_outter__.at<DOUBLE>(i, j);
			result[i * __ext_outter__.rows + j] = isnan(piexl) ? 0.0 : piexl;
		}
	}
	return result;
}

void 
CalibrationController::GetOutterMatrixArray(PDOUBLE& result)
{
	UINT size = (UINT)__ext_outter__.cols * (UINT)__ext_outter__.rows;
	result = (PDOUBLE)MallocMemroy(sizeof(DOUBLE) * size);
	ZeroMemory(result, size * sizeof(DOUBLE));

	for(INT i = 0; i < __ext_outter__.rows; i++)
	{
		for(INT j = 0; j < __ext_outter__.cols; j++)
		{
			DOUBLE piexl = __ext_outter__.at<DOUBLE>(i, j);
			result[i * __ext_outter__.rows + j] = isnan(piexl) ? 0.0 : piexl;
		}
	}
}

SerialDouble 
CalibrationController::GetOutterMatrixVector(void)
{
	SerialDouble result;
	UINT size = (UINT)__ext_outter__.cols * (UINT)__ext_outter__.rows;
	
	for(INT i = 0; i < __ext_outter__.rows; i++)
	{
		for(INT j = 0; j < __ext_outter__.cols; j++)
		{
			DOUBLE piexl = __ext_outter__.at<DOUBLE>(i, j);
			isnan(piexl) ? result.push_back(0.0) : result.push_back(piexl);
			
		}
	}
	return result;
}

void 
CalibrationController::GetOutterMatrixVector(SerialDouble& result)
{
	UINT size = (UINT)__ext_outter__.cols * (UINT)__ext_outter__.rows;

	for(INT i = 0; i < __ext_outter__.rows; i++)
	{
		for(INT j = 0; j < __ext_outter__.cols; j++)
		{
			DOUBLE piexl = __ext_outter__.at<DOUBLE>(i, j);
			isnan(piexl) ? result.push_back(0.0) : result.push_back(piexl);

		}
	}
}

void 
CalibrationController::__Initialize()
{
	__dbg__ = false;
	__p_cnt__ = 0;
	__calibrator__ = new Calibration;
	processer = new ImageProcessing;
	__orderring__ = new OrderingProcessing;
	__clearing__ = new ClearPointProcessing;
	__extener__ = new ExtCalibrationProcessing;
}

void CalibrationController::__DisplayThresholdImage(CMat thresh)
{
	if(__dbg__ == false)
	{
		return;
	}
	
	processer->DownSamplingImage(thresh);
	cv::namedWindow("thresholdImage");
	cv::imshow("thresholdImage", thresh);
}

void CalibrationController::__DisplayFinalCycleMessage()
{
	if(__dbg__ == false)
	{
		return;
	}
	DM::DisplayFilteredConcentricImage(processer->GetSourceImage(), __infos__);
}

NTSTATUS CalibrationController::__BasicImageProcessing(CMat& thresh)
{
	NTSTATUS status = SUCCESSED;

	status = processer->ReadImage(__path);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	CMat __src_img = processer->GetSourceImage();
	if(!__src_img.data)
	{
		return READ_IMAGE_ERROR;
	}

	CMat binImg, gray;
	processer->BinaryzationImage(__src_img, binImg);
	status = processer->GenerateReversedGaryImage(binImg, gray);

	status = processer->ThresholdImage(gray, thresh);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	__DisplayThresholdImage(thresh);

	return status;
}

NTSTATUS CalibrationController::__GenerateResultPoints(PFLOAT& __p_points)
{
	if(__p_cnt__ == 0)
	{
		return CANOT_RECOGNIZE_POINTS;
	}
	__p_points = (PFLOAT)MallocMemroy(sizeof(FLOAT) * __p_cnt__ * 2);
	
	for(UINT i = 0; i < __p_cnt__; i++)
	{
		__p_points[2 * i] = __points_vec__[i].x;
		__p_points[2 * i + 1] = __points_vec__[i].y;

		if(__dbg__)
		{
			TraceLog << "  Cycle [" << std::left
				<< std::setw(2) << i << "],\tcenter: ("
				<< std::setw(8) << __points_vec__[i].x << ", "
				<< std::setw(8) << __points_vec__[i].y << ")";
		}
	}

	return SUCCESSED;
}

NTSTATUS 
CalibrationController::__GenerateResultRadiuses(PFLOAT& __p_radiuses)
{
	if(__p_cnt__ == 0)
	{
		return CANOT_RECOGNIZE_POINTS;
	}
	__p_radiuses = (PFLOAT)MallocMemroy(sizeof(FLOAT) *__p_cnt__);

	for(UINT i = 0; i < __p_cnt__; i++)
	{
		__p_radiuses[i] = __infos__[i].radius;

	}

	return SUCCESSED;
}

NTSTATUS
CalibrationController::__GenerateOrderedResultPoint(PFLOAT & __p_points)
{
	UINT __size = (UINT)__ordered_vec__.size();
	if(__size <= 0)
	{
		PRINT_DBG("ordered point size is 0");
		return ORDERED_POINTS_SIZE_ZERO;
	}
	__p_points = (PFLOAT)MallocMemroy(sizeof(FLOAT) *__size * 2);
	for(UINT i = 0; i < __size; i++)
	{
		__p_points[2 * i] = __ordered_vec__[i].x;
		__p_points[2 * i + 1] = __ordered_vec__[i].y;
	}

	return SUCCESSED;
}

NTSTATUS
CalibrationController::GetResultPoints(_Out_ PFLOAT * pPoints,
									   _Out_ PFLOAT * pRadiuses,
									   _Out_ UINT& cnt)
{
	if(__points_vec__.size() == 0)
	{
		*pPoints = nullptr;
		*pRadiuses = nullptr;
		return CANOT_RECOGNIZE_POINTS;
	}
	cnt = (UINT)__points_vec__.size();
	*pPoints = (PFLOAT)MallocMemroy(sizeof(FLOAT) * cnt * 2);
	*pRadiuses = (PFLOAT)MallocMemroy(sizeof(FLOAT) *cnt);

	for(UINT i = 0; i < cnt; i++)
	{
		(*pPoints)[2 * i]     = __points_vec__[i].x;
		(*pPoints)[2 * i + 1] = __points_vec__[i].y;
		(*pRadiuses)[i]       = __infos__[i].radius;

		if(__dbg__)
		{
			TraceLog << "  Cycle [" << std::left 
				<< std::setw(2) << i << "],\tcenter: ("
				<< std::setw(8) << __points_vec__[i].x << ", "
				<< std::setw(8) << __points_vec__[i].y << ")";
		}
	}
		
	return SUCCESSED;
}

SerialCycleInfo CalibrationController::GetPointsInfo(void)
{
	return __infos__;
}

void CalibrationController::GetPointsInfo(_Out_ SerialCycleInfo& info)
{
	info.assign(__infos__.begin(), __infos__.end());
}

NTSTATUS CalibrationController::OrderImagePoints()
{
	NTSTATUS status = SUCCESSED;
	status = __orderring__->SetSourcePoint(__points_vec__);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = __orderring__->OrderingPoints(__ordered_vec__);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	return status;
}

NTSTATUS CalibrationController::OrderImagePoints(PFLOAT points, UINT cnt)
{
	NTSTATUS status = SUCCESSED;
	__orderring__->SetOriginPointNumber(cnt);
	status = __orderring__->SetSourcePoint(points);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = __orderring__->OrderingPoints(__ordered_vec__);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	return status;
}

NTSTATUS
CalibrationController::ClearImagePoints(CMat srcImge, SerialCycleInfo srcPoints)
{
	NTSTATUS status = SUCCESSED;
	__clearing__->SetSourceImage(srcImge);
	__clearing__->InitializeMaskImage();
	status = __clearing__->GenerateImageMask(srcPoints);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = __clearing__->ClearImagePoints(__cleared_img__);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	return status;
}

NTSTATUS
CalibrationController::ClearImagePoints(CPCHAR path, SerialCycleInfo srcPoints)
{
	CMat srcImge;
	NTSTATUS status = SUCCESSED;	
	__clearing__->ReadImage(path, srcImge);
	__clearing__->SetSourceImage(srcImge);
	__clearing__->InitializeMaskImage();
	status = __clearing__->GenerateImageMask(srcPoints);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = __clearing__->ClearImagePoints(__cleared_img__);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	return status;
}

NTSTATUS
CalibrationController::ClearImagePoints(
	CMat srcImge, SerialPoint2f srcPoints, PFLOAT radiuses)
{
	NTSTATUS status = SUCCESSED;
	__clearing__->SetSourceImage(srcImge);
	__clearing__->InitializeMaskImage();
	status = __clearing__->GenerateImageMask(srcPoints, radiuses);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = __clearing__->ClearImagePoints(__cleared_img__);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	return status;
}

NTSTATUS 
CalibrationController::ClearImagePoints(CPCHAR path, SerialPoint2f srcPoints, PFLOAT radiuses)
{
	CMat srcImge;
	NTSTATUS status = SUCCESSED;
	__clearing__->ReadImage(path, srcImge);
	__clearing__->InitializeMaskImage();
	status = __clearing__->GenerateImageMask(srcPoints, radiuses);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = __clearing__->ClearImagePoints(__cleared_img__);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	return status;
}

NTSTATUS
CalibrationController::ClearImagePoints(
	CMat srcImge, PFLOAT srcPoints, PFLOAT radiuses, UINT cnt)
{
	NTSTATUS status = SUCCESSED;
	__clearing__->SetSourceImage(srcImge);
	__clearing__->InitializeMaskImage();
	status = __clearing__->GenerateImageMask(srcPoints, radiuses, cnt);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = __clearing__->ClearImagePoints(__cleared_img__);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	return status;
}

NTSTATUS 
CalibrationController::ClearImagePoints(
	CPCHAR path, PFLOAT srcPoints, PFLOAT radiuses, UINT cnt)
{
	CMat srcImge;
	NTSTATUS status = SUCCESSED;
	__clearing__->ReadImage(path, srcImge);
	__clearing__->InitializeMaskImage();
	status = __clearing__->GenerateImageMask(srcPoints, radiuses, cnt);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = __clearing__->ClearImagePoints(__cleared_img__);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	return status;
}

NTSTATUS 
CalibrationController::CameraExternalCalibration(
	UINT pointCount, PFLOAT p3Ds, PFLOAT p2Ds, PDOUBLE inner, PDOUBLE distcofs)
{
	NTSTATUS status = SUCCESSED;
	__extener__->SetPointsCount(pointCount);
	status = __extener__->SetWorldPoints(p3Ds);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = __extener__->SetScreenPoints(p2Ds);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = __extener__->SetdistCoeffs(distcofs);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = __extener__->SetCameraMatrix(inner);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = __extener__->SolveExternalMatiexes();
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = __extener__->GenerateRotationMatrix(__ext_outter__);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);	
	status = __extener__->GenerateMeanSquaredError(__error__);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	return status;
}

PFLOAT CalibrationController::GetRadiuses(void)
{
	PFLOAT __pReduised = nullptr;
	__GenerateResultRadiuses(__pReduised);
	return __pReduised;
}

void CalibrationController::GetRadiuses(PFLOAT * pRadiuses)
{
	__GenerateResultRadiuses(*pRadiuses);
}

PFLOAT CalibrationController::GetPoints(void)
{
	PFLOAT __pResult = nullptr;
	__GenerateResultPoints(__pResult);
	return __pResult;
}

void CalibrationController::GetPoints(PFLOAT * pPoints)
{
	__GenerateResultPoints(*pPoints);
}

UINT CalibrationController::GetPointsCount(void)
{
	return __p_cnt__;
}

void CalibrationController::GetPointsCount(UINT & cnt)
{
	cnt = __p_cnt__;
}

SerialPoint2f CalibrationController::GetPointsVec(void)
{
	return __points_vec__;
}

void 
CalibrationController::GetPointsVec(SerialPoint2f & result)
{
	result.assign(__points_vec__.begin(), __points_vec__.end());
}

PFLOAT CalibrationController::GetOrderedPoints(void)
{
	PFLOAT __pResult = nullptr;
	__GenerateOrderedResultPoint(__pResult);
	return __pResult;
}

void CalibrationController::GetOrderedPoints(PFLOAT* pPoints)
{
	__GenerateOrderedResultPoint(*pPoints);
}


UINT CalibrationController::GetOrderPointsCount(void)
{
	return (UINT)__ordered_vec__.size();
}

void
CalibrationController::GetOrderPointsCount(UINT & cnt)
{
	cnt = (UINT)__ordered_vec__.size();
}

SerialPoint2f CalibrationController::GetOrderPointsVec(void)
{
	return __ordered_vec__;
}

void CalibrationController::GetOrderPointsVec(SerialPoint2f & result)
{
	result.assign(__ordered_vec__.begin(), __ordered_vec__.end());
}

CMat CalibrationController::GetClearredPointsImage(void)
{
	return __cleared_img__;
}

void CalibrationController::GetClearredPointsImage(CMat& result)
{
	result = __cleared_img__;
}

PUCHAR CalibrationController::GetResultImageBuffer(void)
{
	if(!__cleared_img__.data)
	{
		return nullptr;
	}
	ULONG len  = (ULONG)(__cleared_img__.size().height) * 
		         (ULONG)(__cleared_img__.size().width);

	if(0 == len)
	{
		return nullptr;
	}

	PUCHAR result = (PUCHAR)MallocMemroy(len * sizeof(UCHAR));
	try 
	{
		memcpy(result, __cleared_img__.data, len * sizeof(UCHAR));
	}
	catch(const std::exception& err)
	{
		TraceError << "out put image buffer dismatch with buffer: \n " << err.what();
		FreeMemory(&result);
		return nullptr;
	}
	return result;
}

NTSTATUS
CalibrationController::GetResultImageBuffer(PUCHAR& result)
{
	if(!__cleared_img__.data)
	{
		result = nullptr;
		PRINT_DBG("output image buffer is 0");
		return OUTPUT_IMAGE_BUFFER_SIZE_ZERO;
	}
	ULONG len  = (ULONG)(__cleared_img__.size().height) * 
		         (ULONG)(__cleared_img__.size().width);

	if(0 == len)
	{
		result = nullptr;
		PRINT_DBG("output image buffer is 0");
		return OUTPUT_IMAGE_BUFFER_SIZE_ZERO;
	}
	result = (PUCHAR)MallocMemroy(len * sizeof(UCHAR));

	try 
	{
		memcpy(result, __cleared_img__.data, len * sizeof(UCHAR));
	}
	catch(const std::exception& err) 
	{
		TraceError << "out put image buffer dismatch with buffer: \n " << err.what();
		FreeMemory(&result);
		return OUT_BUFFER_DISMATCH_WITH_SIZE;
	}

	return SUCCESSED;
}

void 
CalibrationController::__WriteParameter2File(void)
{
	TraceLog << "Parameter List :"   ;
	TraceLog << "filen name:  "      << __path << std::endl;
	TraceLog << "Sobel parameter:  " << std::endl  << "dx \t\t= \t[" << std::left
		     << std::setw(4) << __calibrator__->m_sobel.GetDx()      << "],\ndy \t\t= \t["
		     << std::setw(4) << __calibrator__->m_sobel.GetDy()      << "], \nksize \t= \t["
		     << std::setw(4) << __calibrator__->m_sobel.GetKsize()   << "],\nddepth \t= \t["
		     << std::setw(4) << __calibrator__->m_sobel.GetDdepth()  << "],\nscale \t= \t["
		     << std::setw(4) << __calibrator__->m_sobel.GetScale()   << "]"  << std::endl;

	TraceLog << "Deviation Filter: "     << std::endl << "Deviation Of Points \t= \t[" << std::left
		     << std::setw(4) << __calibrator__->m_dvt.GetDeviation() << "], \nMin contour size \t\t=\t["
		     << std::setw(4) << __calibrator__->m_dvt.GetMinContoursSize()    << "], \nMax contour size \t\t= \t["
		     << std::setw(4) <<  __calibrator__->m_dvt.GetMaxContoursSize()   << "], \nMin Radius \t\t\t\t= \t["
		     << std::setw(4) <<  __calibrator__->m_dvt.GetMinRadius()         << "], \nMax Radius \t\t\t\t= \t["
		     << std::setw(4) <<  __calibrator__->m_dvt.GetMaxRadius()         << "],\nZoom exponent of Image \t= \t["
		     << std::setw(4) <<  __calibrator__->m_dvt.GetZoom() << "]"       << std::endl;
	TraceLog << "Threshold Parameter : " << std::endl << "thresh value \t= \t[" << std::left
		     << std::setw(4) << __calibrator__->m_thresh.GetThresh()                  << "], \nmaxval \t\t\t= \t["
		     << std::setw(4) << __calibrator__->m_thresh.GetMaxval()                  << "], \ntype \t\t\t= \t["
		     << std::setw(4) << __calibrator__->m_thresh.GetType()                    << "]" << std::endl;
}

void CalibrationController::__ReInitializeResultContainer()
{
	if(__infos__.size() != 0)
	{
		SerialCycleInfo().swap(__infos__);
	}

	if(__points_vec__.size() != 0)
	{
		SerialPoint2f().swap(__points_vec__);
	}
}


