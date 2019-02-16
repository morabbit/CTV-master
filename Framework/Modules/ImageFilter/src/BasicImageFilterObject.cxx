#include "pch.h"

#ifndef __BASICIMAGEFILTEROBJECT_CXX
#define __BASICIMAGEFILTEROBJECT_CXX

#include "..\include\BasicImageFilterObject.hxx"


template<class _Type, UINT _Dims>
ImageFilterObject<_Type, _Dims>::ImageFilterObject()
{
}
template<class _Type, UINT _Dims>
ImageFilterObject<_Type, _Dims>::~ImageFilterObject()
{
}

template<class _Type, UINT _Dims>
inline NTSTATUS ImageFilterObject<_Type, _Dims>::GetResultStatus()
{
	return __status__;
}
template<class _Type, UINT _Dims>
inline _String ImageFilterObject<_Type, _Dims>::GetResultErrorMsg()
{
	return __err_msg__.str();
}
template<class _Type, UINT _Dims>
inline vtkSmartPointer<vtkImageData>
ImageFilterObject<_Type, _Dims>::DicomFastReading(CPCHAR __path, PFLOAT& __direct)
{
	__clear_var();
	__f_file_path__ = __path;
	__f_dims__ = _Dims;
	__PathType __file_type = __is_folder(__path);

	vtkSmartPointer<vtkImageData> __vtk_img;
	if(!(/*not >>*/
		(/*3D -->*/(3 == _Dims) && (__file_type == __PathType::dir_path) /*3D <--*/) ||
	   (/*2D -->*/(2 == _Dims) && (__file_type == __PathType::File_path)/*2D <--*/)
	   /*not <<*/)
	   )
	{
		__status__ = READ_IMAGE_FALIED;
		__err_msg__ << "file path error";
		return nullptr;
	}
	try
	{
		__vtk_img = vtkDicomFastReading(__direct);
	}
	catch(const std::exception& err)
	{
		if(__fread_err_code__ == vtkErrorCode::FileFormatError)
		{
			__direct = nullptr;
			typename itk::Image<_Type, _Dims>::Pointer __img_ptr = ReadImage(__path);
			CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(__status__, __err_msg__.str(), nullptr);

			__direct = (PFLOAT)MallocMemroy(9 * sizeof(FLOAT));
			typename itk::Image<_Type, _Dims>::DirectionType __src_direct = __img_ptr->GetDirection();
			for(UINT i = 0; i < __src_direct.RowDimensions; i++)
			{
				for(UINT j = 0; j < __src_direct.ColumnDimensions; j++)
				{
					__direct[i*__src_direct.RowDimensions + j] = __src_direct[i][j];
				}
			}
			__direct[4] = -1;
			//return DataTransform<itk::Image<_Type, _Dims>>::ItkImageToVtkImage(__img_ptr);
			return ItkImageToVtkImage(__img_ptr);
		}
		else
		{
			__direct = nullptr;
			__status__ = __f_status__;
			__err_msg__ << __f_err_msg__.str();
			return nullptr;
		}
	}

	vtkSmartPointer<vtkImageData> imageflip_z
		= RevolveAroundAxis(__vtk_img, COORDINATE_AXIS_Z);
	vtkSmartPointer<vtkImageData> imageflip_x
		= RevolveAroundAxis(imageflip_z, COORDINATE_AXIS_X);

	__direct[0] = -1;
	__direct[8] = -1;

	return imageflip_x;
}

template<class _Type, UINT _Dims>
inline vtkSmartPointer<vtkImageData>
ImageFilterObject<_Type, _Dims>::DicomFastReading(CPCHAR __path, DicomValue<_Type> & __dicom_vo)
{
	load_image __ld;
	HANDLE hHand = nullptr;
	ImageHeader  __out_head;
	__ld.path = __file_path__;
	hHand = CreateThread(0, 0, ::LoadImageProc, &__ld, 0, 0);

	PFLOAT __direct;
	vtkSmartPointer<vtkImageData> __vtk_img = DicomFastReading(__path, __direct);
	fillImageHead(__out_head, __vtk_img, __direct);

	WaitForSingleObject(hHand, INFINITE);
	fillDicomVo(__dicom_vo, __out_head, &__ld);
	hHand != nullptr ? CloseHandle(hHand) : 0;
	FreeMemory(&__direct);

	return __vtk_img;
}

template<class _Type, UINT _Dims>
inline __PathType ImageFilterObject<_Type, _Dims>::GetPathType(CPCHAR __path)
{
	return __is_folder(__path);
}

