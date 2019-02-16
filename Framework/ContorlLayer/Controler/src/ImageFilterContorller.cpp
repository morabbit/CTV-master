#include "pch.h"
#include "TraceLogExporter.h"
#include "FrameworkErrorCode.h"
#include "FrameCommonFunctionMacro.h"
#include "..\include\ImageFilterContorller.h"

DWORD WINAPI  ReadObjProcSetup(void* p)
{
	ObjReader* objRd = (ObjReader*)p;

	SliceImageFilter __img_filter;
	vtkSmartPointer<vtkPolyData> data = 
		__img_filter.ObjFastReading(objRd->file.c_str());

	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(data);

	objRd->ploy = vtkSmartPointer<vtkActor>::New();
	objRd->ploy->SetMapper(mapper);
	
	objRd->status = __img_filter.GetStatus();
	objRd->err_msg << __img_filter.GetErrorMsg();

	return 0;
}

ImageFilterContorller::ImageFilterContorller()
{
	__initinalize();
}

ImageFilterContorller::~ImageFilterContorller()
{
	if(__img_head__ != nullptr)
	{
		delete __img_head__;
	}
}

ImageFilterContorller::ImageFilterContorller(CPCHAR __path, UINT dims)
{
	__initinalize();
	__dims__ = dims;
	__file_path__ = _String(__path);
	__load_image_head();
}

ImageFilterContorller::ImageFilterContorller(const ImageFilterContorller & obj)
{
	*this = obj;
}

ImageFilterContorller&
ImageFilterContorller::operator=(const ImageFilterContorller & obj)
{
	this->__dims__ = obj.__dims__;
	this->__file_path__ = obj.__file_path__;

	this->__status__ = obj.__status__;
	this->__err_msg__ = _StrStm_();
	this->__err_msg__ << obj.__err_msg__.str();
	this->__obj_files__ = obj.__obj_files__;
	this->__vtk_poly__ = obj.__vtk_poly__;
	this->__img_head__ = obj.__img_head__;
	if (obj.__vtk_data__ == nullptr)
	{
		this->__vtk_data__ = nullptr;
		return *this;
	}
	
	if (__vtk_data__ == nullptr)
	{
		__vtk_data__ = vtkSmartPointer<vtkImageData>::New();
	}
	this->__vtk_data__->DeepCopy(obj.__vtk_data__);
	
	return *this;
}

void ImageFilterContorller::SetPath(CPCHAR __pth)
{
	__file_path__ = _String(__pth);
	__load_image_head();
}

_String ImageFilterContorller::GetErrorMsg()
{
	return __err_msg__.str();
}

NTSTATUS ImageFilterContorller::GetStatus()
{
	return __status__;
}

NTSTATUS ImageFilterContorller::ReadImage(UINT __dims)
{
	__dims__ = __dims;
	NTSTATUS status = __GenVTKImageData();

	return status;
}

NTSTATUS ImageFilterContorller::ReadImage(CPCHAR __pth, UINT __dims)
{
	__dims__ = __dims;
	__file_path__ = _String(__pth);
	__load_image_head();
	NTSTATUS status = __GenVTKImageData();

	return status;
}

INT ImageFilterContorller::GetSeriesNumber()
{
	return __img_head__->seriesNO;
}

DOUBLE * ImageFilterContorller::GetOrigin()
{
	// Note: free memory when you used 
	DOUBLE *__origin = (DOUBLE*)MallocMemroy(3 * sizeof(DOUBLE));
	__origin[0] = __img_head__->origin[0];
	__origin[1] = __img_head__->origin[1];
	__origin[2] = __img_head__->origin[2];

	return __origin;
}

DOUBLE * ImageFilterContorller::GetSpacing()
{
	// Note: free memory when you used 
	DOUBLE *__spacing = (DOUBLE*)MallocMemroy(3 * sizeof(DOUBLE));
	__spacing[0] = __img_head__->dx;
	__spacing[1] = __img_head__->dy;
	__spacing[2] = __img_head__->dz;

	return __spacing;
}

UINT * ImageFilterContorller::GetImageSize()
{
	// Note: free memory when you used 
	UINT *__size = (UINT*)MallocMemroy(3 * sizeof(UINT));
	__size[0] = __img_head__->nx;
	__size[1] = __img_head__->ny;
	__size[2] = __img_head__->nz;

	return __size;
}

UINT ImageFilterContorller::GetWidth(UINT index)
{
	if(index == 0)
	{
		return __img_head__->ny * __img_head__->dy;
	}
	else
	{
		return __img_head__->nx * __img_head__->dx;
	}
}

UINT ImageFilterContorller::GetHeight(UINT index)
{
	if(index == 2)
	{
		return __img_head__->ny * __img_head__->dy;
	}
	else
	{
		return __img_head__->nz * __img_head__->dz;
	}
}

