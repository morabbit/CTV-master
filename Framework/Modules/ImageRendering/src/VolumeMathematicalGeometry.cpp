#include "pch.h"
#include "FrameworkDefine.h"
#include "..\include\VolumeMathematicalGeometry.h"

#include <vtkMath.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>

MathematicalGeometry::MathematicalGeometry()
{
	__p1_flag__ = false;
	__p2_flag__ = false;
	__points_count__ = 0;
	__status__ = SUCCESSED;
	__err_msg__ = _StrStm_();
	
	__line__ = vtkSmartPointer<vtkLineSource>::New();
	__line_actor__ = vtkSmartPointer<vtkActor>::New();
	__point1_actor__ = vtkSmartPointer<vtkActor>::New();
	__point2_actor__ = vtkSmartPointer<vtkActor>::New();
}

MathematicalGeometry::~MathematicalGeometry()
{
}

MathematicalGeometry::MathematicalGeometry(const MathematicalGeometry& __obj)
{
	*this = __obj;
}

MathematicalGeometry&
MathematicalGeometry::operator=(const MathematicalGeometry& __obj)
{
	this->__line__ = __obj.__line__;
	this->__status__ = __obj.__status__;
	this->__sphere1__ = __obj.__sphere1__;
	this->__sphere2__ = __obj.__sphere2__;
	this->__p1_flag__ = __obj.__p1_flag__;
	this->__p2_flag__ = __obj.__p2_flag__;
	this->__point_1__ = __obj.__point_1__;
	this->__point_2__ = __obj.__point_2__;
	this->__line_actor__ = __obj.__line_actor__;
	this->__point2_actor__ = __obj.__point2_actor__;
	this->__points_count__ = __obj.__points_count__;	

	this->__err_msg__ = _StrStm_();
	this->__err_msg__ << __obj.__err_msg__.str();
	return *this;
}

void MathematicalGeometry::SetPoint(Point3f __point, bool __first_point)
{	
	if(true == __first_point)
	{
		__point_1__ = __point.TypeTransfer<DOUBLE>();

		(true == __p1_flag__) ?
			__points_count__ :
			__points_count__++;

		__p1_flag__ = true;
	}
	else 
	{
		__point_2__ = __point.TypeTransfer<DOUBLE>();
		(true == __p2_flag__) ?
			__points_count__ : 
			__points_count__++;
		__p2_flag__ = true;
	}
}

void 
MathematicalGeometry::SetPoint(
	Point3d __point, bool __first_point)
{
	if(true == __first_point)
	{
		__point_1__ = __point;

		(true == __p1_flag__) ?
			__points_count__ : 
			__points_count__++;

		__p1_flag__ = true;
	}
	else 
	{
		__point_2__ = __point;
		(true == __p2_flag__) ? 
			__points_count__ :
			__points_count__++;

		__p2_flag__ = true;
	}
}

void 
MathematicalGeometry::SetPoint(
	FLOAT __point[3], bool __first_point)
{
	if(true == __first_point)
	{
		__point_1__.x = (DOUBLE)__point[0];
		__point_1__.y = (DOUBLE)__point[1];
		__point_1__.z = (DOUBLE)__point[2];

		(true == __p1_flag__) ? 
			__points_count__ :
			__points_count__++;

		__p1_flag__ = true;
	}
	else 
	{
		__point_2__.x = (DOUBLE)__point[0];
		__point_2__.y = (DOUBLE)__point[1];
		__point_2__.z = (DOUBLE)__point[2];
		(true == __p2_flag__) ?
			__points_count__ : 
			__points_count__++;

		__p2_flag__ = true;
	}
}

void 
MathematicalGeometry::SetPoint(
	DOUBLE __point[3], bool __first_point)
{
	if(true == __first_point)
	{
		__point_1__.x = __point[0];
		__point_1__.y = __point[1];
		__point_1__.z = __point[2];

		(true == __p1_flag__) ? 
			__points_count__ : 
			__points_count__++;

		__p1_flag__ = true;
	}
	else 
	{
		__point_2__.x = __point[0];
		__point_2__.y = __point[1];
		__point_2__.z = __point[2];
		(true == __p2_flag__) ? 
			__points_count__ : 
			__points_count__++;
		__p2_flag__ = true;
	}
}

