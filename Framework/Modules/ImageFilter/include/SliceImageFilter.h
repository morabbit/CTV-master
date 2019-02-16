#pragma once
#ifndef __SHORTIMAGEFILTER_H
#define __SHORTIMAGEFILTER_H

//#include "ImageReadObject.hxx"
#include "BasicImageFilterObject.hxx"

class SliceImageFilter : public ImageFilterObject<SHORT, 2>
{
public:
	SliceImageFilter();
	~SliceImageFilter();

public:
	SliceImagePointer ReadImage(CPCHAR __path);
	RGBSlicerPointer ReadRgbImage(CPCHAR __path);
	SliceImagePointer ReadImage(CPCHAR __path, ShortDicomVO& __dicom_vo);
	SliceImagePointer ImportImage(PSHORT __buf, ImageHeader __hd, UINT& __bufLenth);
	void SaveImage(SliceImagePointer __img_ptr, CPCHAR __path, CPCHAR __name, CPCHAR __extent);
	
	SliceImagePointer VtkImageToItkImage(vtkSmartPointer<vtkDataSet> __itk_img);

private:

};

#endif // !__SHORTIMAGEFILTER_H
