#include "pch.h"
#include "..\include\RendringControllerBase.h"
#include "FrameworkErrorCode.h"
#include "FrameCommonFunctionMacro.h"
#include "TraceLogExporter.h"


RenderingControllerBase::RenderingControllerBase()
{
	__initinalize();
}

RenderingControllerBase::~RenderingControllerBase()
{
	delete __rend_wnd__;
}

RenderingControllerBase::RenderingControllerBase(const RenderingControllerBase & obj)
{
	*this = obj;
}

RenderingControllerBase & RenderingControllerBase::operator=(const RenderingControllerBase & obj)
{
	this->__status__ = obj.__status__;
	this->__err_msg__ = _StrStm_();
	this->__err_msg__ << obj.__err_msg__.str();
	this->__color_size__ = obj.__color_size__;
	this->__opacity_size__ = obj.__opacity_size__;

	for(size_t i = 0; i < MaxPointCount; i++)
	{
		memcpy(__color_array__[i], obj.__color_array__[i], 4 * sizeof(DOUBLE));
		memcpy(__opacity_array__[i], obj.__opacity_array__[i], 2 * sizeof(DOUBLE));
		memcpy(__gradient_array__[i], obj.__gradient_array__[i], 2 * sizeof(DOUBLE));
	}
	memcpy(__matrial__, obj.__matrial__, sizeof(DOUBLE) * 4);
	__use_default_volum_color__ = obj.__use_default_volum_color__;
	__use_default_volum_property__ = obj.__use_default_volum_property__;
	__use_default_volum_scalar_opacity__ = obj.__use_default_volum_scalar_opacity__;
	__use_default_volum_gradient_opacity__ = obj.__use_default_volum_gradient_opacity__;

	if(this->__rend_wnd__ == nullptr)
	{
		__rend_wnd__ = new RenderingWindows; /*(RenderingWindows*)MallocMemroy(sizeof(RenderingWindows))*/;
	}
	memcpy(__rend_wnd__, obj.__rend_wnd__, sizeof(RenderingWindows));

	return *this;
}

NTSTATUS RenderingControllerBase::GetStatus()
{
	return __status__;
}

_String RenderingControllerBase::GetErrorMsg()
{
	return __err_msg__.str();
}

void RenderingControllerBase::Reflash()
{
	__rend_wnd__->RenderingWnd();
}

vtkSmartPointer<vtkImageData> RenderingControllerBase::GetVtkData()
{
	return __rend_wnd__->GetVtkData();
}

vtkSmartPointer<vtkImageData> RenderingControllerBase::GetVtkData(UINT index)
{
	return __rend_wnd__->GetVtkData(index);
}

vtkSmartPointer<vtkImageData>
RenderingControllerBase::ResliceVtkData(UINT index, DOUBLE slice)
{
	return __rend_wnd__->ResliceVtkData(index, slice);
}

void RenderingControllerBase::ResetImgColorRanger(DOUBLE delta) 
{
	__rend_wnd__->ResetImgColorRanger(delta);
}


void RenderingControllerBase::ResetImgColorCenter(DOUBLE delta)
{
	__rend_wnd__->ResetImgColorCenter(delta);
}

void RenderingControllerBase::Update()
{
	__rend_wnd__->Update();
}

void RenderingControllerBase::UpdateVolumColor(DOUBLE __clr[][4], UINT count)
{
	for(UINT i = 0; i < count; i++)
	{
		__color_array__[i][0] = __clr[i][0];
		__color_array__[i][1] = __clr[i][1];
		__color_array__[i][2] = __clr[i][2];
		__color_array__[i][3] = __clr[i][3];
	}
	__rend_wnd__->UpdateVolumColor(__clr, count);
}

