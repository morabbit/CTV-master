#pragma once
#ifndef __DATATRANSFORMBASE_H
#define __DATATRANSFORMBASE_H

#include <vtkImageCast.h>
#include <itkVTKImageToImageFilter.h>
#include <itkImageToVTKImageFilter.h>

#include "FrameWorkType.h"
#include "ItkCommonDefine.hxx"
#include "FrameworkErrorCode.h"
#include <itkCastImageFilter.h>
#include <itkExtractImageFilter.h>
#include <vtkImageFlip.h>

enum SliceDirection
{
	d_x = 0,
	d_y = 1,
	d_z = 2,
};

template<class _InputImage, class _OutputImage>
class ImageTypeTransform final
{
public:
	static typename _OutputImage::Pointer
		CastImage(typename _InputImage::Pointer __src, NTSTATUS& __status)
	{
		if(_InputImage::ImageDimension != _OutputImage::ImageDimension)
		{
			__status = IMAGE_DIMENSION_NOT_MATCH;
			return nullptr;
		}

		typedef itk::CastImageFilter<_InputImage, _OutputImage> CastFilter;
		typename CastFilter::Pointer __cast = CastFilter::New();
		__cast->SetInput(__src);

		__status = SUCCESSED;
		return __cast->GetOutput();
	}
};

template<class _TInputImage>
class Image2D3DTransform final
{
public:
	static 
		typename itk::Image<typename _TInputImage::PixelType, SliceDimension>::Pointer
		itkImage3Dto2D(typename _TInputImage::Pointer __img_ptr,
					   UINT __sliceNo, SliceDirection __direct=SliceDirection::d_z)
	{
		typedef _TInputImage ITKImageType;
		typedef typename ITKImageType::Pointer ITKImagePointer;
		typedef itk::Image<typename _TInputImage::PixelType, SliceDimension> ITKSliceType;
		typedef typename ITKSliceType::Pointer ITKSlicePointer;
		typedef itk::ExtractImageFilter<ITKImageType, ITKSliceType> ExtractImageFilterType;
		typename ExtractImageFilterType::Pointer extractImageFilter = ExtractImageFilterType::New();

		if((__direct > d_z)||(__direct < d_x))
		{
			__direct = d_z;
		}
		const ImageRegionType& inputImageRegion = __img_ptr->GetLargestPossibleRegion();
		ImageSizeType extractImageSize = inputImageRegion.GetSize();
		extractImageSize[2] = 0;
		ImageIndexType extractImageIndex = inputImageRegion.GetIndex();
		extractImageIndex[(UINT)__direct] = __sliceNo;

		ImageRegionType extractImageRegion;
		extractImageRegion.SetSize(extractImageSize);
		extractImageRegion.SetIndex(extractImageIndex);
		extractImageFilter->SetExtractionRegion(extractImageRegion);
		extractImageFilter->SetDirectionCollapseToSubmatrix();
		extractImageFilter->SetInput(__img_ptr);
		extractImageFilter->SetDirectionCollapseToSubmatrix();
		extractImageFilter->Update();

		return extractImageFilter->GetOutput();
	}

};


template<class _ITKImageType>
class DataTransform
{
private:
	typedef  itk::Image<char, _ITKImageType::ImageDimension> DT_Char_Image;
	typedef  typename DT_Char_Image::Pointer Char_Image_Ptr;

	typedef  itk::Image<double, _ITKImageType::ImageDimension> DT_Double_Image;
	typedef  typename DT_Double_Image::Pointer Double_Image_Ptr;

	typedef  itk::Image<float, _ITKImageType::ImageDimension> DT_Float_Image;
	typedef  typename DT_Float_Image::Pointer Float_Image_Ptr;

	typedef  itk::Image<int, _ITKImageType::ImageDimension> DT_Int_Image;
	typedef  typename DT_Int_Image::Pointer Int_Image_Ptr;

	typedef  itk::Image<long, _ITKImageType::ImageDimension> DT_Long_Image;
	typedef  typename DT_Long_Image::Pointer Long_Image_Ptr;

	typedef  itk::Image<short, _ITKImageType::ImageDimension> DT_Short_Image;
	typedef  typename DT_Short_Image::Pointer Short_Image_Ptr;

	typedef  itk::Image<unsigned char, _ITKImageType::ImageDimension> DT_UChar_Image;
	typedef  typename DT_UChar_Image::Pointer UChar_Image_Ptr;

