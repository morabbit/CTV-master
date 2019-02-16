#include "pch.h"
//#include "FrameworkErrorCode.h"
#include "FrameCommonFunctionMacro.h"
#include "TraceLogExporter.h"

#include "..\include\RoutePlanningContorller.h"


RoutePlanning::RoutePlanning()
{
	__count__ = 0;
}

RoutePlanning::~RoutePlanning()
{
	RemoveAllLine();
}

RoutePlanning::RoutePlanning(const RoutePlanning& __obj)
{
	*this = __obj;
}

RoutePlanning& RoutePlanning::operator=(const RoutePlanning& __obj)
{
	this->__status__ = __obj.__status__;
	this->__err_msg__ = _StrStm_();
	this->__err_msg__ << __obj.__err_msg__.str();
	this->__lines__ = __obj.__lines__;

	return *this;
}

void RoutePlanning::SetPoint(Point3d point, INT id)
{
	__set_point<Point3d>(point, id);
}

void RoutePlanning::SetPoint(Point3f point, INT id)
{
	__set_point<Point3f>(point, id);
}

void RoutePlanning::SetPoint(FLOAT point[3], INT id)
{
	__set_point<FLOAT[3]>(point, id);
}

void RoutePlanning::SetPoint(DOUBLE point[3], INT id)
{
	__set_point<DOUBLE[3]>(point, id);
}

void RoutePlanning::SetPoint(FLOAT x, FLOAT y, FLOAT z, INT id)
{
	__set_point<FLOAT>(x, y, z, id);
}

void RoutePlanning::SetPoint(DOUBLE x, DOUBLE y, DOUBLE z, INT id)
{
	__set_point<DOUBLE>(x, y, z, id);
}

void RoutePlanning::SetLineId(INT id)
{
	pLineObj __obj = new LineObject();
	__obj->id = id;
	__obj->__math__obj__ = new MathematicalGeometry();
	//__lines__.insert(std::make_pair(__obj->id, __obj));
	__lines__.emplace(std::make_pair(__obj->id, __obj));
}

void RoutePlanning::DrawLine(INT id)
{
	pLineObj& __obj = (--(__lines__.end()))->second;
	__obj->__math__obj__->InitializeLineActor();

	vtkSmartPointer<vtkActor> __line_actor
		= __obj->__math__obj__->GetLineActor();
}

void RoutePlanning::UpdatePoint(Point3f point, INT id)
{
	__update_point<Point3f>(point, id);
}

void RoutePlanning::UpdatePoint(Point3d point, INT id)
{
	__update_point<Point3d>(point, id);
}

void RoutePlanning::UpdatePoint(FLOAT point[3], INT id)
{
	__update_point<FLOAT[3]>(point, id);
}

void RoutePlanning::UpdatePoint(DOUBLE point[3], INT id)
{
	__update_point<DOUBLE[3]>(point, id);
}

void RoutePlanning::UpdatePoint(FLOAT x, FLOAT y, FLOAT z, INT id)
{
	__update_point<FLOAT>(x, y, z, id);
}

void RoutePlanning::UpdatePoint(DOUBLE x, DOUBLE y, DOUBLE z, INT id)
{
	__update_point<DOUBLE>(x, y, z, id);
}

void RoutePlanning::SetLinSize(FLOAT size, INT line_id)
{
	if(__lines__.size() == 0)
	{
		return;
	}
	pLineObj __obj = nullptr;
	if(-1 == line_id)
	{
		__obj = (--(__lines__.end()))->second;
	}
	else
	{
		__obj = __lines__[line_id];
	}
	__obj->__math__obj__->SetLineSize(size);
}

void RoutePlanning::GetLinSize(FLOAT& size, INT line_id)
{
	if(__lines__.size() == 0)
	{
		return;
	}
	pLineObj __obj = nullptr;
	if(-1 == line_id)
	{
		__obj = (--(__lines__.end()))->second;
	}
	else
	{
		__obj = __lines__[line_id];
	}

	__obj->__math__obj__->GetLineSize(size);
}

FLOAT RoutePlanning::GetLinSize(INT line_id)
{
	if(__lines__.size() == 0)
	{
		return 0.0;
	}
	pLineObj __obj = nullptr;
	if(-1 == line_id)
	{
		__obj = (--(__lines__.end()))->second;
	}
	else
	{
		__obj = __lines__[line_id];
	}

	return __obj->__math__obj__->GetLineSize();
}

DOUBLE RoutePlanning::GetDistance(INT line_id)
{
	return __lines__[line_id]->__math__obj__->GetDistance2();
}

void RoutePlanning::GetDistance(DOUBLE & dist, INT line_id)
{
	dist = __lines__[line_id]->__math__obj__->GetDistance2();
}

NTSTATUS RoutePlanning::GetStatus()
{
	return __status__;
}

_String RoutePlanning::GetErrorMessage()
{
	return __err_msg__.str();
}

vtkSmartPointer<vtkActor> RoutePlanning::GetLineActor(INT id)
{
	return __lines__[id]->__math__obj__->GetLineActor();
}

vtkSmartPointer<vtkActor> RoutePlanning::GetPoint1Actor(INT id)
{
	return __lines__[id]->__math__obj__->GetPoint1Actor();
}

vtkSmartPointer<vtkActor> RoutePlanning::GetPoint2Actor(INT id)
{
	return __lines__[id]->__math__obj__->GetPoint2Actor();
}

SerialActors RoutePlanning::GetAllActor()
{
	SerialActors actors;
	using mapIter = std::map<INT, pLineObj>::iterator;
	for(mapIter iter = __lines__.begin(); iter != __lines__.end(); iter++)
	{
		actors.push_back(iter->second->__math__obj__->GetLineActor());
		actors.push_back(iter->second->__math__obj__->GetPoint1Actor());
		actors.push_back(iter->second->__math__obj__->GetPoint2Actor());
	}
	return actors;
}

void RoutePlanning::RemoveLine(INT id)
{
	using mapIter = std::map<INT, pLineObj>::iterator;
	for(mapIter iter = __lines__.begin(); iter != __lines__.end(); iter++)
	{
		if(iter->first == id)
		{
			delete iter->second->__math__obj__;
			__lines__.erase(iter);
			break;
		}
	}
}

void RoutePlanning::RemoveAllLine()
{
	using mapIter = std::map<INT, pLineObj>::iterator;
	for(mapIter iter = __lines__.begin(); iter != __lines__.end(); iter++)
	{
		delete iter->second->__math__obj__;
	}
	__lines__.erase(__lines__.begin(), __lines__.end());
}