void RenderingControllerBase::UpdateOneVolumColor(DOUBLE x, DOUBLE __clr[4])
{
	for(UINT i = 0; i < __color_size__; i++)
	{
		if(abs(x - __color_array__[i][0]) < 0.00000001)
		{
			__color_array__[i][0] = __clr[0];
			__color_array__[i][1] = __clr[1];
			__color_array__[i][2] = __clr[2];
			__color_array__[i][3] = __clr[3];
		}
		
	}
	__rend_wnd__->UpdateOneVolumColor(x, __clr);
}

void RenderingControllerBase::UpdateScalarOpacity(DOUBLE opacity[][2], UINT count)
{
	for(UINT i = 0; i < count; i++)
	{
		__opacity_array__[i][0] = opacity[i][0];
		__opacity_array__[i][1] = opacity[i][1];
	}
	__rend_wnd__->UpdateScalarOpacity(opacity, count);
}

void RenderingControllerBase::UpdateOneScalarOpacity(DOUBLE x, DOUBLE opacity[2])
{
	for(UINT i = 0; i < __opacity_size__; i++)
	{
		if(abs(x - __opacity_array__[i][0]) < 0.00000001)
		{
			__opacity_array__[i][0] = opacity[0];
			__opacity_array__[i][1] = opacity[1];
		}		
	}
	__rend_wnd__->UpdateOneScalarOpacity(x, opacity);
}

void RenderingControllerBase::UpdateGradientOpacity(DOUBLE gradient[][2], UINT count)
{
	for(UINT i = 0; i < count; i++)
	{
		__gradient_array__[i][0] = gradient[i][0];
		__gradient_array__[i][1] = gradient[i][1];
	}
	__rend_wnd__->UpdateGradientOpacity(gradient, count);
}

void RenderingControllerBase::UpdateOneGradientOpacity(DOUBLE x, DOUBLE gradient[2])
{
	for(UINT i = 0; i < __gradient_size__; i++)
	{
		if(abs(x - __gradient_array__[i][0]) < 0.00000001)
		{
			__gradient_array__[i][0] = gradient[0];
			__gradient_array__[i][1] = gradient[1];
		}
	}
	__rend_wnd__->UpdateOneGradientOpacity(x, gradient);
}

void RenderingControllerBase::UpdateVolumPropertyPower(DOUBLE __power)
{
	__matrial__[3] = __power;
	__rend_wnd__->UpdateVolumPropertyPower(__power);
}

void RenderingControllerBase::UpdateVolumPropertyAmbient(DOUBLE __ambient)
{
	__matrial__[0] = __ambient;
	__rend_wnd__->UpdateVolumPropertyAmbient(__ambient);
}

void RenderingControllerBase::UpdateVolumPropertyDiffuse(DOUBLE __diffuse)
{
	__matrial__[1] = __diffuse;
	__rend_wnd__->UpdateVolumPropertyDiffuse(__diffuse);
}

void RenderingControllerBase::UpdateVolumPropertySpecular(DOUBLE __specular)
{
	__matrial__[2] = __specular;
	__rend_wnd__->UpdateVolumPropertySpecular(__specular);
}

void RenderingControllerBase::UpdateInteractorType(IT itp)
{
	__rend_wnd__->UpdateInteractorType(itp);
}

void RenderingControllerBase::UpdateVolumProperty(
	DOUBLE abt, DOUBLE difs, DOUBLE spcl, DOUBLE pw)
{
	__matrial__[0] = abt;
	__matrial__[1] = difs;
	__matrial__[2] = spcl;
	__matrial__[3] = pw;
	__rend_wnd__->UpdateVolumProperty(abt, difs, spcl, pw);
}

void RenderingControllerBase::AddVolumColor(DOUBLE __clr[4])
{
	__color_size__++;
	for(UINT i = 0; i < 4; i++)
	{
		__color_array__[__color_size__ - 1][i] = __clr[i];
	}
	
	__rend_wnd__->AddVolumColor(__clr);
}

void RenderingControllerBase::AddScalarOpacity(DOUBLE scl_opt[2])
{

	__opacity_size__++;
	for(UINT i = 0; i < 2; i++)
	{
		__opacity_array__[__opacity_size__ - 1][i] = scl_opt[i];
	}

	__rend_wnd__->AddScalarOpacity(scl_opt);
}

