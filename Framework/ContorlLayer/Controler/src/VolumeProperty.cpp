#include "pch.h"
#include "FrameCommonFunctionMacro.h"
#include "..\include\VolumeProperty.h"


VPInfo::VPInfo()
{
	MaterialSize = 0;
	Map2ColorSize = 0;
	ScalarOpacitySize = 0;
	GrantyOpacitySize = 0;
	Material = nullptr;
	Map2Color = nullptr;
	ScalarOpacity = nullptr;
	GrantyOpacity = nullptr;	
}

VPInfo::~VPInfo()
{
	if(nullptr != Material)
	{
		FreeMemory(&Material);
	}

	if(nullptr != Map2Color)
	{
		for(ULONG i = 0; i < Map2ColorSize; i++)
		{
			if(nullptr != Map2Color[i])
			{
				FreeMemory(&(Map2Color[i]));
			}				
		}
		FreeMemory(&Map2Color);
	}

	if(nullptr != ScalarOpacity)
	{
		for(ULONG i = 0; i < ScalarOpacitySize; i++)
		{
			if(nullptr != ScalarOpacity[i])
			{
				FreeMemory(&(ScalarOpacity[i]));
			}
		}
		FreeMemory(&ScalarOpacity);
	}

	if(nullptr != GrantyOpacity)
	{
		for(ULONG i = 0; i < GrantyOpacitySize; i++)
		{
			if(nullptr != GrantyOpacity[i])
			{
				FreeMemory(&(GrantyOpacity[i]));
			}
		}
		FreeMemory(&GrantyOpacity);
	}
}

VPInfo::VPInfo(const VPInfo & obj)
{
	*this = obj;
}

VPInfo & VPInfo::operator=(const VPInfo & obj)
{
	// here we just shallow copy
	this->Material = obj.Material;
	this->Map2Color = obj.Map2Color;
	this->ScalarOpacity = obj.ScalarOpacity;
	this->GrantyOpacity = obj.GrantyOpacity;

	this->MaterialSize      = obj.MaterialSize; 
	this->Map2ColorSize     = obj.Map2ColorSize;
	this->ScalarOpacitySize = obj.ScalarOpacitySize;
	this->GrantyOpacitySize = obj.GrantyOpacitySize;

	return *this;
}

void VP::FillMaterial(VPInfo * Vi, const DOUBLE SrcMaterial[], ULONG size)
{
	Vi->MaterialSize = size;
	Vi->Material = (DOUBLE*)MallocMemroy(size * sizeof(DOUBLE));
	/// = faster than memcpy
	for(ULONG i = 0; i < size; i++)
	{
		Vi->Material[i] = SrcMaterial[i];
	}
}

void VP::FillScalarOpacity(VPInfo * Vi, const DOUBLE SrcScalarOpacity[][2], ULONG size)
{
	Vi->ScalarOpacitySize = size;
	Vi->ScalarOpacity = (DOUBLE**)MallocMemroy(size * sizeof(DOUBLE*));
	for(ULONG i = 0; i < size; i++)
	{
		Vi->ScalarOpacity[i] = (DOUBLE*)MallocMemroy(2 * sizeof(DOUBLE));
		Vi->ScalarOpacity[i][0] = SrcScalarOpacity[i][0];
		Vi->ScalarOpacity[i][1] = SrcScalarOpacity[i][1];
	}
}

void VP::FillGrantyOpacity(VPInfo * Vi, const DOUBLE SrcGrantyOpacity[][2], ULONG size)
{
	Vi->GrantyOpacitySize = size;
	Vi->GrantyOpacity = (DOUBLE**)MallocMemroy(size * sizeof(DOUBLE*));
	for(ULONG i = 0; i < size; i++)
	{
		Vi->GrantyOpacity[i] = (DOUBLE*)MallocMemroy(2 * sizeof(DOUBLE));
		Vi->GrantyOpacity[i][0] = SrcGrantyOpacity[i][0];
		Vi->GrantyOpacity[i][1] = SrcGrantyOpacity[i][1];
	}
}

void VP::FillMap2Color(VPInfo * Vi, const DOUBLE SrcMap2Color[][4], ULONG size)
{
	Vi->Map2ColorSize = size;
	Vi->Map2Color = (DOUBLE**)MallocMemroy(size * sizeof(DOUBLE*));
	for(ULONG i = 0; i < size; i++)
	{
		Vi->Map2Color[i] = (DOUBLE*)MallocMemroy(4 * sizeof(DOUBLE));
		Vi->Map2Color[i][0] = SrcMap2Color[i][0];
		Vi->Map2Color[i][1] = SrcMap2Color[i][1];
		Vi->Map2Color[i][2] = SrcMap2Color[i][2];
		Vi->Map2Color[i][3] = SrcMap2Color[i][3];
	}
}

VPInfo * VP::GetCTAAAVPInfo(void)
{
	const DOUBLE CT_AAA_proper[4] = {
		.1, .9, .2, 10.
	};
	const DOUBLE CT_AAA_opacity[6][2] = {
		{-3024.   , .0     }, { 143.556, .0     },
		{ 166.222 , .686275}, { 214.389, .696078},
		{ 419.736 ,.833333}, { 3071. ,  .803922}
	};
	const DOUBLE CT_AAA_granty[2][2] = {
		{ .0 , 1. }, { 255. , 1. }
	};
	const DOUBLE CT_AAA_color[6][4] = {
		{-3024.   ,  .0     ,      .0 ,  .0      },
		{ 143.556 ,  .615686,  .356863,  .184314 },
		{ 166.222 ,  .882353,  .603922,  .290196 },
		{ 214.389 , 1.      , 1.      , 1.       },
		{ 419.736 , 1.      ,  .937033,  .954531 },
		{ 3071.   , 0.827451,  .658824, 1.       }
	};

	VPInfo *vpInfo = new VPInfo();
	FillMaterial(vpInfo, CT_AAA_proper, 4);
	FillScalarOpacity(vpInfo, CT_AAA_opacity, 6);
	FillGrantyOpacity(vpInfo, CT_AAA_granty, 2);
	FillMap2Color(vpInfo, CT_AAA_color, 6);

	return vpInfo;
}

void VP::GetCTAAAVPInfo(VPInfo* vpInfo)
{
	if( nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}

	const DOUBLE CT_AAA_proper[4] = {
		.1, .9, .2, 10.
	};
	const DOUBLE CT_AAA_opacity[6][2] = {
		{-3024.   , .0     }, { 143.556, .0     },
		{ 166.222 , .686275}, { 214.389, .696078},
		{ 419.736 ,.833333}, { 3071. ,  .803922}
	};
	const DOUBLE CT_AAA_granty[2][2] = {
		{ .0 , 1. }, { 255. , 1. }
	};
	const DOUBLE CT_AAA_color[6][4] = {
		{-3024.   ,  .0     ,      .0 ,  .0      },
		{ 143.556 ,  .615686,  .356863,  .184314 },
		{ 166.222 ,  .882353,  .603922,  .290196 },
		{ 214.389 , 1.      , 1.      , 1.       },
		{ 419.736 , 1.      ,  .937033,  .954531 },
		{ 3071.   , 0.827451,  .658824, 1.       }
	};

	FillMaterial(vpInfo, CT_AAA_proper, 4);
	FillScalarOpacity(vpInfo, CT_AAA_opacity, 6);
	FillGrantyOpacity(vpInfo, CT_AAA_granty, 2);
	FillMap2Color(vpInfo, CT_AAA_color, 6);
}

