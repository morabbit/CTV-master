#include "pch.h"
#include <vtkDICOMImageReader.h>
#include <vtkMetaImageReader.h>
#include <vtkBMPReader.h>
#include <vtkJPEGReader.h>
#include <vtkPNGReader.h>
#include <vtkTIFFReader.h>
#include <vtkImageReader.h>
#include <vtkOBJReader.h>
#include <vtkImageFlip.h>

#include "ContainerDefine.h"
#include "FrameCommonFunctionMacro.h"
#include "FrameworkErrorCode.h"
#include "..\..\ImageFilter\include\FastReadImage.h"


FastReading::FastReading()
{
	__f_status__ = SUCCESSED;
	__f_err_msg__ = _StrStm_();
	__fread_err_code__ = 0;
}

FastReading::~FastReading()
{
}

vtkSmartPointer<vtkImageData> FastReading::vtkDicomFastReading(PFLOAT& _direction)
{
	__clear_status();
	vtkSmartPointer<vtkDICOMImageReader> __reader =
		vtkSmartPointer<vtkDICOMImageReader>::New();
	if(2U == __f_dims__)
	{
		__reader->SetFileName(__f_file_path__);
	}
	else
	{
		__reader->SetDirectoryName(__f_file_path__);
	}
	
	__reader->Update();
	__fread_err_code__ = __reader->GetErrorCode();

	if(0 != __fread_err_code__)
	{
		_direction = nullptr;
		__f_status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__f_err_msg__ << "read DICOM failed, can not find a dicom file or dicom directory !";
		throw "read DICOM failed, can not find a dicom file or dicom directory !";
	}
	_direction = (PFLOAT)MallocMemroy(9 * sizeof(FLOAT));

	PFLOAT __direct = __reader->GetImageOrientationPatient();
	Vector3f vx(__direct[0], __direct[1], __direct[2]);
	Vector3f vy(__direct[3], __direct[4], __direct[5]);
	Vector3f vz = vx.cross(vy);
	_direction[0] = vx.x;
	_direction[1] = vx.y;
	_direction[2] = vx.z; 
	_direction[3] = vy.x;
	_direction[4] = vy.y;
	_direction[5] = vy.z;
	_direction[6] = vz.x;
	_direction[7] = vz.y;
	_direction[8] = vz.z;
	vtkSmartPointer<vtkImageData> __vtk_data = __reader->GetOutput();

	return __vtk_data;
}

vtkSmartPointer<vtkImageData> FastReading::vtkMetaFastReading()
{
	__clear_status();
	vtkSmartPointer<vtkMetaImageReader> __reader =
		vtkSmartPointer<vtkMetaImageReader>::New();
	__reader->SetFileName(__f_file_path__);
	__reader->Update();

	__fread_err_code__ = __reader->GetErrorCode();
	if(0 != __fread_err_code__)
	{
		__f_status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__f_err_msg__ << "read Meta failed, can not find a .mhd file !";
		throw "read Meta failed, can not find a .mhd file !";
	}
	return __reader->GetOutput();
}

vtkSmartPointer<vtkImageData> FastReading::vtkBmpFastReading()
{
	__clear_status();
	vtkSmartPointer<vtkBMPReader> __reader =
		vtkSmartPointer<vtkBMPReader>::New();
	__reader->SetFileName(__f_file_path__);
	__reader->Update();

	__fread_err_code__ = __reader->GetErrorCode();
	if(0 != __fread_err_code__)
	{
		__f_status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__f_err_msg__ << "read Meta failed, can not find a .bmp file !";
		throw "read Meta failed, can not find a .bmp file !";
	}

	return __reader->GetOutput();
}

vtkSmartPointer<vtkImageData> FastReading::vtkJpegFastReading()
{
	__clear_status();
	vtkSmartPointer<vtkJPEGReader> __reader =
		vtkSmartPointer<vtkJPEGReader>::New();
	__reader->SetFileName(__f_file_path__);
	__reader->Update();
	
	__fread_err_code__ = __reader->GetErrorCode();
	if(0 != __fread_err_code__)
	{
		__f_status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__f_err_msg__ << "read Meta failed, can not find a .jpg file !";
		throw "read Meta failed, can not find a .jpg file !";
	}

	return __reader->GetOutput();
}

