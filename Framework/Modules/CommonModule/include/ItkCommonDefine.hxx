#ifndef __ITKGCOMMONDEFINE_H
#define __ITKGCOMMONDEFINE_H

#include <itkImage.h>
#include <itkImageRegionIterator.h>
#include <itkImageRegionIteratorWithIndex.h>
#include <itkImageLinearIteratorWithIndex.h>
#include <itkImportImageFilter.h>
#include <itkNiftiImageIO.h>
#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>

#include "ItkImportLibrary.hxx"


const unsigned int ImageDimension = 3;
const unsigned int SliceDimension = 2;

typedef short PixelType;
typedef itk::RGBPixel<PixelType>                    RGBType;

typedef itk::Image< RGBType, ImageDimension>        RGBImageType;
typedef itk::Image<PixelType, ImageDimension>	    ImageType;
typedef RGBImageType::Pointer                       RGBPointer;
typedef ImageType::Pointer							ImagePointer;
typedef ImageType::ConstPointer						ImageConstPointer;
typedef ImageType::PixelType						ImagePixelType;
typedef ImageType::RegionType						ImageRegionType;
typedef ImageType::IndexType						ImageIndexType;
typedef ImageType::SizeType							ImageSizeType;

typedef itk::Image< RGBType, SliceDimension>        RGBSliceImageType;
typedef itk::Image<PixelType, SliceDimension>       SliceImageType;
typedef RGBSliceImageType::Pointer                  RGBSlicerPointer;
typedef SliceImageType::Pointer						SliceImagePointer;
typedef SliceImageType::ConstPointer				SliceImageConstPointer;
typedef SliceImageType::PixelType                   SliceImagePixelType;
typedef SliceImageType::RegionType					SliceImageRegionType;
typedef SliceImageType::IndexType					SliceImageIndexType;
typedef SliceImageType::SizeType					SliceImageSizeType;


typedef unsigned short UPixelType;
typedef itk::RGBPixel<UPixelType>                   RGBCBType;
typedef itk::Image<RGBCBType, ImageDimension>       RGBCBImageType;
typedef itk::Image<UPixelType, ImageDimension>	    CBImageType;
typedef RGBCBImageType::Pointer                     RGBCBPointer;
typedef CBImageType::Pointer						CBImagePointer;
typedef CBImageType::ConstPointer					CBImageConstPointer;
typedef CBImageType::PixelType						CBImagePixelType;
typedef CBImageType::RegionType						CBImageRegionType;
typedef CBImageType::IndexType						CBImageIndexType;
typedef CBImageType::SizeType						CBImageSizeType;

typedef itk::Image<UPixelType, SliceDimension>	    SliceCBImageType;
typedef itk::Image<RGBCBType, SliceDimension>       RGBCBSliceImageType;
typedef RGBCBSliceImageType::Pointer                RGBCBSlicerPointer;
typedef SliceCBImageType::Pointer					SliceCBImagePointer;
typedef SliceCBImageType::ConstPointer				SliceCBImageConstPointer;
typedef SliceCBImageType::PixelType					SliceCBImagePixelType;
typedef SliceCBImageType::RegionType				SliceCBImageRegionType;
typedef SliceCBImageType::IndexType					SliceCBImageIndexType;
typedef SliceCBImageType::SizeType					SliceCBImageSizeType;

typedef char CharPixelType;
typedef itk::RGBPixel<CharPixelType>                RGBCharType;
typedef itk::Image<CharPixelType, ImageDimension>	CharImageType;
typedef itk::Image<RGBCharType, ImageDimension>     RGBCharImageType;
typedef RGBCharImageType::Pointer                   RGBCharPointer;
typedef CharImageType::Pointer						CharImagePointer;
typedef CharImageType::ConstPointer				    CharImageConstPointer;
typedef CharImageType::PixelType					CharImagePixelType;
typedef CharImageType::IndexType					CharImageIndexType;
typedef CharImageType::RegionType					CharImageRegionType;
typedef CharImageType::SizeType					    CharImageSizeType;

typedef itk::Image<CharPixelType, SliceDimension>   SliceCharImageType;
typedef itk::Image<RGBCharType, SliceDimension>     RGBSlicerCharImageType;
typedef RGBSlicerCharImageType::Pointer             RGBSlicerCharPointer;
typedef SliceCharImageType::Pointer				    SliceCharImagePointer;
typedef SliceCharImageType::ConstPointer			SliceCharImageConstPointer;
typedef SliceCharImageType::RegionType				SliceCharImageRegionType;
typedef SliceCharImageType::IndexType				SliceCharImageIndexType;
typedef SliceCharImageType::SizeType				SliceCharImageSizeType;

typedef unsigned char LabelPixelType;
typedef itk::RGBPixel<LabelPixelType>               RGBLabelType;
typedef itk::Image<LabelPixelType, ImageDimension>	LabelImageType;
typedef itk::Image<RGBLabelType, ImageDimension>    RGBLabelImageType;
typedef RGBLabelImageType::Pointer                  RGBLabelPointer;
typedef LabelImageType::Pointer						LabelImagePointer;
typedef LabelImageType::ConstPointer				LabelImageConstPointer;
typedef LabelImageType::PixelType					LabelImagePixelType;
typedef LabelImageType::IndexType					LabelImageIndexType;
typedef LabelImageType::RegionType					LabelImageRegionType;
typedef LabelImageType::SizeType					LabelImageSizeType;

