#pragma once
#ifndef __CLEARPOINTSPROCESSING_H
#define __CLEARPOINTSPROCESSING_H
#include "CalibrationPlateCommon.hpp"

class ClearPointProcessing
{
public:
	ClearPointProcessing();
	~ClearPointProcessing();

	void InitializeMaskImage(void);
	void SetSourceImage(_In_ CMat img);
		
	NTSTATUS
		ReadImage(
			_In_ CPCHAR path,
			_Out_ CMat& img
		);

	NTSTATUS
		ClearImagePoints(
			_Out_ CMat& result
		);

	NTSTATUS
		GenerateImageMask(
			_In_ PFLOAT srcPoints,
			_In_ PFLOAT radiuses,
			_In_ UINT cnt			
		);

	NTSTATUS
		GenerateImageMask(
			_In_ SerialPoint2f srcPoints,
			_In_ PFLOAT radiuses
		);

	NTSTATUS
		GenerateImageMask(
			_In_ SerialCycleInfo src
		);


private:
	CMat __src_image__;
	CMat __mask_image__;

	SerialPoint2f __src_point__;
};



#endif // !__CLEARPOINTSPROCESSING_H
