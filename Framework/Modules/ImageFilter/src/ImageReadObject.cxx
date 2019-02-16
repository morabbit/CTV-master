#include "pch.h"

#ifndef __IMAGEREADOBJECT_CXX
#define __IMAGEREADOBJECT_CXX
#include "..\include\ImageReadObject.hxx"


template<class _Type, UINT _ImageDiemsion>
ImageReadWriteObject<_Type, _ImageDiemsion >::ImageReadWriteObject()
{
	__dims__ = _ImageDiemsion;
	__status__ = SUCCESSED;
	ZeroMemory(__ext__, _MAX_EXT);
	ZeroMemory(__fname__, _MAX_FNAME);
	__regist_io_factory();
}

template<class _Type, UINT _ImageDiemsion>
ImageReadWriteObject<_Type, _ImageDiemsion >::~ImageReadWriteObject()
{
	__unregist_io_factory();
}

template<class _Type, UINT _ImageDiemsion>
inline typename itk::Image<_Type, _ImageDiemsion>::Pointer
ImageReadWriteObject<_Type, _ImageDiemsion>::itkReadImage(CPCHAR __path)
{
	__clear_var();
	__file_path__ = __path;
	__parse_path();
	__PathType __pth_tp = __is_folder();

	if(__PathType::Unknown_path == __pth_tp)
	{
		__status__ = FILE_PATH_NOT_EXIST;
		__err_msg__ << "file path is not exist";
		return nullptr;
	}

	if(__PathType::dir_path == __pth_tp)
	{
		if(__dims__ == 2)
		{
			__status__ = READ_IMAGE_FALIED;
			__err_msg__ << "need a 2d file , but this is a dir";
			return nullptr;
		}
		else
		{
			return __read_series();
		}
	}

	return __read_one_file();
}

template<class _Type, UINT _ImageDiemsion>
inline typename itk::Image<_Type, _ImageDiemsion>::Pointer
ImageReadWriteObject<_Type, _ImageDiemsion>::itkReadRgbImage(CPCHAR __path)
{
	__file_path__ = __path;
	return __read_rgb_image();
}

template<class _Type, UINT _ImageDiemsion>
inline typename itk::Image<_Type, _ImageDiemsion>::Pointer
ImageReadWriteObject<_Type, _ImageDiemsion>::ImportBufferToImage(
	_Type * _buf, ImageHeader _head, UINT & bufLenth)
{
	typedef itk::ImportImageFilter<_Type, _ImageDiemsion>  ImportFilterType;
	typename ImportFilterType::Pointer __import_filter = ImportFilterType::New();
	typename ImportFilterType::SizeType  __size;
	typename ImportFilterType::IndexType __start;
	typename ImportFilterType::RegionType __region;
	typename ImportFilterType::DirectionType __direct;
	UINT __numberOfPixels = 1;
	__clear_var();
	for(UINT i = 0; i < ImageDimension; i++) {
		__size[i] = _head.ImageSize[i];
		__numberOfPixels *= __size[i];
	}

	bufLenth = __numberOfPixels;
	for(UINT i = 0; i < __direct.RowDimensions; i++) {
		for(UINT j = 0; j < __direct.ColumnDimensions; j++) {
			__direct[i][j] = _head.direction[i * __direct.RowDimensions + j];
		}
	}
	__start.Fill(0);
	__region.SetSize(__size);
	__region.SetIndex(__start);
	__import_filter->SetRegion(__region);
	__import_filter->SetDirection(__direct);
	__import_filter->SetOrigin(_head.origin);
	__import_filter->SetSpacing(_head.spacing);
	__import_filter->SetImportPointer(_buf, __numberOfPixels, false);

	try
	{
		__import_filter->Update();
	}
	catch(const itk::ExceptionObject & err)
	{
		__status__ = IMPORT_BUFFER_TO_IMAGE_FAILED;
		__err_msg__ << "ExceptionObject caught !\n" << err.what();
	}

	return __import_filter->GetOutput();;
}