void RenderingControllerBase::AddGradientOpacity(DOUBLE gdt[2])
{
	__gradient_size__++;
	for(UINT i = 0; i < 2; i++)
	{
		__gradient_array__[__gradient_size__ - 1][i] = gdt[i];
	}
	__rend_wnd__->AddGradientOpacity(gdt);
}

void RenderingControllerBase::RemoveOneScalarOpacityPoint(DOUBLE x)
{
	for(UINT i = 0; i < __opacity_size__; i++)
	{
		if(abs(x - __opacity_array__[i][0]) < 0.00000001)
		{
			ZeroMemory(__opacity_array__[i], 2 * sizeof(DOUBLE));
			break;
		}
	}
	__opacity_size__--;
	__rend_wnd__->RemoveOneScalarOpacityPoint(x);
}

void RenderingControllerBase::RemoveAllScalarOpacityPoint()
{
	for(UINT i = 0; i < __opacity_size__; i++)
	{
		ZeroMemory(__opacity_array__[i], 2 * sizeof(DOUBLE));
	}
	__opacity_size__ = 0;
	__rend_wnd__->RemoveAllScalarOpacityPoint();
}

void RenderingControllerBase::RemoveOneGradientOpacityPoint(DOUBLE x)
{
	for(UINT i = 0; i < __gradient_size__; i++)
	{
		if(abs(x - __gradient_array__[i][0]) < 0.00000001)
		{
			ZeroMemory(__gradient_array__[i], 2 * sizeof(DOUBLE));
			break;
		}
	}
	__gradient_size__--;
	__rend_wnd__->RemoveOneGradientOpacityPoint(x);
}

void RenderingControllerBase::RemoveAllGradientOpacityPoint()
{
	for(UINT i = 0; i < __gradient_size__; i++)
	{
		ZeroMemory(__gradient_array__[i], 2 * sizeof(DOUBLE));
	}
	__gradient_size__ = 0;
	__rend_wnd__->RemoveAllGradientOpacityPoint();
}

void RenderingControllerBase::RemoveOneColorPoint(DOUBLE x)
{
	for(UINT i = 0; i < __color_size__; i++)
	{
		if(abs(x - __color_array__[i][0]) < 0.00000001)
		{
			ZeroMemory(__color_array__[i], 4 * sizeof(DOUBLE));
			break;
		}
	}
	__color_size__--;
	__rend_wnd__->RemoveOneColorPoint(x);
}

void RenderingControllerBase::RemoveAllColorisePoint()
{
	for(UINT i = 0; i < __color_size__; i++)
	{
		ZeroMemory(__color_array__[i], 4 * sizeof(DOUBLE));
	}
	__color_size__ = 0;
	__rend_wnd__->RemoveAllColorisePoint();
}

UINT RenderingControllerBase::GetMaterial(DOUBLE** matrial)
{
	*matrial = (DOUBLE*)MallocMemroy(sizeof(DOUBLE) * 4);
	for(UINT i = 0; i < ARRAYSIZE(__matrial__); i++)
	{
		(*matrial)[i] = __matrial__[i];
	}
	
	return ARRAYSIZE(__matrial__);
}

void RenderingControllerBase::GetMaterial(DOUBLE matrial[4])
{
	for(UINT i = 0; i < ARRAYSIZE(__matrial__); i++)
	{
		matrial[i] = __matrial__[i];
	}
}

DOUBLE ** RenderingControllerBase::GetScalarOpacity(UINT& size)
{
	DOUBLE** scalar_opacity = nullptr;
	size = __opacity_size__;

	scalar_opacity = (DOUBLE**)MallocMemroy(size * sizeof(DOUBLE*));
	for(ULONG i = 0; i < __opacity_size__; i++)
	{
		scalar_opacity[i] = (DOUBLE*)MallocMemroy(2 * sizeof(DOUBLE));
		scalar_opacity[i][0] = __opacity_array__[i][0];
		scalar_opacity[i][1] = __opacity_array__[i][1];
	}

	return scalar_opacity;
}

