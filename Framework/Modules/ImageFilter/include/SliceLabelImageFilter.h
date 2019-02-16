#pragma once
#ifndef __SLICELABELIMAGEFILTER_H
#define __SLICELABELIMAGEFILTER_H

#include "BasicImageFilterObject.hxx"

class SliceLabelImageFilter : public ImageFilterObject<UCHAR, 2>
{
public:
	SliceLabelImageFilter();
	~SliceLabelImageFilter();

public:

	SliceLabelImagePointer ReadImage(CPCHAR __path);
	RGBSlicerLabelPointer  ReadRgbImage(CPCHAR __path);
	SliceLabelImagePointer ReadImage(CPCHAR __path, UCharDicomVO& __dicom_vo);
	SliceLabelImagePointer ImportImage(PUCHAR __buf, ImageHeader __hd, UINT& __bufLenth);
	void SaveImage(SliceLabelImagePointer __img_ptr, CPCHAR __path, CPCHAR __name, CPCHAR __extent);
	SliceLabelImagePointer VtkImageToItkImage(vtkSmartPointer<vtkDataSet> __itk_img);

private:

};

#endif // !__SLICELABELIMAGEFILTER_H
