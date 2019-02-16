#pragma once
#ifndef __CLASSIMAGEFILTERMIRCRO_H
#define __CLASSIMAGEFILTERMIRCRO_H

#include "BasicImageFilterObject.hxx"


#define IMAGE2DFILTERMACRO(ClassName, _Type, __PiexlType)                 \
class ClassName : public ImageFilterObject<_Type, 2>                      \
{                                                                         \
public:                                                                   \
	ClassName()                                                           \
	{                                                                     \
	}                                                                     \
	~ClassName()                                                          \
	{                                                                     \
	}                                                                     \
public:                                                                   \
	itk::Image<_Type, 2>::Pointer                                         \
		ReadImage(CPCHAR __path)                                          \
	{                                                                     \
		__clear_var();                                                    \
		__file_path__ = __path;                                           \
		__parse_path();                                                   \
		__PathType __pth_tp = __is_folder();                              \
	                                                                      \
		if(__PathType::dir_path == __pth_tp)                              \
		{                                                                 \
			__status__ = READ_IMAGE_FALIED;                               \
			__err_msg__ << "need a 2d file , but this is a dir";          \
			return nullptr;                                               \
		}                                                                 \
		return this->__read_one_file();                                   \
	}                                                                     \
                                                                          \
	itk::Image<itk::RGBPixel<_Type>, 2>::Pointer                          \
		ReadRgbImage(CPCHAR __path)                                       \
	{                                                                     \
		__file_path__ = __path;                                           \
		return this->__read_rgb_image();                                  \
	}                                                                     \
                                                                          \
	itk::Image<_Type, 2>::Pointer                                         \
		ReadImage(CPCHAR __path, DicomValue<_Type>& __dicom_vo)           \
	{                                                                     \
		load_image __ld_img;                                              \
		ImageHeader _img_head;                                            \
		__file_path__ = __path;                                           \
		__parse_path();                                                   \
		itk::Image<_Type, 2>::Pointer  __img =                            \
			__read_sigle_file_with_head(&_img_head, &__ld_img, true);     \
		if(SUCCESSED != __status__)                                       \
		{                                                                 \
			return __img;                                                 \
		}                                                                 \
		if(SUCCESSED == __ld_img.status)                                  \
		{                                                                 \
			__dicom_vo = __ld_img.result;                                 \
		}                                                                 \
		__dicom_vo.nx = _img_head.ImageSize[0];                           \
		__dicom_vo.ny = _img_head.ImageSize[1];                           \
		__dicom_vo.nz = _img_head.ImageSize[2];                           \
		__dicom_vo.dx = _img_head.spacing[0];                             \
		__dicom_vo.dy = _img_head.spacing[1];                             \
		__dicom_vo.dz = _img_head.spacing[2];                             \
		__dicom_vo.imagePosition = Point3f(                               \
			_img_head.origin[0],                                          \
			_img_head.origin[1],                                          \
			_img_head.origin[2]                                           \
		);                                                                \
                                                                          \
		for(size_t i = 0; i < 9; i++)                                     \
		{                                                                 \
			__dicom_vo.imageOrientation.push_back(_img_head.direction[i]);\
		}                                                                 \
			                                                              \
		return __img;                                                     \
	}                                                                     \
                                                                          \
	itk::Image<_Type, 2>::Pointer                                         \
		ImportImage(_Type* __buf, ImageHeader __hd, UINT& __bufLenth)     \
	{                                                                     \
		return this->ImportBufferToImage(__buf, __hd, __bufLenth);        \
	}                                                                     \
                                                                          \
	void                                                                  \
		SaveImage(itk::Image<_Type, 2>::Pointer __img_ptr,                \
				  CPCHAR __path, CPCHAR __name, CPCHAR __extent)          \
	{                                                                     \
		__clear_var();                                                    \
		if(_access(__path, 0) == -1)                                      \
		{                                                                 \
			__status__ = FILE_PATH_NOT_EXIST;                             \
			__err_msg__ << "path not exist";                              \
			return;                                                       \
		}                                                                 \
		if(false == __is_2d_fmt(__extent))                                \
		{                                                                 \
			__status__ = IMAGE_EXTENT_IS_NOT_MATCHED;                     \
			__err_msg__ << "image save format is incorrect";              \
			return;                                                       \
		}                                                                 \
			                                                              \
		CHAR __fname[_MAX_PATH] = { 0 };                                  \
		strcat(__fname, __path);                                          \
		if((__fname[strlen(__fname) - 1] != '\\') &&                      \
			(__fname[strlen(__fname) - 1] != '/'))                        \
		{                                                                 \
			strcat(__fname, "\\");                                        \
		}                                                                 \
		_StrStm_ __msg;                                                   \
		if(__name[0] == '\0')                                             \
		{                                                                 \
			__msg << clock();                                             \
			strcat(__fname, __msg.str().c_str());                         \
		}                                                                 \
		else                                                              \
		{                                                                 \
			strcat(__fname, __name);                                      \
		}                                                                 \
		strcat(__fname, __extent);                                        \
		this->__image_save(__img_ptr, __fname);                           \
	}                                                                     \
    itk::Image<_Type, 2>::Pointer                                         \
        VtkImageToItkImage(vtkSmartPointer<vtkDataSet> __itk_img)         \
    {                                                                     \
        itk::Image<_Type, 2>::Pointer __img_ptr =                         \
            __VtkImageToItkImage(__itk_img, __PiexlType);                 \
       CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(                     \
            GetStatus(), GetErrorMsg(), nullptr);                         \
       return __img_ptr;                                                  \
    }                                                                     \
};                                                                        \