template<class _Type, UINT _ImageDiemsion>
inline void ImageReadWriteObject<_Type, _ImageDiemsion>::itkSaveImage(
	itkImagePtr __img_ptr, CPCHAR __path, CPCHAR __name, CPCHAR __extent)
{
	__clear_var();
	if(_access(__path, 0) == -1)
	{
		__status__ = FILE_PATH_NOT_EXIST;
		__err_msg__ << "path not exist";
		return;
	}

	__write_image(__img_ptr, __path, __name, __extent);
}


template<class _Type, UINT _ImageDiemsion>
inline typename itk::Image<_Type, _ImageDiemsion>::Pointer
ImageReadWriteObject<_Type, _ImageDiemsion>::__read_one_file()
{
	typedef itk::ImageFileReader <itkImageType> ImageReader;
	typename ImageReader::Pointer __reader = ImageReader::New();
	__clear_var();
	__reader->SetFileName(__file_path__);
	try
	{
		__reader->Update();
	}
	catch(const itk::ExceptionObject & err)
	{
		__status__ = READ_IMAGE_FALIED;
		__err_msg__ << "ExceptionObject caught !\n" << err.what();
		return nullptr;
	}
	typedef itk::FlipImageFilter< itkImageType >  itkFilterType;
	typedef typename itkFilterType::FlipAxesArrayType   FlipAxesArrayType;
	typename itkFilterType::Pointer __filter = itkFilterType::New();
	FlipAxesArrayType __flipArray;

	__flipArray[0] = true;
	__flipArray[1] = true;
	if(_ImageDiemsion == 3)
	{
		__flipArray[2] = false;
	}
	__filter->SetFlipAxes(__flipArray);
	__filter->SetInput(__reader->GetOutput());
	__filter->Update();

	return __filter->GetOutput();
}

template<class _Type, UINT _ImageDiemsion>
inline typename itk::Image<_Type, _ImageDiemsion>::Pointer
ImageReadWriteObject<_Type, _ImageDiemsion>::__read_one_file_3d()
{
	typedef itk::ImageSeriesReader <itkImageType> ImageReader;
	typename ImageReader::Pointer __reader = ImageReader::New();
	__clear_var();
	__reader->SetFileName(__file_path__);
	try
	{
		__reader->Update();
	}
	catch(const itk::ExceptionObject & err)
	{
		__status__ = READ_IMAGE_FALIED;
		__err_msg__ << "ExceptionObject caught !\n" << err.what();
		return nullptr;
	}
	typedef itk::FlipImageFilter< itkImageType >  itkFilterType;
	typedef typename itkFilterType::FlipAxesArrayType   FlipAxesArrayType;
	typename itkFilterType::Pointer __filter = itkFilterType::New();
	FlipAxesArrayType __flipArray;

	__flipArray[0] = true;
	__flipArray[1] = true;
	__flipArray[2] = false;
	__filter->SetFlipAxes(__flipArray);
	__filter->SetInput(__reader->GetOutput());
	__filter->Update();

	return __filter->GetOutput();
}

template<class _Type, UINT _ImageDiemsion>
inline typename itk::Image<_Type, _ImageDiemsion>::Pointer
ImageReadWriteObject<_Type, _ImageDiemsion>::__read_series()
{
	__clear_var();
	if(_ImageDiemsion < 3)
	{
		__status__ = READ_IMAGE_FALIED;
		__err_msg__ << "Image is not 3D  !\n";
		return nullptr;
	}

	typedef itk::ImageSeriesReader <itkImageType> ImageReader;
	typename ImageReader::Pointer __reader = ImageReader::New();
	typedef itk::GDCMSeriesFileNames SeriesFileNamesType;
	typedef SeriesFileNamesType::FileNamesContainerType ContainerType;
	SeriesFileNamesType::Pointer __series_files = SeriesFileNamesType::New();
	__series_files->SetInputDirectory(__file_path__);
	const ContainerType& __file_names = __series_files->GetInputFileNames();
	__reader->SetFileNames(__file_names);
	try
	{
		__reader->Update();
	}
	catch(const itk::ExceptionObject & err)
	{
		__status__ = READ_IMAGE_FALIED;
		__err_msg__ << "ExceptionObject caught !\n" << err.what();
		return nullptr;
	}

	typedef itk::FlipImageFilter< itkImageType >  itkFilterType;
	typedef typename itkFilterType::FlipAxesArrayType   FlipAxesArrayType;
	typename itkFilterType::Pointer __filter = itkFilterType::New();
	FlipAxesArrayType __flipArray;

	__flipArray[0] = true;
	__flipArray[1] = true;
	__flipArray[2] = false;
	__filter->SetFlipAxes(__flipArray);
	__filter->SetInput(__reader->GetOutput());
	__filter->Update();

	return __filter->GetOutput();
}

