#include "pch.h"
#include <vtkCamera.h>
#include "FrameworkErrorCode.h"
#include "FrameCommonFunctionMacro.h"
#include "..\include\RenderingWindowsContorler.h"

#include <vtkAssembly.h>
#include <vtkAxesActor.h>
#include <vtkAnnotatedCubeActor.h>
#include <vtkInteractorStyleRubberBandPick.h>

RenderingWindows::RenderingWindows()
{
	InitinalizeCurrentClass();
}

RenderingWindows::RenderingWindows(vtkSmartPointer<vtkImageData> __dt, UINT __dims)
{
	InitinalizeCurrentClass();
	__dims__ = __dims;
	__vtk_data__ = __dt;
}

RenderingWindows::~RenderingWindows()
{
}

RenderingWindows::RenderingWindows(const RenderingWindows & obj)
{
	*this = obj;
}

RenderingWindows & RenderingWindows::operator=(const RenderingWindows & obj)
{
	__dims__ = obj.__dims__;	
	__status__ = obj.__status__;
	__vtk_data__ = obj.__vtk_data__;	
	__data_ready__ = obj.__data_ready__;

	__err_msg__ = _StrStm_();
	__err_msg__ << obj.__err_msg__.str();

	__volum_rend__ = obj.__volum_rend__;	
	__colorMap__[0] = obj.__colorMap__[0];
	__colorMap__[1] = obj.__colorMap__[1];
	__colorMap__[2] = obj.__colorMap__[2];

	__reslice__[0] = obj.__reslice__[0];
	__reslice__[1] = obj.__reslice__[1];
	__reslice__[2] = obj.__reslice__[2];

	__colorTable__[0] = obj.__colorTable__[0];
	__colorTable__[1] = obj.__colorTable__[1];
	__colorTable__[2] = obj.__colorTable__[2];

	__resliceAxes__[0] = obj.__resliceAxes__[0];
	__resliceAxes__[1] = obj.__resliceAxes__[1];
	__resliceAxes__[2] = obj.__resliceAxes__[2];

	__img_color_ranger__ = obj.__img_color_ranger__;
	__img_color_center__ = obj.__img_color_center__;

	
	__slice_actor__[0] = obj.__slice_actor__[0];
	__slice_actor__[1] = obj.__slice_actor__[1];
	__slice_actor__[2] = obj.__slice_actor__[2];

	__volume__ = obj.__volume__;
	__mapper__ = obj.__mapper__;	
	__volum_riw__ = obj.__volum_riw__;
	__volum_color__ = obj.__volum_color__;
	__volum_actor__ = obj.__volum_actor__;
	__volum_marker__ = obj.__volum_marker__;
	__volum_property__ = obj.__volum_property__;
	__volum_scalar_opacity__ = obj.__volum_scalar_opacity__;
	__volum_gradient_opacity__ = obj.__volum_gradient_opacity__;
	memcpy(__img_size__, obj.__img_size__, 3 * sizeof(INT));
	memcpy(__img_extent__, obj.__img_extent__, 3 * sizeof(INT));
	memcpy(__origin__, obj.__origin__, 3 * sizeof(DOUBLE));
	memcpy(__spacing__, obj.__spacing__, 3 * sizeof(DOUBLE));

	return *this;
}

void RenderingWindows::SetImageDiemsions(UINT __dims)
{
	__dims__ = __dims;
}

void RenderingWindows::SetVtkData(vtkSmartPointer<vtkImageData> __dt)
{
	if(__dt == nullptr)
	{
		__vtk_data__ = nullptr;
	}
	else
	{
		__data_ready__ = true;
		__vtk_data__ = vtkSmartPointer<vtkImageData>::New();
		__vtk_data__->DeepCopy(__dt);
	}	
}

vtkSmartPointer<vtkImageData> RenderingWindows::GetVtkData()
{
	return __vtk_data__;
}

vtkSmartPointer<vtkImageData> RenderingWindows::GetVtkData(UINT index)
{
	if (index < 3) {
		return __colorMap__[index]->GetOutput();
	}
	return nullptr;
}

