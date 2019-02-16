#pragma once
#ifndef __FASTREADIMAGE_H
#define __FASTREADIMAGE_H
#include "FrameWorkType.h"

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkPolyData.h>
#include <vtkAlgorithmOutput.h>


class FastReading
{
public:
	FastReading();
	~FastReading();

	vtkSmartPointer<vtkImageData> vtkDicomFastReading(PFLOAT&);
	vtkSmartPointer<vtkImageData> vtkMetaFastReading();
	vtkSmartPointer<vtkImageData> vtkBmpFastReading();
	vtkSmartPointer<vtkImageData> vtkJpegFastReading();
	vtkSmartPointer<vtkImageData> vtkPngFastReading();
	vtkSmartPointer<vtkImageData> vtkTiffFastReading();
	vtkSmartPointer<vtkImageData> vtkRawFastReading();
	vtkSmartPointer<vtkPolyData> vtkObjFastReading();
	vtkSmartPointer<vtkAlgorithmOutput> vtkObjPortFastReading();

	vtkSmartPointer<vtkImageData> RevolveAroundAxis(
		vtkSmartPointer<vtkImageData>__src,
		UINT __axis=0
	);	
	
private:
	void __clear_status();

public:
	UINT __f_dims__;
	ULONG __fread_err_code__;
	NTSTATUS __f_status__;
	CPCHAR __f_file_path__;
	_StrStm_ __f_err_msg__;
};


#endif // !__FASTREADIMAGE_H
