#pragma once
#ifndef __BASICDICOMOBJECT_HXX
#define __BASICDICOMOBJECT_HXX

//#include "FrameworkLibrary.h"
#include <map>
#include <vector>
#include "ContainerDefine.h"

struct DciomObject
{
public:
	DciomObject() {
		nFlag = -1; 
		nLoaded = -1;
	};
	~DciomObject() {};
	DciomObject(const DciomObject& _obj);
	DciomObject& operator=(const DciomObject& _obj);

public:
	/// <@ dimensions
	unsigned int dims;
	/// <@ patient id 
	std::string patientId;
	/// <@ patient name 
	std::string patientName;
	/// <@ study instance uid 
	std::string studyInstanceUID;
	/// <@ study id
	std::string studyID;	
	/// <@ series number 
	int seriesNO;	
	/// <@serues instance uid 
	std::string seriesInstanceUID;
	/// <@ image number 
	int imageNO;
	/// <@ patient sexy 
	std::string patientSex;
	/// <@ paient birth day 
	std::string patientBirthDate;
	/// <@ serise description 
	std::string seriesDescription;
	/// <@ hosptital name 
	std::string institution;
	/// <@ voltage
	int kvp;
	/// <@ electric current
	int electricCurrent;
	/// <@ Instance Creation Date 
	std::string InstanceCreationDate;
	/// <@ Instance Creation Time 
	std::string InstanceCreationTime;
	/// <@ Instance Creation UID 
	std::string InstanceCreatorUID;

	/// <@ summarize of x , it's image width
	UINT nx;
	/// <@ summarize of y , it's image height
	UINT ny;
	/// <@ summarize of z , it's image depth (3D)
	UINT nz;
	/// <@ depth of each layer (3D)
	double dz;
	/// <@ width of each layer 
	double dx;
	/// <@ height of each layer 
	double dy;
	/// <@  patient position 
	std::string patientPosition;
	/// <@  image position 
	Point3f imagePosition; /// origin + spacing * index * dims
	/// <@ image orientation
	std::vector<double> imageOrientation;
	/// <@ image origin
	double origin[3];
	/// <@ max value
	int maxValue;
	/// <@ min value
	int minValue;
	/// <@ default windows width 
	int W;
	/// <@ default windows level
	int L;
	/// <@ The human body orientation represented by
	///    the positive direction of x in this figure 
    ///    is A combination of 'A','P','L','R','S' and 'I'
	std::string rightSide;
	 /// <@ The human body orientation represented by
	///    the negative direction of x in this figure 
    ///    is A combination of 'A','P','L','R','S' and 'I'
	std::string leftSide;
	/// <@ The human body orientation represented by
	///    the positive direction of y in this figure 
	///    is A combination of 'A','P','L','R','S' and 'I'
	std::string upSide;
	/// <@ The human body orientation represented by
	///    the negative direction of y in this figure 
	///    is A combination of 'A','P','L','R','S' and 'I'
	std::string downSide;

	INT nFlag;
	INT nLoaded;
};

inline DciomObject::DciomObject(const DciomObject & _obj)
{
	*this = _obj;
}

inline DciomObject & DciomObject::operator=(const DciomObject & _obj)
{	
	W  = _obj.W; 	L = _obj.L;
	nx = _obj.nx;	ny = _obj.ny;
	nz = _obj.nz;	dz = _obj.dz;
	dx = _obj.dx;	dy = _obj.dy;
	kvp = _obj.kvp; nLoaded = _obj.nLoaded;
	electricCurrent = _obj.electricCurrent;
	seriesDescription = _obj.seriesDescription;
	studyInstanceUID = _obj.studyInstanceUID;
	seriesInstanceUID = _obj.seriesInstanceUID;	
	InstanceCreatorUID = _obj.InstanceCreatorUID;
	InstanceCreationDate = _obj.InstanceCreationDate;
	InstanceCreationTime = _obj.InstanceCreationTime;
	upSide = _obj.upSide;	    imageNO = _obj.imageNO;
	studyID = _obj.studyID;	maxValue = _obj.maxValue;
	minValue = _obj.minValue;	seriesNO = _obj.seriesNO;
	leftSide = _obj.leftSide;	downSide = _obj.downSide;
	rightSide = _obj.rightSide;	patientId = _obj.patientId;
	patientSex = _obj.patientSex; 	patientName = _obj.patientName;
	institution = _obj.institution;	imagePosition = _obj.imagePosition;
	patientPosition = _obj.patientPosition;	patientBirthDate = _obj.patientBirthDate;
	origin[0] = _obj.origin[0]; origin[1] = _obj.origin[1]; origin[2] = _obj.origin[2];	
	
	if(_obj.imageOrientation.size() == 0)
	{
		imageOrientation.clear();
	}
	else
	{
		imageOrientation.assign(_obj.imageOrientation.begin(), _obj.imageOrientation.end());
	}
	nFlag = _obj.nFlag;
	return *this;
}

#endif // !__BASICDICOMOBJECT_H