VPInfo * VP::GetCTAAA2VPInfo(void)
{
	const DOUBLE CT_AAA2_proper[4] = {
		.1, .9, .2, 10.
	};
	const DOUBLE CT_AAA2_opacity[8][2] = {
		{-3024.0 , .0     }, { 129.542 , .0   },
		{ 145.244, .166667}, { 157.02  , .5   },
		{ 169.918, .627451}, { 395.575 , .8125 },
		{ 1578.73, .8125  }, { 3071.   , .8125 }
	};
	const DOUBLE CT_AAA2_granty[2][2] = {
		{ 0.0, 1. }, {255. , 1. }
	};
	const DOUBLE CT_AAA2_color[8][4] = {
		{-3024.   ,  .0     , .0     ,  .0      },
		{ 129.542 ,  .54902 , .25098 ,  .14902  },
		{ 145.244 ,  .6     , .627451,  .843137 },
		{ 157.02  ,  .890196, .47451 ,  .6      },
		{ 169.918 ,  .992157, .870588,  .392157 },
		{ 395.575 ,  1.     , .886275,  .658824 },
		{ 1578.73 ,  1.     , .829256,  .957922 },
		{ 3071.   ,  .827451, .658824,  1.      }
	};
	VPInfo *vpInfo = new VPInfo();
	FillMaterial(vpInfo, CT_AAA2_proper, 4);
	FillScalarOpacity(vpInfo, CT_AAA2_opacity, 8);
	FillGrantyOpacity(vpInfo, CT_AAA2_granty, 2);
	FillMap2Color(vpInfo, CT_AAA2_color, 8);

	return vpInfo;
}

void VP::GetCTAAA2VPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}

	const DOUBLE CT_AAA2_proper[4] = {
		.1, .9, .2, 10.
	};
	const DOUBLE CT_AAA2_opacity[8][2] = {
		{-3024.0 , .0     }, { 129.542 , .0   },
		{ 145.244, .166667}, { 157.02  , .5   },
		{ 169.918, .627451}, { 395.575 , .8125 },
		{ 1578.73, .8125  }, { 3071.   , .8125 }
	};
	const DOUBLE CT_AAA2_granty[2][2] = {
		{ 0.0, 1. }, {255. , 1. }
	};
	const DOUBLE CT_AAA2_color[8][4] = {
		{-3024.   ,  .0     , .0     ,  .0      },
		{ 129.542 ,  .54902 , .25098 ,  .14902  },
		{ 145.244 ,  .6     , .627451,  .843137 },
		{ 157.02  ,  .890196, .47451 ,  .6      },
		{ 169.918 ,  .992157, .870588,  .392157 },
		{ 395.575 ,  .0     , .886275,  .658824 },
		{ 1578.73 ,  .0     , .829256,  .957922 },
		{ 3071.   ,  .827451, .658824,  1.      }
	};

	FillMaterial(vpInfo, CT_AAA2_proper, 4);
	FillScalarOpacity(vpInfo, CT_AAA2_opacity, 8);
	FillGrantyOpacity(vpInfo, CT_AAA2_granty, 2);
	FillMap2Color(vpInfo, CT_AAA2_color, 8);
}


VPInfo * VP::GetCTBoneVPInfo(void)
{
	const DOUBLE CT_Bone_proper[4] = {
		.1 , .9 , .2 , 10.
	};
	const DOUBLE CT_Bone_opacity[4][2] = {
		{-3024.0 , 0.      }, {-16.4458, 0.      },
		{ 641.385, 0.715686}, { 3071.0 , 0.705882}
	};
	const DOUBLE CT_Bone_granty[2][2] = {
		{ 0. ,1. }, { 255. ,1.}
	};
	const DOUBLE CT_Bone_color[4][4] = {
		{-3024.0 , 0.0     , 0.0     , 0.0      },
		{-16.4458, 0.729412, 0.254902, 0.301961 },
		{ 641.385, 0.905882, 0.815686, 0.552941 },
		{ 3071.0 , 1.0     , 1.      , 1.       }
	};
	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Bone_proper, 4);
	FillScalarOpacity(vpInfo, CT_Bone_opacity, 4);
	FillGrantyOpacity(vpInfo, CT_Bone_granty, 2);
	FillMap2Color(vpInfo, CT_Bone_color, 4);

	return vpInfo;
}

void VP::GetCTBoneVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}

	const DOUBLE CT_Bone_proper[4] = {
		.1 , .9 , .2 , 10.
	};
	const DOUBLE CT_Bone_opacity[4][2] = {
		{-3024.0 , 0.      }, {-16.4458, 0.      },
		{ 641.385, 0.715686}, { 3071.0 , 0.705882}
	};
	const DOUBLE CT_Bone_granty[2][2] = {
		{ 0. ,1. }, { 255. ,1.}
	};
	const DOUBLE CT_Bone_color[4][4] = {
		{-3024.0 , 0.0     , 0.0     , 0.0      },
		{-16.4458, 0.729412, 0.254902, 0.301961 },
		{ 641.385, 0.905882, 0.815686, 0.552941 },
		{ 3071.0 , 1.0     , 1.      , 1.       }
	};

	FillMaterial(vpInfo, CT_Bone_proper, 4);
	FillScalarOpacity(vpInfo, CT_Bone_opacity, 4);
	FillGrantyOpacity(vpInfo, CT_Bone_granty, 2);
	FillMap2Color(vpInfo, CT_Bone_color, 4);
}

VPInfo * VP::GetCTBonesVPInfo(void)
{
	const DOUBLE CT_Bones_proper[4] = {
		.2 , 1. , .0 , 1.
	};
	const DOUBLE CT_Bones_opacity[4][2] = {
		{-1000. , .0      }, { 152.19 , .0 },
		{278.93 , .190476 }, { 952.   , .2 }
	};
	const DOUBLE CT_Bones_granty[2][2] = {
		{ .0 , 1. }, { 985.12 , 1. }
	};
	const DOUBLE CT_Bones_color[5][4] = {
		{-1000.  , .3 , .3     , 1.      },
		{-488.   , .3 , 1.     , .3      },
		{ 463.28 , 1. , .0     , .0      },
		{ 659.15 , 1. , .912535, .0374849},
		{ 953.   , 1. , .3     , .3      }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Bones_proper, 4);
	FillScalarOpacity(vpInfo, CT_Bones_opacity, 4);
	FillGrantyOpacity(vpInfo, CT_Bones_granty, 2);
	FillMap2Color(vpInfo, CT_Bones_color, 5);

	return vpInfo;
}

void VP::GetCTBonesVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}

	const DOUBLE CT_Bones_proper[4] = {
		.2 , 1. , .0 , 1.
	};
	const DOUBLE CT_Bones_opacity[4][2] = {
		{-1000. , .0      }, { 152.19 , .0 },
		{278.93 , .190476 }, { 952.   , .2 }
	};
	const DOUBLE CT_Bones_granty[2][2] = {
		{ .0 , 1. }, { 985.12 , 1. }
	};
	const DOUBLE CT_Bones_color[5][4] = {
		{-1000.  , .3 , .3     , 1.      },
		{-488.   , .3 , 1.     , .3      },
		{ 463.28 , 1. , .0     , .0      },
		{ 659.15 , 1. , .912535, .0374849},
		{ 953.   , 1. , .3     , .3      }
	};

	FillMaterial(vpInfo, CT_Bones_proper, 4);
	FillScalarOpacity(vpInfo, CT_Bones_opacity, 4);
	FillGrantyOpacity(vpInfo, CT_Bones_granty, 2);
	FillMap2Color(vpInfo, CT_Bones_color, 5);
}

