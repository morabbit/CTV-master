#pragma once
#ifndef __IMAGEPOINTSFILTERPROCESSING_H
#define __IMAGEPOINTSFILTERPROCESSING_H

#include "ThresholdParameterInterface.hpp"
#include "SobleParameterInterface.hpp"
#include "DevicationFilterInterface.hpp"
#include "CalibrationPlateCommon.hpp"


class PointFilterProcessing
{
	using MPST = std::map<INT, std::set<INT>>;

public:
	PointFilterProcessing();
	~PointFilterProcessing();

public:
	static
		bool
		ContinueToNextLoop(_In_ SerialPoint contour, _In_ DF filter);

	static
		bool
		FilterConcentricCycle(_Out_ SerialCycleInfo *contours,
							  _Out_ DOUBLE& totalRadius,
							  _In_ CycleInfo Info,							  
							  _In_ DOUBLE deviation);
	static
		bool
		FilterFarNearPoints(_Out_ SerialCycleInfo *contours,
							_In_ CycleInfo Info,
							_In_ CMat Image);

	static
		bool
		FinialFilterWithPiexl(_In_ CycleInfo Info, 
							  _In_ CMat srcImg,
							  _In_ FLOAT refAvgPiexl);

	static
		SerialPoint
		GetMinEnclosingRectanglePoints(_In_ CycleInfo Info,
									   _In_ INT rows, 
									   _In_ INT cols);
	
	static
		NTSTATUS
		CalculateRectangleInnerPointsAveragePixel(_In_ SerialPoint RectHull,
												  _In_ CMat Image,
												  _Out_ FLOAT& AveragePixel);

	static
		void
		AssertPointLocateImageFrame(_In_ INT rows,
									_In_ INT cols,
									_Out_ P2D& point);

	static
		bool OuteCrackAveragePiexlFilter(_In_ CycleInfo& Info, _In_ CMat Image);

	static
		SerialPoint
		GetEnclosingRectangleVertexes(_In_ CycleInfo Info, _In_ CMat Image,
									  _In_ FLOAT ExtraSize = 1.0);

	static
		SerialPoint
		GetAboveRectanglePointsSet(_In_ SerialPoint innerVexes,
								   _In_ SerialPoint outterVexes,
								   _In_ CMat Image);

	static
		SerialPoint
		GetBelowRectanglePointsSet(_In_ SerialPoint innerVexes,
								   _In_ SerialPoint outterVexes,
								   _In_ CMat Image);

	static
		SerialPoint
		GetLeftRectanglePointsSet(_In_ SerialPoint innerVexes,
								  _In_ SerialPoint outterVexes,
								  _In_ CMat Image);

	static
		SerialPoint
		GetRightRectanglePointsSet(_In_ SerialPoint innerVexes,
								   _In_ SerialPoint outterVexes,
								   _In_ CMat Image);

	static
		double
		CalculateDictance(_In_ P2F p1, _In_ P2F p2);

	static
		FLOAT
		GetRectangleInnerPiexl(_In_ SerialPoint RectHull, 
							   _In_ CycleInfo Info,
							   _In_ CMat Image,
							   _Out_ INT& NumberOfPoints);

	static
		void
		FilterNearestCycle(_Out_ SerialCycleInfo *target,
						   _Out_ SerialPoint2f *points,
						   _In_ SerialCycleInfo source,
						   _In_ FLOAT totalRadius);

	static
		void
		FilterCycleWithDistance(_Out_ SerialPoint2f *points,
								_Out_ SerialCycleInfo& info,
								_In_ SerialCycleInfo source);
	template<typename T>
	static
		bool
		CoincideCycle(_In_ T contour,
					  _Out_ FLOAT *radius,
					  _Out_ CycleInfo& Info,
					  _Out_ P2F *center,
					  _In_  DF filter,
					  _In_ INT zoom
		);

private:
	static
		void GetDistanceForEachPoints(
			_In_  SerialCycleInfo source,
			_Out_ MPST& dist_set
		);

	static
		void GetValidPointsIndex(
			_In_  MPST src,
			_Out_ std::set<int>& target
		);
private:
	using PFP = PointFilterProcessing;

};



template<typename T>
inline bool
PointFilterProcessing::CoincideCycle(
	_In_ T contour, _Out_  FLOAT *radius, _Out_ CycleInfo& Info,
	_Out_ P2F *center, _In_  DF filter, _In_ INT zoom)
{
	cv::minEnclosingCircle(
		cv::Mat(contour),
		*center,
		*radius
	);

	*radius = *radius / (FLOAT)zoom;
	center->x = center->x / (FLOAT)zoom;
	center->y = center->y / (FLOAT)zoom;

	if(*radius > filter.GetMaxRadius() ||
	   *radius < filter.GetMinRadius())return false;

	Info.radius = *radius;
	Info.center.x = center->x;
	Info.center.y = center->y;
	Info.contour = contour;
	Info.area = cv::contourArea(contour) / (DOUBLE)pow(zoom, 2);

	return true;
}


#endif // !__IMAGEPOINTSFILTERPROCESSING_H
