#pragma once
#ifndef __BASICIMAGEFILTEROBJECT_H
#define __BASICIMAGEFILTEROBJECT_H

#include "ContainerDefine.h"
#include "FrameCommonFunctionMacro.h"
#include "ModulesCommonMacro.h"
#include "ImageReadObject.hxx"
#include "DataTransformBase.hxx"
#include "FastReadImage.h"
#include <vtkErrorCode.h>


template<class _Type, UINT _Dims = 2>
class ImageFilterObject :	
	protected FastReading,
	protected ImageReadWriteObject<_Type, _Dims>,	
	public DataTransform<itk::Image<_Type, _Dims>>	
{
public:
	ImageFilterObject();
	~ImageFilterObject();
	
public:
	virtual typename itk::Image<_Type, _Dims>::Pointer ReadImage(CPCHAR __path) = 0;
	virtual typename itk::Image<itk::RGBPixel<_Type>, _Dims>::Pointer ReadRgbImage(CPCHAR __path) = 0;
	virtual typename itk::Image<_Type, _Dims>::Pointer ReadImage(CPCHAR __path, DicomValue<_Type>& __dicom_vo) = 0;
	virtual typename itk::Image<_Type, _Dims>::Pointer ImportImage(_Type* __buf, ImageHeader __hd, UINT& __bufLenth) = 0;
	virtual void SaveImage(typename itk::Image<_Type, _Dims>::Pointer __img_ptr, CPCHAR _path, CPCHAR __name, CPCHAR __extent) = 0;
	
	virtual typename itk::Image<_Type, _Dims>::Pointer VtkImageToItkImage(vtkSmartPointer<vtkDataSet> __itk_img) = 0;
	
public:
	NTSTATUS GetResultStatus();
	_String GetResultErrorMsg();

	virtual __PathType GetPathType(CPCHAR __path);
	virtual vtkSmartPointer<vtkAlgorithmOutput> ObjPortFastReading(CPCHAR __path);
	virtual vtkSmartPointer<vtkPolyData>  ObjFastReading(CPCHAR __path);	
	virtual vtkSmartPointer<vtkImageData> MetaFastReading(CPCHAR __path);
	virtual vtkSmartPointer<vtkImageData> BmpFastReading(CPCHAR __path);
	virtual vtkSmartPointer<vtkImageData> JpegFastReading(CPCHAR __path);
	virtual vtkSmartPointer<vtkImageData> PngFastReading(CPCHAR __path);
	virtual vtkSmartPointer<vtkImageData> TiffFastReading(CPCHAR __path);
	virtual vtkSmartPointer<vtkImageData> RawFastReading(CPCHAR __path);
	virtual vtkSmartPointer<vtkImageData> DicomFastReading(CPCHAR __path, PFLOAT &__direct);
	virtual vtkSmartPointer<vtkImageData> DicomFastReading(CPCHAR __path, DicomValue<_Type>& __dicom_vo);

private:
	void fillDicomVo(DicomValue<_Type>& __dicom_vo, ImageHeader __hd, load_image* __ld);
	void fillImageHead(ImageHeader& __hd, vtkSmartPointer<vtkImageData> __dt, PFLOAT __direct);
};

#include "..\src\BasicImageFilterObject.cxx"

#endif // !__BASICIMAGEFILTEROBJECT_H