#define IMAGE3DFILTERMACRO(ClassName, _Type, __PiexlType)                       \
class ClassName : public ImageFilterObject<_Type, 3>                            \
{                                                                               \
public:                                                                         \
	ClassName()                                                                 \
	{                                                                           \
                                                                                \
	}                                                                           \
	~ClassName()                                                                \
	{                                                                           \
                                                                                \
	}                                                                           \
                                                                                \
public:                                                                         \
	itk::Image<_Type, 3>::Pointer                                               \
		ReadImage(CPCHAR __path)                                                \
	{                                                                           \
		__clear_var();                                                          \
		__file_path__ = __path;                                                 \
		__parse_path();                                                         \
		__PathType __pth_tp = __is_folder();                                    \
                                                                                \
		if(__PathType::dir_path == __pth_tp)                                    \
		{                                                                       \
			return __read_series();                                             \
		}                                                                       \
                                                                                \
		return this->__read_one_file_3d();                                      \
	}                                                                           \
                                                                                \
	itk::Image< itk::RGBPixel<_Type>, 3> ::Pointer                              \
		ReadRgbImage(CPCHAR __path)                                             \
	{                                                                           \
		__clear_var();                                                          \
		__status__ = RGB_3D_NOT_SUPPORT;                                        \
		__err_msg__ << "not support RBG read for 3D image " <<__path;           \
		return nullptr;                                                         \
	}                                                                           \
                                                                                \
	itk::Image<_Type, 3> ::Pointer                                              \
		ReadImage(CPCHAR __path,  DicomValue<_Type>& __dicom_vo)                \
	{                                                                           \
		load_image __ld_img;                                                    \
		ImageHeader _img_head;                                                  \
		__file_path__ = __path;                                                 \
		__parse_path();                                                         \
		itk::Image<_Type, 3> ::Pointer  __img =                                 \
			__read_sigle_file_with_head(&_img_head, &__ld_img, true);           \
                                                                                \
		if(SUCCESSED != __status__)                                             \
		{                                                                       \
			return __img;                                                       \
		}                                                                       \
                                                                                \
		if(SUCCESSED == __ld_img.status)                                        \
		{                                                                       \
			__dicom_vo = __ld_img.result;                                       \
		}                                                                       \
                                                                                \
		__dicom_vo.nx = _img_head.ImageSize[0];                                 \
		__dicom_vo.ny = _img_head.ImageSize[1];                                 \
		__dicom_vo.nz = _img_head.ImageSize[2];                                 \
		__dicom_vo.dx = _img_head.spacing[0];                                   \
		__dicom_vo.dy = _img_head.spacing[1];                                   \
		__dicom_vo.dz = _img_head.spacing[2];                                   \
		__dicom_vo.imagePosition = Point3f(                                     \
			_img_head.origin[0],                                                \
			_img_head.origin[1],                                                \
			_img_head.origin[2]                                                 \
		);                                                                      \
                                                                                \
		for(size_t i = 0; i < 9; i++)                                           \
		{                                                                       \
			__dicom_vo.imageOrientation.push_back(                              \
				_img_head.direction[i]);                                        \
		}                                                                       \
                                                                                \
		return __img;                                                           \
	}                                                                           \
                                                                                \
	itk::Image<_Type, 3> ::Pointer                                              \
		ImportImage(_Type* __buf, ImageHeader __hd, UINT& __bufLenth)           \
	{                                                                           \
		return this->ImportBufferToImage(__buf, __hd, __bufLenth);              \
	}                                                                           \
	void                                                                        \
		SaveImage(itk::Image<_Type, 3>::Pointer __img_ptr,                      \
				  CPCHAR __path, CPCHAR __name, CPCHAR __extent)                \
	{                                                                           \
		__clear_var();                                                          \
		if(_access(__path, 0) == -1)                                            \
		{                                                                       \
			__status__ = FILE_PATH_NOT_EXIST;                                   \
			__err_msg__ << "path not exist";                                    \
			return;                                                             \
		}                                                                       \
		if(false == __is_2d_fmt(__extent))                                      \
		{                                                                       \
			__status__ = IMAGE_EXTENT_IS_NOT_MATCHED;                           \
			__err_msg__ << "image save format is incorrect";                    \
			return;                                                             \
		}                                                                       \
                                                                                \
		CHAR __fname[_MAX_PATH] = { 0 };                                        \
		strcat(__fname, __path);                                                \
		if((__fname[strlen(__fname) - 1] != '\\') &&                            \
			(__fname[strlen(__fname) - 1] != '/'))                              \
		{                                                                       \
			strcat(__fname, "\\");                                              \
		}                                                                       \
		_StrStm_ __msg;                                                         \
		if(__name[0] == '\0')                                                   \
		{                                                                       \
			__msg << clock();                                                   \
			strcat(__fname, __msg.str().c_str());                               \
		}                                                                       \
		else                                                                    \
		{                                                                       \
			strcat(__fname, __name);                                            \
		}                                                                       \
		strcat(__fname, __extent);                                              \
		this->__image_save(__img_ptr, __fname);                                 \
	}                                                                           \
    itk::Image<_Type, 3>::Pointer                                               \
        VtkImageToItkImage(vtkSmartPointer<vtkDataSet> __itk_img)               \
    {                                                                           \
       itk::Image<_Type, 3>::Pointer __img_ptr =                                \
            __VtkImageToItkImage(__itk_img, __PiexlType);                       \
       CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(                           \
            GetStatus(), GetErrorMsg(), nullptr);                               \
       return __img_ptr;                                                        \
    }                                                                           \
};                                                                              \


#define IMAGEFILTER_3D(name, _type, __pixel)  IMAGE3DFILTERMACRO(name##ImageFilter, _type, __pixel)
#define IMAGEFILTER_2D(name, _type, __pixel)  IMAGE2DFILTERMACRO(Slice##name##ImageFilter, _type, __pixel)



#endif // !__CLASSIMAGEFILTERMIRCRO_H