VPInfo * VP::GetCTCardiacVPInfo(void)
{
	const DOUBLE CT_Cardiac_proper[4] = {
		.1 , .9 , .2 ,10.
	};
	const DOUBLE CT_Cardiac_opacity[6][2] = {
		{-3024.  , .0      }, {-77.6875, .0     },
		{ 94.9518, 0.285714}, { 179.052, .553571},
		{ 260.439, 0.848214}, { 3071.  , .875   }
	};
	const DOUBLE CT_Cardiac_granty[2][2] = {
		{ .0 , 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Cardiac_color[6][4] = {
		{-3024.  , .0     , .0     , .0     },
		{-77.6875, .54902 , .25098 , .14902 },
		{94.9518 , .882353, .603922, .290196},
		{179.052 , 1.     , .937033, .954531},
		{260.439 , .615686, .0     , .0     },
		{3071.   , .827451, .658824, 1.     }
	};
	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Cardiac_proper, 4);
	FillScalarOpacity(vpInfo, CT_Cardiac_opacity, 6);
	FillGrantyOpacity(vpInfo, CT_Cardiac_granty, 2);
	FillMap2Color(vpInfo, CT_Cardiac_color, 6);

	return vpInfo;
}

void VP::GetCTCardiacVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}

	const DOUBLE CT_Cardiac_proper[4] = {
		.1 , .9 , .2 ,10.
	};
	const DOUBLE CT_Cardiac_opacity[6][2] = {
		{-3024.  , .0      }, {-77.6875, .0     },
		{ 94.9518, 0.285714}, { 179.052, .553571},
		{ 260.439, 0.848214}, { 3071.  , .875   }
	};
	const DOUBLE CT_Cardiac_granty[2][2] = {
		{ .0 , 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Cardiac_color[6][4] = {
		{-3024.  , .0     , .0     , .0     },
		{-77.6875, .54902 , .25098 , .14902 },
		{94.9518 , .882353, .603922, .290196},
		{179.052 , 1.     , .937033, .954531},
		{260.439 , .615686, .0     , .0     },
		{3071.   , .827451, .658824, 1.     }
	};

	FillMaterial(vpInfo, CT_Cardiac_proper, 4);
	FillScalarOpacity(vpInfo, CT_Cardiac_opacity, 6);
	FillGrantyOpacity(vpInfo, CT_Cardiac_granty, 2);
	FillMap2Color(vpInfo, CT_Cardiac_color, 6);
}

VPInfo * VP::GetCTCardiac2VPInfo(void)
{
	const DOUBLE CT_Cardiac2_proper[4] = {
		.1 , .9 , .2 , 10.
	};
	const DOUBLE CT_Cardiac2_opacity[6][2] = {
		{-3024.   , .0      }, { 42.8964 , .0      },
		{ 163.488 , .428571 }, { 277.642 , .776786 },
		{ 1587    , .754902 }, { 3071.   , .754902 }
	};
	const DOUBLE CT_Cardiac2_granty[2][2] = {
		{ .0 , 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Cardiac2_color[6][4] = {
		{-3024.  , .0     , .0     , .0      },
		{ 42.8964, .54902 , .25098 , .14902  },
		{ 163.488, .917647, .639216, .0588235},
		{ 277.642, 1.     , .878431, .623529 },
		{ 1587.  , 1.     , 1.     , 1.      },
		{ 3071.  , .827451, .658824, 1.      }
	};
	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Cardiac2_proper, 4);
	FillScalarOpacity(vpInfo, CT_Cardiac2_opacity, 6);
	FillGrantyOpacity(vpInfo, CT_Cardiac2_granty, 2);
	FillMap2Color(vpInfo, CT_Cardiac2_color, 6);

	return vpInfo;
}

void VP::GetCTCardiac2VPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}

	const DOUBLE CT_Cardiac2_proper[4] = {
		.1 , .9 , .2 , 10.
	};
	const DOUBLE CT_Cardiac2_opacity[6][2] = {
		{-3024.   , .0      }, { 42.8964 , .0      },
		{ 163.488 , .428571 }, { 277.642 , .776786 },
		{ 1587    , .754902 }, { 3071.   , .754902 }
	};
	const DOUBLE CT_Cardiac2_granty[2][2] = {
		{ .0 , 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Cardiac2_color[6][4] = {
		{-3024.  , .0     , .0     , .0      },
		{ 42.8964, .54902 , .25098 , .14902  },
		{ 163.488, .917647, .639216, .0588235},
		{ 277.642, 1.     , .878431, .623529 },
		{ 1587.  , 1.     , 1.     , 1.      },
		{ 3071.  , .827451, .658824, 1.      }
	};

	FillMaterial(vpInfo, CT_Cardiac2_proper, 4);
	FillScalarOpacity(vpInfo, CT_Cardiac2_opacity, 6);
	FillGrantyOpacity(vpInfo, CT_Cardiac2_granty, 2);
	FillMap2Color(vpInfo, CT_Cardiac2_color, 6);
}

VPInfo * VP::GetCTCardiac3VPInfo(void)
{
	const DOUBLE CT_Cardiac3_proper[4] = {
		.1, .9, .2, 10.
	};
	const DOUBLE CT_Cardiac3_opacity[7][2] = {
		{-3024.  , .0      }, {-86.9767, .0      },
		{ 45.3791, .169643 }, { 139.919, .589286 },
		{ 347.907, .607143 }, { 1224.16, .607143 },
		{ 3071.  , .616071 }
	};
	const DOUBLE CT_Cardiac3_granty[2][2] = {
	{ .0, 1. }, { 255., 1. }
	};
	const DOUBLE CT_Cardiac3_color[7][4] = {
		{-3024.  , .0     , .0      , .0     },
		{-86.9767, .0     , .25098  , 1.     },
		{ 45.3791, 1.     , .0      , .0     },
		{ 139.919, 1.     , .894893 , .894893},
		{ 347.907, 1.     , 1.      , .25098 },
		{ 1224.16, 1.     , 1.      , 1.     },
		{ 3071.  , .827451, 0.658824, 1.     }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Cardiac3_proper, 4);
	FillScalarOpacity(vpInfo, CT_Cardiac3_opacity, 7);
	FillGrantyOpacity(vpInfo, CT_Cardiac3_granty, 2);
	FillMap2Color(vpInfo, CT_Cardiac3_color, 7);
	return vpInfo;
}

void VP::GetCTCardiac3VPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}

	const DOUBLE CT_Cardiac3_proper[4] = {
	    .1, .9, .2, 10.
	};
	const DOUBLE CT_Cardiac3_opacity[7][2] = {
		{-3024.  , .0      }, {-86.9767, .0      },
		{ 45.3791, .169643 }, { 139.919, .589286 },
		{ 347.907, .607143 }, { 1224.16, .607143 },
		{ 3071.  , .616071 }
	};
	const DOUBLE CT_Cardiac3_granty[2][2] = {
	{ .0, 1. }, { 255., 1. }
	};
	const DOUBLE CT_Cardiac3_color[7][4] = {
		{-3024.  , .0     , .0      , .0     },
		{-86.9767, .0     , .25098  , 1.     },
		{ 45.3791, 1.     , .0      , .0     },
		{ 139.919, 1.     , .894893 , .894893},
		{ 347.907, 1.     , 1.      , .25098 },
		{ 1224.16, 1.     , 1.      , 1.     },
		{ 3071.  , .827451, 0.658824, 1.     }
	};

	FillMaterial(vpInfo, CT_Cardiac3_proper, 4);
	FillScalarOpacity(vpInfo, CT_Cardiac3_opacity, 7);
	FillGrantyOpacity(vpInfo, CT_Cardiac3_granty, 2);
	FillMap2Color(vpInfo, CT_Cardiac3_color, 7);
}

VPInfo * VP::GetCTChestVesselsVPInfo(void)
{
	const DOUBLE CT_Chest_Vessels_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE CT_Chest_Vessels_opacity[5][2] = {
		{-3024.  , .0     }, {-1278.35, .0  },
		{ 22.8277, .428571}, { 439.291, .625},
		{ 3071.  , .616071}
	};
	const DOUBLE CT_Chest_Vessels_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Chest_Vessels_color[5][4] = {
		{-3024.  , .0     , .0     , .0     },
		{-1278.35, .54902 , .25098 , .14902 },
		{ 22.8277, .882353, .603922, .290196},
		{ 439.291, 1.     , .937033, .954531},
		{ 3071.  , .827451, .658824, 1.     }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Chest_Vessels_proper, 4);
	FillScalarOpacity(vpInfo, CT_Chest_Vessels_opacity, 5);
	FillGrantyOpacity(vpInfo, CT_Chest_Vessels_granty, 2);
	FillMap2Color(vpInfo, CT_Chest_Vessels_color, 5);

	return vpInfo;
}

void VP::GetCTChestVesselsVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE CT_Chest_Vessels_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE CT_Chest_Vessels_opacity[5][2] = {
		{-3024.  , .0     }, {-1278.35, .0  },
		{ 22.8277, .428571}, { 439.291, .625},
		{ 3071.  , .616071}
	};
	const DOUBLE CT_Chest_Vessels_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Chest_Vessels_color[5][4] = {
		{-3024.  , .0     , .0     , .0     },
		{-1278.35, .54902 , .25098 , .14902 },
		{ 22.8277, .882353, .603922, .290196},
		{ 439.291, 1.     , .937033, .954531},
		{ 3071.  , .827451, .658824, 1.     }
	};

	FillMaterial(vpInfo, CT_Chest_Vessels_proper, 4);
	FillScalarOpacity(vpInfo, CT_Chest_Vessels_opacity, 5);
	FillGrantyOpacity(vpInfo, CT_Chest_Vessels_granty, 2);
	FillMap2Color(vpInfo, CT_Chest_Vessels_color, 5);
}

