#pragma once
#ifndef __SLICECHARIMAGEFILTER_H
#define __SLICECHARIMAGEFILTER_H

#include "BasicImageFilterObject.hxx"

class SliceCharImageFileter : public ImageFilterObject<CHAR, 2>
{
public:
	SliceCharImageFileter();
	~SliceCharImageFileter();

public:
	SliceCharImagePointer ReadImage(CPCHAR __path);
	RGBSlicerCharPointer  ReadRgbImage(CPCHAR __path);
	SliceCharImagePointer ReadImage(CPCHAR __path, CharDicomValue& __dicom_vo);
	SliceCharImagePointer ImportImage(PCHAR __buf, ImageHeader __hd, UINT& __bufLenth);
	void SaveImage(SliceCharImagePointer __img_ptr, CPCHAR __path, CPCHAR __name, CPCHAR __extent);
	SliceCharImagePointer VtkImageToItkImage(vtkSmartPointer<vtkDataSet> __itk_img);

private:

};

#endif // !__SLICECHARIMAGEFILTER_H
