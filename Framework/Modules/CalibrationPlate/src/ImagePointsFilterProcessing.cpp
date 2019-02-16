#include "pch.h"
#include "TraceLogExporter.h"
#include "FrameworkDefine.h"
//#include "..\include\CalibrationPlateCommon.hpp"
#include "..\include\ImagePointsFilterProcessing.h"


PointFilterProcessing::PointFilterProcessing()
{
}

PointFilterProcessing::~PointFilterProcessing()
{
}

bool
PointFilterProcessing::ContinueToNextLoop(_In_ SerialPoint contour, _In_ DF filter)
{
	if(contour.size() < filter.GetMinContoursSize())return true;
	if(contour.size() > filter.GetMaxContoursSize()) return true;

	cv::RotatedRect rotatedElipse = fitEllipse(contour);
	DOUBLE aspectRatio = MAX(rotatedElipse.size.width, rotatedElipse.size.height)
		/ MIN(rotatedElipse.size.width, rotatedElipse.size.height);
	if((aspectRatio > 1.7) || (aspectRatio < 0))return true;

	return false;
}

bool 
PointFilterProcessing::FilterConcentricCycle(_Out_ SerialCycleInfo *contours,
											 _Out_ DOUBLE& totalRadius,
											 _In_  CycleInfo Info,
											 _In_  DOUBLE deviation)
{
	bool bRet = false;
	for(INT i = 0; i < contours->size(); i++) 
	{
		DOUBLE delta_r = (*contours)[i].radius - Info.radius;
		DOUBLE delta_x = abs((*contours)[i].center.x - Info.center.x);
		DOUBLE delta_y = abs((*contours)[i].center.y - Info.center.y);

		if((delta_x >= deviation) || (delta_y >= deviation))continue;

		DOUBLE maxRadius = MAX((*contours)[i].radius, Info.radius);
		DOUBLE minRadius = MIN((*contours)[i].radius, Info.radius);
		
		totalRadius -= (*contours)[i].radius;
		if(maxRadius > minRadius * 1.6) {
			(*contours)[i].radius = (maxRadius + minRadius) / 2;
		}
		else {
			(*contours)[i].radius = maxRadius;
		}

		totalRadius += (*contours)[i].radius;
		delta_r < 0 ? (*contours)[i].contour.swap(Info.contour) : void();
		(*contours)[i].area = delta_r < 0 ? Info.area : (*contours)[i].area;
		(*contours)[i].center.x = ((*contours)[i].center.x + Info.center.x) / 2.;
		(*contours)[i].center.y = ((*contours)[i].center.y + Info.center.y) / 2.;

		bRet = bRet || true;
	}
	return bRet;
}

bool 
PointFilterProcessing::FilterFarNearPoints(
	_Out_ SerialCycleInfo * contours, _In_ CycleInfo Info, _In_ CMat Image)
{
	for(int i = 0; i < contours->size(); i++)
	{
		DOUBLE dist =
			CalculateDictance((*contours)[i].center, Info.center);
		if(dist < 40.0)
		{
			if(((*contours)[i].radius < 3.1) && (Info.radius > 3.1))
			{
				(*contours)[i].contour.swap(Info.contour);
				(*contours)[i].radius = MAX((*contours)[i].radius, Info.radius);
				(*contours)[i].center = Info.center;
			}
			else if((*contours)[i].area < 36.)
			{
				(*contours)[i].contour.swap(Info.contour);
				(*contours)[i].radius = MAX((*contours)[i].radius, Info.radius);
				(*contours)[i].center = Info.center;
			}
			else if((Info.area > 150) && (*contours)[i].area > Info.area * 2.0)
			{
				(*contours)[i].contour.swap(Info.contour);
				(*contours)[i].radius = MAX((*contours)[i].radius, Info.radius);
				(*contours)[i].center = Info.center;
			}
			return false;
		}
	}
	return true;
}

bool
PointFilterProcessing::FinialFilterWithPiexl(_In_ CycleInfo Info, 
											 _In_ CMat srcImg,
											 _In_ FLOAT refAvgPiexl)
{
	if(srcImg.channels() > 1)
	{
		cv::cvtColor(srcImg, srcImg, CV_BGR2GRAY);
	}

	SerialPoint HullPoints =
		PFP::GetMinEnclosingRectanglePoints(
			Info, srcImg.rows, srcImg.cols);

	float averagePiexl = 0.0;
	PFP::CalculateRectangleInnerPointsAveragePixel(
		HullPoints, srcImg, averagePiexl);

	if(averagePiexl > refAvgPiexl) return false;

	return true;
}