VPInfo * VP::GetCTChestContrastEnhancedVPInfo(void)
{
	const DOUBLE CT_Chest_Contrast_Enhanced_proper[4] = {
		.1, .9, .2, 10.
	};
	const DOUBLE CT_Chest_Contrast_Enhanced_opacity[5][2] = {
		{-3024.  , .0     }, { 67.0106, .0  },
		{ 251.105, .446429}, { 439.291, .625},
		{ 3071.  , .616071}
	};
	const DOUBLE CT_Chest_Contrast_Enhanced_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Chest_Contrast_Enhanced_color[5][4] = {
		{-3024.  , .0     , .0     , .0     },
		{ 67.0106, .54902 , .25098 , .14902 },
		{ 251.105, .882353, .603922, .290196},
		{ 439.291, 1.     , .937033, .954531},
		{ 3071.  , .827451, .658824, 1.     }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Chest_Contrast_Enhanced_proper, 4);
	FillScalarOpacity(vpInfo, CT_Chest_Contrast_Enhanced_opacity, 5);
	FillGrantyOpacity(vpInfo, CT_Chest_Contrast_Enhanced_granty, 2);
	FillMap2Color(vpInfo, CT_Chest_Contrast_Enhanced_color, 5);
	return vpInfo;
}

void VP::GetCTChestContrastEnhancedVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE CT_Chest_Contrast_Enhanced_proper[4] = {
		.1, .9, .2, 10.
	};
	const DOUBLE CT_Chest_Contrast_Enhanced_opacity[5][2] = {
		{-3024.  , .0     }, { 67.0106, .0  },
		{ 251.105, .446429}, { 439.291, .625},
		{ 3071.  , .616071}
	};
	const DOUBLE CT_Chest_Contrast_Enhanced_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Chest_Contrast_Enhanced_color[5][4] = {
		{-3024.  , .0     , .0     , .0     },
		{ 67.0106, .54902 , .25098 , .14902 },
		{ 251.105, .882353, .603922, .290196},
		{ 439.291, 1.     , .937033, .954531},
		{ 3071.  , .827451, .658824, 1.     }
	};

	FillMaterial(vpInfo, CT_Chest_Contrast_Enhanced_proper, 4);
	FillScalarOpacity(vpInfo, CT_Chest_Contrast_Enhanced_opacity, 5);
	FillGrantyOpacity(vpInfo, CT_Chest_Contrast_Enhanced_granty, 2);
	FillMap2Color(vpInfo, CT_Chest_Contrast_Enhanced_color, 5);
}

VPInfo * VP::GetCTCoronaryArteriesVPInfo(void)
{
	const DOUBLE CT_Coronary_Arteries_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE CT_Coronary_Arteries_opacity[6][2] = {
		{-2048.  , .0     }, { 136.47, .0     },
		{ 159.215, .258929}, { 318.43, .571429},
		{ 478.693, .776786}, { 3661. , 1.     }
	};
	const DOUBLE CT_Coronary_Arteries_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Coronary_Arteries_color[6][4] = {
		{-2048.  , .0     , .0     , .0     },
		{ 136.47 , .0     , .0     , .0     },
		{ 159.215, .159804, .159804, .159804},
		{ 318.43 , .764706, .764706, .764706},
		{ 478.693, 1.     , 1.     , 1.     },
		{ 3661.  , 1.     , 1.     , 1.     }
	};
	VPInfo* vpInfo = new VPInfo;

	FillMaterial(vpInfo, CT_Coronary_Arteries_proper, 4);
	FillScalarOpacity(vpInfo, CT_Coronary_Arteries_opacity, 6);
	FillGrantyOpacity(vpInfo, CT_Coronary_Arteries_granty, 2);
	FillMap2Color(vpInfo, CT_Coronary_Arteries_color, 6);

	return vpInfo;
}

void VP::GetCTCoronaryArteriesVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE CT_Coronary_Arteries_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE CT_Coronary_Arteries_opacity[6][2] = {
		{-2048.  , .0     }, { 136.47, .0     },
		{ 159.215, .258929}, { 318.43, .571429},
		{ 478.693, .776786}, { 3661. , 1.     }
	};
	const DOUBLE CT_Coronary_Arteries_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Coronary_Arteries_color[6][4] = {
		{-2048.  , .0     , .0     , .0     },
		{ 136.47 , .0     , .0     , .0     },
		{ 159.215, .159804, .159804, .159804},
		{ 318.43 , .764706, .764706, .764706},
		{ 478.693, 1.     , 1.     , 1.     },
		{ 3661.  , 1.     , 1.     , 1.     }
	};

	FillMaterial(vpInfo, CT_Coronary_Arteries_proper, 4);
	FillScalarOpacity(vpInfo, CT_Coronary_Arteries_opacity, 6);
	FillGrantyOpacity(vpInfo, CT_Coronary_Arteries_granty, 2);
	FillMap2Color(vpInfo, CT_Coronary_Arteries_color, 6);
}

VPInfo * VP::GetCTCoronaryArteries2VPInfo(void)
{
	const DOUBLE CT_Coronary_Arteries_2_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE CT_Coronary_Arteries_2_opacity[7][2] = {
	{-2048.  , .0     }, { 142.677, .0     },
	{ 145.016, .116071}, { 192.174, .5625  },
	{ 217.24 , .776786}, { 384.347, .830357},
	{ 3661.  , .830357}
	};
	const DOUBLE CT_Coronary_Arteries_2_granty[2][2] = {
		{ .0, 1. }, { 255., 1. }
	};
	const DOUBLE CT_Coronary_Arteries_2_color[7][4] = {
	{-2048.   , .0     , .0     , .0      },
	{ 142.677 , .0     , .0     , .0      },
	{ 145.016 , .615686, .0     , .0156863},
	{ 192.174 , .909804, .454902, .0      },
	{ 217.24  , .972549, .807843, .611765 },
	{ 384.347 , .909804, .909804, 1.      },
	{ 3661.   , 1.     , 1.     , 1.      }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Coronary_Arteries_2_proper, 4);
	FillScalarOpacity(vpInfo, CT_Coronary_Arteries_2_opacity, 7);
	FillGrantyOpacity(vpInfo, CT_Coronary_Arteries_2_granty, 2);
	FillMap2Color(vpInfo, CT_Coronary_Arteries_2_color, 7);

	return vpInfo;
}

void VP::GetCTCoronaryArteries2VPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}

	const DOUBLE CT_Coronary_Arteries_2_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE CT_Coronary_Arteries_2_opacity[7][2] = {
	{-2048.  , .0     }, { 142.677, .0     },
	{ 145.016, .116071}, { 192.174, .5625  },
	{ 217.24 , .776786}, { 384.347, .830357},
	{ 3661.  , .830357}
	};
	const DOUBLE CT_Coronary_Arteries_2_granty[2][2] = {
		{ .0, 1. }, { 255., 1. }
	};
	const DOUBLE CT_Coronary_Arteries_2_color[7][4] = {
	{-2048.   , .0     , .0     , .0      },
	{ 142.677 , .0     , .0     , .0      },
	{ 145.016 , .615686, .0     , .0156863},
	{ 192.174 , .909804, .454902, .0      },
	{ 217.24  , .972549, .807843, .611765 },
	{ 384.347 , .909804, .909804, 1.      },
	{ 3661.   , 1.     , 1.     , 1.      }
	};

	FillMaterial(vpInfo, CT_Coronary_Arteries_2_proper, 4);
	FillScalarOpacity(vpInfo, CT_Coronary_Arteries_2_opacity, 7);
	FillGrantyOpacity(vpInfo, CT_Coronary_Arteries_2_granty, 2);
	FillMap2Color(vpInfo, CT_Coronary_Arteries_2_color, 7);
}