void 
MathematicalGeometry::SetPoint(
	FLOAT x, FLOAT y, FLOAT z, bool __first_point)
{
	if(true == __first_point)
	{
		__point_1__.x = (DOUBLE)x;
		__point_1__.y = (DOUBLE)y;
		__point_1__.z = (DOUBLE)z;

		(true == __p1_flag__) ?
			__points_count__ :
			__points_count__++;

		__p1_flag__ = true;
	}
	else
	{
		__point_2__.x = (DOUBLE)x;
		__point_2__.y = (DOUBLE)y;
		__point_2__.z = (DOUBLE)z;
		(true == __p2_flag__) ? 
			__points_count__ :
			__points_count__++;

		__p2_flag__ = true;
	}
}

void 
MathematicalGeometry::SetPoint(
	DOUBLE x, DOUBLE y, DOUBLE z, bool __first_point)
{
	if(true == __first_point)
	{
		__point_1__.x = x;
		__point_1__.y = y;
		__point_1__.z = z;

		(true == __p1_flag__) ?
			__points_count__ :
			__points_count__++;

		__p1_flag__ = true;
	}
	else 
	{
		__point_2__.x = x;
		__point_2__.y = y;
		__point_2__.z = z;
		(true == __p2_flag__) ?
			__points_count__ :
			__points_count__++;

		__p2_flag__ = true;
	}
}

void MathematicalGeometry::InitializeLineActor()
{
	if(__points_count__ != 2)
	{
		__status__ = ONLY_SUPPORT_TWO_POINTS;
		__err_msg__ << "need 2 points, but current only ["
			<< __points_count__ << "] point(s) setted !"
			<< "Point1 Setted status = [" << __p1_flag__
			<< "], Point2 Setted status = [" << __p2_flag__
			<< "].";
		return;
	}
	__line__->SetPoint1(
		__point_1__.x,
		__point_1__.y,
		__point_1__.z
	);
	__line__->SetPoint2(
		__point_2__.x,
		__point_2__.y,
		__point_2__.z
	);
	RefreshLine();
	STATUS_SUCCESS(__status__);

	vtkSmartPointer<vtkPolyDataMapper> __mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	__mapper->SetInputData(__line__->GetOutput());
	
	__line_actor__->SetMapper(__mapper);
	__line_actor__->GetProperty()->SetLineWidth(5);
	__line_actor__->GetProperty()->SetColor(0.3, 0.1, 0.5);
}

void MathematicalGeometry::InitializePoint1Actor()
{
	__sphere1__ = vtkSmartPointer<vtkSphereSource>::New();
	__sphere1__->SetCenter(
		__point_1__.x, 
		__point_1__.y,
		__point_1__.z
	);
	__sphere1__->SetRadius(8.0);
	vtkSmartPointer<vtkPolyDataMapper> __mapper1 =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	__mapper1->SetInputConnection(__sphere1__->GetOutputPort());

	__point1_actor__->SetMapper(__mapper1);
	__point1_actor__->GetProperty()->SetColor(0.3, 0.1, 0.5);
}

void MathematicalGeometry::InitializePoint2Actor()
{
	__sphere2__ = vtkSmartPointer<vtkSphereSource>::New();
	__sphere2__->SetCenter(
		__point_2__.x,
		__point_2__.y,
		__point_2__.z
	);
	__sphere2__->SetRadius(8.0);
	vtkSmartPointer<vtkPolyDataMapper> __mapper2 =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	__mapper2->SetInputConnection(__sphere2__->GetOutputPort());

	__point2_actor__->SetMapper(__mapper2);
	__point2_actor__->GetProperty()->SetColor(0.3, 0.1, 0.5);
}

vtkSmartPointer<vtkActor> MathematicalGeometry::GetLineActor()
{
	return __line_actor__;
}

vtkSmartPointer<vtkActor> MathematicalGeometry::GetPoint1Actor()
{
	return __point1_actor__;
}

vtkSmartPointer<vtkActor> MathematicalGeometry::GetPoint2Actor()
{
	return __point2_actor__;
}