SerialPoint 
PointFilterProcessing::GetMinEnclosingRectanglePoints(
	_In_ CycleInfo Info, _In_ INT rows, _In_ INT cols)
{
	SerialPoint RectPoint;
	P2D leftFront;
	leftFront.x = INT(ceil(Info.center.x - Info.radius * SINE_45));
	leftFront.y = INT(floor(Info.center.y + Info.radius * COSINE_45));

	P2D leftBack;
	leftBack.x = INT(ceil(Info.center.x - Info.radius * SINE_45));
	leftBack.y = INT(ceil(Info.center.y - Info.radius * COSINE_45));

	P2D rightFront;
	rightFront.x = INT(floor(Info.center.x + Info.radius * SINE_45));
	rightFront.y = INT(floor(Info.center.y + Info.radius * COSINE_45));

	P2D rightBack;
	rightBack.x = INT(floor(Info.center.x + Info.radius * SINE_45));
	rightBack.y = INT(ceil(Info.center.y - Info.radius * COSINE_45));

	AssertPointLocateImageFrame(rows, cols, leftFront);
	AssertPointLocateImageFrame(rows, cols, rightFront);
	AssertPointLocateImageFrame(rows, cols, leftBack);
	AssertPointLocateImageFrame(rows, cols, rightBack);

	RectPoint.push_back(leftFront);
	RectPoint.push_back(rightFront);
	RectPoint.push_back(leftBack);
	RectPoint.push_back(rightBack);

	return RectPoint;
}

NTSTATUS 
PointFilterProcessing::CalculateRectangleInnerPointsAveragePixel(
	_In_ SerialPoint RectHull, _In_ CMat Image, _Out_ FLOAT& AveragePixel)
{
	INT X_Line_Above = abs(RectHull[0].x - RectHull[1].x);
	INT X_Line_Below = abs(RectHull[2].x - RectHull[3].x);

	INT Y_Line_left = abs(RectHull[0].y - RectHull[2].y);
	INT Y_Line_Right = abs(RectHull[1].y - RectHull[3].y);

	INT TotalPiexl = 0;
	INT NumberOfPoints = 0;
	for(INT i = 0; i < Y_Line_left; i++)
	{
		INT y = RectHull[2].y + i;
		for(INT j = 0; j < X_Line_Below; j++)
		{
			NumberOfPoints++;
			INT x = RectHull[2].x + j;
			try {
				TotalPiexl += (INT)(Image.ptr<uchar>(y)[x]);
			}
			catch(const std::exception& err) {
				TraceLog << "Point(x, y) = (" << x << "," << y
					<< ")\nPoint out of image: \n " << err.what();
				return POINT_OUT_OF_FRAME;
			}
		}
	}
	AveragePixel = NumberOfPoints > 0 ? FLOAT(TotalPiexl) / FLOAT(NumberOfPoints) : 0.0f;

	return SUCCESSED;
}

void 
PointFilterProcessing::AssertPointLocateImageFrame(
	_In_ INT rows, _In_ INT cols, _Out_ P2D& point)
{
	point.x = (point.x) < 0 ? 0 : point.x;
	point.x = (point.x) >= cols ? cols - 1 : point.x;

	point.y = (point.y) < 0 ? 0 : point.y;
	point.y = (point.y) >= rows ? rows - 1 : point.y;
}

bool 
PointFilterProcessing::OuteCrackAveragePiexlFilter(_In_ CycleInfo& Info,
												   _In_ CMat Image)
{
	SerialPoint MinRectangleVexes = PFP::GetEnclosingRectangleVertexes(Info, Image, 4.0);
	SerialPoint RectangleVexes = PFP::GetEnclosingRectangleVertexes(Info, Image, 8.0);
	SerialPoint AboveRectVexes = PFP::GetAboveRectanglePointsSet(
	                             	MinRectangleVexes, RectangleVexes, Image);
	SerialPoint BelowRectVexes = PFP::GetBelowRectanglePointsSet(
		                            MinRectangleVexes, RectangleVexes, Image);
	SerialPoint LeftRectVexes = PFP::GetLeftRectanglePointsSet(
	                                MinRectangleVexes, RectangleVexes, Image);
	SerialPoint RightRectVexes = PFP::GetRightRectanglePointsSet(
		                            MinRectangleVexes, RectangleVexes, Image);
	int NumberOfPoints = 0;
	float TotalPiexl = PFP::GetRectangleInnerPiexl(AboveRectVexes, Info, Image, NumberOfPoints);
	TotalPiexl += PFP::GetRectangleInnerPiexl(BelowRectVexes, Info, Image, NumberOfPoints);
	TotalPiexl += PFP::GetRectangleInnerPiexl(LeftRectVexes, Info, Image, NumberOfPoints);
	TotalPiexl += PFP::GetRectangleInnerPiexl(RightRectVexes, Info, Image, NumberOfPoints);

	float averagePixel = NumberOfPoints > 0 ? float(TotalPiexl) / float(NumberOfPoints) : 0.0f;
	return averagePixel > 100.;
}