vtkSmartPointer<vtkImageData>
RenderingWindows::ResliceVtkData(UINT index, DOUBLE slice) 
{
	if((index > 3) || (index < 0))
	{
		return nullptr;
	}	

	DOUBLE step = __origin__[index] + (1.0 - slice) *
		__spacing__[index] * __img_size__[index];
		
	__reslice__[index]->Update();
	DOUBLE sliceSpacing = __reslice__[index]->GetOutput()->GetSpacing()[2];
	vtkMatrix4x4 *matrix = __reslice__[index]->GetResliceAxes();
		
	DOUBLE center[4];
	DOUBLE point[4] = { 0.0 ,0.0 ,1.0 ,1.0 };		
	matrix->MultiplyPoint(point, center);

	center[index] = step;
	matrix->SetElement(0, 3, center[0]);
	matrix->SetElement(1, 3, center[1]);
	matrix->SetElement(2, 3, center[2]);

	__colorMap__[index]->Update();
	__slice_actor__[index]->SetPosition(center);
	__slice_actor__[index]->Update();
	Update();

	return __colorMap__[index]->GetOutput();	
}

void RenderingWindows::RenderingWnd()
{
	INT __img_dims[3];
	if(__vtk_data__ != nullptr)
	{
		__vtk_data__->GetDimensions(__img_dims);
	}
	__rendering_window();
}


void RenderingWindows::ResetImgColorRanger(DOUBLE delta) {
	__img_color_ranger__ += delta;

	for (int i = 0; i < 3; i++)
	{
		__colorTable__[i]->SetRange(
			__img_color_center__ - 
			__img_color_ranger__ ,
			__img_color_center__ + 
			__img_color_ranger__
		);
		__colorMap__[i]->Update();
		__slice_actor__[i]->Update();
	}
	Update();
}

void RenderingWindows::ResetImgColorCenter(DOUBLE delta) {
	__img_color_center__ += delta;

	for (int i = 0; i < 3; i++)
	{
		__colorTable__[i]->SetRange(
			__img_color_center__ -
			__img_color_ranger__,
			__img_color_center__ +
			__img_color_ranger__
		);

		__colorMap__[i]->Update();
		__slice_actor__[i]->Update();
	}
	Update();
}

DOUBLE RenderingWindows::GetImgColorRanger()
{
	return __colorTable__[0]->GetRange()[1] - __colorTable__[0]->GetRange()[0];
}

DOUBLE RenderingWindows::GetImgColorCenter()
{
	return (__colorTable__[0]->GetRange()[1] + __colorTable__[0]->GetRange()[0]) / 2.0;
}

void RenderingWindows::InitializeVolum()
{
	__volume__ = vtkSmartPointer<vtkVolume>::New();
	__volume__->SetMapper(__mapper__);
	__volume__->SetProperty(__volum_property__);
	__volume__->Update();
}

void RenderingWindows::NoneInitializeVolum()
{
	__volume__ = vtkSmartPointer<vtkVolume>::New();
}

void RenderingWindows::InitializeMapper()
{
	__mapper__ = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	__mapper__->SetInputData(__vtk_data__);	
	__mapper__->Update();
}

void RenderingWindows::InitializeVolumRender()
{
	__volum_rend__ = vtkSmartPointer<vtkRenderer>::New();
	__volum_rend__->SetBackground(0.52, 0.44, 1.);
	__volum_rend__->AddVolume(__volume__);
}

void RenderingWindows::InitializeVolumRender2()
{
		__volum_rend__ = vtkSmartPointer<vtkRenderer>::New();
		__volum_rend__->SetBackground(0.52, 0.44, 1.);
		__volum_rend__->AddVolume(__slice_actor__[0]);
		__volum_rend__->AddVolume(__slice_actor__[1]);
		__volum_rend__->AddVolume(__slice_actor__[2]);
}

