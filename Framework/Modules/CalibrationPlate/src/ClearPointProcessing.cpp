#include "pch.h"
#include "TraceLogExporter.h"
#include "FrameworkDefine.h"
#include "..\include\ClearPointProcessing.h"

#include <io.h>

ClearPointProcessing::ClearPointProcessing()
{
}

ClearPointProcessing::~ClearPointProcessing()
{
}

void ClearPointProcessing::InitializeMaskImage(void)
{
	__mask_image__ = CMat(__src_image__.size(), CV_8UC1, cv::Scalar::all(0));
}

void ClearPointProcessing::SetSourceImage(CMat img)
{
	__src_image__ = img;
}

NTSTATUS 
ClearPointProcessing::ReadImage(_In_ CPCHAR path, _Out_ CMat& img)
{
	if(_access(path, 0) == -1) return IMAGE_NOT_EXIST;

	img = cv::imread(path, 0);

	if(!img.data)
	{
		TraceLog << "Read Image [" << path << "] failed";
		return READ_CLEAR_IMAGE_ERROR;
	}
	PRINT_DBG("image chnel = [%d]", img.channels());

	return SUCCESSED;
}

NTSTATUS 
ClearPointProcessing::ClearImagePoints(_Out_ CMat& result)
{
	try 
	{
		cv::inpaint(__src_image__, __mask_image__,
					result, 5, cv::INPAINT_TELEA);
	}
	catch(const std::exception& err) 
	{
		PRINT_DBG("inpaint image error ");
		TraceLog << "inpaint image error : \n " << err.what();

		return INPAINT_IMAGE_FAILED;
	}
	return SUCCESSED;
}

NTSTATUS 
ClearPointProcessing::GenerateImageMask(
	_In_ PFLOAT srcPoints, _In_ PFLOAT radiuses, _In_ UINT cnt)
{
	for(UINT i = 0; i < cnt; i++)
	{
		P2F point;
		try 
		{
			point.x = srcPoints[2*i];
			point.y = srcPoints[2*i + 1];
		}
		catch(const std::exception& err) 
		{
			PRINT_DBG("Points number = [%d], current x index = [%d], current y index = [%d]",
					  cnt, 2 * i, 2 * i + 1);
			TraceLog << "findContours get an exception: \n " << err.what();
			return POINTS_DISMATCHED_WITTH_NUM;
		}
		__src_point__.push_back(point);
		cv::circle(__mask_image__, point,int(round(radiuses[i])), 
				   cv::Scalar(255, 255, 255), -1, 8);
	}

	return SUCCESSED;
}

NTSTATUS
ClearPointProcessing::GenerateImageMask(
	_In_ SerialPoint2f srcPoints, _In_ PFLOAT radiuses)
{
	UINT len = (UINT)srcPoints.size();
	if(len < 1)
	{
		return CLEAR_POINTS_SIZE_ZERO;
	}
	__src_point__.swap(SerialPoint2f());
	__src_point__.assign(srcPoints.begin(), srcPoints.end());

	for(UINT i = 0; i < len; i++)
	{
		cv::circle(__mask_image__, __src_point__[i], int(round(radiuses[i])),
				   cv::Scalar(255, 255, 255), -1, 8);
	}
	
	return SUCCESSED;
}

NTSTATUS 
ClearPointProcessing::GenerateImageMask(_In_ SerialCycleInfo src)
{
	UINT len = (UINT)src.size();
	if(len < 1)
	{
		return CLEAR_POINTS_SIZE_ZERO;
	}

	for(UINT i = 0; i < len; i++)
	{
		__src_point__.push_back(src[i].center);
		cv::circle(__mask_image__, src[i].center, int(round(src[i].radius)),
				   cv::Scalar(255, 255, 255), -1, 8);
	}


	return SUCCESSED;
}