void ImageFilterContorller::GetSpacing(DOUBLE __spacing[3])
{
	__spacing[0] = __img_head__->dx;
	__spacing[1] = __img_head__->dy;
	__spacing[2] = __img_head__->dz;
}

void ImageFilterContorller::GetImageSize(UINT __size[3])
{
	__size[0] = __img_head__->nx;
	__size[1] = __img_head__->ny;
	__size[2] = __img_head__->nz;
}

_String ImageFilterContorller::GetPatientName()
{
	return __img_head__->patientName;
}

_String ImageFilterContorller::GetDisplayName()
{
	_StrStm_ msg;
	msg << GetPatientName() << "-"
		<< GetSeriesNumber() << "-"
		<< GetSeriesDescription();

	PRINT_DBG("GetPatientName() :: %s", GetPatientName());
	PRINT_DBG("GetSeriesNumber() :: %d", GetSeriesNumber());
	PRINT_DBG("GetSeriesDescription() :: %s", GetSeriesDescription());
	PRINT_DBG("%s", msg.str());

	return msg.str();
}

_String ImageFilterContorller::GetSeriesDescription()
{
	return __img_head__->seriesDescription;
}

SerialDouble ImageFilterContorller::GetOrientation()
{
	return __img_head__->imageOrientation;
}

DciomObject * ImageFilterContorller::GetDicomHeader()
{
	return __img_head__;
}

void ImageFilterContorller::GetOrigin(DOUBLE __origin[3])
{
	__origin[0] = __img_head__->origin[0];
	__origin[1] = __img_head__->origin[1];
	__origin[2] = __img_head__->origin[2];
}

vtkSmartPointer<vtkImageData> ImageFilterContorller::GetVtkImageData()
{
	return __vtk_data__;
}

vtkSmartPointer<vtkActor>
ImageFilterContorller::GetObjImageData(UINT index)
{
	if(__vtk_poly__.find(index) == __vtk_poly__.end())
	{
		return nullptr;
	}

	return __vtk_poly__[index];
}

vtkSmartPointer<vtkActor>
ImageFilterContorller::GetLastObjImageData()
{
	if(__vtk_poly__.size() == 0)
	{
		return nullptr;
	}
	auto obj = --(__vtk_poly__.end());

	return obj->second;
}

vtkSmartPointer<vtkActor>
ImageFilterContorller::GetFirstObjImageData()
{
	if(__vtk_poly__.size() == 0)
	{
		return nullptr;
	}

	return __vtk_poly__.begin()->second;
}

_String ImageFilterContorller::GetObjFilePath(UINT index)
{
	if(__obj_files__.find(index) == __obj_files__.end())
	{
		return nullptr;
	}

	return __obj_files__[index];
}

_String ImageFilterContorller::GetLastObjFile()
{
	if(__obj_files__.size() == 0)
	{
		return nullptr;
	}
	auto obj = --(__obj_files__.end());

	return obj->second;
}

_String ImageFilterContorller::GetFirstObjFile()
{
	if(__obj_files__.size() == 0)
	{
		return nullptr;
	}

	return __obj_files__.begin()->second;
}

UINT ImageFilterContorller::GetLastHashIndex()
{
	if(__vtk_poly__.size() == 0)
	{
		return -1;
	}

	auto lastObj = --(__vtk_poly__.end());
	return lastObj->first;
}

void ImageFilterContorller::ReadObjFile(_String __files)
{
	UINT lastIndex = GetLastHashIndex();
	lastIndex++;
	SliceImageFilter __img_filter;
	vtkSmartPointer<vtkPolyData> ployData =
		__img_filter.ObjFastReading(__files.c_str());
	
	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(ployData);

	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	__status__ = __img_filter.GetStatus();
	__err_msg__ << __img_filter.GetErrorMsg();

	__obj_files__.emplace(std::make_pair(lastIndex + 1, __files));
	__vtk_poly__.emplace(std::make_pair(lastIndex + 1, actor));
}

void ImageFilterContorller::ReadObjFile(SerialString __files)
{
	DWORD num = __files.size();
	PObjReader objs =
		(PObjReader)MallocMemroy(sizeof(ObjReader) * num);
	PHANDLE hThreads = 
		(PHANDLE)MallocMemroy(sizeof(HANDLE) *num);

	for(UINT i = 0; i < num; i++)
	{
		objs[i].file = __files[i];
		hThreads[i] = CreateThread(0, 0, ::ReadObjProcSetup, &objs[i], 0, 0);
	}
	WaitForMultipleObjects(num, hThreads, TRUE, INFINITE);

	UINT lastIndex = GetLastHashIndex();
	lastIndex++;

	for(UINT i = 0; i < num; i++)
	{
		if(objs[i].status != SUCCESSED)
		{
			__status__ = objs[i].status;
			__err_msg__ << "the [" << i << "] file read failed: " << objs[i].err_msg.str();
		}
		__obj_files__.emplace(std::make_pair(lastIndex + i, objs[i].file));
		__vtk_poly__.emplace(std::make_pair(lastIndex + i, objs[i].ploy));
		CloseHandle(hThreads[i]);
	}

	FreeMemory(&objs);
	FreeMemory(&hThreads);
}