	typedef  itk::Image<unsigned int, _ITKImageType::ImageDimension> DT_UInt_Image;
	typedef  typename DT_UInt_Image::Pointer UInt_Image_Ptr;

	typedef  itk::Image<unsigned long, _ITKImageType::ImageDimension> DT_ULong_Image;
	typedef  typename DT_ULong_Image::Pointer ULong_Image_Ptr;

	typedef  itk::Image<unsigned short, _ITKImageType::ImageDimension> DT_UShort_Image;
	typedef  typename DT_UShort_Image::Pointer UShort_Image_Ptr;

public:
	DataTransform();
	~DataTransform();

public:
	vtkSmartPointer<vtkImageData> ItkImageToVtkImage(typename _ITKImageType::Pointer __itk_img);
	
	typename _ITKImageType::Pointer CastChar2Image(Char_Image_Ptr __src);
	typename _ITKImageType::Pointer CastDouble2Image(Double_Image_Ptr __src);
	typename _ITKImageType::Pointer CastFloat2Image(Float_Image_Ptr __src);
	typename _ITKImageType::Pointer CastInt2Image(Int_Image_Ptr __src);
	typename _ITKImageType::Pointer CastInt2Image(Long_Image_Ptr __src);	
	typename _ITKImageType::Pointer CastShort2Image(Short_Image_Ptr __src);
	typename _ITKImageType::Pointer CastUChar2Image(UChar_Image_Ptr __src);
	typename _ITKImageType::Pointer CastUInt2Image(UInt_Image_Ptr __src);	
	typename _ITKImageType::Pointer CastULong2Image(ULong_Image_Ptr __src);	
	typename _ITKImageType::Pointer CastUShort2Image(UShort_Image_Ptr __src);

	typename itk::Image<char, _ITKImageType::ImageDimension>::Pointer 
		Cast2CharImage(
			typename _ITKImageType::Pointer __src
		);

	typename itk::Image<double, _ITKImageType::ImageDimension>::Pointer
		Cast2DoubleImage(
			typename _ITKImageType::Pointer __src
		);

	typename itk::Image<float, _ITKImageType::ImageDimension>::Pointer
		Cast2FloatImage(
			typename _ITKImageType::Pointer __src
		);

	typename itk::Image<int, _ITKImageType::ImageDimension>::Pointer 
		Cast2IntImage(
			typename _ITKImageType::Pointer __src
		);

	typename itk::Image<long, _ITKImageType::ImageDimension>::Pointer 
		Cast2LongImage(
			typename _ITKImageType::Pointer __src
		);

	typename itk::Image<short, _ITKImageType::ImageDimension>::Pointer 
		Cast2ShortImage(
			typename _ITKImageType::Pointer __src
		);

	typename itk::Image<unsigned char, _ITKImageType::ImageDimension>::Pointer
		Cast2UCharImage(
			typename _ITKImageType::Pointer __src
		);

	typename itk::Image<unsigned int, _ITKImageType::ImageDimension>::Pointer 
		Cast2UIntImage(
			typename _ITKImageType::Pointer __src
		);

	typename itk::Image<unsigned long, _ITKImageType::ImageDimension>::Pointer 
		Cast2ULongImage(
			typename _ITKImageType::Pointer __src
		);

	typename itk::Image<unsigned short, _ITKImageType::ImageDimension>::Pointer 
		Cast2UShortImage(
			typename _ITKImageType::Pointer __src
		);

	typename itk::Image<typename _ITKImageType::PixelType, SliceDimension>::Pointer
		Image3DTo2DXimage(
			typename _ITKImageType::Pointer __img_ptr,
			UINT __sliceNo
		);	

	typename itk::Image<typename _ITKImageType::PixelType, SliceDimension>::Pointer
		Image3DTo2DYimage(
			typename _ITKImageType::Pointer __img_ptr,
			UINT __sliceNo
		);
	
	typename itk::Image<typename _ITKImageType::PixelType, SliceDimension>::Pointer
		Image3DTo2DZimage(
			typename _ITKImageType::Pointer __img_ptr,
			UINT __sliceNo
		);

	NTSTATUS GetStatus();
	_String GetErrorMsg();

protected:
		typename _ITKImageType::Pointer 
			__VtkImageToItkImage(
				vtkSmartPointer<vtkDataSet> __vtk_img, 
				int __type = VTK_VOID
			);

private:
	NTSTATUS __state__;
	_StrStm_ __err__;
};

#include "..\src\DataTransformBase.cxx"

#endif // !__DATATRANSFORMBASE_H

