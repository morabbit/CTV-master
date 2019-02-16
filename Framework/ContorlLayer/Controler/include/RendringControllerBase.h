#pragma once
#ifndef __RENDRINGCTL_H
#define __RENDRINGCTL_H
#include "FrameWorkType.h"
#include "CommonImageFilterCtl.hxx"
#include <QVTKWidget.h>
#include <QVTKOpenGLWidget.h>

typedef 
enum Panel3DDisplayType
{
	Display_None             = 0,
	Display_3_Slice          = 1,
	Display_Volume           = 2,
	Remove_Slice_Image       = 3,
	Display_Volume_And_Slice = 4,
	
}P3DT;


class RenderingControllerBase
{
public:
	RenderingControllerBase();
	~RenderingControllerBase();
	RenderingControllerBase(const RenderingControllerBase&);
	RenderingControllerBase& operator=(const RenderingControllerBase&);	

	DOUBLE GetImgColorRanger();
	DOUBLE GetImgColorCenter();
		
public:
	_String GetErrorMsg();

	NTSTATUS GetStatus();

	void Reflash();
	void Update();

	void ResetImgColorRanger(DOUBLE);
	void ResetImgColorCenter(DOUBLE);
	void ChangeRendering3DPlane(P3DT);
	void SetVtkImageData(vtkSmartPointer<vtkImageData>);

	vtkSmartPointer<vtkImageData> GetVtkData();
	vtkSmartPointer<vtkImageData> GetVtkData(UINT);
	vtkSmartPointer<vtkImageData> ResliceVtkData(UINT, DOUBLE);

	vtkSmartPointer<vtkRenderWindow>
		Rendering3DPlane(
			vtkSmartPointer<vtkRenderWindowInteractor>,
			P3DT s = P3DT::Display_Volume
		);

	/**********************************************/
	/*****************volum render****************/
	/********************************************/
	void SetVolumColor(DOUBLE[][4], UINT);
	void SetScalarOpacity(DOUBLE[][2], UINT);
	void SetGradientOpacity(DOUBLE[][2], UINT);
	void SetVolumScalarOpacityPercentage(INT);

	void SetVolumPropertyParmater(
		DOUBLE ambient,
		DOUBLE diffuse,
		DOUBLE specular, 
		DOUBLE power
	);
	/// line , point actor
	void AddActor(vtkSmartPointer<vtkActor>);
	void RemoveActor(vtkSmartPointer<vtkActor>);
	void RemoveAllMathActor(SerialActors);
	vtkSmartPointer<vtkRenderWindow> GetEmptyRenderWindow();

	/// color :: x is point mask 
	void UpdateVolumColor(DOUBLE __clr[][4], UINT count);
	void UpdateOneVolumColor(DOUBLE x, DOUBLE __clr[4]);
	/// Scalar Opacity :: x is point mask 
	void UpdateScalarOpacity(DOUBLE opacity[][2], UINT count);
	void UpdateOneScalarOpacity(DOUBLE x, DOUBLE opacity[2]);
	/// Gradient Opacity :: x is point mask 
	void UpdateGradientOpacity(DOUBLE gradient[][2], UINT count);
	void UpdateOneGradientOpacity(DOUBLE x, DOUBLE gradient[2]);
	/// property	
	void UpdateVolumPropertyPower(DOUBLE __power);
	void UpdateVolumPropertyAmbient(DOUBLE __ambient);
	void UpdateVolumPropertyDiffuse(DOUBLE __diffuse);
	void UpdateVolumPropertySpecular(DOUBLE __specular);
	void UpdateInteractorType(IT itp = IT::InteractorTypeLinear);
	void UpdateVolumProperty(
		DOUBLE __ambient,
		DOUBLE __diffuse,
		DOUBLE __specular,
		DOUBLE __power
	);

	void AddVolumColor(DOUBLE[4]);
	void AddScalarOpacity(DOUBLE[2]);
	void AddGradientOpacity(DOUBLE[2]);

	void RemoveOneScalarOpacityPoint(DOUBLE);
	void RemoveAllScalarOpacityPoint();

	void RemoveOneGradientOpacityPoint(DOUBLE);
	void RemoveAllGradientOpacityPoint();

	void RemoveOneColorPoint(DOUBLE);
	void RemoveAllColorisePoint();

	UINT GetMaterial(DOUBLE** matrial);
	void GetMaterial(DOUBLE matrial[4]);
	DOUBLE** GetScalarOpacity(UINT& size);
	DOUBLE** GetGradientOpacity(UINT& size);
	DOUBLE** GetMap2Color(UINT& size);

private:
	void __clear_varb();
	void __initinalize();
	void __InitializeVolumeRenderColor();
	void __InitializeVolumeRenderProperty();
	void __InitializeVolumeRenderScalarOpacity();
	void __InitializeVolumeRenderGradientOpacity();

	vtkSmartPointer<vtkRenderWindow>
		VolumeRendering(
			vtkSmartPointer<vtkRenderWindowInteractor>
		);

	vtkSmartPointer<vtkRenderWindow>
		NoneDataRendering(
			vtkSmartPointer<vtkRenderWindowInteractor>
		);

	vtkSmartPointer<vtkRenderWindow>
		Slice3DRendering(
			vtkSmartPointer<vtkRenderWindowInteractor>
		);

protected:
	NTSTATUS __status__;
	_StrStm_ __err_msg__;	

	//opacity array and size 
	UINT __color_size__;
	UINT __opacity_size__;
	UINT __gradient_size__;
	DOUBLE __matrial__[4];
	DOUBLE __color_array__[MaxPointCount][4];
	DOUBLE __opacity_array__[MaxPointCount][2];
	DOUBLE __gradient_array__[MaxPointCount][2];
	
	bool __use_default_volum_color__;
	bool __use_default_volum_property__;
	bool __use_default_volum_scalar_opacity__;
	bool __use_default_volum_gradient_opacity__;
	RenderingWindows* __rend_wnd__;
};

#endif // !__RENDRINGCTL_H
