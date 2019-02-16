#pragma once
#ifndef __COMMONMODULESLIBRARY_H
#define __COMMONMODULESLIBRARY_H

#include "ItkCommonDefine.hxx"

typedef struct ImageSourceDataAssemble
{
	double origin[ImageDimension];
	double spacing[ImageDimension];
	double direction[ImageDimension*ImageDimension];
	unsigned long ImageSize[ImageDimension];

}ImageHeader;

#endif // !__COMMONMODULESLIBRARY_H
