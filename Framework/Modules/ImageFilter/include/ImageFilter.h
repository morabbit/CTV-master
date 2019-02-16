#pragma once
#ifndef __IMAGEFILTER_H
#define __IMAGEFILTER_H

#include "BasicImageFilterObject.hxx"

class ImageFilter : public ImageFilterObject<SHORT, 3>
{
public:
	ImageFilter();
	~ImageFilter();
	ImageFilter(const ImageFilter& obj);
	ImageFilter& operator=(const ImageFilter& obj);

public:
	ImagePointer ReadImage(CPCHAR __path);
	RGBPointer   ReadRgbImage(CPCHAR __path);
	ImagePointer ReadImage(CPCHAR __path, ShortDicomVO& __dicom_vo);	
	ImagePointer ImportImage(PSHORT __buf, ImageHeader __hd, UINT& __bufLenth);
	void SaveImage(ImagePointer __img_ptr, CPCHAR __path, CPCHAR __name, CPCHAR __extent);

	ImagePointer VtkImageToItkImage(vtkSmartPointer<vtkDataSet> __itk_img);

private:

};

#endif // !__IMAGEFILTER_H