SerialPoint 
PointFilterProcessing::GetEnclosingRectangleVertexes(
	_In_ CycleInfo Info, _In_ CMat Image, _In_ FLOAT ExtraSize)
{
	SerialPoint RectPoint;
	P2D leftFront;
	leftFront.x = int(floor(Info.center.x - Info.radius - ExtraSize));
	leftFront.y = int(ceil(Info.center.y + Info.radius + ExtraSize));
	leftFront.x = (leftFront.x > Image.cols) ? Image.cols : leftFront.x;
	leftFront.y = (leftFront.y > Image.rows) ? Image.rows : leftFront.y;
	leftFront.x = (leftFront.x < 0) ? 0 : leftFront.x;
	leftFront.y = (leftFront.y < 0) ? 0 : leftFront.y;

	P2D rightFront;
	rightFront.x = int(ceil(Info.center.x + Info.radius + ExtraSize));
	rightFront.y = int(ceil(Info.center.y + Info.radius + ExtraSize));
	rightFront.x = (rightFront.x > Image.cols) ? Image.cols : rightFront.x;
	rightFront.y = (rightFront.y > Image.rows) ? Image.rows : rightFront.y;
	rightFront.x = (rightFront.x < 0) ? 0 : rightFront.x;
	rightFront.y = (rightFront.y < 0) ? 0 : rightFront.y;

	P2D leftBack;
	leftBack.x = int(floor(Info.center.x - Info.radius - ExtraSize));
	leftBack.y = int(floor(Info.center.y - Info.radius - ExtraSize));
	leftBack.x = (leftBack.x > Image.cols) ? Image.cols : leftBack.x;
	leftBack.y = (leftBack.y > Image.rows) ? Image.rows : leftBack.y;
	leftBack.x = (leftBack.x < 0) ? 0 : leftBack.x;
	leftBack.y = (leftBack.y < 0) ? 0 : leftBack.y;

	P2D rightBack;
	rightBack.x = int(ceil(Info.center.x + Info.radius + ExtraSize));
	rightBack.y = int(floor(Info.center.y - Info.radius - ExtraSize));
	rightBack.x = (rightBack.x > Image.cols) ? Image.cols : rightBack.x;
	rightBack.y = (rightBack.y > Image.rows) ? Image.rows : rightBack.y;
	rightBack.x = (rightBack.x < 0) ? 0 : rightBack.x;
	rightBack.y = (rightBack.y < 0) ? 0 : rightBack.y;

	RectPoint.push_back(leftFront);
	RectPoint.push_back(rightFront);
	RectPoint.push_back(leftBack);
	RectPoint.push_back(rightBack);

	return RectPoint;
}

SerialPoint 
PointFilterProcessing::GetAboveRectanglePointsSet(
	_In_ SerialPoint innerVexes, _In_ SerialPoint outterVexes, _In_ CMat Image)
{
	P2D leftFront;
	leftFront = outterVexes[0];

	P2D leftBack;
	leftBack.x = outterVexes[0].x;
	leftBack.y = innerVexes[0].y;

	P2D rightFront;
	rightFront = outterVexes[1];

	P2D rightBack;
	rightBack.x = outterVexes[1].x;;
	rightBack.y = innerVexes[1].y;

	AssertPointLocateImageFrame(Image.rows, Image.cols, leftFront);
	AssertPointLocateImageFrame(Image.rows, Image.cols, rightFront);
	AssertPointLocateImageFrame(Image.rows, Image.cols, leftBack);
	AssertPointLocateImageFrame(Image.rows, Image.cols, rightBack);

	SerialPoint RectPoint;
	RectPoint.push_back(leftFront);
	RectPoint.push_back(rightFront);
	RectPoint.push_back(leftBack);
	RectPoint.push_back(rightBack);

	return RectPoint;
}