template<class _Type, UINT _Dims>
vtkSmartPointer<vtkAlgorithmOutput>
ImageFilterObject<_Type, _Dims>::ObjPortFastReading(CPCHAR __path)
{
	__clear_var();
	__file_path__ = __path;
	__f_file_path__ = __path;
	__f_dims__ = _Dims;
	__dims__ = _Dims;

	__parse_path(__path);
	CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
		__status__,
		__err_msg__.str(),
		nullptr
	);

	__PathType __file_type = __is_folder(__path);
	if(__PathType::File_path != __file_type)
	{
		__status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__err_msg__ << "can not find a .mhd file";
		return nullptr;
	}

	vtkSmartPointer<vtkAlgorithmOutput> __vtk_img = nullptr;
	try {
		__vtk_img = vtkObjPortFastReading();
	}
	catch(const std::exception& err) {
		__status__ = __f_status__;
		__err_msg__ = _StrStm_();
		__err_msg__ << __f_err_msg__.str();
		return nullptr;
	}

	return __vtk_img;
}

template<class _Type, UINT _Dims>
vtkSmartPointer<vtkPolyData> ImageFilterObject<_Type, _Dims>::ObjFastReading(CPCHAR __path)
{
	__clear_var();
	__file_path__ = __path;
	__f_file_path__ = __path;
	__f_dims__ = _Dims;
	__dims__ = _Dims;

	__parse_path(__path);
	CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
		__status__,
		__err_msg__.str(),
		nullptr
	);

	__PathType __file_type = __is_folder(__path);
	if(__PathType::File_path != __file_type)
	{
		__status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__err_msg__ << "can not find a .mhd file";
		return nullptr;
	}

	vtkSmartPointer<vtkPolyData> __vtk_img = nullptr;
	try {
		__vtk_img = vtkObjFastReading();
	}
	catch(const std::exception& err) {
		__status__ = __f_status__;
		__err_msg__ = _StrStm_();
		__err_msg__ << __f_err_msg__.str();
		return nullptr;
	}

	return __vtk_img;
}

template<class _Type, UINT _Dims>
inline vtkSmartPointer<vtkImageData>
ImageFilterObject<_Type, _Dims>::MetaFastReading(CPCHAR __path)
{
	__clear_var();
	__file_path__ = __path;
	__f_file_path__ = __path;
	__f_dims__ = _Dims;
	__dims__ = _Dims;

	__parse_path(__path);
	CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
		__status__,
		__err_msg__.str(),
		nullptr
	);

	__PathType __file_type = __is_folder(__path);
	if(__PathType::File_path != __file_type)
	{
		__status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__err_msg__ << "can not find a .mhd file";
		return nullptr;
	}

	vtkSmartPointer<vtkImageData> __vtk_img;

	try
	{
		__vtk_img = vtkMetaFastReading();
	}
	catch(const std::exception& err)
	{
		if(__fread_err_code__ == vtkErrorCode::FileFormatError)
		{
			typename itk::Image<_Type, _Dims>::Pointer __img_ptr = ReadImage(__path);
			CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
				__status__,
				__err_msg__.str(),
				nullptr
			);
			//return DataTransform<itk::Image<_Type, _Dims>>::ItkImageToVtkImage(__img_ptr);
			return ItkImageToVtkImage(__img_ptr);
		}
		else
		{
			__status__ = __f_status__;
			__err_msg__ << __f_err_msg__.str();
			return nullptr;
		}
	}

	vtkSmartPointer<vtkImageData> imageflip_z
		= RevolveAroundAxis(__vtk_img, COORDINATE_AXIS_Z);
	vtkSmartPointer<vtkImageData> imageflip_x
		= RevolveAroundAxis(imageflip_z, COORDINATE_AXIS_X);

	return imageflip_x;
}

template<class _Type, UINT _Dims>
inline vtkSmartPointer<vtkImageData> ImageFilterObject<_Type, _Dims>::BmpFastReading(CPCHAR __path)
{
	__clear_var();
	__file_path__ = __path;
	__f_file_path__ = __path;
	__f_dims__ = _Dims;
	__dims__ = _Dims;

	__parse_path(__path);
	CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
		__status__,
		__err_msg__.str(),
		nullptr
	);

	__PathType __file_type = __is_folder(__path);
	if(__PathType::File_path != __file_type)
	{
		__status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__err_msg__ << "can not find a .mhd file";
		return nullptr;
	}

	vtkSmartPointer<vtkImageData> __vtk_img;

	try
	{
		__vtk_img = vtkBmpFastReading();
	}
	catch(const std::exception& err)
	{
		if(__fread_err_code__ == vtkErrorCode::FileFormatError)
		{
			typename itk::Image<_Type, _Dims>::Pointer __img_ptr = __read_one_file();
			CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
				__status__,
				__err_msg__.str(),
				nullptr
			);
			//return DataTransform<itk::Image<_Type, _Dims>>::ItkImageToVtkImage(__img_ptr);
			return ItkImageToVtkImage(__img_ptr);
		}
		else
		{
			__status__ = __f_status__;
			__err_msg__ << __f_err_msg__.str();
			return nullptr;
		}
	}

	vtkSmartPointer<vtkImageData> imageflip_z
		= RevolveAroundAxis(__vtk_img, COORDINATE_AXIS_Z);
	vtkSmartPointer<vtkImageData> imageflip_x
		= RevolveAroundAxis(imageflip_z, COORDINATE_AXIS_X);

	return imageflip_x;
}