VPInfo * VP::GetCTCoronaryArteries3VPInfo(void)
{
	const DOUBLE CT_Coronary_Arteries_3_proper[4] = {
			.1, .9, .2, 10.
	};
	const DOUBLE CT_Coronary_Arteries_3_opacity[7][2] = {
	{-2048.  , .0      }, { 128.643, .0      },
	{ 129.982, .0982143}, { 173.636, .669643 },
	{ 255.884, .857143 }, { 584.878, .866071 },
	{ 3661.  , 1.      }
	};
	const DOUBLE CT_Coronary_Arteries_3_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Coronary_Arteries_3_color[7][4] = {
		{-2048.  , .0      , .0     , .0      },
		{ 128.643, .0      , .0     , .0      },
		{ 129.982, 0.615686, .0     , .0156863},
		{ 173.636, 0.909804, .454902, .0      },
		{ 255.884, 0.886275, .886275, .886275 },
		{ 584.878, 0.968627, .968627, .968627 },
		{ 3661.  , 1.      , 1.     , 1.      }
	};
	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Coronary_Arteries_3_proper, 4);
	FillScalarOpacity(vpInfo, CT_Coronary_Arteries_3_opacity, 7);
	FillGrantyOpacity(vpInfo, CT_Coronary_Arteries_3_granty, 2);
	FillMap2Color(vpInfo, CT_Coronary_Arteries_3_color, 7);

	return vpInfo;
}

void VP::GetCTCoronaryArteries3VPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE CT_Coronary_Arteries_3_proper[4] = {
			.1, .9, .2, 10.
	};
	const DOUBLE CT_Coronary_Arteries_3_opacity[7][2] = {
	{-2048.  , .0      }, { 128.643, .0      },
	{ 129.982, .0982143}, { 173.636, .669643 },
	{ 255.884, .857143 }, { 584.878, .866071 },
	{ 3661.  , 1.      }
	};
	const DOUBLE CT_Coronary_Arteries_3_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Coronary_Arteries_3_color[7][4] = {
		{-2048.  , .0      , .0     , .0      },
		{ 128.643, .0      , .0     , .0      },
		{ 129.982, 0.615686, .0     , .0156863},
		{ 173.636, 0.909804, .454902, .0      },
		{ 255.884, 0.886275, .886275, .886275 },
		{ 584.878, 0.968627, .968627, .968627 },
		{ 3661.  , 1.      , 1.     , 1.      }
	};

	FillMaterial(vpInfo, CT_Coronary_Arteries_3_proper, 4);
	FillScalarOpacity(vpInfo, CT_Coronary_Arteries_3_opacity, 7);
	FillGrantyOpacity(vpInfo, CT_Coronary_Arteries_3_granty, 2);
	FillMap2Color(vpInfo, CT_Coronary_Arteries_3_color, 7);
}

VPInfo * VP::GetCTCroppedVolumeBoneVPInfo(void)
{
	const DOUBLE CT_Cropped_Volume_Bone_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE CT_Cropped_Volume_Bone_opacity[5][2] = {
		{-2048. , .0 }, {-451.  , .0 },
		{-450.  , 1. }, { 1050. , 1. },
		{3661.  , 1. }
	};
	const DOUBLE CT_Cropped_Volume_Bone_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Cropped_Volume_Bone_color[5][4] = {
		{-2048. , .0      , .0      , .0       },
		{-451.  , .0      , .0      , .0       },
		{-450.  , .0556356, .0556356, .0556356 },
		{ 1050. , 1.      , 1.      , 1.       },
		{ 3661. , 1.      , 1.      , 1.       }
	};
	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Cropped_Volume_Bone_proper, 4);
	FillScalarOpacity(vpInfo, CT_Cropped_Volume_Bone_opacity, 5);
	FillGrantyOpacity(vpInfo, CT_Cropped_Volume_Bone_granty, 2);
	FillMap2Color(vpInfo, CT_Cropped_Volume_Bone_color, 5);

	return vpInfo;
}

void VP::GetCTCroppedVolumeBoneVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE CT_Cropped_Volume_Bone_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE CT_Cropped_Volume_Bone_opacity[5][2] = {
		{-2048. , .0 }, {-451.  , .0 },
		{-450.  , 1. }, { 1050. , 1. },
		{3661.  , 1. }
	};
	const DOUBLE CT_Cropped_Volume_Bone_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Cropped_Volume_Bone_color[5][4] = {
		{-2048. , .0      , .0      , .0       },
		{-451.  , .0      , .0      , .0       },
		{-450.  , .0556356, .0556356, .0556356 },
		{ 1050. , 1.      , 1.      , 1.       },
		{ 3661. , 1.      , 1.      , 1.       }
	};

	FillMaterial(vpInfo, CT_Cropped_Volume_Bone_proper, 4);
	FillScalarOpacity(vpInfo, CT_Cropped_Volume_Bone_opacity, 5);
	FillGrantyOpacity(vpInfo, CT_Cropped_Volume_Bone_granty, 2);
	FillMap2Color(vpInfo, CT_Cropped_Volume_Bone_color, 5);
}

VPInfo * VP::GetCTFatVPInfo(void)
{
	const DOUBLE CT_Fat_proper[4] = {
		.2, 1. , .0, 1.
	};
	const DOUBLE CT_Fat_opacity[7][2] = {
		{-1000., .0 }, {-100. , .0  },
		{-99.  , .15}, {-60.  , .15 },
		{-59.  , .0 }, { 101.2, .0  },
		{ 952. , .0 }
	};
	const DOUBLE CT_Fat_granty[3][2] = {
		{ .0, 1. }, { 985.12 , 1. }, { 988. , 1. }
	};
	const DOUBLE CT_Fat_color[9][4] = {
		{-1000. , .3     , .3     , 1.       },
		{-497.5 , .3     , 1.     , .3       },
		{-99.   , .0     , .0     , 1.       },
		{-76.946, .0     , 1.     , .0       },
		{-65.481, .835431, .888889, .0165387 },
		{ 83.89 , 1.     , .0     , .0       },
		{ 463.28, 1.     , .0     , .0       },
		{ 659.15, 1.     , .912535, .0374849 },
		{ 2952. , 1.     , .300267, .299886  }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Fat_proper, 4);
	FillScalarOpacity(vpInfo, CT_Fat_opacity, 7);
	FillGrantyOpacity(vpInfo, CT_Fat_granty, 3);
	FillMap2Color(vpInfo, CT_Fat_color, 9);
	return vpInfo;
}

void VP::GetCTFatVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE CT_Fat_proper[4] = {
		.2, 1. , .0, 1.
	};
	const DOUBLE CT_Fat_opacity[7][2] = {
		{-1000., .0 }, {-100. , .0  },
		{-99.  , .15}, {-60.  , .15 },
		{-59.  , .0 }, { 101.2, .0  },
		{ 952. , .0 }
	};
	const DOUBLE CT_Fat_granty[3][2] = {
		{ .0, 1. }, { 985.12 , 1. }, { 988. , 1. }
	};
	const DOUBLE CT_Fat_color[9][4] = {
		{-1000. , .3     , .3     , 1.       },
		{-497.5 , .3     , 1.     , .3       },
		{-99.   , .0     , .0     , 1.       },
		{-76.946, .0     , 1.     , .0       },
		{-65.481, .835431, .888889, .0165387 },
		{ 83.89 , 1.     , .0     , .0       },
		{ 463.28, 1.     , .0     , .0       },
		{ 659.15, 1.     , .912535, .0374849 },
		{ 2952. , 1.     , .300267, .299886  }
	};

	FillMaterial(vpInfo, CT_Fat_proper, 4);
	FillScalarOpacity(vpInfo, CT_Fat_opacity, 7);
	FillGrantyOpacity(vpInfo, CT_Fat_granty, 3);
	FillMap2Color(vpInfo, CT_Fat_color, 9);
}

VPInfo * VP::GetCTLiverVasculatureVPInfo(void)
{
	const DOUBLE CT_Liver_Vasculature_proper[4] = {
		.2, 1. , .0 , 1.
	};
	const DOUBLE CT_Liver_Vasculature_opacity[7][2] = {
		{-2048.  , .0      }, { 149.113 , .0      },
		{ 157.884, .482143 }, { 339.96  , .660714 },
		{ 388.526, .830357 }, { 1197.95 , .839286 },
		{ 3661.  , .848214 }
	};
	const DOUBLE CT_Liver_Vasculature_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Liver_Vasculature_color[7][4] = {
		{-2048.  , .0     , .0    , .0      },
		{ 149.113, .0     , .0    , .0      },
		{ 157.884, .501961, .25098, .0      },
		{ 339.96 , .695386, .59603, .36886  },
		{ 388.526, .854902, .85098, .827451 },
		{ 1197.95, 1.     , 1.    , 1.      },
		{ 3661.  , 1.     , 1.    , 1.      }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Liver_Vasculature_proper, 4);
	FillScalarOpacity(vpInfo, CT_Liver_Vasculature_opacity, 7);
	FillGrantyOpacity(vpInfo, CT_Liver_Vasculature_granty, 2);
	FillMap2Color(vpInfo, CT_Liver_Vasculature_color, 7);

	return vpInfo;
}

void VP::GetCTLiverVasculatureVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE CT_Liver_Vasculature_proper[4] = {
		.2, 1. , .0 , 1.
	};
	const DOUBLE CT_Liver_Vasculature_opacity[7][2] = {
		{-2048.  , .0      }, { 149.113 , .0      },
		{ 157.884, .482143 }, { 339.96  , .660714 },
		{ 388.526, .830357 }, { 1197.95 , .839286 },
		{ 3661.  , .848214 }
	};
	const DOUBLE CT_Liver_Vasculature_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Liver_Vasculature_color[7][4] = {
		{-2048.  , .0     , .0    , .0      },
		{ 149.113, .0     , .0    , .0      },
		{ 157.884, .501961, .25098, .0      },
		{ 339.96 , .695386, .59603, .36886  },
		{ 388.526, .854902, .85098, .827451 },
		{ 1197.95, 1.     , 1.    , 1.      },
		{ 3661.  , 1.     , 1.    , 1.      }
	};

	FillMaterial(vpInfo, CT_Liver_Vasculature_proper, 4);
	FillScalarOpacity(vpInfo, CT_Liver_Vasculature_opacity, 7);
	FillGrantyOpacity(vpInfo, CT_Liver_Vasculature_granty, 2);
	FillMap2Color(vpInfo, CT_Liver_Vasculature_color, 7);
}

VPInfo * VP::GetCTLungVPInfo(void)
{
	const DOUBLE CT_Lung_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE CT_Lung_opacity[6][2] = {
		{-1000. , .0  }, {-600.  , .0  },
		{-599.  , .15 }, {-400.  , .15 },
		{-399.  , .0  }, { 2952. , .0  }
	};
	const DOUBLE CT_Lung_granty[3][2] = {
		{ .0, 1. }, { 985.12 , 1. }, { 988. , 1. }
	};
	const DOUBLE CT_Lung_color[6][4] = {
		{-1000. , .3     , .3      , 1.       },
		{-600.  , .0     , .0      , 1.       },
		{-530.  , .134704, .781726 , .0724558 },
		{-460.  , .929244, 1.      , .109473  },
		{-400.  , .888889, 0.254949, .0240258 },
		{ 2952. , 1.     , 0.3     , .3       }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Lung_proper, 4);
	FillScalarOpacity(vpInfo, CT_Lung_opacity, 6);
	FillGrantyOpacity(vpInfo, CT_Lung_granty, 3);
	FillMap2Color(vpInfo, CT_Lung_color, 6);

	return vpInfo;
}

void VP::GetCTLungVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE CT_Lung_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE CT_Lung_opacity[6][2] = {
		{-1000. , .0  }, {-600.  , .0  },
		{-599.  , .15 }, {-400.  , .15 },
		{-399.  , .0  }, { 2952. , .0  }
	};
	const DOUBLE CT_Lung_granty[3][2] = {
		{ .0, 1. }, { 985.12 , 1. }, { 988. , 1. }
	};
	const DOUBLE CT_Lung_color[6][4] = {
		{-1000. , .3     , .3      , 1.       },
		{-600.  , .0     , .0      , 1.       },
		{-530.  , .134704, .781726 , .0724558 },
		{-460.  , .929244, 1.      , .109473  },
		{-400.  , .888889, 0.254949, .0240258 },
		{ 2952. , 1.     , 0.3     , .3       }
	};

	FillMaterial(vpInfo, CT_Lung_proper, 4);
	FillScalarOpacity(vpInfo, CT_Lung_opacity, 6);
	FillGrantyOpacity(vpInfo, CT_Lung_granty, 3);
	FillMap2Color(vpInfo, CT_Lung_color, 6);
}

VPInfo * VP::GetCTMIPVPInfo(void)
{
	const DOUBLE CT_MIP_proper[4] = {
		.1, .9, .2, 10.
	};
	const DOUBLE CT_MIP_opacity[4][2] = {
		{-3024. , .0 }, {-637.62, .0 },
		{ 700.  , 1. }, { 3071. , 1. }
	};
	const DOUBLE CT_MIP_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_MIP_color[4][4] = {
		{-3024.  , .0 , .0 , .0 },
		{-637.62 , 1. , 1. , 1. },
		{ 700.   , 1. , 1. , 1. },
		{ 3071.  , 1. , 1. , 1. }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_MIP_proper, 4);
	FillScalarOpacity(vpInfo, CT_MIP_opacity, 4);
	FillGrantyOpacity(vpInfo, CT_MIP_granty, 2);
	FillMap2Color(vpInfo, CT_MIP_color, 4);

	return vpInfo;
}

void VP::GetCTMIPVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE CT_MIP_proper[4] = {
		.1, .9, .2, 10.
	};
	const DOUBLE CT_MIP_opacity[4][2] = {
		{-3024. , .0 }, {-637.62, .0 },
		{ 700.  , 1. }, { 3071. , 1. }
	};
	const DOUBLE CT_MIP_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_MIP_color[4][4] = {
		{-3024.  , .0 , .0 , .0 },
		{-637.62 , 1. , 1. , 1. },
		{ 700.   , 1. , 1. , 1. },
		{ 3071.  , 1. , 1. , 1. }
	};

	FillMaterial(vpInfo, CT_MIP_proper, 4);
	FillScalarOpacity(vpInfo, CT_MIP_opacity, 4);
	FillGrantyOpacity(vpInfo, CT_MIP_granty, 2);
	FillMap2Color(vpInfo, CT_MIP_color, 4);
}

VPInfo * VP::GetCTMuscleVPInfo(void)
{
	const DOUBLE CT_Muscle_proper[4] = {
		.1, .9, .2, 10.
	};
	const DOUBLE CT_Muscle_opacity[5][2] = {
		{-3024.  , .0      }, {-155.407, .0      },
		{ 217.641, .676471 }, { 419.736, .833333 },
		{ 3071.  , .803922 }
	};
	const DOUBLE CT_Muscle_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Muscle_color[5][4] = {
		{-3024.  , .0     , .0     , .0      },
		{-155.407, .54902 , .25098 , .14902  },
		{ 217.641, .882353, .603922, .290196 },
		{ 419.736, 1.     , .937033, .954531 },
		{ 3071.  , .827451, .658824, 1.      }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Muscle_proper, 4);
	FillScalarOpacity(vpInfo, CT_Muscle_opacity, 5);
	FillGrantyOpacity(vpInfo, CT_Muscle_granty, 2);
	FillMap2Color(vpInfo, CT_Muscle_color, 5);

	return vpInfo;
}

void VP::GetCTMuscleVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE CT_Muscle_proper[4] = {
		.1, .9, .2, 10.
	};
	const DOUBLE CT_Muscle_opacity[5][2] = {
		{-3024.  , .0      }, {-155.407, .0      },
		{ 217.641, .676471 }, { 419.736, .833333 },
		{ 3071.  , .803922 }
	};
	const DOUBLE CT_Muscle_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Muscle_color[5][4] = {
		{-3024.  , .0     , .0     , .0      },
		{-155.407, .54902 , .25098 , .14902  },
		{ 217.641, .882353, .603922, .290196 },
		{ 419.736, 1.     , .937033, .954531 },
		{ 3071.  , .827451, .658824, 1.      }
	};

	FillMaterial(vpInfo, CT_Muscle_proper, 4);
	FillScalarOpacity(vpInfo, CT_Muscle_opacity, 5);
	FillGrantyOpacity(vpInfo, CT_Muscle_granty, 2);
	FillMap2Color(vpInfo, CT_Muscle_color, 5);
}