SerialPoint
PointFilterProcessing::GetBelowRectanglePointsSet(_In_ SerialPoint innerVexes,
												  _In_ SerialPoint outterVexes,
												  _In_ CMat Image)
{

	P2D leftFront;
	leftFront.x = outterVexes[2].x;
	leftFront.y = innerVexes[2].y;

	P2D leftBack;
	leftBack = outterVexes[2];

	P2D rightFront;
	rightFront.x = outterVexes[3].x;
	rightFront.y = innerVexes[3].y;

	P2D rightBack;
	rightBack = outterVexes[3];

	AssertPointLocateImageFrame(Image.rows, Image.cols, leftFront);
	AssertPointLocateImageFrame(Image.rows, Image.cols, rightFront);
	AssertPointLocateImageFrame(Image.rows, Image.cols, leftBack);
	AssertPointLocateImageFrame(Image.rows, Image.cols, rightBack);

	SerialPoint RectPoint;
	RectPoint.push_back(leftFront);
	RectPoint.push_back(rightFront);
	RectPoint.push_back(leftBack);
	RectPoint.push_back(rightBack);

	return RectPoint;
}

SerialPoint
PointFilterProcessing::GetLeftRectanglePointsSet(_In_ SerialPoint innerVexes,
												 _In_ SerialPoint outterVexes,
												 _In_ CMat Image)
{
	P2D leftFront;
	leftFront.x = outterVexes[0].x;
	leftFront.y = innerVexes[0].y;

	P2D leftBack;
	leftFront.x = outterVexes[2].x;
	leftFront.y = innerVexes[2].y;

	P2D rightFront;
	rightFront = innerVexes[0];

	P2D rightBack;
	rightBack = innerVexes[2];

	AssertPointLocateImageFrame(Image.rows, Image.cols, leftFront);
	AssertPointLocateImageFrame(Image.rows, Image.cols, rightFront);
	AssertPointLocateImageFrame(Image.rows, Image.cols, leftBack);
	AssertPointLocateImageFrame(Image.rows, Image.cols, rightBack);

	SerialPoint RectPoint;
	RectPoint.push_back(leftFront);
	RectPoint.push_back(rightFront);
	RectPoint.push_back(leftBack);
	RectPoint.push_back(rightBack);

	return RectPoint;
}

SerialPoint
PointFilterProcessing::GetRightRectanglePointsSet(_In_ SerialPoint innerVexes,
												  _In_ SerialPoint outterVexes,
												  _In_ CMat Image)
{
	P2D leftFront;
	leftFront = innerVexes[1];

	P2D leftBack;
	leftFront = innerVexes[3];

	P2D rightFront;
	rightFront.x = outterVexes[1].x;
	rightFront.y = innerVexes[1].y;

	P2D rightBack;
	rightBack.x = outterVexes[3].x;
	rightBack.y = innerVexes[3].y;

	AssertPointLocateImageFrame(Image.rows, Image.cols, leftFront);
	AssertPointLocateImageFrame(Image.rows, Image.cols, rightFront);
	AssertPointLocateImageFrame(Image.rows, Image.cols, leftBack);
	AssertPointLocateImageFrame(Image.rows, Image.cols, rightBack);

	SerialPoint RectPoint;
	RectPoint.push_back(leftFront);
	RectPoint.push_back(rightFront);
	RectPoint.push_back(leftBack);
	RectPoint.push_back(rightBack);

	return RectPoint;
}

double
PointFilterProcessing::CalculateDictance(_In_ P2F p1, _In_ P2F p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}