void RenderingWindows::InitializeVolumProperty(
	DOUBLE __ambient, DOUBLE __diffuse, DOUBLE __specular, DOUBLE __power)
{
	__volum_property__ = vtkSmartPointer<vtkVolumeProperty>::New();
	__volum_property__->SetInterpolationTypeToLinear();
	__volum_property__->ShadeOn();
	__volum_property__->SetAmbient(__ambient);
	__volum_property__->SetDiffuse(__diffuse);
	__volum_property__->SetSpecular(__specular);
	__volum_property__->SetSpecularPower(__power);
	__volum_property__->SetScalarOpacity(__volum_scalar_opacity__);
	__volum_property__->SetGradientOpacity(__volum_gradient_opacity__);
	__volum_property__->SetColor(__volum_color__);

}

void RenderingWindows::UpdateVolumColor(DOUBLE __color[][4], UINT __count)
{
	__volum_color__->RemoveAllPoints();
	for(UINT i = 0; i < __count; i++)
	{
		__volum_color__->AddRGBPoint(
			__color[i][0],
			__color[i][1],
			__color[i][2],
			__color[i][3]
		);
	}
	Update();
}

void RenderingWindows::UpdateOneVolumColor(DOUBLE x, DOUBLE __color[4])
{
	__volum_color__->RemovePoint(x);
	__volum_color__->AddRGBPoint(
		__color[0],
		__color[1],
		__color[2],
		__color[3]
	);
	Update();
}

void RenderingWindows::UpdateScalarOpacity(DOUBLE __pnt[][2], UINT __cnt)
{
	__volum_scalar_opacity__->RemoveAllPoints();
	for(UINT i = 0; i < __cnt; i++)
	{
		__volum_scalar_opacity__->AddPoint(__pnt[i][0], __pnt[i][1]);
	}
	Update();
}

void RenderingWindows::UpdateOneScalarOpacity(DOUBLE x, DOUBLE __pnt[2])
{
	__volum_scalar_opacity__->RemovePoint(x);
	__volum_scalar_opacity__->AddPoint(__pnt[0], __pnt[1]);
	Update();
}

void RenderingWindows::UpdateGradientOpacity(DOUBLE __pnt[][2], UINT __cnt)
{
	__volum_gradient_opacity__->RemoveAllPoints();
	for(UINT i = 0; i < __cnt; i++)
	{
		__volum_gradient_opacity__->AddPoint(__pnt[i][0], __pnt[i][1]);
	}
	Update();
}

void RenderingWindows::UpdateOneGradientOpacity(DOUBLE x, DOUBLE __pnt[2])
{
	__volum_gradient_opacity__->RemovePoint(x);
	__volum_gradient_opacity__->AddPoint(__pnt[0], __pnt[1]);
	Update();
}

void RenderingWindows::UpdateInteractorType(IT itp)
{
	if(IT::InteractorTypeNearst == itp)
	{
		__volum_property__->SetInterpolationTypeToNearest();
	}
	else
	{
		__volum_property__->SetInterpolationTypeToLinear();
	}	
	Update();
}

void RenderingWindows::AddVolumColor(DOUBLE __color[4])
{
	__volum_color__->AddRGBPoint(
		__color[0],
		__color[1],
		__color[2],
		__color[3]
	);
	Update();
}

void RenderingWindows::AddScalarOpacity(DOUBLE __pnt[2])
{
	__volum_scalar_opacity__->AddPoint(__pnt[0], __pnt[1]);
	Update();
}

void RenderingWindows::AddGradientOpacity(DOUBLE __pnt[2])
{
	__volum_gradient_opacity__->AddPoint(__pnt[0], __pnt[1]);
	Update();
}

void RenderingWindows::UpdateVolumProperty(
	DOUBLE __ambient, DOUBLE __diffuse, DOUBLE __specular, DOUBLE __power)
{
	__volum_property__->SetAmbient(__ambient);
	__volum_property__->SetDiffuse(__diffuse);
	__volum_property__->SetSpecular(__specular);
	__volum_property__->SetSpecularPower(__power);
	Update();
}

void RenderingWindows::UpdateVolumPropertyPower(DOUBLE __power)
{
	__volum_property__->SetSpecularPower(__power);
	Update();
}

