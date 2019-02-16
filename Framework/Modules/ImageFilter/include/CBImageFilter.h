#pragma once
#ifndef __CBIMAGEFILTER_H
#define __CBIMAGEFILTER_H
#include "BasicImageFilterObject.hxx"

class CBImageFilter : public ImageFilterObject<USHORT, 3>
{
public:
	CBImageFilter();
	~CBImageFilter();

public:
	CBImagePointer ReadImage(CPCHAR __path);
	RGBCBPointer ReadRgbImage(CPCHAR __path);
	CBImagePointer ReadImage(CPCHAR __path, UShortDicomVO& __dicom_vo);
	CBImagePointer ImportImage(PUSHORT __buf, ImageHeader __hd, UINT& __bufLenth);
	void SaveImage(CBImagePointer __img_ptr, CPCHAR __path, CPCHAR __name, CPCHAR __extent);

	CBImagePointer VtkImageToItkImage(vtkSmartPointer<vtkDataSet> __itk_img);
	
private:

};


#endif // !__CBIMAGEFILTER_H