template<class _Type, UINT _ImageDiemsion>
inline typename itk::Image< itk::RGBPixel<_Type>, _ImageDiemsion>::Pointer
ImageReadWriteObject<_Type, _ImageDiemsion>::__read_rgb_image()
{
	__clear_var();
	if(false == __is_rgb_file())
	{
		return nullptr;
	}

	typedef itk::ImageFileReader<RGBImageType> RgbReader;
	typename RgbReader::Pointer __rgb_reader = RgbReader::New();
	__rgb_reader->SetFileName(__file_path__);

	try
	{
		__rgb_reader->Update();
	}
	catch(const itk::ExceptionObject & err)
	{
		__status__ = READ_IMAGE_FALIED;
		__err_msg__ << "ExceptionObject caught !\n" << err.what();
		return nullptr;
	}

	return __rgb_reader->GetOutput();
}

template<class _Type, UINT _ImageDiemsion>
inline std::shared_ptr<_Type>
ImageReadWriteObject<_Type, _ImageDiemsion>::__read_dicom_image(CPCHAR __path)
{
	__parse_path();
	if(__PathType::File_path != __is_folder(__path))
	{
		__status__ = READ_IMAGE_FALIED;
		__err_msg__ << "need dcm file only !\n";
		return nullptr;
	}
	ULONG __cbLength;
	DcmtkLoadImage<_Type> __load_img;
	__load_img.LoadFile(__file_path__);

	return __load_img.ReadDicomData(__path, __cbLength);
}

template<class _Type, UINT _ImageDiemsion>
inline typename itk::Image<_Type, _ImageDiemsion>::Pointer
ImageReadWriteObject<_Type, _ImageDiemsion>::__read_series_file_with_head(
	ImageHeader * __out_head, load_image* __ld, bool __b_get_name)
{
	HANDLE hHand;
	__clear_var();
	if(_ImageDiemsion < 3)
	{
		__status__ = READ_IMAGE_FALIED;
		__err_msg__ << "Image is not 3D  !\n";
		return nullptr;
	}

	typedef itk::ImageSeriesReader <itkImageType> ImageReader;
	typename ImageReader::Pointer __reader = ImageReader::New();
	typedef itk::GDCMSeriesFileNames SeriesFileNamesType;
	typedef SeriesFileNamesType::FileNamesContainerType ContainerType;
	SeriesFileNamesType::Pointer __series_files = SeriesFileNamesType::New();
	__series_files->SetInputDirectory(__file_path__);
	const ContainerType& __file_names = __series_files->GetInputFileNames();
	if(true == __b_get_name)
	{
		__ld->path = __file_names[0].c_str();
		hHand = CreateThread(0, 0, ::LoadImageProc, __ld, 0, 0);
	}

	__reader->SetFileNames(__file_names);
	try
	{
		__reader->Update();
	}
	catch(const itk::ExceptionObject & err)
	{
		__status__ = READ_IMAGE_FALIED;
		__err_msg__ << "ExceptionObject caught !\n" << err.what();
		return nullptr;
	}
	typedef itk::FlipImageFilter< itkImageType >  itkFilterType;
	typedef typename itkFilterType::FlipAxesArrayType   FlipAxesArrayType;
	typename itkFilterType::Pointer __filter = itkFilterType::New();
	FlipAxesArrayType __flipArray;

	__flipArray[0] = true;
	__flipArray[1] = true;
	__flipArray[2] = false;
	__filter->SetFlipAxes(__flipArray);
	__filter->SetInput(__reader->GetOutput());

	itkImagePtr __image_ptr = __filter->GetOutput();

	__fill_origion(__out_head->origin, __image_ptr->GetOrigin());
	__fill_spacing(__out_head->spacing, __image_ptr->GetSpacing());
	__fill_direct(__out_head->direction, __image_ptr->GetDirection());
	__fill_img_size(__out_head->ImageSize, __image_ptr->GetLargestPossibleRegion().GetSize());

	if(true == __b_get_name)
	{
		WaitForSingleObject(hHand, INFINITE);
		CloseHandle(hHand);
	}

	return __image_ptr;
}

