#include "pch.h"
#include "..\include\VolumeRenderController.h"


VolumeRenderController::VolumeRenderController()
{
	Supper();
	BaseClass();
}

VolumeRenderController::~VolumeRenderController()
{
}

void VolumeRenderController::VolumPropertyTypeRender(VPType vptp)
{
	VPInfo* vp = nullptr;
	switch(vptp)
	{
		case VP_CT_Fat:
			vp = GetCTFatVPInfo();
			break;
		case VP_CT_MIP:
			vp = GetCTMIPVPInfo();
			break;
		case VP_CT_AAA:
			vp = GetCTAAAVPInfo();
			break;
		case VP_CT_Lung:
			vp = GetCTLungVPInfo();
			break;
		case VP_MR_MIP:
			vp = GetMRMIPVPInfo();
			break;
		case VP_CT_AAA2:
			vp = GetCTAAA2VPInfo();
			break;
		case VP_CT_Bone:
			vp = GetCTBoneVPInfo();
			break;
		case VP_CT_Bones:
			vp = GetCTBonesVPInfo();
			break;
		case VP_MR_Angio:
			vp = GetMRAngioVPInfo();
			break;
		case VP_CT_Muscle:
			vp = GetCTMuscleVPInfo();
			break;
		case VP_CT_Cardiac:
			vp = GetCTCardiacVPInfo();
			break;
		case VP_CT_Cardiac2:
			vp = GetCTCardiac2VPInfo();
			break;
		case VP_CT_Cardiac3:
			vp = GetCTCardiac3VPInfo();
			break;
		case VP_MR_Default:
			vp = GetMRDefaultVPInfo();
			break;
		case VP_MR_T2_Brain:
			vp = GetMRT2BrainVPInfo();
			break;
		case VP_DTI_FA_Brain:
			vp = GetDTIFABrainVPInfo();
			break;
		case VP_CT_Soft_Tissue:
			vp = GetCTSoftTissueVPInfo();
			break;
		case VP_CT_Chest_Vessels:
			vp = GetCTChestVesselsVPInfo();
			break;
		case VP_CT_Liver_Vasculature:
			vp = GetCTLiverVasculatureVPInfo();
			break;
		case VP_CT_Coronary_Arteries:
			vp = GetCTCoronaryArteriesVPInfo();
			break;
		case VP_CT_Coronary_Arteries2:
			vp = GetCTCoronaryArteries2VPInfo();
			break;
		case VP_CT_Coronary_Arteries3:
			vp = GetCTCoronaryArteries3VPInfo();
			break;
		case VP_CT_Cropped_VolumeBone:
			vp = GetCTCroppedVolumeBoneVPInfo();
			break;
		case VP_CT_Pulmonary_Arteries:
			vp = GetCTPulmonaryArteriesVPInfo();
			break;
		case VP_CT_Chest_Contrast_Enhanced:
			vp = GetCTChestContrastEnhancedVPInfo();
			break;
		default:
			vp = GetCTAAAVPInfo();
			break;
	}
	
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();

	delete vp;
}

void VolumeRenderController::SetCTAAAVPInfo()
{
	VPInfo* vp = GetCTAAAVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();

	delete vp;
}

