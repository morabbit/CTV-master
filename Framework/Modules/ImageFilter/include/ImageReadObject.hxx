#pragma once
#ifndef __IMAGEREADOBJECT_H
#define __IMAGEREADOBJECT_H
#include "FrameWorkType.h"
#include "CommonModulesLibrary.hxx"
#include "itkCommonDefine.hxx" 
#include "FrameworkDefine.h"
#include <io.h>
//#include <itkGiplImageIOFactory.h>

#include <itkNIFTIImageIOFactory.h>
#include <itkJPEGImageIOFactory.h>
#include <itkVTKImageIOFactory.h>
#include <itkGDCMImageIOFactory.h>
#include <itkPNGImageIOFactory.h>
#include <itkBMPImageIOFactory.h>
#include <itkTIFFImageIOFactory.h>
#include <itkMetaImageIOFactory.h>
#include "LoadImageHead.h"



enum __PathType
{
	Unknown_path = -1,
	File_path = 0,
	dir_path = 2,
};

template<class _Type, UINT _ImageDiemsion = 2>
class ImageReadWriteObject
{
public:	
	typedef itk::Image<_Type, _ImageDiemsion> itkImageType;
	typedef typename itkImageType::Pointer itkImagePtr;
	typedef ImageReadWriteObject<_Type, _ImageDiemsion> Self;
	typedef itk::RGBPixel<_Type> RGBPixelType;
	typedef  itk::Image< RGBPixelType, _ImageDiemsion> RGBImageType;
	typedef typename RGBImageType::Pointer  RGBPointer;

public:
	ImageReadWriteObject();
	~ImageReadWriteObject();

public:	
	void __clear_var();
	void __parse_path();
	void __parse_path(CPCHAR __path);

	__PathType __is_folder();
	__PathType __is_folder(CPCHAR __path);
	
	itkImagePtr  __read_one_file();	
	itkImagePtr  __read_one_file_3d();
	itkImagePtr  __read_series();
	RGBPointer  __read_rgb_image();

	std::shared_ptr<_Type> __read_dicom_image(CPCHAR __path);

	itkImagePtr  __read_sigle_file_with_head(ImageHeader* __out_head,
											 load_image* __ld = &load_image(),
											 bool __b_get_name = false);
	itkImagePtr  __read_series_file_with_head(ImageHeader* __out_head,
											  load_image* __ld = &load_image(), 
											  bool __b_get_name=false);
	//itkImagePtr  __read_rgb_image(ImageHeader* __out_head);
	
	bool __is_3d_fmt(CPCHAR __ext);
	bool __is_2d_fmt(CPCHAR __ext);
	bool __is_rgb_file();

	itkImagePtr itkReadImage(CPCHAR __path);
	itkImagePtr itkReadRgbImage(CPCHAR __path);
	itkImagePtr ImportBufferToImage(_Type* __buf, 
									ImageHeader __head, UINT& __bufLenth);

	void __image_save(itkImagePtr __img_ptr, CPCHAR __fname);
	void itkSaveImage(itkImagePtr __img_ptr, CPCHAR _path, 
					  CPCHAR __name, CPCHAR __extent);

private:
	void __regist_io_factory();
	void __unregist_io_factory();
	
	bool __validate_path();
	bool __validate_extent();	
	
	void __write_image(itkImagePtr __img_ptr, CPCHAR _path,
					   CPCHAR __name, CPCHAR __extent);
	void __fill_origion(ImageHeader* __hd, typename itkImageType::PointType __src_org);
	void __fill_spacing(ImageHeader* __hd, typename itkImageType::SpacingType __src_spacing);
	void __fill_img_size(ImageHeader* __hd, typename itkImageType::SizeType __src_size);
	void __fill_direct(ImageHeader* __hd, typename itkImageType::DirectionType __src_direct);

private:
	CPCHAR __dicom_file_fmt[9] = { ".dcm", ".mhd", ".nii",
							 ".tif", ".tiff", ".png",
							 ".bmp", "jpeg", ".nii.gz" };
	CPCHAR __rgb_fmt[3] = { ".png", ".bmp", "jpeg" };
	CPCHAR __2d_write_fmt[5] = { ".mhd", ".dcm", ".png" , ".bmp", "jpeg"};
	CPCHAR __3d_write_fmt[5] = { ".mhd", ".nii", ".tif", ".tiff", ".nii.gz" };

public:
	UINT __dims__;
	NTSTATUS __status__;
	CPCHAR __file_path__;
	CHAR __ext__[_MAX_EXT];
	CHAR __fname__[_MAX_FNAME];
	_StrStm_ __err_msg__;
};

#include "..\src\ImageReadObject.cxx"
#endif // !__IMAGEREADOBJECT_H
