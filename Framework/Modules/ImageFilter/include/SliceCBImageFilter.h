#pragma once
#ifndef __SLICECBIMAGEFILTER_H
#define __SLICECBIMAGEFILTER_H

#include "BasicImageFilterObject.hxx"

class SliceCBImageFilter : public ImageFilterObject<USHORT, 2>
{
public:
	SliceCBImageFilter();
	~SliceCBImageFilter();

public:
	SliceCBImagePointer ReadImage(CPCHAR __path);
	RGBCBSlicerPointer ReadRgbImage(CPCHAR __path);
	SliceCBImagePointer ReadImage(CPCHAR __path, UShortDicomVO& __dicom_vo);
	SliceCBImagePointer ImportImage(PUSHORT __buf, ImageHeader __hd, UINT& __bufLenth);
	void SaveImage(SliceCBImagePointer __img_ptr, CPCHAR __path, CPCHAR __name, CPCHAR __extent);
	SliceCBImagePointer VtkImageToItkImage(vtkSmartPointer<vtkDataSet> __itk_img);

private:

};

#endif // !__SLICECBIMAGEFILTER_H