void VolumeRenderController::SetCTAAA2VPInfo()
{
	VPInfo* vp = GetCTAAA2VPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTBoneVPInfo()
{
	VPInfo* vp = GetCTBoneVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTBonesVPInfo()
{
	VPInfo* vp = GetCTBonesVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTFatVPInfo()
{
	VPInfo* vp = GetCTFatVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTMIPVPInfo()
{
	VPInfo* vp = GetCTMIPVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTLungVPInfo()
{
	VPInfo* vp = GetCTLungVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTMuscleVPInfo()
{
	VPInfo* vp = GetCTMuscleVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTCardiacVPInfo()
{
	VPInfo* vp = GetCTCardiacVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTCardiac2VPInfo()
{
	VPInfo* vp = GetCTCardiac2VPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTCardiac3VPInfo()
{
	VPInfo* vp = GetCTCardiac3VPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTSoftTissueVPInfo()
{
	VPInfo* vp = GetCTSoftTissueVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTChestVesselsVPInfo()
{
	VPInfo* vp = GetCTChestVesselsVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTChestContrastEnhancedVPInfo()
{
	VPInfo* vp = GetCTChestContrastEnhancedVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTCoronaryArteriesVPInfo()
{
	VPInfo* vp = GetCTCoronaryArteriesVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTCoronaryArteries2VPInfo()
{
	VPInfo* vp = GetCTCoronaryArteries2VPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTCoronaryArteries3VPInfo()
{
	VPInfo* vp = GetCTCoronaryArteries3VPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTCroppedVolumeBoneVPInfo()
{
	VPInfo* vp = GetCTCroppedVolumeBoneVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTLiverVasculatureVPInfo()
{
	VPInfo* vp = GetCTLiverVasculatureVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetCTPulmonaryArteriesVPInfo()
{
	VPInfo* vp = GetCTPulmonaryArteriesVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetDTIFABrainVPInfo()
{
	VPInfo* vp = GetDTIFABrainVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetMRAngioVPInfo()
{
	VPInfo* vp = GetMRAngioVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetMRDefaultVPInfo()
{
	VPInfo* vp = GetMRDefaultVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetMRMIPVPInfo()
{
	VPInfo* vp = GetMRMIPVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::SetMRT2BrainVPInfo()
{
	VPInfo* vp = GetMRT2BrainVPInfo();
	__SetVolumColorAndFreeMemory(vp);
	__SetScalarOpacityAndFreeMemory(vp);
	__SetGradientOpacityAndFreeMemory(vp);
	__SetMaterialInfoAndFreeMemory(vp);
	Update();
	delete vp;
}

void VolumeRenderController::__SetMaterialInfoAndFreeMemory(VPInfo * vp)
{
	__matrial__[0] = vp->Material[0];
	__matrial__[1] = vp->Material[1];
	__matrial__[2] = vp->Material[2];
	__matrial__[3] = vp->Material[3];

	UpdateVolumProperty(
		vp->Material[0],
		vp->Material[1],
		vp->Material[2],
		vp->Material[3]
	);

	if(nullptr != vp->Material)
	{
		FreeMemory(&(vp->Material));
	}
}

void VolumeRenderController::__SetVolumColorAndFreeMemory(VPInfo * vp)
{
	for(ULONG i = 0; i < vp->Map2ColorSize; i++)
	{
		__color_array__[i][0] = vp->Map2Color[i][0];
		__color_array__[i][1] = vp->Map2Color[i][1];
		__color_array__[i][2] = vp->Map2Color[i][2];
		__color_array__[i][3] = vp->Map2Color[i][3];
	}
	__color_size__ = vp->Map2ColorSize;
	UpdateVolumColor(__color_array__, vp->Map2ColorSize);

	if(nullptr != vp->Map2Color)
	{
		for(ULONG i = 0; i < vp->Map2ColorSize; i++)
		{
			if(nullptr != vp->Map2Color[i])
			{
				FreeMemory(&(vp->Map2Color[i]));
			}
		}
		FreeMemory(&(vp->Map2Color));
	}
}

void VolumeRenderController::__SetScalarOpacityAndFreeMemory(VPInfo * vp)
{
	for(ULONG i = 0; i < vp->ScalarOpacitySize; i++)
	{
		__opacity_array__[i][0] = vp->ScalarOpacity[i][0];
		__opacity_array__[i][1] = vp->ScalarOpacity[i][1];
		__opacity_array__[i][2] = vp->ScalarOpacity[i][2];
		__opacity_array__[i][3] = vp->ScalarOpacity[i][3];
	}
	__opacity_size__ = vp->ScalarOpacitySize;
	UpdateScalarOpacity(__opacity_array__, vp->ScalarOpacitySize);

	if(nullptr != vp->ScalarOpacity)
	{
		for(ULONG i = 0; i < vp->ScalarOpacitySize; i++)
		{
			if(nullptr != vp->ScalarOpacity[i])
			{
				FreeMemory(&(vp->ScalarOpacity[i]));
			}
		}
		FreeMemory(&(vp->ScalarOpacity));
	}
}

void VolumeRenderController::__SetGradientOpacityAndFreeMemory(VPInfo * vp)
{
	for(ULONG i = 0; i < vp->GrantyOpacitySize; i++)
	{
		__gradient_array__[i][0] = vp->GrantyOpacity[i][0];
		__gradient_array__[i][1] = vp->GrantyOpacity[i][1];
		__gradient_array__[i][2] = vp->GrantyOpacity[i][2];
		__gradient_array__[i][3] = vp->GrantyOpacity[i][3];
	}
	__gradient_size__ = vp->GrantyOpacitySize;
	UpdateGradientOpacity(__gradient_array__, vp->GrantyOpacitySize);

	if(nullptr != vp->GrantyOpacity)
	{
		for(ULONG i = 0; i < vp->GrantyOpacitySize; i++)
		{
			if(nullptr != vp->GrantyOpacity[i])
			{
				FreeMemory(&(vp->GrantyOpacity[i]));
			}
		}
		FreeMemory(&(vp->GrantyOpacity));
	}
}