DOUBLE ** RenderingControllerBase::GetGradientOpacity(UINT & size)
{
	DOUBLE** gradient_opacity = nullptr;
	size = __gradient_size__;

	gradient_opacity = (DOUBLE**)MallocMemroy(size * sizeof(DOUBLE*));
	for(ULONG i = 0; i < __gradient_size__; i++)
	{
		gradient_opacity[i] = (DOUBLE*)MallocMemroy(2 * sizeof(DOUBLE));
		gradient_opacity[i][0] = __gradient_array__[i][0];
		gradient_opacity[i][1] = __gradient_array__[i][1];
	}

	return gradient_opacity;
}

DOUBLE** RenderingControllerBase::GetMap2Color(UINT & size)
{
	DOUBLE ** map_2_color = nullptr;

	size = __color_size__;
	map_2_color = (DOUBLE**)MallocMemroy(size * sizeof(DOUBLE*));
	for(ULONG i = 0; i < __color_size__; i++)
	{
		map_2_color[i] = (DOUBLE*)MallocMemroy(4 * sizeof(DOUBLE));
		map_2_color[i][0] = __color_array__[i][0];
		map_2_color[i][1] = __color_array__[i][1];
		map_2_color[i][2] = __color_array__[i][2];
		map_2_color[i][3] = __color_array__[i][3];
	}

	return map_2_color;
}

vtkSmartPointer<vtkRenderWindow>
RenderingControllerBase::Rendering3DPlane(
	vtkSmartPointer<vtkRenderWindowInteractor>__actor, P3DT __show_type)
{
	if(P3DT::Display_Volume == __show_type)
	{
		return VolumeRendering(__actor);
	}
	else if(P3DT::Display_3_Slice == __show_type)
	{
		return Slice3DRendering(__actor);
	}
	else
	{
		return NoneDataRendering(__actor);
	}
}

void RenderingControllerBase::ChangeRendering3DPlane(P3DT __show_type)
{
	if (P3DT::Display_Volume_And_Slice == __show_type)
	{
		__rend_wnd__->DisplayVolumeAndSlice();
	}
	else //P3DT::Remove_Slice_Image 
	{
		__rend_wnd__->RemoveSliceImage();
	}
}

void 
RenderingControllerBase::SetVtkImageData(vtkSmartPointer<vtkImageData> data)
{
	__rend_wnd__->SetVtkData(data);
}

DOUBLE RenderingControllerBase::GetImgColorRanger()
{
	return __rend_wnd__->GetImgColorRanger();
}

DOUBLE RenderingControllerBase::GetImgColorCenter()
{
	return __rend_wnd__->GetImgColorCenter();
}

void RenderingControllerBase::SetVolumColor(DOUBLE __clr[][4], UINT __cnt)
{
	__color_size__ = __cnt;
	for(UINT i = 0; i < __cnt; i++)
	{
		__color_array__[i][0] = __clr[i][0];
		__color_array__[i][1] = __clr[i][1];
		__color_array__[i][2] = __clr[i][2];
		__color_array__[i][3] = __clr[i][3];
	}
	__use_default_volum_color__ = false;
	__rend_wnd__->SetVolumColor(__color_array__, __cnt);
}

void RenderingControllerBase::SetScalarOpacity(DOUBLE __pnt[][2], UINT __cnt)
{
	__opacity_size__ = __cnt;
	for(UINT i = 0; i < __cnt; i++)
	{
		__opacity_array__[i][0] = __pnt[i][0];
		__opacity_array__[i][1] = __pnt[i][1];
	}
	__use_default_volum_scalar_opacity__ = false;
	__rend_wnd__->SetScalarOpacity(__opacity_array__, __opacity_size__);
}