template<class _Type, UINT _ImageDiemsion>
inline typename itk::Image<_Type, _ImageDiemsion>::Pointer
ImageReadWriteObject<_Type, _ImageDiemsion>::__read_sigle_file_with_head(
	ImageHeader * __out_head, load_image* __ld, bool __b_get_name)
{
	HANDLE hHand = nullptr;
	if(true == __b_get_name)
	{
		__ld->path = __file_path__;
		hHand = CreateThread(0, 0, ::LoadImageProc, __ld, 0, 0);
	}

	typedef itk::ImageSeriesReader <itkImageType> ImageReader;
	typename ImageReader::Pointer __reader = ImageReader::New();
	__clear_var();
	__reader->SetFileName(__file_path__);
	try
	{
		__reader->Update();
	}
	catch(const itk::ExceptionObject & err)
	{
		__status__ = READ_IMAGE_FALIED;
		__err_msg__ << "ExceptionObject caught !\n" << err.what();
		return nullptr;
	}
	typedef itk::FlipImageFilter< itkImageType >  itkFilterType;
	typedef typename itkFilterType::FlipAxesArrayType   FlipAxesArrayType;
	typename itkFilterType::Pointer __filter = itkFilterType::New();
	FlipAxesArrayType __flipArray;

	__flipArray[0] = true;
	__flipArray[1] = true;
	__filter->SetFlipAxes(__flipArray);
	__filter->SetInput(__reader->GetOutput());

	itkImagePtr __image_ptr = __filter->GetOutput();

	__fill_origion(__out_head, __image_ptr->GetOrigin());
	__fill_spacing(__out_head, __image_ptr->GetSpacing());
	__fill_direct(__out_head, __image_ptr->GetDirection());
	__fill_img_size(__out_head, __image_ptr->GetLargestPossibleRegion().GetSize());

	if(true == __b_get_name)
	{
		WaitForSingleObject(hHand, INFINITE);
		hHand != nullptr ? CloseHandle(hHand) : 0;
	}
	return __image_ptr;
}

template<class _Type, UINT _ImageDiemsion>
inline void ImageReadWriteObject<_Type, _ImageDiemsion>::__image_save(
	itkImagePtr __img_ptr, CPCHAR __fname)
{
	__clear_var();
	typedef itk::Image<_Type, _ImageDiemsion>   OutImageType;
	typedef itk::ImageFileWriter<OutImageType>  itkWriterType;
	typename itkWriterType::Pointer __writer = itkWriterType::New();
	__writer->SetFileName(__fname);
	__writer->SetInput(__img_ptr);
	try
	{
		__writer->Update();
	}
	catch(itk::ExceptionObject & err)
	{
		__status__ = WRITE_IMAGE_FALIED;
		__err_msg__ << "ExceptionObject caught !" << err.what();
	}
}

template<class _Type, UINT _ImageDiemsion>
inline void ImageReadWriteObject<_Type, _ImageDiemsion>::__write_image(
	itkImagePtr __img_ptr, CPCHAR _path, CPCHAR __name, CPCHAR __extent)
{
	__clear_var();
	bool __bret = false;
	if(2 == _ImageDiemsion)
	{
		__bret = __is_2d_fmt(__extent);
	}
	else
	{
		__bret = __is_3d_fmt(__extent);
	}

	if(false == __bret)
	{
		__status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__err_msg__ << "image save format is incorrect";
	}
	CHAR __fname[_MAX_PATH] = { 0 };
	strcat(__fname, _path);
	if((__fname[strlen(__fname) - 1] != '\\') &&
		(__fname[strlen(__fname) - 1] != '/'))
	{
		strcat(__fname, "\\");
	}

	_StrStm_ __msg;
	if(__name[0] == '\0')
	{
		__msg << (rand() + 123456);
		strcat(__fname, __msg.str().c_str());
	}
	else
	{
		strcat(__fname, __name);
	}
	strcat(__fname, __extent);

	__image_save(__img_ptr, __fname);
}