void RenderingWindows::UpdateVolumPropertyAmbient(DOUBLE __ambient)
{
	__volum_property__->SetAmbient(__ambient);
	Update();
}

void RenderingWindows::UpdateVolumPropertyDiffuse(DOUBLE __diffuse)
{
	__volum_property__->SetDiffuse(__diffuse);
	Update();
}

void RenderingWindows::UpdateVolumPropertySpecular(DOUBLE __specular)
{
	__volum_property__->SetSpecular(__specular);
	Update();
}

void RenderingWindows::Display_Volume()
{
	__volum_rend__->RemoveActor(__slice_actor__[0]);
	__volum_rend__->RemoveActor(__slice_actor__[1]);
	__volum_rend__->RemoveActor(__slice_actor__[2]);
	__volum_rend__->AddVolume(__volume__);
	Update();
}

void RenderingWindows::Display_3_Slice()
{
	__volum_rend__->RemoveVolume(__volume__);
	__volum_rend__->AddActor(__slice_actor__[0]);
	__volum_rend__->AddActor(__slice_actor__[1]);
	__volum_rend__->AddActor(__slice_actor__[2]);
	Update();
}

void RenderingWindows::Display_None()
{
	__volum_rend__->RemoveAllViewProps();
	Update();
}

void RenderingWindows::DisplayVolumeAndSlice()
{
	__volum_rend__->AddActor(__slice_actor__[0]);
	__volum_rend__->AddActor(__slice_actor__[1]);
	__volum_rend__->AddActor(__slice_actor__[2]);
	Update();
}

void RenderingWindows::RemoveSliceImage()
{
	__volum_rend__->RemoveActor(__slice_actor__[0]);
	__volum_rend__->RemoveActor(__slice_actor__[1]);
	__volum_rend__->RemoveActor(__slice_actor__[2]);
	Update();
}

void 
RenderingWindows::SetScalarOpacity(DOUBLE __points[][2], UINT __count)
{
	__volum_scalar_opacity__ 
		= vtkSmartPointer<vtkPiecewiseFunction>::New();
	for(UINT i = 0; i < __count; i++)
	{
		__volum_scalar_opacity__->AddPoint(__points[i][0], __points[i][1]);
	}
}

void RenderingWindows::SetGradientOpacity(DOUBLE __points[][2], UINT __count)
{
	__volum_gradient_opacity__
		= vtkSmartPointer<vtkPiecewiseFunction>::New();
	for(UINT i = 0; i < __count; i++)
	{
		__volum_gradient_opacity__->AddPoint(__points[i][0], __points[i][1]);
	}
}

void 
RenderingWindows::SetVolumInteractor(
	vtkSmartPointer<vtkRenderWindowInteractor> __actor)
{
	__volum_actor__ = __actor;

	vtkSmartPointer<vtkInteractorStyleRubberBandPick> __style =
		vtkSmartPointer<vtkInteractorStyleRubberBandPick>::New();
	
	__volum_actor__->SetRenderWindow(__volum_riw__);
	__volum_actor__->SetInteractorStyle(__style);
}

void RenderingWindows::AddActor(vtkSmartPointer<vtkActor> __actor)
{
	__volum_rend__->AddActor(__actor);
	Update();
}

void RenderingWindows::RemoveActor(vtkSmartPointer<vtkActor> __actor)
{
	__volum_rend__->RemoveActor(__actor);
	Update();
}

void RenderingWindows::RemoveAllMathActor(SerialActors __actors)
{
	for(size_t i = 0; i < __actors.size(); i++)
	{
		__volum_rend__->RemoveActor(__actors[i]);
	}
	Update();
}

vtkSmartPointer<vtkRenderWindow> RenderingWindows::GetRenderWindow()
{
	return __volum_riw__;
}

void RenderingWindows::InitializeRenderWindow()
{
	__volum_riw__->AddRenderer(__volum_rend__);
}


void RenderingWindows::Update()
{
	if (!__volum_actor__) return;
	__volum_actor__->Render();
}

