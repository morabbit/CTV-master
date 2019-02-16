#pragma once
#ifndef __RENDERINGWINDOWSCONTORLER_H
#define __RENDERINGWINDOWSCONTORLER_H
#include "FrameWorkType.h"


#include <QVTKWidget.h>
#include <QVTKOpenGLWidget.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkCellPicker.h>
#include <vtkResliceCursor.h>
#include <vtkResliceImageViewer.h>
#include <vtkResliceImageViewerMeasurements.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkResliceCursorWidget.h>
#include <vtkResliceCursorActor.h>
#include <vtkResliceCursorPolyDataAlgorithm.h>
#include <vtkResliceCursorThickLineRepresentation.h>
#include <vtkImagePlaneWidget.h>
#include <vtkProperty.h>
#include <vtkPlaneSource.h>

#include <vtkImageActor.h>

#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkVolumeMapper.h>
#include <vtkImageReslice.h>
#include <vtkMatrix4x4.h>
#include <vtkLookupTable.h>
#include <vtkImageMapToColors.h>

#include "vtkCommonDefine.h"

class RenderingWindows
{
public:
	RenderingWindows();	
	~RenderingWindows();
	RenderingWindows(vtkSmartPointer<vtkImageData>, UINT);
	RenderingWindows(const RenderingWindows&);
	RenderingWindows& operator=(const RenderingWindows&);

public:
	void SetImageDiemsions(UINT);
	void SetVtkData(vtkSmartPointer<vtkImageData>);

	void RenderingWnd();
	void ResetImgColorRanger(DOUBLE);
	void ResetImgColorCenter(DOUBLE);
	DOUBLE GetImgColorRanger();
	DOUBLE GetImgColorCenter();

	void InitializeVolum();
	void NoneInitializeVolum();// no image display
	void InitializeMapper();
	void InitializeVolumRender();	
	void InitializeVolumRender2();		
	void InitializeRenderWindow();
	void InitializeVolumProperty(DOUBLE, DOUBLE, DOUBLE, DOUBLE);
	void SetVolumColor(DOUBLE[][4], UINT);
	/// for each point, the point[x][0] is point x , 
	///point[x][1] is diaphaneity, the it must be from 0 to 1
	void SetScalarOpacity(DOUBLE[][2], UINT);
	void SetGradientOpacity(DOUBLE[][2], UINT);
	/// color :: x is point mask 
	void UpdateVolumColor(DOUBLE[][4], UINT);	
	void UpdateOneVolumColor(DOUBLE x, DOUBLE[4]);
	/// Scalar Opacity :: x is point mask 
	void UpdateScalarOpacity(DOUBLE[][2], UINT);	
	void UpdateOneScalarOpacity(DOUBLE x,DOUBLE[2]);
	///Gradient Opacity
	void UpdateGradientOpacity(DOUBLE[][2], UINT);
	void UpdateOneGradientOpacity(DOUBLE x, DOUBLE[2]);

	/// property
	void UpdateVolumProperty(DOUBLE, DOUBLE, DOUBLE, DOUBLE);
	void UpdateVolumPropertyPower(DOUBLE __power);
	void UpdateVolumPropertyAmbient(DOUBLE __ambient);
	void UpdateVolumPropertyDiffuse(DOUBLE __diffuse);
	void UpdateVolumPropertySpecular(DOUBLE __specular);
	void UpdateInteractorType(IT itp = IT::InteractorTypeLinear);

	void AddVolumColor(DOUBLE[4]);
	void AddScalarOpacity(DOUBLE[2]);
	void AddGradientOpacity(DOUBLE[2]);

	void Display_Volume();	
	void Display_3_Slice();
	void Display_None();
	void DisplayVolumeAndSlice();
	void RemoveSliceImage();

	void Update();
	void AdjustCamera();
	void SetOrientationMarker();	
	
	void RemoveOneScalarOpacityPoint(DOUBLE);
	void RemoveAllScalarOpacityPoint();

