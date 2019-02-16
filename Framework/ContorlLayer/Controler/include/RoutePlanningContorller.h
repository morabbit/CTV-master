#pragma once
#ifndef __MATHEMATICALGEOMETRYCTL_H
#define __MATHEMATICALGEOMETRYCTL_H
#include "Geometry.hpp"
#include "vtkCommonDefine.h"

class RoutePlanning final
{
public:
	RoutePlanning();
	~RoutePlanning();
	RoutePlanning(const RoutePlanning&);
	RoutePlanning& operator=(const RoutePlanning&);

public:
	void SetPoint(Point3d point, INT id);
	void SetPoint(Point3f point, INT id);

	void SetPoint(FLOAT point[3], INT id);
	void SetPoint(DOUBLE point[3], INT id);

	void SetPoint(FLOAT x, FLOAT y, FLOAT z, INT id);
	void SetPoint(DOUBLE x, DOUBLE y, DOUBLE z, INT id);

	void SetLineId(INT id);
	void DrawLine(INT id);

	void UpdatePoint(Point3f point, INT id);
	void UpdatePoint(Point3d point, INT id);

	void UpdatePoint(FLOAT point[3], INT id);
	void UpdatePoint(DOUBLE point[3], INT id);

	void UpdatePoint(FLOAT x, FLOAT y, FLOAT z, INT id);
	void UpdatePoint(DOUBLE x, DOUBLE y, DOUBLE z, INT id);
	
	// float type need to be complete
	SetColorMacro(FLOAT);
	SetColorMacro(DOUBLE);
	GetColorMacro(FLOAT);
	GetColorMacro(DOUBLE);

	void SetLinSize(FLOAT size, INT line_id);
	void GetLinSize(FLOAT& size, INT line_id);
	FLOAT GetLinSize(INT line_id);

	DOUBLE GetDistance(INT line_id);
	void GetDistance(DOUBLE& dist, INT line_id);

	NTSTATUS GetStatus();
	_String GetErrorMessage();
	
	vtkSmartPointer<vtkActor> GetLineActor(INT id);
	vtkSmartPointer<vtkActor> GetPoint1Actor(INT id);
	vtkSmartPointer<vtkActor> GetPoint2Actor(INT id);
	SerialActors GetAllActor();
	void RemoveLine(INT id);
	void RemoveAllLine();

private:
	template<class _Type>
	void __set_color_2_actor(_Type color, pLineObj& __obj, GOT gotp);

	template<class _Type>
	void __update_point(_Type point, INT id);

	template<class _Type>
	void __update_point(_Type x, _Type y, _Type z, INT id);

	template<class _Type>
	void __set_point(_Type point, INT id);

	template<class _Type>
	void __set_point(_Type x, _Type y, _Type z, INT id);

private:
	UINT __count__;
	_StrStm_ __err_msg__;
	NTSTATUS __status__;
	std::map<INT, pLineObj>  __lines__;// line id , obj 

};

template<class _Type>
inline void RoutePlanning::__set_color_2_actor(_Type color, pLineObj & __obj, GOT gotp)
{
	if(gotp == GOT::GeometryObjectTypeDefault)
	{
		__obj->__math__obj__->SetColor(color, PaintType::PaintTypeLine);
		__obj->__math__obj__->SetColor(color, PaintType::PaintTypeHeadPoint);
		__obj->__math__obj__->SetColor(color, PaintType::PaintTypeTailPoint);
	}
	else
	{
		if(gotp & GOT::GeometryObjectTypeLine)
		{
			__obj->__math__obj__->SetColor(color, PaintType::PaintTypeLine);
		}
		if(gotp & GOT::GeometryObjectTypeHeadPoint)
		{
			__obj->__math__obj__->SetColor(color, PaintType::PaintTypeHeadPoint);
		}
		if(gotp & GOT::GeometryObjectTypetailPoint)
		{
			__obj->__math__obj__->SetColor(color, PaintType::PaintTypeTailPoint);
		}
	}
}

template<class _Type>
inline void RoutePlanning::__update_point(_Type point, INT id)
{
	using mapIter = std::map<INT, pLineObj>::iterator;
	for(mapIter iter = __lines__.begin(); iter != __lines__.end(); iter++)
	{
		if(iter->second->headId == id)
		{
			iter->second->__math__obj__->UpdatePoint(point, 0);
			iter->second->__math__obj__->RefreshLine();
		}
		else if(iter->second->tailId == id)
		{
			iter->second->__math__obj__->UpdatePoint(point, 1);
			iter->second->__math__obj__->RefreshLine();
		}
	}
}

template<class _Type>
inline void RoutePlanning::__update_point(_Type x, _Type y, _Type z, INT id)
{
	using mapIter = std::map<INT, pLineObj>::iterator;
	for(mapIter iter = __lines__.begin(); iter != __lines__.end(); iter++)
	{
		if(iter->second->headId == id)
		{
			iter->second->__math__obj__->UpdatePoint(x, y, z, 0);
			iter->second->__math__obj__->RefreshLine();
		}
		else if(iter->second->tailId == id)
		{
			iter->second->__math__obj__->UpdatePoint(x, y, z, 1);
			iter->second->__math__obj__->RefreshLine();
		}
	}
}

template<class _Type>
inline void RoutePlanning::__set_point(_Type point, INT id)
{
	pLineObj& __obj = (--(__lines__.end()))->second;
	if(__count__ % 2 == 0)
	{
		__obj->headId = id;
		__obj->__math__obj__->SetPoint(point, true);
		__obj->__math__obj__->InitializePoint1Actor();
	}
	else
	{
		__obj->tailId = id;
		__obj->__math__obj__->SetPoint(point, false);
		__obj->__math__obj__->InitializePoint2Actor();
		__obj->__math__obj__->InitializeLineActor();
	}
	__count__++;
}

template<class _Type>
inline void RoutePlanning::__set_point(_Type x, _Type y, _Type z, INT id)
{
	pLineObj& __obj = (--(__lines__.end()))->second;
	if(__count__ % 2 == 0)
	{
		__obj->headId = id;
		__obj->__math__obj__->SetPoint(x, y, z, true);
		__obj->__math__obj__->InitializePoint1Actor();
	}
	else
	{
		__obj->tailId = id;
		__obj->__math__obj__->SetPoint(x, y, z, false);
		__obj->__math__obj__->InitializePoint2Actor();
		__obj->__math__obj__->InitializeLineActor();
	}
	__count__++;
}


#endif // !__MATHEMATICALGEOMETRYCTL_H