#pragma once
#ifndef __VOLUMPROPERTY_H
#define __VOLUMPROPERTY_H
#include "FrameWorkType.h"

struct VPInfo
{
public:
	VPInfo();
	~VPInfo();
	VPInfo(const VPInfo& obj);
	VPInfo& operator=(const VPInfo& obj);

public:
	ULONG MaterialSize;
	ULONG ScalarOpacitySize;
	ULONG GrantyOpacitySize;
	ULONG Map2ColorSize;
	DOUBLE*  Material;
	DOUBLE** ScalarOpacity;
	DOUBLE** GrantyOpacity;
	DOUBLE** Map2Color;
};


class VP
{
public:
	VP() {};
	~VP() {};

public:
	///CT-AAA
	VPInfo* GetCTAAAVPInfo(void);
	void GetCTAAAVPInfo(VPInfo* vpInfo);
	/// CT-AAA2
	VPInfo* GetCTAAA2VPInfo(void);
	void GetCTAAA2VPInfo(VPInfo* vpInfo);
	///CT-Bone
	VPInfo* GetCTBoneVPInfo(void);
	void GetCTBoneVPInfo(VPInfo* vpInfo);
	///CT-Bones
	VPInfo* GetCTBonesVPInfo(void);
	void GetCTBonesVPInfo(VPInfo* vpInfo);
	/// CT-Cardiac
	VPInfo* GetCTCardiacVPInfo(void);
	void GetCTCardiacVPInfo(VPInfo* vpInfo);
	///CT-Cardiac2
	VPInfo* GetCTCardiac2VPInfo(void);
	void GetCTCardiac2VPInfo(VPInfo* vpInfo);
	///CT-Cardiac3
	VPInfo* GetCTCardiac3VPInfo(void);
	void GetCTCardiac3VPInfo(VPInfo* vpInfo);
	///CT-Chest-Vessels
	VPInfo* GetCTChestVesselsVPInfo(void);
	void GetCTChestVesselsVPInfo(VPInfo* vpInfo);
	///CT-Chest-Contrast-Enhanced
	VPInfo* GetCTChestContrastEnhancedVPInfo(void);
	void GetCTChestContrastEnhancedVPInfo(VPInfo* vpInfo);
	///CT-Coronary-Arteries
	VPInfo* GetCTCoronaryArteriesVPInfo(void);
	void GetCTCoronaryArteriesVPInfo(VPInfo* vpInfo);
	///CT-Coronary-Arteries2
	VPInfo* GetCTCoronaryArteries2VPInfo(void);
	void GetCTCoronaryArteries2VPInfo(VPInfo* vpInfo);
	///CT-Coronary-Arteries3
	VPInfo* GetCTCoronaryArteries3VPInfo(void);
	void GetCTCoronaryArteries3VPInfo(VPInfo* vpInfo);
	///CT-Cropped-Volume-Bone
	VPInfo* GetCTCroppedVolumeBoneVPInfo(void);
	void GetCTCroppedVolumeBoneVPInfo(VPInfo* vpInfo);
	/// CT-Fat
	VPInfo* GetCTFatVPInfo(void);
	void GetCTFatVPInfo(VPInfo* vpInfo);
	///CT-Liver-Vasculature
	VPInfo* GetCTLiverVasculatureVPInfo(void);
	void GetCTLiverVasculatureVPInfo(VPInfo* vpInfo);
	/// CT-Lung
	VPInfo* GetCTLungVPInfo(void);
	void GetCTLungVPInfo(VPInfo* vpInfo);
	///CT-MIP
	VPInfo* GetCTMIPVPInfo(void);
	void GetCTMIPVPInfo(VPInfo* vpInfo);
	/// CT-Muscle
	VPInfo* GetCTMuscleVPInfo(void);
	void GetCTMuscleVPInfo(VPInfo* vpInfo);
	///CT-Pulmonary-Arteries
	VPInfo* GetCTPulmonaryArteriesVPInfo(void);
	void GetCTPulmonaryArteriesVPInfo(VPInfo* vpInfo);
	///CT-Soft-Tissue
	VPInfo* GetCTSoftTissueVPInfo(void);
	void GetCTSoftTissueVPInfo(VPInfo* vpInfo);
	///DTI-FA-Brain
	VPInfo* GetDTIFABrainVPInfo(void);
	void GetDTIFABrainVPInfo(VPInfo* vpInfo);
	///MR-Angio
	VPInfo* GetMRAngioVPInfo(void);
	void GetMRAngioVPInfo(VPInfo* vpInfo);
	///MR-Default
	VPInfo* GetMRDefaultVPInfo(void);
	void GetMRDefaultVPInfo(VPInfo* vpInfo);
	///MR-MIP
	VPInfo* GetMRMIPVPInfo(void);
	void GetMRMIPVPInfo(VPInfo* vpInfo);
	///MRT-2-Brain
	VPInfo* GetMRT2BrainVPInfo(void);
	void GetMRT2BrainVPInfo(VPInfo* vpInfo);	

private:
	void FillMaterial(VPInfo* Vi, const DOUBLE SrcMaterial[], ULONG size);
	void FillScalarOpacity(VPInfo* Vi, const DOUBLE SrcScalarOpacity[][2], ULONG size);
	void FillGrantyOpacity(VPInfo* Vi, const DOUBLE SrcGrantyOpacity[][2], ULONG size);
	void FillMap2Color(VPInfo* Vi, const DOUBLE SrcMap2Color[][4], ULONG size);

};

#endif // !__VOLUMPROPERTY_HPP