vtkSmartPointer<vtkImageData> FastReading::vtkPngFastReading()
{
	//vtkPNGReader
	__clear_status();
	vtkSmartPointer<vtkPNGReader> __reader =
		vtkSmartPointer<vtkPNGReader>::New();
	__reader->SetFileName(__f_file_path__);
	__reader->Update();

	__fread_err_code__ = __reader->GetErrorCode();
	if(0 != __fread_err_code__)
	{
		__f_status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__f_err_msg__ << "read Meta failed, can not find a .png file !";
		throw "read Meta failed, can not find a .png file !";
	}

	return __reader->GetOutput();
}

vtkSmartPointer<vtkImageData> FastReading::vtkTiffFastReading()
{
	__clear_status();
	vtkSmartPointer<vtkTIFFReader> __reader =
		vtkSmartPointer<vtkTIFFReader>::New();
	__reader->SetFileName(__f_file_path__);
	__reader->Update();
	__fread_err_code__ = __reader->GetErrorCode();
	if(0 != __fread_err_code__)
	{
		__f_status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__f_err_msg__ << "read Meta failed, can not find a .tiff/tif file !";
		throw "read Meta failed, can not find a .tiff/.tif file !";
	}

	return __reader->GetOutput();
}

vtkSmartPointer<vtkImageData> FastReading::vtkRawFastReading()
{
	__clear_status();
	vtkSmartPointer<vtkImageReader> __reader =
		vtkSmartPointer<vtkImageReader>::New();
	__reader->SetFileName(__f_file_path__);
	__reader->Update();

	__fread_err_code__ = __reader->GetErrorCode();
	if(0 != __fread_err_code__)
	{
		__f_status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__f_err_msg__ << "read Meta failed, can not find a .raw file !";
		throw "read Meta failed, can not find a .raw file !";
	}

	return __reader->GetOutput();
}

vtkSmartPointer<vtkPolyData> FastReading::vtkObjFastReading()
{
	__clear_status();
	vtkSmartPointer<vtkOBJReader> __reader =
		vtkSmartPointer<vtkOBJReader>::New();
	__reader->SetFileName(__f_file_path__);
	__reader->Update();

	__fread_err_code__ = __reader->GetErrorCode();
	if(0 != __fread_err_code__)
	{
		__f_status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__f_err_msg__ << "read Meta failed, can not find a .obj file !";
		throw "read Meta failed, can not find a .obj file !";
	}

	return __reader->GetOutput();
}

vtkSmartPointer<vtkAlgorithmOutput>
FastReading::vtkObjPortFastReading()
{
	__clear_status();
	vtkSmartPointer<vtkOBJReader> __reader =
		vtkSmartPointer<vtkOBJReader>::New();
	__reader->SetFileName(__f_file_path__);
	__reader->Update();

	__fread_err_code__ = __reader->GetErrorCode();
	if(0 != __fread_err_code__)
	{
		__f_status__ = IMAGE_EXTENT_IS_NOT_MATCHED;
		__f_err_msg__ << "read Meta failed, can not find a .obj file !";
		throw "read Meta failed, can not find a .obj file !";
	}

	return __reader->GetOutputPort();
}

vtkSmartPointer<vtkImageData> 
FastReading::RevolveAroundAxis(
	vtkSmartPointer<vtkImageData> __src, UINT __axis)
{
	__clear_status();
	if(__axis > __f_dims__)
	{
		__f_status__ = COORDINATE_AXIS_NOMBER_ERROR;
		__f_err_msg__ << "axis must set 0,1 and 2. 0 is x, 1 is y, 2 is z !";
		return __src;
	}
	vtkSmartPointer <vtkImageFlip> __image_flip
		= vtkSmartPointer<vtkImageFlip>::New();
	__image_flip->SetInputData(__src);
	__image_flip->SetFilteredAxes(__axis);
	__image_flip->Update();

	return __image_flip->GetOutput();
}

void FastReading::__clear_status()
{
	__f_status__ = SUCCESSED;
	__f_err_msg__ = _StrStm_();
}