template<class _Type, UINT _ImageDiemsion>
inline void ImageReadWriteObject<_Type, _ImageDiemsion>::__fill_origion(
	ImageHeader* __hd, typename itkImageType::PointType __src_org)
{
	ZeroMemory(__hd->origin, 3 * sizeof(double));
	for(unsigned int i = 0; i < __src_org.Size(); i++)
	{
		__hd->origin[i] = __src_org[i];
	}
}

template<class _Type, UINT _ImageDiemsion>
inline void ImageReadWriteObject<_Type, _ImageDiemsion>::__fill_spacing(
	ImageHeader* __hd, typename itkImageType::SpacingType __src_spacing)
{
	ZeroMemory(__hd->spacing, 3 * sizeof(double));
	for(unsigned int i = 0; i < __src_spacing.Size(); i++)
	{
		__hd->spacing[i] = __src_spacing[i];
	}
}

template<class _Type, UINT _ImageDiemsion>
inline void ImageReadWriteObject<_Type, _ImageDiemsion>::__fill_img_size(
	ImageHeader* __hd, typename itkImageType::SizeType __src_size)
{
	ZeroMemory(__hd->ImageSize, 3 * sizeof(ULONG));
	for(ULONG i = 0; i < _ImageDiemsion; i++)
	{
		__hd->ImageSize[i] = __src_size[i];
	}
}

template<class _Type, UINT _ImageDiemsion>
inline void ImageReadWriteObject<_Type, _ImageDiemsion>::__fill_direct(
	ImageHeader* __hd, typename itkImageType::DirectionType __src_direct)
{
	ZeroMemory(__hd->direction, 9 * sizeof(double));
	for(UINT i = 0; i < __src_direct.RowDimensions; i++)
	{
		for(UINT j = 0; j < __src_direct.ColumnDimensions; j++)
		{
			__hd->direction[i*__src_direct.RowDimensions + j] = __src_direct[i][j];
		}
	}

}

template<class _Type, UINT _ImageDiemsion>
inline void ImageReadWriteObject<_Type, _ImageDiemsion>::__clear_var()
{
	__status__ = SUCCESSED;
	__err_msg__ = _StrStm_();
}

template<class _Type, UINT _ImageDiemsion>
inline void ImageReadWriteObject<_Type, _ImageDiemsion>::__regist_io_factory()
{
	itk::NiftiImageIOFactory::RegisterOneFactory(); // .nii
	itk::JPEGImageIOFactory::RegisterOneFactory(); // .jpeg
	itk::VTKImageIOFactory::RegisterOneFactory(); // .vtk
	itk::GDCMImageIOFactory::RegisterOneFactory(); // .dcm
	itk::PNGImageIOFactory::RegisterOneFactory();  // .png
	itk::BMPImageIOFactory::RegisterOneFactory();  // .bmp
	itk::TIFFImageIOFactory::RegisterOneFactory(); // .tiff  .tif
	itk::MetaImageIOFactory::RegisterOneFactory();  //.mhd
}

template<class _Type, UINT _ImageDiemsion>
inline void ImageReadWriteObject<_Type, _ImageDiemsion>::__unregist_io_factory()
{
	itk::NiftiImageIOFactory::UnRegisterAllFactories(); // .nii
	itk::JPEGImageIOFactory::UnRegisterAllFactories(); // .jpeg
	itk::VTKImageIOFactory::UnRegisterAllFactories(); // .vtk
	itk::GDCMImageIOFactory::UnRegisterAllFactories(); // .dcm
	itk::PNGImageIOFactory::UnRegisterAllFactories();  // .png
	itk::BMPImageIOFactory::UnRegisterAllFactories();  // .bmp
	itk::TIFFImageIOFactory::UnRegisterAllFactories(); // .tiff  .tif
	itk::MetaImageIOFactory::UnRegisterAllFactories();  //.mhd
}

template<class _Type, UINT _ImageDiemsion>
inline void ImageReadWriteObject<_Type, _ImageDiemsion>::__parse_path()
{
	__parse_path(__file_path__);
}