VPInfo * VP::GetCTPulmonaryArteriesVPInfo(void)
{
	const DOUBLE CT_Pulmonary_Arteries_proper[4] = {
		.2, 1. , .0, 1.
	};
	const DOUBLE CT_Pulmonary_Arteries_opacity[7][2] = {
		{-2048.  , .0       }, {-568.625, .0      },
		{-364.081, .0714286 }, {-244.813, .401786 },
		{ 18.2775, .607143  }, { 447.798, .830357 },
		{ 3592.73, .839286  }
	};
	const DOUBLE CT_Pulmonary_Arteries_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Pulmonary_Arteries_color[7][4] = {
		{-2048.  , 0.     , .0      , .0       },
		{-568.625, 0.     , .0      , .0       },
		{-364.081, .396078, .301961 , .180392  },
		{-244.813, .611765, .352941 , .0705882 },
		{ 18.2775, .843137, .0156863, .156863  },
		{ 447.798, .752941, .752941 , .752941  },
		{ 3592.73, 1.     , 1.      , 1.       }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Pulmonary_Arteries_proper, 4);
	FillScalarOpacity(vpInfo, CT_Pulmonary_Arteries_opacity, 7);
	FillGrantyOpacity(vpInfo, CT_Pulmonary_Arteries_granty, 2);
	FillMap2Color(vpInfo, CT_Pulmonary_Arteries_color, 7);
	return vpInfo;
}

void VP::GetCTPulmonaryArteriesVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE CT_Pulmonary_Arteries_proper[4] = {
		.2, 1. , .0, 1.
	};
	const DOUBLE CT_Pulmonary_Arteries_opacity[7][2] = {
		{-2048.  , .0       }, {-568.625, .0      },
		{-364.081, .0714286 }, {-244.813, .401786 },
		{ 18.2775, .607143  }, { 447.798, .830357 },
		{ 3592.73, .839286  }
	};
	const DOUBLE CT_Pulmonary_Arteries_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Pulmonary_Arteries_color[7][4] = {
		{-2048.  , 0.     , .0      , .0       },
		{-568.625, 0.     , .0      , .0       },
		{-364.081, .396078, .301961 , .180392  },
		{-244.813, .611765, .352941 , .0705882 },
		{ 18.2775, .843137, .0156863, .156863  },
		{ 447.798, .752941, .752941 , .752941  },
		{ 3592.73, 1.     , 1.      , 1.       }
	};

	FillMaterial(vpInfo, CT_Pulmonary_Arteries_proper, 4);
	FillScalarOpacity(vpInfo, CT_Pulmonary_Arteries_opacity, 7);
	FillGrantyOpacity(vpInfo, CT_Pulmonary_Arteries_granty, 2);
	FillMap2Color(vpInfo, CT_Pulmonary_Arteries_color, 7);
}

VPInfo * VP::GetCTSoftTissueVPInfo(void)
{
	const DOUBLE CT_Soft_Tissue_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE CT_Soft_Tissue_opacity[5][2] = {
		{-2048. , .0 }, {-167.01, .0 },
		{-160.  , 1. }, { 240.  , 1. },
		{ 3661. , 1. }
	};
	const DOUBLE CT_Soft_Tissue_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Soft_Tissue_color[5][4] = {
		{-2048. , .0      , .0      , .0      },
		{-167.01, .0      , .0      , .0      },
		{-160.  , .0556356, .0556356, .0556356},
		{ 240.  , 1.      , 1.      , 1.      },
		{ 3661. , 1.      , 1.      , 1.      }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, CT_Soft_Tissue_proper, 4ul);
	FillScalarOpacity(vpInfo, CT_Soft_Tissue_opacity, 5ul);
	FillGrantyOpacity(vpInfo, CT_Soft_Tissue_granty, 2ul);
	FillMap2Color(vpInfo, CT_Soft_Tissue_color, 5ul);

	return vpInfo;
}

void VP::GetCTSoftTissueVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE CT_Soft_Tissue_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE CT_Soft_Tissue_opacity[5][2] = {
		{-2048. , .0 }, {-167.01, .0 },
		{-160.  , 1. }, { 240.  , 1. },
		{ 3661. , 1. }
	};
	const DOUBLE CT_Soft_Tissue_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE CT_Soft_Tissue_color[5][4] = {
		{-2048. , .0      , .0      , .0      },
		{-167.01, .0      , .0      , .0      },
		{-160.  , .0556356, .0556356, .0556356},
		{ 240.  , 1.      , 1.      , 1.      },
		{ 3661. , 1.      , 1.      , 1.      }
	};

	FillMaterial(vpInfo, CT_Soft_Tissue_proper, 4ul);
	FillScalarOpacity(vpInfo, CT_Soft_Tissue_opacity, 5ul);
	FillGrantyOpacity(vpInfo, CT_Soft_Tissue_granty, 2ul);
	FillMap2Color(vpInfo, CT_Soft_Tissue_color, 5ul);
}

VPInfo * VP::GetDTIFABrainVPInfo(void)
{
	const DOUBLE DTI_FA_Brain_proper[4] = {
		.3, .9, .5, 40.
	};
	const DOUBLE DTI_FA_Brain_opacity[8][2] = {
		{ .0    , .0   }, { .0    , .0   },
		{ .3501 , .0158}, { .49379, .7619},
		{ .6419 , 1.   }, { .992  , 1.   },
		{ .995  , .0   }, { .995  , .0   }
	};
	const DOUBLE DTI_FA_Brain_granty[2][2] = {
		{ .0, 1. }, { .995, 1. }
	};
	const DOUBLE DTI_FA_Brain_color[7][4] = {
		{ .0    , 1.    , .0   , .0 },
		{ .0    , 1.    , .0   , .0 },
		{ .24974, .4941 , 1.   , .0 },
		{ .49949, .0    , .9882, 1. },
		{ .7492 , .51764, .0   , 1. },
		{ .995  , 1.    , .0   , .0 },
		{ .995  , 1.    , .0   , .0 }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, DTI_FA_Brain_proper, 4ul);
	FillScalarOpacity(vpInfo, DTI_FA_Brain_opacity, 8ul);
	FillGrantyOpacity(vpInfo, DTI_FA_Brain_granty, 2ul);
	FillMap2Color(vpInfo, DTI_FA_Brain_color, 7ul);

	return vpInfo;
}

void VP::GetDTIFABrainVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE DTI_FA_Brain_proper[4] = {
		.3, .9, .5, 40.
	};
	const DOUBLE DTI_FA_Brain_opacity[8][2] = {
		{ .0    , .0   }, { .0    , .0   },
		{ .3501 , .0158}, { .49379, .7619},
		{ .6419 , 1.   }, { .992  , 1.   },
		{ .995  , .0   }, { .995  , .0   }
	};
	const DOUBLE DTI_FA_Brain_granty[2][2] = {
		{ .0, 1. }, { .995, 1. }
	};
	const DOUBLE DTI_FA_Brain_color[7][4] = {
		{ .0    , 1.    , .0   , .0 },
		{ .0    , 1.    , .0   , .0 },
		{ .24974, .4941 , 1.   , .0 },
		{ .49949, .0    , .9882, 1. },
		{ .7492 , .51764, .0   , 1. },
		{ .995  , 1.    , .0   , .0 },
		{ .995  , 1.    , .0   , .0 }
	};

	FillMaterial(vpInfo, DTI_FA_Brain_proper, 4ul);
	FillScalarOpacity(vpInfo, DTI_FA_Brain_opacity, 8ul);
	FillGrantyOpacity(vpInfo, DTI_FA_Brain_granty, 2ul);
	FillMap2Color(vpInfo, DTI_FA_Brain_color, 7ul);
}

VPInfo * VP::GetMRAngioVPInfo(void)
{
	const DOUBLE MR_Angio_proper[4] = {
		.2, 1. , .0 , 1.
	};
	const DOUBLE MR_Angio_opacity[6][2] = {
		{-2048.  , .0     }, { 151.354, .0     },
		{ 158.279, .4375  }, { 190.112, .580357},
		{ 200.873, .732143}, { 3661.  , .741071}
	};
	const DOUBLE MR_Angio_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE MR_Angio_color[6][4] = {
		{-2048.  , .0     , .0     , .0     },
		{ 151.354, .0     , .0     , .0     },
		{ 158.279, .74902 , .376471, .0     },
		{ 190.112, 1.     , .866667, .733333},
		{ 200.873, .937255, .937255, .937255},
		{ 3661.  , 1.     , 1.     , 1.     }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, MR_Angio_proper, 4ul);
	FillScalarOpacity(vpInfo, MR_Angio_opacity, 6ul);
	FillGrantyOpacity(vpInfo, MR_Angio_granty, 2ul);
	FillMap2Color(vpInfo, MR_Angio_color, 6ul);

	return vpInfo;
}