NTSTATUS
MathematicalGeometry::UpdatePoint(Point3f __point, UINT __index)
{
	if((false == __p1_flag__) || (false == __p2_flag__))
	{
		__status__ = ANOTHER_POINT_NOT_SET;
		__err_msg__ << "need to set 2 points to generate a line , "\
			"and then each points can be update";
		return __status__;
	}

	if(0 == __index)
	{		
		__point_1__ = __point.TypeTransfer<DOUBLE>();
		__set_point1();
	}
	else if(1 == __index)
	{
		__point_2__ = __point.TypeTransfer<DOUBLE>();
		__set_point2();
	}
	else
	{
		__status__ = ONLY_SUPPORT_TWO_POINTS;
		__err_msg__ << "input Index out of point index, "\
			"only support 2 points, start from 0 !";
		return __status__;
	}
	return SUCCESSED;
}

NTSTATUS MathematicalGeometry::UpdatePoint(Point3d __point, UINT __index)
{
	if((false == __p1_flag__) || (false == __p2_flag__))
	{
		__status__ = ANOTHER_POINT_NOT_SET;
		__err_msg__ << "need to set 2 points to generate a line , "\
			"and then each points can be update";
		return __status__;
	}

	if(0 == __index)
	{
		__point_1__ = __point;
		__set_point1();
	}
	else if(1 == __index)
	{
		__point_2__ = __point;
		__set_point2();
	}
	else
	{
		__status__ = ONLY_SUPPORT_TWO_POINTS;
		__err_msg__ << "input Index out of point index, "\
			"only support 2 points, start from 0 !";
		return __status__;
	}
	return SUCCESSED;
}

NTSTATUS MathematicalGeometry::UpdatePoint(FLOAT __point[3], UINT __index)
{
	if((false == __p1_flag__) || (false == __p2_flag__))
	{
		__status__ = ANOTHER_POINT_NOT_SET;
		__err_msg__ << "need to set 2 points to generate a line , "\
			"and then each points can be update";
		return __status__;
	}

	if(0 == __index)
	{
		__point_1__.x =(DOUBLE)__point[0];
		__point_1__.y =(DOUBLE)__point[1];
		__point_1__.z =(DOUBLE)__point[2];
		__set_point1();
	}
	else if(1 == __index)
	{
		__point_2__.x = (DOUBLE)__point[0];
		__point_2__.y = (DOUBLE)__point[1];
		__point_2__.z = (DOUBLE)__point[2];
		__set_point2();
	}
	else
	{
		__status__ = ONLY_SUPPORT_TWO_POINTS;
		__err_msg__ << "input Index out of point index, "\
			"only support 2 points, start from 0 !";
		return __status__;
	}

	return SUCCESSED;
}

NTSTATUS MathematicalGeometry::UpdatePoint(DOUBLE __point[3], UINT __index)
{
	if((false == __p1_flag__) || (false == __p2_flag__))
	{
		__status__ = ANOTHER_POINT_NOT_SET;
		__err_msg__ << "need to set 2 points to generate a line , "\
			"and then each points can be update";
		return __status__;
	}

	if(0 == __index)
	{
		__point_1__.x = __point[0];
		__point_1__.y = __point[1];
		__point_1__.z = __point[2];
		__set_point1();
	}
	else if(1 == __index)
	{
		__point_2__.x = __point[0];
		__point_2__.y = __point[1];
		__point_2__.z = __point[2];
		__set_point2();
	}
	else
	{
		__status__ = ONLY_SUPPORT_TWO_POINTS;
		__err_msg__ << "input Index out of point index, "\
			"only support 2 points, start from 0 !";
		return __status__;
	}

	return SUCCESSED;
}

NTSTATUS
MathematicalGeometry::UpdatePoint(
	FLOAT x, FLOAT y, FLOAT z, UINT __index)
{
	if((false == __p1_flag__) || (false == __p2_flag__))
	{
		__status__ = ANOTHER_POINT_NOT_SET;
		__err_msg__ << "need to set 2 points to generate a line , "\
			"and then each points can be update";
		return __status__;
	}

	if(0 == __index)
	{
		__point_1__.x = (DOUBLE)x;
		__point_1__.y = (DOUBLE)y;
		__point_1__.z = (DOUBLE)z;
		__set_point1();
	}
	else if(1 == __index)
	{
		__point_2__.x = (DOUBLE)x;
		__point_2__.y = (DOUBLE)y;
		__point_2__.z = (DOUBLE)z;
		__set_point2();
	}
	else
	{
		__status__ = ONLY_SUPPORT_TWO_POINTS;
		__err_msg__ << "input Index out of point index, "\
			"only support 2 points, start from 0 !";
		return __status__;
	}

	return SUCCESSED;
}