void 
ImageFilterContorller::GetFileDisplayName(CHAR fname[_MAX_FNAME], _String file)
{	
	CHAR dir[_MAX_DIR], ext[_MAX_EXT], drive[_MAX_DRIVE];
	_splitpath("F:\\test\\pro\\amdin.obj", drive, dir, fname, ext);
	strcat(fname, ext);
}

void ImageFilterContorller::__clear_varb()
{
	__status__ = SUCCESSED;
	__err_msg__ = _StrStm_();
}

void ImageFilterContorller::__initinalize()
{
	__dims__ = 3u;
	__status__ = SUCCESSED;
	__err_msg__ = _StrStm_();
	__vtk_data__ = nullptr;
	__img_head__ = new DciomObject;

}

void ImageFilterContorller::__load_image_head()
{
	_String p;
	intptr_t HANDLE, k;
	struct _finddata_t fileinfo;
	char* path = const_cast<char*>(__file_path__.c_str());
	k = HANDLE = _findfirst(p.assign(path).append("//*").c_str(), &fileinfo);
	while(k != -1)
	{
		_String filename = p.assign(path).append("//").append(fileinfo.name);
		*__img_head__ = ReadImageHead::LoadImageHead(filename.c_str());
		if(__img_head__->nFlag != -1)
		{
			break;
		}
		k = _findnext(HANDLE, &fileinfo);
	}
	_findclose(HANDLE);
}

NTSTATUS ImageFilterContorller::__GenVTKImageData()
{
	if(__dims__ == 2) {
		__vtk_data__ = this->__get_2d_vtk_data();
	}
	else {
		__vtk_data__ = __get_3d_vtk_data();
	}
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(__status__);


	return SUCCESSED;
}

NTSTATUS ImageFilterContorller::__GenVTKImageData2()
{
	vtkSmartPointer<vtkImageData> __vtk_data = nullptr;
	PFLOAT __direct = nullptr;
	if(__dims__ == 2)
	{
		SliceImageFilter __img_filter;
		__vtk_data = __img_filter.DicomFastReading(__file_path__.c_str(), __direct);
		__status__ = __img_filter.GetStatus();
		__err_msg__ << __img_filter.GetErrorMsg();
		__PathType a = __img_filter.GetPathType(__file_path__.c_str());
	}
	else
	{
		ImageFilter __img_filter;
		__vtk_data = __img_filter.DicomFastReading(__file_path__.c_str(), __direct);
		__status__ = __img_filter.GetStatus();
		__err_msg__ << __img_filter.GetErrorMsg();
	}
	FreeMemory(&__direct);
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(__status__);


	return SUCCESSED;
}

vtkSmartPointer<vtkImageData> ImageFilterContorller::__get_2d_vtk_data()
{
	__clear_varb();
	SliceImageFilter __img_filter;
	SliceImagePointer __img_ptr = __img_filter.ReadImage(__file_path__.c_str());

	CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
		__img_filter.GetResultStatus(),
		__img_filter.GetResultErrorMsg(),
		nullptr
	);
	__file_head<SliceImageType>(__img_ptr);
	vtkSmartPointer<vtkImageData> __vtk_data =
		__img_filter.ItkImageToVtkImage(__img_ptr);

	CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
		__img_filter.GetResultStatus(),
		__img_filter.GetResultErrorMsg(),
		nullptr
	);

	return __vtk_data;
}

vtkSmartPointer<vtkImageData> ImageFilterContorller::__get_3d_vtk_data()
{
	__clear_varb();
	ImageFilter __img_filter;
	ImagePointer __img_ptr = __img_filter.ReadImage(__file_path__.c_str());
	CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
		__img_filter.GetResultStatus(),
		__img_filter.GetResultErrorMsg(),
		nullptr
	);
	__file_head<ImageType>(__img_ptr);
	vtkSmartPointer<vtkImageData> __vtk_data =
		__img_filter.ItkImageToVtkImage(__img_ptr);

	CHECK_STATUS_SET_MSG_AND_RETURN_OBJ_IF_FAILED(
		__img_filter.GetResultStatus(),
		__img_filter.GetResultErrorMsg(),
		nullptr
	);

	return __vtk_data;
}
