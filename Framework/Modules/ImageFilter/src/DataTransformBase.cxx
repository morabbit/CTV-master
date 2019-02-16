#include "pch.h"

#ifndef __DATATRANSFORMBASE_CXX
#define __DATATRANSFORMBASE_CXX

#include "..\include\DataTransformBase.hxx"


template<class _ITKImageType>
DataTransform<_ITKImageType>::DataTransform()
{
}

template<class _ITKImageType>
DataTransform<_ITKImageType>::~DataTransform()
{
}

template<class _ITKImageType>
inline vtkSmartPointer<vtkImageData>
DataTransform<_ITKImageType>::ItkImageToVtkImage(typename _ITKImageType::Pointer __itk_img)
{
	typedef itk::ImageToVTKImageFilter<_ITKImageType> FilterType;
	typename FilterType::Pointer __itk_2_vtk_filter = FilterType::New();
	__itk_2_vtk_filter->SetInput(__itk_img);
	try
	{
		__itk_2_vtk_filter->Update();
	}
	catch(const itk::ExceptionObject & err)
	{
		__state__ = ITK_2_VTK_FAILED;
		__err__ << "ExceptionObject caught !\n" << err.what();
		return nullptr;
	}
	vtkSmartPointer <vtkImageFlip> imageflip = vtkSmartPointer<vtkImageFlip>::New();
	imageflip->SetInputData(__itk_2_vtk_filter->GetOutput());
	imageflip->SetFilteredAxes(1);
	try
	{
		imageflip->Update();
	}
	catch(const itk::ExceptionObject & err)
	{
		__state__ = ITK_2_VTK_FAILED;
		__err__ << "ExceptionObject caught !\n" << err.what();
		return nullptr;
	}

	vtkSmartPointer <vtkImageFlip> imageflip_org = vtkSmartPointer<vtkImageFlip>::New();
	imageflip_org->SetInputData(imageflip->GetOutput());
	imageflip_org->SetFilteredAxes(1);
	try
	{
		imageflip_org->Update();
	}
	catch(const itk::ExceptionObject & err)
	{
		__state__ = ITK_2_VTK_FAILED;
		__err__ << "ExceptionObject caught !\n" << err.what();
		return nullptr;
	}

	return imageflip_org->GetOutput();
}

template<class _ITKImageType>
inline typename _ITKImageType::Pointer
DataTransform<_ITKImageType>::__VtkImageToItkImage(vtkSmartPointer<vtkDataSet> __vtk_img, int __type)
{
	vtkSmartPointer<vtkImageCast> __cast_filter = vtkSmartPointer<vtkImageCast>::New();
	__cast_filter->SetInputData(__vtk_img);
	__cast_filter->SetOutputScalarType(__type);
	//__cast_filter->SetOutputScalarTypeToShort();
	try
	{
		__cast_filter->Update();
	}
	catch(const std::exception& err)
	{
		__state__ = VTK_CAST_IMAGE_FAILED;
		__err__ << "ExceptionObject caught !\n" << err.what();
		return nullptr;
	}

	typedef itk::VTKImageToImageFilter<_ITKImageType>  VTK2ITKFilter;
	typename VTK2ITKFilter::Pointer __vtk_2_itk_filter = VTK2ITKFilter::New();
	__vtk_2_itk_filter->SetInput(__cast_filter->GetOutput());
	__vtk_2_itk_filter->UpdateLargestPossibleRegion();

	try
	{
		__vtk_2_itk_filter->Update();
	}
	catch(const std::exception& err)
	{
		__state__ = VTK_2_ITK_FAILED;
		__err__ << "ExceptionObject caught !\n" << err.what();
		return nullptr;
	}
	return __vtk_2_itk_filter->GetOutput();
}