NTSTATUS
MathematicalGeometry::UpdatePoint(
	DOUBLE x, DOUBLE y, DOUBLE z, UINT __index)
{
	if((false == __p1_flag__) || (false == __p2_flag__))
	{
		__status__ = ANOTHER_POINT_NOT_SET;
		__err_msg__ << "need to set 2 points to generate a line , "\
			"and then each points can be update";
		return __status__;
	}

	if(0 == __index)
	{
		__point_1__.x = x;
		__point_1__.y = y;
		__point_1__.z = z;
		__set_point1();
	}
	else if(1 == __index)
	{
		__point_2__.x = x;
		__point_2__.y = y;
		__point_2__.z = z;
		__set_point2();
	}
	else
	{
		__status__ = ONLY_SUPPORT_TWO_POINTS;
		__err_msg__ << "input Index out of point index, "\
			"only support 2 points, start from 0 !";
		return __status__;
	}

	return SUCCESSED;
}

NTSTATUS MathematicalGeometry::RefreshLine()
{
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(__status__);
	__line__->Update();

	return SUCCESSED;
}

NTSTATUS MathematicalGeometry::GetStatus()
{
	return __status__;
}

_String MathematicalGeometry::GetErrorMessage()
{
	return __err_msg__.str();
}

DOUBLE MathematicalGeometry::GetDistance()
{
	DOUBLE p1[3], p2[3];
	p1[0] = __point_1__.x;
	p1[1] = __point_1__.y;
	p1[2] = __point_1__.z;
	p2[0] = __point_2__.x;
	p2[1] = __point_2__.y;
	p2[2] = __point_2__.z;	

	return sqrt(vtkMath::Distance2BetweenPoints(p1, p2));
}

DOUBLE MathematicalGeometry::GetDistance2()
{
	Vector3d vec(__point_1__, __point_2__);
	
	return vec.mod();
}

void MathematicalGeometry::GetPoint1(Point3d & point)
{
	point = __point_1__;
}

void MathematicalGeometry::GetPoint2(Point3d & point)
{
	point = __point_2__;
}

void MathematicalGeometry::GetPoint1(DOUBLE point[3])
{
	point[0] = __point_1__.x;
	point[2] = __point_1__.y;
	point[3] = __point_1__.z;
}

void MathematicalGeometry::GetPoint2(DOUBLE point[3])
{
	point[0] = __point_2__.x;
	point[2] = __point_2__.y;
	point[3] = __point_2__.z;
}

void MathematicalGeometry::GetPoint1(DOUBLE & x, DOUBLE & y, DOUBLE & z)
{
	x = __point_1__.x;
	y = __point_1__.y;
	z = __point_1__.z;
}

void MathematicalGeometry::GetPoint2(DOUBLE & x, DOUBLE & y, DOUBLE & z)
{
	x = __point_2__.x;
	y = __point_2__.y;
	z = __point_2__.z;
}

void MathematicalGeometry::SetColor(FLOAT color[3], PaintType ptp)
{
	switch(ptp)
	{
		case PaintTypeLine:
			__line_actor__->GetProperty()->SetColor(
				static_cast<DOUBLE>(color[0]), 
				static_cast<DOUBLE>(color[1]),
				static_cast<DOUBLE>(color[2])
			);
			break;
		case PaintTypeHeadPoint:
			__point1_actor__->GetProperty()->SetColor(
				static_cast<DOUBLE>(color[0]),
				static_cast<DOUBLE>(color[1]),
				static_cast<DOUBLE>(color[2])
			);
			break;
		case PaintTypeTailPoint:
			__point2_actor__->GetProperty()->SetColor(
				static_cast<DOUBLE>(color[0]),
				static_cast<DOUBLE>(color[1]),
				static_cast<DOUBLE>(color[2])
			);
			break;
		default:
			break;
	}
}

