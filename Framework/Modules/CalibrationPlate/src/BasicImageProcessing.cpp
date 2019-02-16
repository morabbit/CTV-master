#include "pch.h"
#include "TraceLogExporter.h"
#include "FrameworkDefine.h"
#include "..\include\BasicImageProcessing.h"
#include "..\include\ImagePointsFilterProcessing.h"

#include <io.h>

using PFP = PointFilterProcessing;

ImageProcessing::ImageProcessing()
{
	__Initialize();
}

ImageProcessing::~ImageProcessing()
{
	if((true == __free_cbt__) && (nullptr != __calibrator__))
	{
		delete __calibrator__;
	}
}

ImageProcessing::ImageProcessing(const ImageProcessing & obj)
{
	*this = obj;
}

ImageProcessing & ImageProcessing::operator=(const ImageProcessing & obj)
{
	this->__free_cbt__ = obj.__free_cbt__;

	this->__zoom__ = obj.__zoom__;
	this->__src_img__ = obj.__src_img__;

	this->__eda_type__ = obj.__eda_type__;
	this->__avg_pixel__ = obj.__avg_pixel__;
	this->__calibrator__ = obj.__calibrator__;

	return *this;
}


void ImageProcessing::SetCalibration(_In_ PCalibration cbt)
{
	if(nullptr == cbt)
	{
		__free_cbt__ = true;
		__calibrator__ = new Calibration;
	}
	else
	{
		__calibrator__ = cbt;
	}	

	__InitializeZoom();
}

void ImageProcessing::SetEdgeDetectionAlgorithm(_In_ EDA alg)
{
	__eda_type__ = alg;
}


void
ImageProcessing::EnlargementImage(CMat & Image)
{
	for(int i = 0; i < log(__zoom__) / log(2); i++) {
		CMat tempImage;
		pyrUp(Image, tempImage, CSize(Image.cols * 2, Image.rows * 2));
		Image = tempImage.clone();
	}
}

void
ImageProcessing::DownSamplingImage(CMat & Image)
{
	for(int i = 0; i < log(__zoom__) / log(2); i++) {
		CMat tempImage;
		pyrDown(Image, tempImage, CSize(Image.cols / 2, Image.rows / 2));
		Image = tempImage.clone();
	}
}

void
ImageProcessing::EnlargementPoint(SerialPoint2f & points)
{
	for(int i = 0; i < points.size(); i++)
		points[i] = points[i] * __zoom__;
}

NTSTATUS ImageProcessing::ReadImage(_In_ CPCHAR __path)
{

	__SetAveragePixel(__path);

	if(_access(__path, 0) == -1)
	{
		return IMAGE_NOT_EXIST;
	}

	__src_img__ = cv::imread(__path, 1);

	if(!__src_img__.data) 
	{
		TraceLog << "Read Image [" << __path << "] failed";
		return READ_IMAGE_ERROR;
	}
	PRINT_DBG("image chnel = [%d]", __src_img__.channels());

	return SUCCESSED;
}

NTSTATUS 
ImageProcessing::SobelImage(_In_ CMat image, _Out_ CMat& gray)
{
	NTSTATUS status = SUCCESSED;

	CMat grad_x, grad_y;
	CMat abs_grad_x, abs_grad_y;
	int kSize = __calibrator__->m_sobel.GetKsize();

	status = __ValidKSizeCheck(kSize);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	status = __SobelCoordinateAxis(
		image, __calibrator__->m_sobel.GetDx(), 0, abs_grad_x);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	status = __SobelCoordinateAxis(
		image, 0, __calibrator__->m_sobel.GetDy(), abs_grad_y);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, gray);

	return status;
}

NTSTATUS ImageProcessing::CannyGaussImage(CMat image, CMat & gray)
{
	try {
		cv::Canny(image, image, 80, 140, 3);
		cv::GaussianBlur(image, gray, cv::Size(5, 5), 1);
	}
	catch(const std::exception& err)
	{
		TraceLog << "Canny get an exception: \n " << err.what();
		return CANNY_GAUSS_ERROR;
	}

	return SUCCESSED;
}

NTSTATUS 
ImageProcessing::ThresholdImage(_In_ CMat gray, _Out_ CMat& thresh)
{
	NTSTATUS status = SUCCESSED;
	status = __CheckThresholdType();
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	try 
	{
		threshold(
			gray, thresh,
			__calibrator__->m_thresh.GetThresh(),
			__calibrator__->m_thresh.GetMaxval(),
			__calibrator__->m_thresh.GetType()
		);
	}
	catch(const std::exception& err)
	{
		TraceLog << "threshold get an exception: \n " << err.what();
		return THRESHOLD_ERROR;
	}

	return SUCCESSED;
}

NTSTATUS
ImageProcessing::GenerateReversedGaryImage(
	_In_ CMat image, _Out_ CMat& Revertgray)
{
	CMat gray(image.size(), CV_8U);
	NTSTATUS status = SUCCESSED;

	if(EDA::Algorithm_Canny == __eda_type__) 
	{
		status = CannyGaussImage(image, gray);
		CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	}
	else 
	{
		status = this->SobelImage(image, gray);
		CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	}

	if(!gray.data) 
	{
		PRINT_DBG("gray image is NULL !");
		return GARY_IMAGE_IS_NULL;
	}
	Revertgray = /*100 +*/ gray;

	return status;
}

