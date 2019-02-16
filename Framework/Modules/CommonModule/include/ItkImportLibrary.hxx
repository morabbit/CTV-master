#pragma once
#ifndef __ITKGIMPORTHEADER_h
#define __ITKGIMPORTHEADER_h


#include <string>

#include <itkTwoProjectionImageRegistrationMethod.h>

// The transformation used is a rigid 3D Euler transform with the
// provision of a center of rotation which defaults to the center of
// the 3D volume. In practice the center of the particular feature of
// interest in the 3D volume should be used.

#include <itkEuler3DTransform.h>

// We have chosen to implement the registration using the normalized coorelation
// similarity measure.

//#include "itkGradientDifferenceTwoImageToOneImageMetric.h"
#include <itkNormalizedCorrelationTwoImageToOneImageMetric.h>

// This is an intensity based registration algorithm so ray casting is
// used to project the 3D volume onto pixels in the target 2D image.
#include <itkSiddonJacobsRayCastInterpolateImageFunction.h>

// Finally the Powell optimizer is used to avoid requiring gradient information.
#include <itkPowellOptimizer.h>

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

#include <itkResampleImageFilter.h>
#include <itkCastImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkFlipImageFilter.h>

#include <itkCommand.h>
#include <itkTimeProbesCollectorBase.h>

#include <itkNeighborhoodAlgorithm.h>
#include <itkMatrix.h>
#include <itkMatrixOffsetTransformBase.h>

#include <itkMetaImageIOFactory.h>
#include <itkShiftScaleImageFilter.h>
#include <itkLinearInterpolateImageFunction.h>
#include <itkImageToVTKImageFilter.h>
#include <itkVTKImageToImageFilter.h>

#include <itkRGBPixel.h>
#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>
#include <itkImageSeriesReader.h>

#include <itkNiftiImageIO.h>


#endif // !__ITKGIMPORTHEADER_h