void VP::GetMRAngioVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE MR_Angio_proper[4] = {
		.2, 1. , .0 , 1.
	};
	const DOUBLE MR_Angio_opacity[6][2] = {
		{-2048.  , .0     }, { 151.354, .0     },
		{ 158.279, .4375  }, { 190.112, .580357},
		{ 200.873, .732143}, { 3661.  , .741071}
	};
	const DOUBLE MR_Angio_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE MR_Angio_color[6][4] = {
		{-2048.  , .0     , .0     , .0     },
		{ 151.354, .0     , .0     , .0     },
		{ 158.279, .74902 , .376471, .0     },
		{ 190.112, 1.     , .866667, .733333},
		{ 200.873, .937255, .937255, .937255},
		{ 3661.  , 1.     , 1.     , 1.     }
	};

	FillMaterial(vpInfo, MR_Angio_proper, 4ul);
	FillScalarOpacity(vpInfo, MR_Angio_opacity, 6ul);
	FillGrantyOpacity(vpInfo, MR_Angio_granty, 2ul);
	FillMap2Color(vpInfo, MR_Angio_color, 6ul);
}

VPInfo * VP::GetMRDefaultVPInfo(void)
{
	const DOUBLE MR_Default_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE MR_Default_opacity[6][2] = {
		{ .0   , .0  }, { 20.   , .0 },
		{ 40.  , .15 }, { 120.  , .3 },
		{ 220. , .375}, { 1024. , .5 }
	};
	const DOUBLE MR_Default_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE MR_Default_color[6][4] = {
		{ .0    , .0     , .0     , .0       },
		{ 20.   , .168627, .0     , .0       },
		{ 40.   , .403922, .145098, .0784314 },
		{ 120.  , .780392, .607843, .380392  },
		{ 220.  , .847059, .835294, .788235  },
		{ 1024. , 1.     , 1.     , 1.       }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, MR_Default_proper, 4ul);
	FillScalarOpacity(vpInfo, MR_Default_opacity, 6ul);
	FillGrantyOpacity(vpInfo, MR_Default_granty, 2ul);
	FillMap2Color(vpInfo, MR_Default_color, 6ul);

	return vpInfo;
}

void VP::GetMRDefaultVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE MR_Default_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE MR_Default_opacity[6][2] = {
		{ .0   , .0  }, { 20.   , .0 },
		{ 40.  , .15 }, { 120.  , .3 },
		{ 220. , .375}, { 1024. , .5 }
	};
	const DOUBLE MR_Default_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE MR_Default_color[6][4] = {
		{ .0    , .0     , .0     , .0       },
		{ 20.   , .168627, .0     , .0       },
		{ 40.   , .403922, .145098, .0784314 },
		{ 120.  , .780392, .607843, .380392  },
		{ 220.  , .847059, .835294, .788235  },
		{ 1024. , 1.     , 1.     , 1.       }
	};

	FillMaterial(vpInfo, MR_Default_proper, 4ul);
	FillScalarOpacity(vpInfo, MR_Default_opacity, 6ul);
	FillGrantyOpacity(vpInfo, MR_Default_granty, 2ul);
	FillMap2Color(vpInfo, MR_Default_color, 6ul);
}

VPInfo * VP::GetMRMIPVPInfo(void)
{
	const DOUBLE MR_MIP_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE MR_MIP_opacity[4][2] = {
	{ .0     , .0 }, { 98.3725 , .0 },
	{ 416.637, 1. }, { 2800.   , 1. }
	};
	const DOUBLE MR_MIP_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE MR_MIP_color[4][4] = {
	{ .0     , 1.  , 1.  , 1. },
	{ 98.3725, 1.  , 1.  , 1. },
	{ 416.637, 1.  , 1.  , 1. },
	{ 2800.  , 1.  , 1.  , 1. }
	};

	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, MR_MIP_proper, 4ul);
	FillScalarOpacity(vpInfo, MR_MIP_opacity, 4ul);
	FillGrantyOpacity(vpInfo, MR_MIP_granty, 2ul);
	FillMap2Color(vpInfo, MR_MIP_color, 4ul);
	return vpInfo;
}

void VP::GetMRMIPVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}
	const DOUBLE MR_MIP_proper[4] = {
		.2, 1., .0, 1.
	};
	const DOUBLE MR_MIP_opacity[4][2] = {
	{ .0     , .0 }, { 98.3725 , .0 },
	{ 416.637, 1. }, { 2800.   , 1. }
	};
	const DOUBLE MR_MIP_granty[2][2] = {
		{ .0, 1. }, { 255. , 1. }
	};
	const DOUBLE MR_MIP_color[4][4] = {
	{ .0     , 1.  , 1.  , 1. },
	{ 98.3725, 1.  , 1.  , 1. },
	{ 416.637, 1.  , 1.  , 1. },
	{ 2800.  , 1.  , 1.  , 1. }
	};

	FillMaterial(vpInfo, MR_MIP_proper, 4ul);
	FillScalarOpacity(vpInfo, MR_MIP_opacity, 4ul);
	FillGrantyOpacity(vpInfo, MR_MIP_granty, 2ul);
	FillMap2Color(vpInfo, MR_MIP_color, 4ul);
}

VPInfo * VP::GetMRT2BrainVPInfo(void)
{
	const DOUBLE MR_T2_Brain_proper[4] = {
		   .3, .6, .5, 40.
	};
	const DOUBLE MR_T2_Brain_opacity[5][2] = {
	{ .0     , .0     }, { 36.05  , .0 },
	{ 218.302, .171429}, { 412.406, 1. },
	{ 641.   , 1.     }
	};
	const DOUBLE MR_T2_Brain_granty[2][2] = {
		{ .0, 1. }, { 160.25 , 1. }
	};
	const DOUBLE MR_T2_Brain_color[4][4] = {
		{ .0     , .0     , .0     , .0     },
		{ 98.7223, .956863, .839216, .192157},
		{ 412.406, .0     , .592157, .807843},
		{ 641.   , 1.     , 1.     , 1.     }
	};
	VPInfo* vpInfo = new VPInfo;
	FillMaterial(vpInfo, MR_T2_Brain_proper, 4ul);
	FillScalarOpacity(vpInfo, MR_T2_Brain_opacity, 5ul);
	FillGrantyOpacity(vpInfo, MR_T2_Brain_granty, 2ul);
	FillMap2Color(vpInfo, MR_T2_Brain_color, 4ul);

	return vpInfo;
}

void VP::GetMRT2BrainVPInfo(VPInfo * vpInfo)
{
	if(nullptr == vpInfo)
	{
		vpInfo = new VPInfo();
	}

	const DOUBLE MR_T2_Brain_proper[4] = {
		   .3, .6, .5, 40.
	};
	const DOUBLE MR_T2_Brain_opacity[5][2] = {
	{ .0     , .0     }, { 36.05  , .0 },
	{ 218.302, .171429}, { 412.406, 1. },
	{ 641.   , 1.     }
	};
	const DOUBLE MR_T2_Brain_granty[2][2] = {
		{ .0, 1. }, { 160.25 , 1. }
	};
	const DOUBLE MR_T2_Brain_color[4][4] = {
		{ .0     , .0     , .0     , .0     },
		{ 98.7223, .956863, .839216, .192157},
		{ 412.406, .0     , .592157, .807843},
		{ 641.   , 1.     , 1.     , 1.     }
	};
	FillMaterial(vpInfo, MR_T2_Brain_proper, 4ul);
	FillScalarOpacity(vpInfo, MR_T2_Brain_opacity, 5ul);
	FillGrantyOpacity(vpInfo, MR_T2_Brain_granty, 2ul);
	FillMap2Color(vpInfo, MR_T2_Brain_color, 4ul);
}