	void RemoveOneGradientOpacityPoint(DOUBLE);
	void RemoveAllGradientOpacityPoint();

	void RemoveOneColorPoint(DOUBLE);
	void RemoveAllColorisePoint();

	void SetVolumInteractor(
		vtkSmartPointer<vtkRenderWindowInteractor>
	);

	// line , point actor
	void AddActor(vtkSmartPointer<vtkActor>);
	void RemoveActor(vtkSmartPointer<vtkActor>);
	void RemoveAllMathActor(SerialActors);

	vtkSmartPointer<vtkImageData> GetVtkData();
	vtkSmartPointer<vtkImageData> GetVtkData(UINT);
	vtkSmartPointer<vtkImageData> ResliceVtkData(UINT, DOUBLE);

	vtkSmartPointer<vtkRenderWindow> GetRenderWindow();
	
	NTSTATUS GetStatus();
	_String GetErrorMsg();

	bool GetDataState();

private:
	void __clear_varb();

	
	void __rendering_window();
	void InitinalizeCurrentClass();
		
	void __CalculateCenter(DOUBLE[3]);
	void __InitializeSliceActors(DOUBLE[3]);
	void __InitializeLookUpTable(vtkSmartPointer<vtkLookupTable>&);
	void __InitializeMap2Color(vtkSmartPointer<vtkImageMapToColors>&, INT);
	void __InitializeReslice(vtkSmartPointer<vtkImageReslice>&, INT);
	void __InitializeResliceAxes(vtkSmartPointer<vtkMatrix4x4>&, DOUBLE[3], INT);
	

protected:
	const DOUBLE axialElements[3][16] = {
		{ 0,  0,  -1,  0,
		 -1,  0,  0,  0,
		  0,  1,  0,  0,
		  0,  0,  0,  1},
        {-1,  0,  0,  0,
		  0,  0, -1,  0,
		  0,  1,  0,  0,
		  0,  0,  0,  1},
        {-1,  0,  0,  0,
		  0,  1,  0,  0,
		  0,  0,  1,  0,
		  0,  0,  0,  1}
	};
	const DOUBLE viewUp[3][3] = {
		{ 0, 0, -1 }, 
	    { 0, 0, -1 }, 
	    { 0, 1,  0 }
	};

private:
	bool __data_ready__;
	bool __is_rotate__;

	INT __img_size__[3];
	INT __img_extent__[6];

	DOUBLE __spacing__[3];
	DOUBLE __origin__[3];	
	DOUBLE __img_color_ranger__;
	DOUBLE __img_color_center__;

	UINT __dims__;
	NTSTATUS __status__;
	_StrStm_ __err_msg__;
	
	vtkSmartPointer<vtkImageData> __vtk_data__;
	vtkSmartPointer<vtkMatrix4x4> __resliceAxes__[3];
	vtkSmartPointer<vtkImageReslice> __reslice__[3];
	vtkSmartPointer<vtkLookupTable> __colorTable__[3];
	vtkSmartPointer<vtkImageMapToColors> __colorMap__[3];

	vtkSmartPointer<vtkImageActor> __slice_actor__[3];
	
	vtkSmartPointer<vtkVolume> __volume__;	
	vtkSmartPointer<vtkRenderer> __volum_rend__;
	vtkSmartPointer<vtkRenderWindow> __volum_riw__;
	vtkSmartPointer<vtkVolumeProperty> __volum_property__;
	vtkSmartPointer<vtkGPUVolumeRayCastMapper> __mapper__;
	vtkSmartPointer<vtkColorTransferFunction> __volum_color__;
	vtkSmartPointer<vtkRenderWindowInteractor> __volum_actor__;
	vtkSmartPointer<vtkPiecewiseFunction> __volum_scalar_opacity__;
	vtkSmartPointer<vtkPiecewiseFunction> __volum_gradient_opacity__;
	vtkSmartPointer<vtkOrientationMarkerWidget> __volum_marker__;
};

#endif // !__RENDERINGWINDOWSCONTORLER_H