void RenderingWindows::AdjustCamera()
{
	__volum_rend__->Render();
	vtkSmartPointer<vtkCamera> camera 
		= __volum_rend__->GetActiveCamera();
	camera->SetViewUp(0, 0, 1);
	camera->SetPosition(0, 1, 0);
	camera->SetFocalPoint(0, 0, 0);
	camera->ComputeViewPlaneNormal();
	__volum_rend__->ResetCamera();
}

void RenderingWindows::SetOrientationMarker()
{
	vtkSmartPointer<vtkAnnotatedCubeActor> __mark 
		= vtkSmartPointer<vtkAnnotatedCubeActor>::New();
	__mark->SetXPlusFaceText("R");
	__mark->SetXMinusFaceText("L");
	__mark->SetYMinusFaceText("P");
	__mark->SetYPlusFaceText("A");
	__mark->SetZMinusFaceText("I");
	__mark->SetZPlusFaceText("S");
	__mark->GetTextEdgesProperty()->SetColor(1, 1, 0);
	__mark->GetTextEdgesProperty()->SetLineWidth(2);
	__mark->GetCubeProperty()->SetColor(0, 0, 1);

	vtkSmartPointer<vtkAxesActor> __axis 
		= vtkSmartPointer<vtkAxesActor>::New();
	vtkSmartPointer<vtkAssembly> __assemble 
		= vtkSmartPointer<vtkAssembly>::New();

	__assemble->AddPart(__mark);
	__assemble->AddPart(__axis);
	__volum_marker__ = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	__volum_marker__->SetOrientationMarker(__assemble);
	__volum_marker__->SetCurrentRenderer(__volum_rend__);
	__volum_marker__->SetInteractor(__volum_actor__);
	__volum_marker__->SetEnabled(1);
	__volum_marker__->SetInteractive(0);
	__volum_marker__->SetViewport(0., 0., 0.4, 0.4);	
}

void
RenderingWindows::SetVolumColor(DOUBLE __color[][4], UINT __count)
{
	__volum_color__ 
		= vtkSmartPointer<vtkColorTransferFunction>::New();
	for(UINT i = 0; i < __count; i++)
	{
		__volum_color__->AddRGBPoint(
			__color[i][0],
			__color[i][1],
			__color[i][2], 
			__color[i][3]
		);
	}
}

void RenderingWindows::RemoveOneScalarOpacityPoint(DOUBLE x)
{
	__volum_scalar_opacity__->RemovePoint(x);
	Update();
}

void RenderingWindows::RemoveAllScalarOpacityPoint()
{
	__volum_scalar_opacity__->RemoveAllPoints();
	Update();
}

void RenderingWindows::RemoveOneGradientOpacityPoint(DOUBLE x)
{
	__volum_gradient_opacity__->RemovePoint(x);
	Update();
}

void RenderingWindows::RemoveAllGradientOpacityPoint()
{
	__volum_gradient_opacity__->RemoveAllPoints();
	Update();
}

void RenderingWindows::RemoveOneColorPoint(DOUBLE x)
{
	__volum_color__->RemovePoint(x);
	Update();
}

void RenderingWindows::RemoveAllColorisePoint()
{
	__volum_color__->RemoveAllPoints();
	Update();
}

NTSTATUS RenderingWindows::GetStatus()
{
	return __status__;
}

_String RenderingWindows::GetErrorMsg()
{
	return __err_msg__.str();
}

void RenderingWindows::__clear_varb()
{
	__status__ = SUCCESSED;
	__err_msg__ = _StrStm_();
}

void RenderingWindows::__rendering_window()
{
	__img_color_center__ = 0.0;
	__img_color_ranger__ = 1000.0;

	DOUBLE center[3];
	__CalculateCenter(center);

	for (int i = 0; i < 3; i++) 
	{
		__InitializeResliceAxes(__resliceAxes__[i], center, i);
		__InitializeReslice(__reslice__[i], i);
		__InitializeLookUpTable(__colorTable__[i]);
		__InitializeMap2Color(__colorMap__[i], i);
	}
	__InitializeSliceActors(center);
}

