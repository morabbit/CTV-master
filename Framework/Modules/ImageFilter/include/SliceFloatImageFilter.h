#pragma once
#ifndef __SLICEFLOATIMAGEFILTER_H
#define __SLICEFLOATIMAGEFILTER_H

#include "BasicImageFilterObject.hxx"


class SliceFloatImageFilter : public ImageFilterObject<FLOAT, 2>
{
public:
	SliceFloatImageFilter();
	~SliceFloatImageFilter();

public:
	SliceFloatImagePointer ReadImage(CPCHAR __path);
	RGBSliceFloatPointer ReadRgbImage(CPCHAR __path);
	SliceFloatImagePointer ReadImage(CPCHAR __path, FloatDicomValue& __dicom_vo);
	SliceFloatImagePointer ImportImage(PFLOAT __buf, ImageHeader __hd, UINT& __bufLenth);
	void SaveImage(SliceFloatImagePointer __img_ptr, CPCHAR __path, CPCHAR __name, CPCHAR __extent);
	SliceFloatImagePointer VtkImageToItkImage(vtkSmartPointer<vtkDataSet> __itk_img);
private:

};

#endif // !__SLICEFLOATIMAGEFILTER_H