typedef itk::Image<LabelPixelType, SliceDimension>  SliceLabelImageType;
typedef itk::Image<RGBLabelType, SliceDimension>    RGBSliceLabelImageType;
typedef RGBSliceLabelImageType::Pointer             RGBSlicerLabelPointer;
typedef SliceLabelImageType::Pointer				SliceLabelImagePointer;
typedef SliceLabelImageType::ConstPointer			SliceLabelImageConstPointer;
typedef SliceLabelImageType::RegionType				SliceLabelImageRegionType;
typedef SliceLabelImageType::IndexType				SliceLabelImageIndexType;
typedef SliceLabelImageType::SizeType				SliceLabelImageSizeType;

typedef float FloatPixelType;
typedef itk::RGBPixel<FloatPixelType>               RGBFloatType;
typedef itk::Image<float, ImageDimension>			FloatImageType;
typedef itk::Image<RGBFloatType, ImageDimension>    RGBFloatImageType; 
typedef RGBFloatImageType::Pointer                  RGBFloatPointer;
typedef FloatImageType::Pointer						FloatImagePointer;
typedef FloatImageType::ConstPointer				FloatImageConstPointer;
typedef FloatImageType::PixelType					FloatImagePixelType;
typedef FloatImageType::RegionType					FloatImageRegionType;
typedef FloatImageType::IndexType					FloatImageIndexType;
typedef FloatImageType::SizeType					FloatImageSizeType;

typedef itk::Image<float, SliceDimension>			SliceFloatImageType;
typedef itk::Image<RGBFloatType, SliceDimension>    RGBSliceFloatImageType;
typedef RGBSliceFloatImageType::Pointer             RGBSliceFloatPointer;
typedef SliceFloatImageType::Pointer				SliceFloatImagePointer;
typedef SliceFloatImageType::ConstPointer			SliceFloatImageConstPointer;
typedef SliceFloatImageType::PixelType				SliceFloatImagePixelType;
typedef SliceFloatImageType::RegionType				SliceFloatImageRegionType;
typedef SliceFloatImageType::IndexType				SliceFloatImageIndexType;
typedef SliceFloatImageType::SizeType				SliceFloatImageSizeType;

typedef unsigned long ULongPixelType;
typedef itk::Image<ULongPixelType, ImageDimension>  ULongImageType;
typedef ULongImageType::Pointer						ULongImagePointer;

typedef itk::Image<ULongPixelType, SliceDimension>  SliceULongImageType;
typedef SliceULongImageType::Pointer				SliceULongImagePointer;

typedef long LongPixelType;
typedef itk::Image<LongPixelType, ImageDimension>   LongImageType;
typedef LongImageType::Pointer						LongImagePointer;

typedef itk::Image<LongPixelType, SliceDimension>   SliceLongImageType;
typedef SliceLongImageType::Pointer					SliceLongImagePointer;

typedef int IntPixelType;
typedef itk::Image<IntPixelType, ImageDimension>    IntImageType;
typedef IntImageType::Pointer						IntImagePointer;

typedef itk::Image<IntPixelType, SliceDimension>   SliceIntImageType;
typedef SliceIntImageType::Pointer				   SliceIntImagePointer;

typedef unsigned int UIntPixelType;
typedef itk::Image<UIntPixelType, ImageDimension>   UIntImageType;
typedef UIntImageType::Pointer						UIntImagePointer;

typedef itk::Image<UIntPixelType, SliceDimension>  SliceUIntImageType;
typedef SliceUIntImageType::Pointer				   SliceUIntImagePointer;

typedef double DoublePixelType;
typedef itk::Image<DoublePixelType, ImageDimension> DoubleImageType; 
typedef DoubleImageType::Pointer					DoubleImagePointer;

typedef itk::Image<DoublePixelType, SliceDimension> SliceDoubleImageType;
typedef SliceDoubleImageType::Pointer				SliceDoubleImagePointer;

typedef itk::ImportImageFilter<ImagePixelType, ImageDimension> ImageFilterType;
typedef itk::ImportImageFilter<ImagePixelType, SliceDimension> SliceFilterType;
typedef itk::ImportImageFilter<CBImagePixelType, ImageDimension> CBImageFilterType;
typedef itk::ImportImageFilter<LabelPixelType, ImageDimension> LabelFilterType;
typedef itk::ImportImageFilter<LabelPixelType, SliceDimension> LabelSliceFilterType;
typedef itk::ImportImageFilter<FloatPixelType, ImageDimension> FloatFilterType;
typedef itk::ImportImageFilter<FloatPixelType, SliceDimension> FloatSliceFilterType;


typedef itk::ImageRegionIterator<ImageType> ImageRegionIteratorType;
typedef itk::ImageRegionIterator<LabelImageType> LabelRegionIteratorType;
typedef itk::ImageRegionIterator<SliceImageType> SliceImageRegionIteratorType;
typedef itk::ImageRegionIterator<SliceLabelImageType> SliceLabelRegionIteratorType;
typedef itk::ImageRegionIterator<ULongImageType> ULongRegionIteratorType;
typedef itk::ImageRegionIterator<LongImageType>  LongRegionIteratorType;
typedef itk::ImageRegionIteratorWithIndex<ImageType> ImageRegionIteratorWithIndexType;
typedef itk::ImageRegionIteratorWithIndex<LabelImageType> LabelRegionIteratorWithIndexType;
typedef itk::ImageRegionIteratorWithIndex<SliceImageType> SliceImageRegionIteratorWithIndexType;
typedef itk::ImageRegionIteratorWithIndex<SliceLabelImageType> SliceLabelRegionIteratorWithIndexType;
typedef itk::ImageLinearIteratorWithIndex<LabelImageType> LabelLinearIteratorWithIndexType;
typedef itk::ImageRegionIteratorWithIndex<ULongImageType> ULongRegionIteratorWithIndexType;
typedef itk::ImageLinearIteratorWithIndex<LongImageType>  LongRegionIteratorWithIndexType;




#endif //!__ITKGCOMMONDEFINE_H