template<class _Type, UINT _Dims>
inline vtkSmartPointer<vtkImageData> ImageFilterObject<_Type, _Dims>::JpegFastReading(CPCHAR __path)
{
	__clear_var();
	__file_path__ = __path;
	__f_file_path__ = __path;
	__f_dims__ = _Dims;
	__dims__ = _Dims;

	__parse_path(__path);
	CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
		__status__,
		__err_msg__.str(),
		nullptr
	);

	__PathType __file_type = __is_folder(__path);
	if(__PathType::File_path != __file_type)
	{
		__status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__err_msg__ << "can not find a .mhd file";
		return nullptr;
	}

	vtkSmartPointer<vtkImageData> __vtk_img;

	try
	{
		__vtk_img = vtkJpegFastReading();
	}
	catch(const std::exception& err)
	{
		if(__fread_err_code__ == vtkErrorCode::FileFormatError)
		{
			typename itk::Image<_Type, _Dims>::Pointer __img_ptr = __read_one_file();
			CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
				__status__,
				__err_msg__.str(),
				nullptr
			);
			//return DataTransform<itk::Image<_Type, _Dims>>::ItkImageToVtkImage(__img_ptr);
			return ItkImageToVtkImage(__img_ptr);
		}
		else
		{
			__status__ = __f_status__;
			__err_msg__ << __f_err_msg__.str();
			return nullptr;
		}
	}

	vtkSmartPointer<vtkImageData> imageflip_z
		= RevolveAroundAxis(__vtk_img, COORDINATE_AXIS_Z);
	vtkSmartPointer<vtkImageData> imageflip_x
		= RevolveAroundAxis(imageflip_z, COORDINATE_AXIS_X);

	return imageflip_x;
}

template<class _Type, UINT _Dims>
inline vtkSmartPointer<vtkImageData> ImageFilterObject<_Type, _Dims>::PngFastReading(CPCHAR __path)
{
	__clear_var();
	__file_path__ = __path;
	__f_file_path__ = __path;
	__f_dims__ = _Dims;
	__dims__ = _Dims;

	__parse_path(__path);
	CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
		__status__,
		__err_msg__.str(),
		nullptr
	);

	__PathType __file_type = __is_folder(__path);
	if(__PathType::File_path != __file_type)
	{
		__status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__err_msg__ << "can not find a .mhd file";
		return nullptr;
	}

	vtkSmartPointer<vtkImageData> __vtk_img;

	try
	{
		__vtk_img = vtkPngFastReading();
	}
	catch(const std::exception& err)
	{
		if(__fread_err_code__ == vtkErrorCode::FileFormatError)
		{
			typename itk::Image<_Type, _Dims>::Pointer __img_ptr = __read_one_file();
			CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
				__status__,
				__err_msg__.str(),
				nullptr
			);
			//return DataTransform<itk::Image<_Type, _Dims>>::ItkImageToVtkImage(__img_ptr);
			return ItkImageToVtkImage(__img_ptr);
		}
		else
		{
			__status__ = __f_status__;
			__err_msg__ << __f_err_msg__.str();
			return nullptr;
		}
	}

	vtkSmartPointer<vtkImageData> imageflip_z
		= RevolveAroundAxis(__vtk_img, COORDINATE_AXIS_Z);
	vtkSmartPointer<vtkImageData> imageflip_x
		= RevolveAroundAxis(imageflip_z, COORDINATE_AXIS_X);

	return imageflip_x;
}

template<class _Type, UINT _Dims>
inline vtkSmartPointer<vtkImageData> ImageFilterObject<_Type, _Dims>::TiffFastReading(CPCHAR __path)
{
	__clear_var();
	__file_path__ = __path;
	__f_file_path__ = __path;
	__f_dims__ = _Dims;
	__dims__ = _Dims;

	__parse_path(__path);
	CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
		__status__,
		__err_msg__.str(),
		nullptr
	);

	__PathType __file_type = __is_folder(__path);
	if(__PathType::File_path != __file_type)
	{
		__status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__err_msg__ << "can not find a .mhd file";
		return nullptr;
	}

	vtkSmartPointer<vtkImageData> __vtk_img;

	try
	{
		__vtk_img = vtkTiffFastReading();
	}
	catch(const std::exception& err)
	{
		if(__fread_err_code__ == vtkErrorCode::FileFormatError)
		{
			typename itk::Image<_Type, _Dims>::Pointer __img_ptr = __read_one_file();
			CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
				__status__,
				__err_msg__.str(),
				nullptr
			);
			//return DataTransform<itk::Image<_Type, _Dims>>::ItkImageToVtkImage(__img_ptr);
			return ItkImageToVtkImage(__img_ptr);
		}
		else
		{
			__status__ = __f_status__;
			__err_msg__ << __f_err_msg__.str();
			return nullptr;
		}
	}

	vtkSmartPointer<vtkImageData> imageflip_z
		= RevolveAroundAxis(__vtk_img, COORDINATE_AXIS_Z);
	vtkSmartPointer<vtkImageData> imageflip_x
		= RevolveAroundAxis(imageflip_z, COORDINATE_AXIS_X);

	return imageflip_x;
}