NTSTATUS 
ImageProcessing::FindImageContours(_In_ CMat thresh, _Out_ SerialPoints& contours)
{
	if(thresh.channels() != 1)
	{
		return IMAGE_NOT_THRESHOLD;
	}

	try 
	{
		cv::findContours(thresh, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	}
	catch(const std::exception& err) 
	{
		TraceLog << "findContours get an exception: \n " << err.what();
		return FIND_CONTOURS_EXCEPTION;
	}

	return SUCCESSED;
}

NTSTATUS ImageProcessing::ExtractImagePoints(_In_ SerialPoints imgContours, 
											 _Out_ SerialCycleInfo& cInfos,
											 _Out_ SerialPoint2f& points)
{
	if(imgContours.size() == 0) return CANOT_RECOGNIZE_POINTS;

	DOUBLE radiuses = 0.0;
	SerialCycleInfo CycleInfos;
	DF dev = __calibrator__->m_dvt;
	for(size_t i = 0; i < imgContours.size(); i++)
	{
		bool result = PFP::ContinueToNextLoop(imgContours[i], dev);
		if(true == result) continue;

		FLOAT radius; cv::Point2f center; CycleInfo Info;
		result = PFP::CoincideCycle<SerialPoint>(
			imgContours[i], &radius, Info, &center, dev, __zoom__);
		if(false == result) continue;

		result = PFP::FilterConcentricCycle(
			&CycleInfos, radiuses,Info, dev.GetDeviation());
		if(true == result) continue;

		result = PFP::FilterFarNearPoints(&CycleInfos, Info, __src_img__);
		if(false == result) continue;

		result = PFP::FinialFilterWithPiexl(Info, __src_img__, __avg_pixel__);
		if(false == result) continue;

		result = PFP::OuteCrackAveragePiexlFilter(Info, __src_img__);
		if(false == result) continue;

		radiuses += Info.radius;
		CycleInfos.push_back(std::move(Info));
	}

	SerialPoint2f pptsl; SerialCycleInfo infos;
	PFP::FilterNearestCycle(&infos, &pptsl, CycleInfos, radiuses);
	PFP::FilterCycleWithDistance(&points, cInfos, infos);

	return SUCCESSED;
}

NTSTATUS 
ImageProcessing::__SobelCoordinateAxis(
	_In_ CMat image, _In_ INT dx, _In_ INT dy, _Out_ CMat& abs_grad)
{
	CMat grad;
	try
	{
		cv::Sobel(image, grad, __calibrator__->m_sobel.GetDdepth(),
				  dx, dy, __calibrator__->m_sobel.GetKsize(),
				  __calibrator__->m_sobel.GetScale(),
				  0, cv::BORDER_DEFAULT);

		cv::convertScaleAbs(grad, abs_grad);
	}
	catch(const std::exception& err)
	{
		TraceLog << "Sobel get an exception: \n " << err.what();
		return SOBEL_ERROR;
	}


	return SUCCESSED;
}

void 
ImageProcessing::BinaryzationImage(_In_ CMat src, _Out_ CMat& image)
{
	cv::medianBlur(src, src, int(ceil(1) * 2 + 1));
	for(int i = 0; i < log(__zoom__) / log(2); i++) {
		CMat tempImage;
		pyrUp(src, tempImage, CSize(src.cols * 2, src.rows * 2));
		src = tempImage.clone();
	}
	if(src.channels() == 1)image = src.clone();
	else cvtColor(src, image, CV_BGR2GRAY);
	cv::medianBlur(image, image, int(ceil(1) * 2 + 1));
}

CMat& ImageProcessing::GetSourceImage()
{
	return __src_img__;
}


PCalibration & ImageProcessing::GetCalibration(void)
{
	return __calibrator__;
}

void ImageProcessing::__Initialize()
{
	__free_cbt__ = false;
	__avg_pixel__ = 0.0f;
	__eda_type__ = EDA::Algorithm_Sobel;
	__calibrator__ = new Calibration;
}

void ImageProcessing::__InitializeZoom()
{
	__zoom__ = __calibrator__->m_dvt.GetZoom();
	int exponent = (int)ceil(log(__zoom__) / log(2));
	__zoom__ = (int)pow(2, exponent);
}

void ImageProcessing::__SetAveragePixel(_In_ CPCHAR __path)
{
	char fname[_MAX_FNAME], dir[_MAX_DIR];
	char drive[_MAX_DRIVE], ext[_MAX_EXT];

	_splitpath(__path, drive, dir, fname, ext);

	if(0 == memcmp(ext, ".jpg", 4))
	{
		__avg_pixel__ = 120.0;
	}
	else
	{
		__avg_pixel__ = 110.0;
	}
}

NTSTATUS ImageProcessing::__CheckThresholdType()
{
	int Types[7] = { 1, 2, 3, 4, 7, 8,16 };
	int type = __calibrator__->m_thresh.GetType();
	for(int i = 0; i < 7; i++)
	{
		if(type == Types[i])
		{
			return SUCCESSED;
		}
	}
	return INVALID_THRESHOLD_TYPE;
}

NTSTATUS ImageProcessing::__ValidKSizeCheck(_In_ INT kSize)
{
	bool bKsizeError = true;
	int ReferenceKSize[] = { 1, 3, 5, 7 };

	for(int i = 0; i < 4; i++) 
	{
		if(kSize == ReferenceKSize[i])
		{
			return SUCCESSED;
		}
	}

	return INVALID_KERNEL_SIZE;
}