template<class _ITKImageType>
inline typename _ITKImageType::Pointer
DataTransform<_ITKImageType>::CastChar2Image(Char_Image_Ptr __src)
{
	return ImageTypeTransform<DT_Char_Image, _ITKImageType>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename _ITKImageType::Pointer
DataTransform<_ITKImageType>::CastDouble2Image(Double_Image_Ptr __src)
{
	return ImageTypeTransform<DT_Double_Image, _ITKImageType>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename _ITKImageType::Pointer
DataTransform<_ITKImageType>::CastFloat2Image(Float_Image_Ptr __src)
{
	return ImageTypeTransform<DT_Float_Image, _ITKImageType>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename _ITKImageType::Pointer
DataTransform<_ITKImageType>::CastInt2Image(Int_Image_Ptr __src)
{
	return ImageTypeTransform<DT_Int_Image, _ITKImageType>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename _ITKImageType::Pointer
DataTransform<_ITKImageType>::CastInt2Image(Long_Image_Ptr __src)
{
	return ImageTypeTransform<DT_Long_Image, _ITKImageType>::CastImage(__src);
}

template<class _ITKImageType>
inline typename _ITKImageType::Pointer
DataTransform<_ITKImageType>::CastShort2Image(Short_Image_Ptr __src)
{
	return ImageTypeTransform<DT_Short_Image, _ITKImageType>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename _ITKImageType::Pointer
DataTransform<_ITKImageType>::CastUChar2Image(UChar_Image_Ptr __src)
{
	return ImageTypeTransform<DT_UChar_Image, _ITKImageType>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename _ITKImageType::Pointer
DataTransform<_ITKImageType>::CastUInt2Image(UInt_Image_Ptr __src)
{
	return ImageTypeTransform<DT_UInt_Image, _ITKImageType>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename _ITKImageType::Pointer
DataTransform<_ITKImageType>::CastULong2Image(ULong_Image_Ptr __src)
{
	return ImageTypeTransform<DT_ULong_Image, _ITKImageType>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename _ITKImageType::Pointer
DataTransform<_ITKImageType>::CastUShort2Image(UShort_Image_Ptr __src)
{
	return ImageTypeTransform<DT_UShort_Image, _ITKImageType>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename itk::Image<char, _ITKImageType::ImageDimension>::Pointer
DataTransform<_ITKImageType>::Cast2CharImage(typename _ITKImageType::Pointer __src)
{
	return ImageTypeTransform<_ITKImageType, DT_Char_Image>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename itk::Image<double, _ITKImageType::ImageDimension>::Pointer
DataTransform<_ITKImageType>::Cast2DoubleImage(typename _ITKImageType::Pointer __src)
{
	return ImageTypeTransform<_ITKImageType, DT_Double_Image>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename itk::Image<float, _ITKImageType::ImageDimension>::Pointer
DataTransform<_ITKImageType>::Cast2FloatImage(typename _ITKImageType::Pointer __src)
{
	return ImageTypeTransform<_ITKImageType, DT_Float_Image>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename itk::Image<int, _ITKImageType::ImageDimension>::Pointer
DataTransform<_ITKImageType>::Cast2IntImage(typename _ITKImageType::Pointer __src)
{
	return ImageTypeTransform<_ITKImageType, DT_Int_Image>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename itk::Image<long, _ITKImageType::ImageDimension>::Pointer
DataTransform<_ITKImageType>::Cast2LongImage(typename _ITKImageType::Pointer __src)
{
	return ImageTypeTransform<_ITKImageType, DT_Long_Image>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename itk::Image<short, _ITKImageType::ImageDimension>::Pointer
DataTransform<_ITKImageType>::Cast2ShortImage(typename _ITKImageType::Pointer __src)
{
	return ImageTypeTransform<_ITKImageType, DT_Short_Image>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename itk::Image<unsigned char, _ITKImageType::ImageDimension>::Pointer
DataTransform<_ITKImageType>::Cast2UCharImage(typename _ITKImageType::Pointer __src)
{
	return ImageTypeTransform<_ITKImageType, DT_UChar_Image>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename itk::Image<unsigned int, _ITKImageType::ImageDimension>::Pointer
DataTransform<_ITKImageType>::Cast2UIntImage(typename _ITKImageType::Pointer __src)
{
	return ImageTypeTransform<_ITKImageType, DT_UInt_Image>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename itk::Image<unsigned long, _ITKImageType::ImageDimension>::Pointer
DataTransform<_ITKImageType>::Cast2ULongImage(typename _ITKImageType::Pointer __src)
{
	return ImageTypeTransform<_ITKImageType, DT_ULong_Image>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename itk::Image<unsigned short, _ITKImageType::ImageDimension>::Pointer
DataTransform<_ITKImageType>::Cast2UShortImage(typename _ITKImageType::Pointer __src)
{
	return ImageTypeTransform<_ITKImageType, DT_UShort_Image>::CastImage(__src, __state__);
}

template<class _ITKImageType>
inline typename itk::Image<typename _ITKImageType::PixelType, SliceDimension>::Pointer
DataTransform<_ITKImageType>::Image3DTo2DXimage(
	typename _ITKImageType::Pointer __img_ptr, UINT __sliceNo)
{
	if(_ITKImageType::ImageDimension == 2)
	{
		return __img_ptr;
	}

	return Image2D3DTransform<_ITKImageType>::itkImage3Dto2D(__img_ptr,
															 __sliceNo,
															 SliceDirection::d_x);
}

template<class _ITKImageType>
inline typename itk::Image<typename _ITKImageType::PixelType, SliceDimension>::Pointer
DataTransform<_ITKImageType>::Image3DTo2DYimage(
	typename _ITKImageType::Pointer __img_ptr, UINT __sliceNo)
{
	if(_ITKImageType::ImageDimension == 2)
	{
		return __img_ptr;
	}
	return Image2D3DTransform<_ITKImageType>::itkImage3Dto2D(__img_ptr,
															 __sliceNo,
															 SliceDirection::d_y);
}

template<class _ITKImageType>
inline typename itk::Image<typename _ITKImageType::PixelType, SliceDimension>::Pointer
DataTransform<_ITKImageType>::Image3DTo2DZimage(
	typename _ITKImageType::Pointer __img_ptr, UINT __sliceNo)
{
	if(_ITKImageType::ImageDimension == 2)
	{
		return __img_ptr;
	}
	return Image2D3DTransform<_ITKImageType>::itkImage3Dto2D(__img_ptr,
															 __sliceNo,
															 SliceDirection::d_z);
}

template<class _ITKImageType>
inline NTSTATUS DataTransform<_ITKImageType>::GetStatus()
{
	return __state__;
}

template<class _ITKImageType>
inline _String DataTransform<_ITKImageType>::GetErrorMsg()
{
	return __err__.str();
}


#endif // !__DATATRANSFORMBASE_CXX
