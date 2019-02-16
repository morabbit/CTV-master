#pragma once
#ifndef __HULLCONTROLPARAMETERINTERFACE_H
#define __HULLCONTROLPARAMETERINTERFACE_H

#include <Windows.h>

typedef struct ParmHullControl
{
public:
	float GetAngle() { return angle; }
	float GetTrimSize() { return trimSize; }
	int GetMinHullSize() { return minHullSize; }
	int GetCoordinateDeviation() { return cooDev; }
	int GetWidthPointsNumber() { return pointsNumbX; }
	int GetheightPointsNumber() { return pointsNumbY; }

	ParmHullControl& operator=(const ParmHullControl &hull) 
	{
		if(this == &hull) return *this;
		memset(this, 0, sizeof(ParmHullControl));
		memcpy(this, &hull, sizeof(ParmHullControl));
		return *this;
	}
public:
	ParmHullControl(const ParmHullControl& hull)
	{ 
		*this = hull;
	}

	ParmHullControl() 
		: pointsNumbX(7), pointsNumbY(7), trimSize(1.5),
		minHullSize(pointsNumbX * 2 + (pointsNumbY - 2) * 2),
		angle(10.0), cooDev(5)
	{}

	ParmHullControl(
		int width, int height, float size, 
		float agl, int cooDeviation, int hull_size = 0
	) :
		pointsNumbX(width), pointsNumbY(height), trimSize(size),
		minHullSize((hull_size == 0) ? (width * 2 + (height - 2) * 2) : hull_size),
		angle(agl), cooDev(cooDeviation) 
	{}

public:
	void SetAngle(float value) { angle = value; }
	void SetTrimSize(float value) { trimSize = value; }
	void SetMinHullSize(int size) { minHullSize = size; }
	void SetCoordinateDeviation(int value) { cooDev = value; }
	void SetWidthPointsNumber(int value) { pointsNumbX = value; }	
	void SetHeightPointsNumber(int value) { pointsNumbY = value; }

private:
	float angle    ;
	int   cooDev   ;
	float trimSize ;
	int pointsNumbX;
	int pointsNumbY;
	int minHullSize;	
}HullControl;

using HC = HullControl;

#endif // !__HULLCONTROLPARAMETERINTERFACE_H