template<class _Type, UINT _ImageDiemsion>
inline void ImageReadWriteObject<_Type, _ImageDiemsion>::__parse_path(CPCHAR __path)
{
	__clear_var();
	if(_access(__path, 0) == -1)
	{
		__status__ = FILE_PATH_NOT_EXIST;
		__err_msg__ << "path not exist";
		return;
	}
	ZeroMemory(__ext__, _MAX_EXT);
	ZeroMemory(__fname__, _MAX_FNAME);
	char drive[_MAX_DRIVE], dir[_MAX_DIR];

	_splitpath(__path, drive, dir, __fname__, __ext__);
}

template<class _Type, UINT _ImageDiemsion>
inline bool ImageReadWriteObject<_Type, _ImageDiemsion>::__is_3d_fmt(CPCHAR __ext)
{
	for(UINT i = 0; i < ARRAYSIZE(__3d_write_fmt); i++)
	{
		if(0 == memcmp(__ext, __3d_write_fmt[i], strlen(__3d_write_fmt[i])))
		{
			return true;
		}
	}
	return false;
}

template<class _Type, UINT _ImageDiemsion>
inline bool ImageReadWriteObject<_Type, _ImageDiemsion>::__is_2d_fmt(CPCHAR __ext)
{
	for(UINT i = 0; i < ARRAYSIZE(__2d_write_fmt); i++)
	{
		if(0 == memcmp(__ext, __2d_write_fmt[i], strlen(__2d_write_fmt[i])))
		{
			return true;
		}
	}
	return false;
}

template<class _Type, UINT _ImageDiemsion>
inline bool ImageReadWriteObject<_Type, _ImageDiemsion>::__is_rgb_file()
{
	__clear_var();
	if(__PathType::File_path == __is_folder())
	{
		__parse_path();
		for(UINT i = 0; i < ARRAYSIZE(__rgb_fmt); i++)
		{
			if(0 == memcmp(__ext__, const_cast<PCHAR>(__rgb_fmt[i]), strlen(__ext__)))
			{
				return true;
			}
		}
	}

	__status__ = READ_IMAGE_FALIED;
	__err_msg__ << "need a RGB image, but now this is a path or this path is not exist!\n";

	return false;
}

template<class _Type, UINT _ImageDiemsion>
inline __PathType ImageReadWriteObject<_Type, _ImageDiemsion>::__is_folder(CPCHAR __path)
{
	if(_access(__path, 0) == -1)
	{
		__status__ = FILE_PATH_NOT_EXIST;
		__err_msg__ << "path not exist";

		return __PathType::Unknown_path;
	}

	WIN32_FIND_DATAA __fi_data;
	FindFirstFileA(__path, &__fi_data);
	if(__fi_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		return __PathType::dir_path;
	}

	return __PathType::File_path;
}

template<class _Type, UINT _ImageDiemsion>
inline __PathType ImageReadWriteObject<_Type, _ImageDiemsion>::__is_folder()
{
	return __is_folder(__file_path__);
}

template<class _Type, UINT _ImageDiemsion>
inline bool ImageReadWriteObject<_Type, _ImageDiemsion>::__validate_extent()
{
	if(__ext__[0] == '\0')
	{
		return false;
	}

	for(UINT i = 0; i < ARRAYSIZE(__dicom_file_fmt); i++)
	{
		if(0 == memcmp(const_cast<PCHAR>(__dicom_file_fmt[i]), __ext__, strlen(__ext__)))
		{
			return true;
		}
	}

	return false;
}

template<class _Type, UINT _ImageDiemsion>
inline bool ImageReadWriteObject<_Type, _ImageDiemsion>::__validate_path()
{
	if(__dims__ == 2)
	{
		return this->__validate_extent();
	}

	else if(__PathType::File_path == __is_folder())
	{
		/// 3d file: nii , nii.gz, tif, tiff, mhd
		PCHAR __3D_file[] = { ".nii", ".nii.gz", ".mhd", ".tif", ".tiff" };
		for(size_t i = 0; i < ARRAYSIZE(__3D_file); i++)
		{
			if(0 == memcmp(__ext__, __3D_file[i], strlen(__ext__)))
			{
				return true;
			}
		}
		return true;
	}
	else if(__PathType::dir_path == __is_folder())
	{
		return true;
	}

	return false;
}

#endif // !__IMAGEREADOBJECT_CXX