template<class _Type, UINT _Dims>
inline vtkSmartPointer<vtkImageData> ImageFilterObject<_Type, _Dims>::RawFastReading(CPCHAR __path)
{
	__clear_var();
	__file_path__ = __path;
	__f_file_path__ = __path;
	__f_dims__ = _Dims;
	__dims__ = _Dims;

	__parse_path(__path);
	CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
		__status__,
		__err_msg__.str(),
		nullptr
	);

	__PathType __file_type = __is_folder(__path);
	if(__PathType::File_path != __file_type)
	{
		__status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__err_msg__ << "can not find a .mhd file";
		return nullptr;
	}

	vtkSmartPointer<vtkImageData> __vtk_img;

	try
	{
		__vtk_img = vtkRawFastReading();
	}
	catch(const std::exception& err)
	{
		if(__fread_err_code__ == vtkErrorCode::FileFormatError)
		{
			typename itk::Image<_Type, _Dims>::Pointer __img_ptr = __read_one_file();
			CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
				__status__,
				__err_msg__.str(),
				nullptr
			);
			//return DataTransform<itk::Image<_Type, _Dims>>::ItkImageToVtkImage(__img_ptr);
			return ItkImageToVtkImage(__img_ptr);
		}
		else
		{
			__status__ = __f_status__;
			__err_msg__ << __f_err_msg__.str();
			return nullptr;
		}
	}

	vtkSmartPointer<vtkImageData> imageflip_z
		= RevolveAroundAxis(__vtk_img, COORDINATE_AXIS_Z);
	vtkSmartPointer<vtkImageData> imageflip_x
		= RevolveAroundAxis(imageflip_z, COORDINATE_AXIS_X);

	return imageflip_x;
}

template<class _Type, UINT _Dims>
inline void
ImageFilterObject<_Type, _Dims>::fillDicomVo(
	DicomValue<_Type>& __dicom_vo, ImageHeader __hd, load_image* __ld)
{
	__dicom_vo = __ld->result;
	__dicom_vo.nx = __hd.ImageSize[0];
	__dicom_vo.ny = __hd.ImageSize[1];
	__dicom_vo.nz = __hd.ImageSize[2];
	__dicom_vo.dx = __hd.spacing[0];
	__dicom_vo.dy = __hd.spacing[1];
	__dicom_vo.dz = __hd.spacing[2];
	__dicom_vo.imagePosition = Point3f(
		__hd.origin[0],
		__hd.origin[1],
		__hd.origin[2]
	);

	for(size_t i = 0; i < 9; i++)
	{
		__dicom_vo.imageOrientation.push_back(__hd.direction[i]);
	}
}

template<class _Type, UINT _Dims>
inline void
ImageFilterObject<_Type, _Dims>::fillImageHead(
	ImageHeader& __hd, vtkSmartPointer<vtkImageData> __dt, PFLOAT __direct)
{

	double* __origin = __dt->GetOrigin();
	__hd.origin[0] = __origin[0];
	__hd.origin[1] = __origin[1];
	__hd.origin[2] = (_Dims == 3) ? __origin[2] : 0;

	double* __spcing = __dt->GetSpacing();
	__hd.spacing[0] = __spcing[0];
	__hd.spacing[1] = __spcing[1];
	__hd.spacing[2] = (_Dims == 3) ? __spcing[2] : 0;

	INT __img_size[3] = { 0 };
	__dt->GetDimensions(__img_size);
	__hd.ImageSize[0] = (ULONG)__img_size[0];
	__hd.ImageSize[1] = (ULONG)__img_size[1];
	__hd.ImageSize[2] = (ULONG)__img_size[2];

	for(UINT i = 0; i < 9; i++)
	{
		if(__direct = nullptr)
		{
			__hd.direction[i] = 0;
		}
		else
		{
			__hd.direction[i] = __direct[i];
		}
	}
}


#endif // !__BASICIMAGEFILTEROBJECT_CXX
