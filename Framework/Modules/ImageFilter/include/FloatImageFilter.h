#pragma once
#ifndef __FLOATIMAGEFILTER_H
#define __FLOATIMAGEFILTER_H
#include "BasicImageFilterObject.hxx"

class FloatImageFilter : public ImageFilterObject<FLOAT, 3>
{
public:
	FloatImageFilter();
	~FloatImageFilter();

public:
	FloatImagePointer ReadImage(CPCHAR __path);
	RGBFloatPointer ReadRgbImage(CPCHAR __path);
	FloatImagePointer ReadImage(CPCHAR __path, ShortDicomVO& __dicom_vo);
	FloatImagePointer ImportImage(PFLOAT __buf, ImageHeader __hd, UINT& __bufLenth);
	void SaveImage(FloatImagePointer __img_ptr, CPCHAR __path, CPCHAR __name, CPCHAR __extent);

	FloatImagePointer VtkImageToItkImage(vtkSmartPointer<vtkDataSet> __itk_img);
private:

};


#endif // !__FLOATIMAGEFILTER_H
