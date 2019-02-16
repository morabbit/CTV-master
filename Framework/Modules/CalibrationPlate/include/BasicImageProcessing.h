#pragma once
#ifndef __BASICIMAGEPROCESSING_H
#define __BASICIMAGEPROCESSING_H
#include "CalibrationPlateCommon.hpp"
#include "CalibrationPrecisionParameter.hpp"


class ImageProcessing
{
public:
	ImageProcessing();
	~ImageProcessing();
	ImageProcessing(const ImageProcessing& obj);
	ImageProcessing& operator=(const ImageProcessing& obj);

public:	
	/// option

	void 
		SetCalibration(
			_In_ PCalibration cbt
		);

	void 
		SetEdgeDetectionAlgorithm(
			_In_ EDA alg
		);

	void
		BinaryzationImage(
			_In_ CMat src,
			_Out_ CMat& image
		);

	void
		EnlargementImage(
			_Out_ CMat& Image
		);

	void
		DownSamplingImage(
			_Out_ CMat& Image
		);

	void 
		EnlargementPoint(
			_Out_ SerialPoint2f& points
		);


	CMat&
		GetSourceImage();

	NTSTATUS 
		ReadImage(
			_In_ CPCHAR __path
		);

	NTSTATUS
		SobelImage(
			_In_ CMat image,
			_Out_ CMat& gray
		);

	NTSTATUS
		CannyGaussImage(
			_In_ CMat image,
			_Out_ CMat& gray
		);

	NTSTATUS
		ThresholdImage(
			_In_ CMat gray, 
			_Out_ CMat& thresh
		);

	NTSTATUS 
		GenerateReversedGaryImage(
			_In_ CMat image,
			_Out_ CMat& Revertgray
		);

	NTSTATUS
		FindImageContours(
			_In_ CMat thresh,
			_Out_ SerialPoints& imgContours
		);

	NTSTATUS 
		ExtractImagePoints(
			_In_ SerialPoints imgContours,
			_Out_ SerialCycleInfo& cInfos,
			_Out_ SerialPoint2f& points
		);

	
	PCalibration& GetCalibration(void);

private:
	void __Initialize();
	void __InitializeZoom();
	void __SetAveragePixel(_In_ CPCHAR __path);

	NTSTATUS __CheckThresholdType();
	NTSTATUS __ValidKSizeCheck(_In_ INT kSize);

	NTSTATUS
		__SobelCoordinateAxis(
			_In_ CMat image,
			_In_ INT dx,
			_In_ INT dy,
			_Out_ CMat& abs_grad
		);


private:	
	bool __free_cbt__;

	INT __zoom__;
	CMat __src_img__;

	EDA  __eda_type__;
	FLOAT __avg_pixel__;	
	PCalibration __calibrator__;

};


#endif // !__BASICIMAGEPROCESSING_H