bool RenderingWindows::GetDataState()
{
	return __data_ready__;
}

void RenderingWindows::__CalculateCenter(DOUBLE center[3])
{
	__vtk_data__->GetExtent(__img_extent__);
	__vtk_data__->GetSpacing(__spacing__);
	__vtk_data__->GetOrigin(__origin__);
	__vtk_data__->GetDimensions(__img_size__);
	center[0] = __origin__[0] + __spacing__[0] * 0.5 * __img_size__[0];
	center[1] = __origin__[1] + __spacing__[1] * 0.5 * __img_size__[1];
	center[2] = __origin__[2] + __spacing__[2] * 0.5 * __img_size__[2];
}

void RenderingWindows::__InitializeSliceActors(DOUBLE center[3])
{
	__slice_actor__[0]->SetInputData(__colorMap__[0]->GetOutput());
	__slice_actor__[0]->SetPosition(center);

	__slice_actor__[1]->SetInputData(__colorMap__[1]->GetOutput());
	__slice_actor__[1]->SetPosition(center);

	__slice_actor__[2]->SetInputData(__colorMap__[2]->GetOutput());
	__slice_actor__[2]->SetPosition(center);

	if (__is_rotate__) 
	{
		__slice_actor__[0]->RotateX(90);
		__slice_actor__[0]->RotateY(-90);
		__slice_actor__[1]->RotateX(90);
		__slice_actor__[1]->RotateY(180);
		__slice_actor__[2]->RotateY(180);

		__is_rotate__ = false;
	}
}

void
RenderingWindows::__InitializeLookUpTable(
	vtkSmartPointer<vtkLookupTable>& __color_tbl)
{
	__color_tbl = vtkSmartPointer<vtkLookupTable>::New();
	__color_tbl->SetRange(
		__img_color_center__ -
		__img_color_ranger__,
		__img_color_center__ +
		__img_color_ranger__
	);
	__color_tbl->SetValueRange(0.0, 1.0);
	__color_tbl->SetSaturationRange(0.0, 0.0);
	__color_tbl->SetRampToLinear();
	__color_tbl->Build();
}

void 
RenderingWindows::__InitializeMap2Color(
	vtkSmartPointer<vtkImageMapToColors>& __map2Color, INT i)
{
	__map2Color = vtkSmartPointer<vtkImageMapToColors>::New();
	__map2Color->SetLookupTable(__colorTable__[i]);
	__map2Color->SetInputConnection(__reslice__[i]->GetOutputPort());
	__map2Color->Update();

}

void
RenderingWindows::__InitializeReslice(
	vtkSmartPointer<vtkImageReslice>& __slice, INT i)
{
	__slice = vtkSmartPointer<vtkImageReslice>::New();
	__slice->SetInputData(__vtk_data__);
	__slice->SetOutputDimensionality(2);
	__slice->SetResliceAxes(__resliceAxes__[i]);
	__slice->SetInterpolationModeToLinear();
}

void
RenderingWindows::__InitializeResliceAxes(
	vtkSmartPointer<vtkMatrix4x4>& __sliceAxes, DOUBLE center[3], INT i)
{
	__sliceAxes = vtkSmartPointer<vtkMatrix4x4>::New();
	__sliceAxes->DeepCopy(axialElements[i]);
	__sliceAxes->SetElement(0, 3, center[0]);
	__sliceAxes->SetElement(1, 3, center[1]);
	__sliceAxes->SetElement(2, 3, center[2]);
}

void RenderingWindows::InitinalizeCurrentClass()
{
	__data_ready__ = false;
	__is_rotate__ = true;
	__status__ = SUCCESSED;
	__err_msg__ = _StrStm_();
	__dims__ = 3u;
	__volum_riw__ = vtkSmartPointer<vtkRenderWindow>::New();
	for(UINT i = 0; i < 3; i++)
	{
		__slice_actor__[i] = vtkSmartPointer<vtkImageActor>::New();
	}	
}