void RenderingControllerBase::SetGradientOpacity(DOUBLE __pnt[][2], UINT __cnt)
{
	__gradient_size__ = __cnt;
	for(UINT i = 0; i < __cnt; i++)
	{
		__gradient_array__[i][0] = __pnt[i][0];
		__gradient_array__[i][1] = __pnt[i][1];
	}
	__use_default_volum_gradient_opacity__ = false;
	__rend_wnd__->SetGradientOpacity(__gradient_array__, __gradient_size__);
}

void RenderingControllerBase::SetVolumPropertyParmater(
	DOUBLE abt, DOUBLE difs, DOUBLE spcl, DOUBLE pw)
{
	__use_default_volum_property__ = false;
	__rend_wnd__->InitializeVolumProperty(abt, difs, spcl, pw);
	__matrial__[0] = abt;
	__matrial__[1] = difs;
	__matrial__[2] = spcl;
	__matrial__[3] = pw;
}

void RenderingControllerBase::AddActor(vtkSmartPointer<vtkActor> __actor)
{
	__rend_wnd__->AddActor(__actor);
}

void RenderingControllerBase::RemoveActor(vtkSmartPointer<vtkActor> __actor)
{
	__rend_wnd__->RemoveActor(__actor);
}

void RenderingControllerBase::RemoveAllMathActor(SerialActors actors)
{
	__rend_wnd__->RemoveAllMathActor(actors);
}

vtkSmartPointer<vtkRenderWindow> RenderingControllerBase::GetEmptyRenderWindow()
{
	return __rend_wnd__->GetRenderWindow();
}

void RenderingControllerBase::__clear_varb()
{
	__status__ = SUCCESSED;
	__err_msg__ = _StrStm_();
}

void RenderingControllerBase::__initinalize()
{
	__status__ = SUCCESSED;
	__err_msg__ = _StrStm_();
	__use_default_volum_color__ = true;
	__use_default_volum_property__ = true;
	__use_default_volum_scalar_opacity__ = true;
	__use_default_volum_gradient_opacity__ = true;
	__rend_wnd__ = new RenderingWindows;
}

void RenderingControllerBase::__InitializeVolumeRenderColor()
{
	if(true == __use_default_volum_color__)
	{
		const DOUBLE __default_skeleton__color[6][4] = {
			{ -3024  , 0.00    , 0.00    , 0.00     },
			{ 143.556, 0.615686, 0.356863, 0.184314 },
			{ 166.222, 0.882353, 0.603922, 0.290196 },
			{ 214.389, 1.0     , 1.0     , 1.0      },
			{ 419.736, 1.0     , 0.937033, 0.954531 },
			{ 3071   , 0.827451, 0.658824, 1.0      }
		};
		__color_size__ = 6;
		for(UINT i = 0; i < ARRAYSIZE(__default_skeleton__color); i++)
		{
			for(UINT j = 0; j < 4; j++)
			{
				__color_array__[i][j] = __default_skeleton__color[i][j];
			}
		}
		__rend_wnd__->SetVolumColor(__color_array__, __color_size__);
	}
}

void RenderingControllerBase::__InitializeVolumeRenderProperty()
{
	if(true == __use_default_volum_property__)
	{
		const DOUBLE __default_property[4] = {
		    0.1, 0.9, 0.2, 10.0
		};
		__rend_wnd__->InitializeVolumProperty(
			__default_property[0],
			__default_property[1],
			__default_property[2],
			__default_property[3]
		);
	}
}

void RenderingControllerBase::__InitializeVolumeRenderScalarOpacity()
{
	if(true == __use_default_volum_scalar_opacity__)
	{
		const DOUBLE __default_skeleton_opacity[6][2] = {
		   { -3024,   0.0      }, { 143.556, 0.0      },
		   { 166.222, 0.686275 }, { 214.389, 0.696078 },
		   { 419.736, 0.833333 }, { 3071   , 0.803922 },
		};
		__opacity_size__ = 6;
		for(UINT i = 0; i < ARRAYSIZE(__default_skeleton_opacity); i++)
		{
			__opacity_array__[i][0] = __default_skeleton_opacity[i][0];
			__opacity_array__[i][1] = __default_skeleton_opacity[i][1];
		}
		__rend_wnd__->SetScalarOpacity(__opacity_array__, __opacity_size__);
	}
}

