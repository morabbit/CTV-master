#pragma once
#ifndef __VTKCOMMONDEFINE_H

#define __VTKCOMMONDEFINE_H
#include <vector>
#include <vtkSmartPointer.h>
#include <vtkActor.h>

typedef std::vector<vtkSmartPointer<vtkActor>> SerialActors;

typedef enum InteractorType
{
	/// here we just supoort nearst and linear ,
	/// but Cubic can not support at this time ,
	/// bcs vtk do not allow us to set interactor
	/// type ac cubic
	InteractorTypeNearst = 0,
	InteractorTypeLinear = 1,
	InteractorTypeCubic  = 2,
}IT;

typedef enum VolumePropertyType
{
	VP_CT_Fat                      = 0 ,
	VP_CT_MIP                      = 1 ,
	VP_CT_AAA                      = 2 ,
	VP_CT_Lung                     = 3 ,
	VP_MR_MIP                      = 4 ,
	VP_CT_AAA2                     = 5 ,
	VP_CT_Bone                     = 6 ,
	VP_CT_Bones                    = 7 ,
	VP_MR_Angio                    = 8 ,	
	VP_CT_Muscle                   = 9 ,
	VP_CT_Cardiac                  = 10,
	VP_CT_Cardiac2                 = 11,
	VP_CT_Cardiac3                 = 12,
	VP_MR_Default                  = 13,
	VP_MR_T2_Brain                 = 14,
	VP_DTI_FA_Brain                = 15,
	VP_CT_Soft_Tissue              = 16,
	VP_CT_Chest_Vessels            = 17,
	VP_CT_Liver_Vasculature        = 18,
	VP_CT_Coronary_Arteries        = 19,
	VP_CT_Coronary_Arteries2       = 20,
	VP_CT_Coronary_Arteries3       = 21,
	VP_CT_Cropped_VolumeBone       = 22,		
	VP_CT_Pulmonary_Arteries       = 23,
	VP_CT_Chest_Contrast_Enhanced  = 24,	
}VPType;

#endif // !__VTKCOMMONDEFINE_H
