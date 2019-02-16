#pragma once
#ifndef __RECONDITEIMAGEFILTER_H
#define __RECONDITEIMAGEFILTER_H

#include "ClassImageFilterMacro.hxx"


/****************************************************
*************** Image Read Write Class **************
*****************************************************/

IMAGEFILTER_3D(Int, INT, VTK_INT)    // IntImageFilter
IMAGEFILTER_2D(Int, INT, VTK_INT)    // SliceIntImageFilter

IMAGEFILTER_3D(Uint, UINT, VTK_UNSIGNED_INT)  // UintImageFilter
IMAGEFILTER_2D(Uint, UINT, VTK_UNSIGNED_INT)  // SliceUintImageFilter

IMAGEFILTER_3D(Long, LONG, VTK_LONG)    // LongImageFilter
IMAGEFILTER_2D(Long, LONG, VTK_LONG)    // SliceLongImageFilter  

IMAGEFILTER_3D(Ulong, ULONG, VTK_UNSIGNED_LONG)  // UlongImageFilter
IMAGEFILTER_2D(Ulong, ULONG, VTK_UNSIGNED_LONG)  // SliceUlongImageFilter

IMAGEFILTER_3D(Double, DOUBLE, VTK_DOUBLE)  // DoubleImageFilter
IMAGEFILTER_2D(Double, DOUBLE, VTK_DOUBLE)  // SliceDoubleImageFilter

#endif // !__RECONDITEIMAGEFILTER_H
