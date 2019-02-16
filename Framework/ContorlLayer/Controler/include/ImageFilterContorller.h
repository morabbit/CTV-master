#pragma once
#ifndef __IMAGEFILTERCONTORLLER_H
#define __IMAGEFILTERCONTORLLER_H
#include "FrameWorkType.h"
#include "CommonImageFilterCtl.hxx"
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>


typedef std::map<UINT, vtkSmartPointer<vtkActor>> HashPolyData;
typedef struct ObjFileReader
{
	_String file;	
	_StrStm_ err_msg;
	NTSTATUS status;
	vtkSmartPointer<vtkActor> ploy;

}ObjReader, *PObjReader;

class ImageFilterContorller
{
public:
	ImageFilterContorller();
	~ImageFilterContorller();
	ImageFilterContorller(CPCHAR __path, UINT dims);
	ImageFilterContorller(const ImageFilterContorller& obj);
	ImageFilterContorller& operator=(const ImageFilterContorller& obj);

public:
	void SetPath(CPCHAR __pth);

	_String GetErrorMsg();

	NTSTATUS GetStatus();
	NTSTATUS ReadImage(UINT __dims = 3);
	NTSTATUS ReadImage(CPCHAR __pth, UINT __dims = 3);

	INT GetSeriesNumber();

	DOUBLE* GetOrigin();
	DOUBLE* GetSpacing();

	UINT* GetImageSize();
	UINT GetWidth(UINT);
	UINT GetHeight(UINT);

	void GetSpacing(DOUBLE __spacing[3]);
	void GetOrigin(DOUBLE __origin[3]);
	void GetImageSize(UINT __size[3]);	

	_String GetPatientName();
	_String GetDisplayName();
	_String GetSeriesDescription();

	SerialDouble GetOrientation();
	DciomObject* GetDicomHeader();

	UINT GetLastHashIndex();
	void ReadObjFile(_String __files);
	void ReadObjFile(SerialString __files);
	void GetFileDisplayName(CHAR fname[_MAX_FNAME], _String file);

	vtkSmartPointer<vtkImageData> GetVtkImageData();
	vtkSmartPointer<vtkActor> GetObjImageData(UINT index);
	vtkSmartPointer<vtkActor> GetLastObjImageData();
	vtkSmartPointer<vtkActor> GetFirstObjImageData();

	_String GetObjFilePath(UINT index);
	_String GetLastObjFile();
	_String GetFirstObjFile();

private:
	void __clear_varb();
	void __initinalize();
	void __load_image_head();	

	NTSTATUS __GenVTKImageData();
	NTSTATUS __GenVTKImageData2();

	vtkSmartPointer<vtkImageData> __get_2d_vtk_data();
	vtkSmartPointer<vtkImageData> __get_3d_vtk_data();

	template<class _InputImageType>
	void __file_head(typename _InputImageType::Pointer);

private:
	UINT __dims__;
	_String __file_path__;
	//CPCHAR __file_path__;
	NTSTATUS __status__;
	_StrStm_ __err_msg__;
	ObjNameMap __obj_files__;
	HashPolyData __vtk_poly__;
	DciomObject* __img_head__;
	vtkSmartPointer<vtkImageData> __vtk_data__;
	
};

template<class _InputImageType>
inline void ImageFilterContorller::__file_head(typename _InputImageType::Pointer __img_ptr)
{
	if(__img_head__->nLoaded != -1)return;
	__img_head__->dims = __dims__;

	typedef typename _InputImageType::SizeType       ISTP;
	typedef typename _InputImageType::PointType      IPTP;
	typedef typename _InputImageType::SpacingType    ISPT;
	typedef typename _InputImageType::DirectionType  IDTP;
	
	ISPT spacing = __img_ptr->GetSpacing();
	IPTP origin  = __img_ptr->GetOrigin();
	IDTP direct  = __img_ptr->GetDirection();
	ISTP size    = __img_ptr->GetLargestPossibleRegion().GetSize();

	__img_head__->dx = spacing[0];
	__img_head__->dy = spacing[1];
	__img_head__->dz = (__dims__ == 2) ? 0.0 : spacing[2];

	__img_head__->nx = size[0];
	__img_head__->ny = size[1];
	__img_head__->nz = (__dims__ == 2) ? 0 : size[2];
	__img_head__->origin[0] = origin[0];
	__img_head__->origin[1] = origin[1];
	__img_head__->origin[2] = (__dims__ == 2) ? 0.0 : origin[2];

	if(__img_head__->imageOrientation.size() > 0)
	{
		__img_head__->imageOrientation.clear();
	}

	for(UINT i = 0; i < direct.RowDimensions; i++)
	{
		for(UINT j = 0; j < direct.ColumnDimensions; j++)
		{
			__img_head__->imageOrientation.push_back(direct[i][j]);
		}
	}
}

#endif // !__IMAGEFILTERCONTORLLER_H
