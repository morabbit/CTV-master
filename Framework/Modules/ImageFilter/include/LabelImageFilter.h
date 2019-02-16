#pragma once
#ifndef __LABELIMAGEFILTER_H
#define __LABELIMAGEFILTER_H

#include "BasicImageFilterObject.hxx"

//LabelImagePointer

class LabelImageFilter : public ImageFilterObject<UCHAR, 3>
{
public:
	LabelImageFilter();
	~LabelImageFilter();

public :
	LabelImagePointer ReadImage(CPCHAR __path);
	RGBLabelPointer   ReadRgbImage(CPCHAR __path);
	LabelImagePointer ReadImage(CPCHAR __path, UCharDicomVO& __dicom_vo);
	LabelImagePointer ImportImage(PUCHAR __buf, ImageHeader __hd, UINT& __bufLenth);
	void SaveImage(LabelImagePointer __img_ptr, CPCHAR __path, CPCHAR __name, CPCHAR __extent);
	LabelImagePointer VtkImageToItkImage(vtkSmartPointer<vtkDataSet> __itk_img);

private:

};

#endif // !__LABELIMAGEFILTER_H