void MathematicalGeometry::SetColor(DOUBLE color[3], PaintType ptp)
{
	switch(ptp)
	{
		case PaintTypeLine:
			__line_actor__->GetProperty()->SetColor(color);
			break;
		case PaintTypeHeadPoint:
			__point1_actor__->GetProperty()->SetColor(color);
			break;
		case PaintTypeTailPoint:
			__point2_actor__->GetProperty()->SetColor(color);
			break;
		default:
			break;
	}
}

void MathematicalGeometry::SetColor(FLOAT r, FLOAT g, FLOAT b, PaintType ptp)
{
	switch(ptp)
	{
		case PaintTypeLine:
			__line_actor__->GetProperty()->SetColor(
				static_cast<DOUBLE>(r),
				static_cast<DOUBLE>(g),
				static_cast<DOUBLE>(b)
			);
			break;
		case PaintTypeHeadPoint:
			__point1_actor__->GetProperty()->SetColor(
				static_cast<DOUBLE>(r),
				static_cast<DOUBLE>(g),
				static_cast<DOUBLE>(b)
			);
			break;
		case PaintTypeTailPoint:
			__point2_actor__->GetProperty()->SetColor(
				static_cast<DOUBLE>(r),
				static_cast<DOUBLE>(g),
				static_cast<DOUBLE>(b)
			);
			break;
		default:
			break;
	}
}

void MathematicalGeometry::SetColor(DOUBLE r, DOUBLE g, DOUBLE b, PaintType ptp)
{
	switch(ptp)
	{
		case PaintTypeLine:
			__line_actor__->GetProperty()->SetColor(r, g, b);
			break;
		case PaintTypeHeadPoint:
			__point1_actor__->GetProperty()->SetColor(r, g, b);
			break;
		case PaintTypeTailPoint:
			__point2_actor__->GetProperty()->SetColor(r, g, b);
			break;
		default:
			break;
	}
}

void MathematicalGeometry::GetColor(DOUBLE color[3], PaintType ptp)
{
	switch(ptp)
	{
		case PaintTypeLine:
			__line_actor__->GetProperty()->GetColor(color);
			break;
		case PaintTypeHeadPoint:
			__point1_actor__->GetProperty()->GetColor(color);
			break;
		case PaintTypeTailPoint:
			__point2_actor__->GetProperty()->GetColor(color);
			break;
		default:
			color[0] = -1.;
			color[1] = -1.;
			color[2] = -1.;
			break;
	}
}

void
MathematicalGeometry::GetColor(DOUBLE& r, DOUBLE& g, DOUBLE& b, PaintType ptp)
{
	switch(ptp)
	{
		case PaintTypeLine:
			__line_actor__->GetProperty()->GetColor(r, g, b);
			break;
		case PaintTypeHeadPoint:
			__point1_actor__->GetProperty()->GetColor(r, g, b);
			break;
		case PaintTypeTailPoint:
			__point2_actor__->GetProperty()->GetColor(r, g, b);
			break;
		default:
			r = -1.;
			g = -1.;
			b = -1.;
			break;
	}
}

void MathematicalGeometry::SetLineSize(FLOAT size)
{
	__line_actor__->GetProperty()->SetLineWidth(size);
}

void MathematicalGeometry::GetLineSize(FLOAT & size)
{
	size = __line_actor__->GetProperty()->GetLineWidth();
}

FLOAT MathematicalGeometry::GetLineSize(void)
{
	return __line_actor__->GetProperty()->GetLineWidth();
}

void MathematicalGeometry::__set_point1()
{
	__line__->SetPoint1(
		__point_1__.x,
		__point_1__.y,
		__point_1__.z
	);
	__sphere1__->SetCenter(
		__point_1__.x,
		__point_1__.y,
		__point_1__.z
	);
}

void MathematicalGeometry::__set_point2()
{
	__line__->SetPoint2(
		__point_2__.x,
		__point_2__.y,
		__point_2__.z
	);
	__sphere2__->SetCenter(
		__point_2__.x,
		__point_2__.y,
		__point_2__.z
	);
}

