#pragma once
#ifndef __VOLUMERENDERCONTROLLER_H
#define __VOLUMERENDERCONTROLLER_H
#include "VolumeProperty.h"
#include "RendringControllerBase.h"
#include "vtkCommonDefine.h"


class VolumeRenderController final : 
	private   VP,
	public    RenderingControllerBase
{
	typedef VP                      Supper;
	typedef RenderingControllerBase BaseClass;

public:
	VolumeRenderController();
	~VolumeRenderController();

public:
	void SetCTAAAVPInfo();
	void SetCTAAA2VPInfo();
	void SetCTBoneVPInfo();
	void SetCTBonesVPInfo();
	void SetCTFatVPInfo();
	void SetCTMIPVPInfo();
	void SetCTLungVPInfo();
	void SetCTMuscleVPInfo();
	void SetCTCardiacVPInfo();
	void SetCTCardiac2VPInfo();
	void SetCTCardiac3VPInfo();
	void SetCTSoftTissueVPInfo();
	void SetCTChestVesselsVPInfo();
	void SetCTChestContrastEnhancedVPInfo();
	void SetCTCoronaryArteriesVPInfo();
	void SetCTCoronaryArteries2VPInfo();
	void SetCTCoronaryArteries3VPInfo();
	void SetCTCroppedVolumeBoneVPInfo();
	void SetCTLiverVasculatureVPInfo();	
	void SetCTPulmonaryArteriesVPInfo();	
	void SetDTIFABrainVPInfo();
	void SetMRAngioVPInfo();
	void SetMRDefaultVPInfo();
	void SetMRMIPVPInfo();
	void SetMRT2BrainVPInfo();

	void VolumPropertyTypeRender(VPType vptp);

private:
	void __SetMaterialInfoAndFreeMemory(VPInfo* vp);
	void __SetVolumColorAndFreeMemory(VPInfo* vp);
	void __SetScalarOpacityAndFreeMemory(VPInfo* vp);
	void __SetGradientOpacityAndFreeMemory(VPInfo* vp);
};

#endif // !__VOLUMERENDERCONTROLLER_H
