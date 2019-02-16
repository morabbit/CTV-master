#pragma once
#ifndef __CALIBRATIONPLATECOMMON_HPP
#define __CALIBRATIONPLATECOMMON_HPP
#include <math.h>

#include <cpd/affine.hpp>
#include <cpd/nonrigid.hpp>
#include <cpd/rigid.hpp>

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui.hpp>
#include "opencv2/features2d/features2d.hpp"
#include "FrameWorkType.h"

#define PI  3.141592589793
#define ERROR_PIXEL         15.00
#define STANDARD_SIZE       1024.00
#define MIN_DISTANCE_ERROR  10.00
#define InnerRectLeftFrontPointAngle  45.0
#define InnerRectLeftFrontPointRadian    (InnerRectLeftFrontPointAngle * PI / 180.0)
#define SINE_45    sin(InnerRectLeftFrontPointRadian)
#define COSINE_45  cos(InnerRectLeftFrontPointRadian)

#define ANGLE_90_TO_RADIAN     (90 * PI / 180.0)
#define RADIAN_DEVIATION(x)    ((x) * PI / 180.0)

#define MaxDistance   350.0
#define MinDistance   45.0

using P2D   = cv::Point;
using P2F   = cv::Point2f;
using P3F   = cv::Point3f;
using CMat  = cv::Mat;
using CSize = cv::Size;

using CPDMatrix = cpd::Matrix;
using CPDNonrigid = cpd::Nonrigid;
using CPDNonrigidResult = cpd::NonrigidResult;

typedef enum EdgeDetectionAlgorithm
{
	Algorithm_Default = 0,
	Algorithm_Canny   = 1,
	Algorithm_Sobel   = 2,
}EDA;

typedef struct CycleInformation
{	
	P2D					 point;
	P2F					 center;
	FLOAT				 radius;
	DOUBLE				 totalDIst;
	DOUBLE				 area;
	std::vector<P2D>     contour;
	std::vector<P2F>     orgContour;
}CycleInfo;


typedef std::vector<CMat>            SerialMat;
typedef std::vector<P2D>			 SerialPoint;
typedef std::vector<P2F>             SerialPoint2f;
typedef std::vector<P3F>             SerialPoint3f;
typedef std::vector<CycleInfo>       SerialCycleInfo;
typedef std::vector<SerialPoint>     SerialPoints;
typedef std::vector<SerialPoint2f>   SerialPoint2fs;
typedef std::vector<SerialPoint3f>   SerialPoint3fs;

typedef const SerialMat                 CSerialMat;
typedef const SerialFloat               CSerialFloat;
typedef const SerialPoints              CSerialPoints;
typedef const SerialPoint3fs            CSerialPoint3fs;
typedef const SerialPoint2fs            CSerialPoint2fs;


typedef struct OrderPointResultCollectInput
{	
	_In_ INT fit1;
	_In_ INT fit2;
	_In_ INT fit1_f;
	_In_ INT fit2_f;
	_In_ P2F drct1;
	_In_ P2F drct2;
	_In_ P2F drct1_f;
	_In_ P2F drct2_f;
	_In_ P2F center1_f;
	_In_ P2F center2_f;
	_In_ DOUBLE error1;
	_In_ DOUBLE error1_f;
	_In_ DOUBLE error2_f;
	_In_ SerialPoint2f crspd1;
	_In_ SerialPoint2f crspd2;
	_In_ SerialPoint2f crspd1_f;
	_In_ SerialPoint2f crspd2_f;

}OPRCI, *POPRCI;

#endif // !__CALIBRATIONPLATECOMMON_HPP