FLOAT
PointFilterProcessing::GetRectangleInnerPiexl(_In_ SerialPoint RectHull, _In_ CycleInfo Info,
											  _In_ CMat Image, _Out_ INT& NumberOfPoints)
{
	INT X_Line_Below = abs(RectHull[2].x - RectHull[3].x);
	INT Y_Line_left = abs(RectHull[0].y - RectHull[2].y);

	FLOAT TotalPiexl = 0;
	for(INT i = 0; i < Y_Line_left; i++) 
	{
		INT y = RectHull[2].y + i;
		for(INT j = 0; j < X_Line_Below; j++)
		{
			INT x = RectHull[2].x + j;
			INT rf_x = INT(ceil(x + 2 * (Info.center.x - x)));
			INT lb_y = INT(floor(y - 2 * (y - Info.center.y)));
			INT rb_y = INT(floor(y - 2 * (y - Info.center.y)));
			rf_x = (rf_x < 0) ? 0 : rf_x;
			rb_y = (rb_y < 0) ? 0 : rb_y;
			lb_y = (lb_y < 0) ? 0 : lb_y;
			rf_x = (rf_x >= Image.cols) ? Image.cols - 1 : rf_x;
			lb_y = (lb_y >= Image.rows) ? Image.rows - 1 : lb_y;
			rb_y = (rb_y >= Image.rows) ? Image.rows - 1 : rb_y;

			TotalPiexl += (FLOAT)(Image.ptr<uchar>(y)[x]); // lf
			TotalPiexl += (FLOAT)(Image.ptr<uchar>(y)[rf_x]);// rf
			TotalPiexl += (FLOAT)(Image.ptr<uchar>(lb_y)[x]); // lb
			TotalPiexl += (FLOAT)(Image.ptr<uchar>(rb_y)[rf_x]); // rb
			NumberOfPoints = NumberOfPoints + 4;
		}
	}
	return TotalPiexl;
}

void
PointFilterProcessing::FilterNearestCycle(_Out_ SerialCycleInfo * target,
										  _Out_ SerialPoint2f *points,
										  _In_ SerialCycleInfo source,
										  _In_ FLOAT totalRadius)
{
	if(source.size() <= 0)return;
	DOUBLE averageRadius = totalRadius / source.size();
	for(size_t i = 0; i < source.size(); i++)
	{
		if((source[i].radius > averageRadius * 1.6) ||
			(source[i].radius < averageRadius / 2.2))
		{
			continue;
		}
		target->push_back(source[i]);
		points->push_back(source[i].center);
	}
}

void
PointFilterProcessing::FilterCycleWithDistance(_Out_ SerialPoint2f *points,
											   _Out_ SerialCycleInfo& info,
											   _In_ SerialCycleInfo source)
{
	MPST pot_set;
	GetDistanceForEachPoints(source, pot_set);

	std::set<INT> a;
	GetValidPointsIndex(pot_set, a);

	std::vector<INT> result;
	for(auto i = a.begin(); i != a.end(); i++)
	{
		bool add1 = true;
		for(size_t j = 0; j < result.size(); j++)
		{
			if(result[j] == *i)
			{
				add1 = false;
			}
		}
		if(add1 == true)
		{
			result.push_back(*i);
			points->push_back(source[*i].center);
			info.push_back(source[*i]);
		}
	}
}


void
PointFilterProcessing::GetDistanceForEachPoints(
	_In_  SerialCycleInfo source, _Out_ MPST& dist_set)
{
	MPST temp;
	for(UINT i = 0; i < source.size(); i++)
	{
		for(UINT j = i + 1; j < source.size(); j++)
		{
			double dist =
				CalculateDictance(source[i].center, source[j].center);

			if((dist > MaxDistance) || (dist < MinDistance))
			{
				continue;
			}
			temp = dist_set;
			bool find = false; INT __key = -1;
			std::set<INT> __value; auto iter0 = dist_set.begin();
			for(auto iter = temp.begin(); iter != temp.end(); iter++)
			{
				if(abs(iter->first - dist) <= 12.5)
				{
					find = true;
					__key = (INT)round((iter->first + dist) / 2.);
					__value = iter->second;
					__value.insert(i);
					__value.insert(j);
					iter0 = dist_set.erase(iter0);
					__key = (dist_set.find(__key) != dist_set.end()) ? __key + 1 : __key;
					dist_set.insert(std::make_pair(__key, __value));
					continue;
				}
				iter0++;
			}

			if(find == false)
			{
				dist_set[(INT)round(dist)].insert(i);
			}
		}
	}
}

void
PointFilterProcessing::GetValidPointsIndex(
	_In_  MPST src, _Out_ std::set<INT>& target)
{
	int MaxLenIndex = 999, MaxLenIndex2 = 0;
	int MaxLength = 30, MaxLength2 = 0;

	for(auto iter = src.begin(); iter != src.end(); iter++)
	{
		if((iter->second.size() > MaxLength) && (iter->first < MaxLenIndex))
		{
			MaxLength = iter->second.size();
			MaxLenIndex = iter->first;
		}

		if(iter->second.size() > MaxLength2)
		{
			MaxLength2 = iter->second.size();
			MaxLenIndex2 = iter->first;
		}
	}

	if(999 == MaxLenIndex)
	{
		target = src[MaxLenIndex2];
	}
	else
	{
		target = src[MaxLenIndex];
	}
}
