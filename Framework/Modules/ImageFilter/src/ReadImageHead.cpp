#include "pch.h"
#include "FrameworkErrorCode.h"
#include "..\..\ImageFilter\include\ReadImageHead.h"


ReadImageHead::ReadImageHead()
{
}

ReadImageHead::~ReadImageHead()
{
}

DciomObject ReadImageHead::LoadImageHead(CPCHAR __path)
{

	DcmtkLoadImage<void> __dcmtk;
	__dcmtk.LoadFile(__path);

	if(__dcmtk.GetStatus() != SUCCESSED)
	{
		return DciomObject();
	}
	__dcmtk.ParseFileFormat();
	__dcmtk.FillingDicomObj();

	return __dcmtk.GetData();
}