void RenderingControllerBase::__InitializeVolumeRenderGradientOpacity()
{
	if(true == __use_default_volum_gradient_opacity__)
	{
		const DOUBLE __default_skeleton_gradient[2][2] = {
		    { .0 , 1. }, { 255. , 1. }
		};
		__gradient_size__ = 2;
		for(UINT i = 0; i < ARRAYSIZE(__default_skeleton_gradient); i++)
		{
			__gradient_array__[i][0] = __default_skeleton_gradient[i][0];
			__gradient_array__[i][1] = __default_skeleton_gradient[i][1];
		}
		__rend_wnd__->SetGradientOpacity(__gradient_array__, __gradient_size__);
	}
}

void RenderingControllerBase::SetVolumScalarOpacityPercentage(INT __ptg)
{
	DOUBLE __percentage = (DOUBLE)__ptg / 100.0;
	DOUBLE __opacity[MaxPointCount][2];
	for(UINT i = 0; i < __opacity_size__; i++)
	{
		__opacity[i][0] = __opacity_array__[i][0];
		__opacity[i][1] = __opacity_array__[i][1] * __percentage;
	}
	__rend_wnd__->UpdateScalarOpacity(__opacity, __opacity_size__);
	
}

vtkSmartPointer<vtkRenderWindow>
RenderingControllerBase::VolumeRendering(
	vtkSmartPointer<vtkRenderWindowInteractor> __actor)
{
	if(false == __rend_wnd__->GetDataState())
	{
		__status__ = IMAGE_DATA_NULL;
		__err_msg__ << "image data is NULL";
		return nullptr;
	}

	__InitializeVolumeRenderColor();
	__InitializeVolumeRenderScalarOpacity();
	__InitializeVolumeRenderGradientOpacity();
	__InitializeVolumeRenderProperty();

	__rend_wnd__->InitializeMapper();
	__rend_wnd__->InitializeVolum();
	__rend_wnd__->InitializeVolumRender();
	__rend_wnd__->InitializeRenderWindow();
	__rend_wnd__->SetVolumInteractor(__actor);	
	__rend_wnd__->SetOrientationMarker();
	__rend_wnd__->AdjustCamera();

	return __rend_wnd__->GetRenderWindow();
}

vtkSmartPointer<vtkRenderWindow>
RenderingControllerBase::NoneDataRendering(
	vtkSmartPointer<vtkRenderWindowInteractor>__actor)
{
	__rend_wnd__->NoneInitializeVolum();
	__rend_wnd__->InitializeVolumRender();
	__rend_wnd__->InitializeRenderWindow();
	__rend_wnd__->SetVolumInteractor(__actor);
	__rend_wnd__->SetOrientationMarker();
	__rend_wnd__->AdjustCamera();

	return __rend_wnd__->GetRenderWindow();
}

vtkSmartPointer<vtkRenderWindow>
RenderingControllerBase::Slice3DRendering(
	vtkSmartPointer<vtkRenderWindowInteractor> __actor)
{
	if(false == __rend_wnd__->GetDataState())
	{
		__status__ = IMAGE_DATA_NULL;
		__err_msg__ << "image data is NULL";
		return nullptr;
	}

	__rend_wnd__->NoneInitializeVolum();
	__rend_wnd__->InitializeVolumRender2();
	__rend_wnd__->InitializeRenderWindow();
	__rend_wnd__->SetVolumInteractor(__actor);
	__rend_wnd__->SetOrientationMarker();
	__rend_wnd__->AdjustCamera();

	return __rend_wnd__->GetRenderWindow();
}
