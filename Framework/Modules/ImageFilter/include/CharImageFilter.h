#pragma once
#ifndef __CHARIMAGEFILTER_H
#define __CHARIMAGEFILTER_H

#include "BasicImageFilterObject.hxx"

class CharImageFilter : public ImageFilterObject<CHAR, 3>
{
public:
	CharImageFilter();
	~CharImageFilter();

public:
	CharImagePointer ReadImage(CPCHAR __path);
	RGBCharPointer   ReadRgbImage(CPCHAR __path);
	CharImagePointer ReadImage(CPCHAR __path, CharDicomValue& __dicom_vo);
	CharImagePointer ImportImage(PCHAR __buf, ImageHeader __hd, UINT& __bufLenth);
	void SaveImage(CharImagePointer __img_ptr, CPCHAR __path, CPCHAR __name, CPCHAR __extent);

	CharImagePointer VtkImageToItkImage(vtkSmartPointer<vtkDataSet> __itk_img);

private:

};

#endif // !__CHARIMAGEFILTER_H
