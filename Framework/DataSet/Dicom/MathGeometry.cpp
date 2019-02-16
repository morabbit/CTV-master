#include "pch.h"
#include "MathGeometry.h"


VolumLine::VolumLine()
{
	__line_color__[0] = 180.0;
	__line_color__[1] = 0.0;
	__line_color__[2] = 210.0;
}

VolumLine::~VolumLine()
{
}

VolumLine::VolumLine(Point3d __hd, Point3d __tl)
{
	__head__ = __hd;
	__tail__ = __tl;
	__line_color__[0] = 180.0;
	__line_color__[1] = 0.0;
	__line_color__[2] = 210.0;
}

VolumLine::VolumLine(Point3f __hd, Point3f __tl)
{
	__head__ = __hd.TypeTransfer<DOUBLE>();
	__tail__ = __tl.TypeTransfer<DOUBLE>();
	__line_color__[0] = 180.0;
	__line_color__[1] = 0.0;
	__line_color__[2] = 210.0;
}

VolumLine::VolumLine(const VolumLine& __obj)
{
	*this = __obj;
}

VolumLine::VolumLine(FLOAT __points[6])
{
	__line_color__[0] = 180.0;
	__line_color__[1] = 0.0;
	__line_color__[2] = 210.0;
	__head__.x = static_cast<DOUBLE>(__points[0]);
	__head__.y = static_cast<DOUBLE>(__points[1]);
	__head__.z = static_cast<DOUBLE>(__points[2]);
	__tail__.x = static_cast<DOUBLE>(__points[3]);
	__tail__.y = static_cast<DOUBLE>(__points[4]);
	__tail__.z = static_cast<DOUBLE>(__points[5]);
}

VolumLine::VolumLine(DOUBLE __points[6])
{
	__line_color__[0] = 180.0;
	__line_color__[1] = 0.0;
	__line_color__[2] = 210.0;

	__head__.x = __points[0];
	__head__.y = __points[1];
	__head__.z = __points[2];

	__tail__.x = __points[3];
	__tail__.y = __points[4];
	__tail__.z = __points[5];
}

VolumLine::VolumLine(FLOAT __hd[3], FLOAT __tl[3])
{
	__line_color__[0] = 180.0;
	__line_color__[1] = 0.0;
	__line_color__[2] = 210.0;

	__head__.x = static_cast<DOUBLE>(__hd[0]);
	__head__.y = static_cast<DOUBLE>(__hd[1]);
	__head__.z = static_cast<DOUBLE>(__hd[2]);

	__tail__.x = static_cast<DOUBLE>(__tl[0]);
	__tail__.y = static_cast<DOUBLE>(__tl[1]);
	__tail__.z = static_cast<DOUBLE>(__tl[2]);
}

VolumLine::VolumLine(DOUBLE __hd[3], DOUBLE __tl[3])
{
	__head__.x = __hd[0];
	__head__.y = __hd[1];
	__head__.z = __hd[2];

	__tail__.x = __tl[0];
	__tail__.y = __tl[1];
	__tail__.z = __tl[2];

	__line_color__[0] = 180.0;
	__line_color__[1] = 0.0;
	__line_color__[2] = 210.0;
}

VolumLine::VolumLine(DOUBLE x1, DOUBLE y1, DOUBLE z1,
					 DOUBLE x2, DOUBLE y2, DOUBLE z2)
{
	__head__.x = x1;
	__head__.y = y1;
	__head__.z = z1;

	__tail__.x = x2;
	__tail__.y = y2;
	__tail__.z = z2;

	__line_color__[0] = 180.0;
	__line_color__[1] = 0.0;
	__line_color__[2] = 210.0;
}

void VolumLine::UpdatePoint(Point3d point, bool isHead)
{
	if(true == isHead)
	{
		__update_head_point(point);
	}
	else
	{
		__update_tail_point(point);
	}
}

void VolumLine::UpdatePoint(Point3f point, bool isHead)
{
	if(true == isHead)
	{
		__update_head_point(point.TypeTransfer<DOUBLE>());
	}
	else
	{
		__update_tail_point(point.TypeTransfer<DOUBLE>());
	}
}

void VolumLine::UpdatePoint(FLOAT points[3], bool isHead)
{
	Point3d __point;
	__point.x = static_cast<DOUBLE>(points[0]);
	__point.y = static_cast<DOUBLE>(points[1]);
	__point.z = static_cast<DOUBLE>(points[2]);

	if(true == isHead)
	{
		__update_head_point(__point);
	}
	else
	{
		__update_tail_point(__point);
	}
}

void VolumLine::UpdatePoint(DOUBLE points[3], bool isHead)
{
	Point3d __point;
	__point.x = points[0];
	__point.y = points[1];
	__point.z = points[2];

	if(true == isHead)
	{
		__update_head_point(__point);
	}
	else
	{
		__update_tail_point(__point);
	}
}

void VolumLine::UpdatePoint(FLOAT x, FLOAT y, FLOAT z, bool isHead)
{
	Point3d __point;
	__point.x = static_cast<DOUBLE>(x);
	__point.y = static_cast<DOUBLE>(y);
	__point.z = static_cast<DOUBLE>(z);

	if(true == isHead)
	{
		__update_head_point(__point);
	}
	else
	{
		__update_tail_point(__point);
	}
}

void VolumLine::UpdatePoint(DOUBLE x, DOUBLE y, DOUBLE z, bool isHead)
{
	Point3d __point;
	__point.x = x;
	__point.y = y;
	__point.z = z;

	if(true == isHead)
	{
		__update_head_point(__point);
	}
	else
	{
		__update_tail_point(__point);
	}
}

VolumLine & VolumLine::operator=(const VolumLine& __obj)
{
	this->__id__ = __obj.__id__;
	this->__head__ = __obj.__head__;
	this->__tail__= __obj.__tail__;
	this->__line_size__ = __obj.__line_size__;
	this->__line_color__[0] = __obj.__line_color__[0];
	this->__line_color__[1] = __obj.__line_color__[1];
	this->__line_color__[2] = __obj.__line_color__[2];

	return *this;
}

VolumLine::VolumLine(FLOAT x1, FLOAT y1, FLOAT z1,
					 FLOAT x2, FLOAT y2, FLOAT z2)
{
	__head__.x = static_cast<DOUBLE>(x1);
	__head__.y = static_cast<DOUBLE>(y1);
	__head__.z = static_cast<DOUBLE>(z1);

	__tail__.x = static_cast<DOUBLE>(x2);
	__tail__.y = static_cast<DOUBLE>(y2);
	__tail__.z = static_cast<DOUBLE>(z2);
}

void VolumLine::SetLineId(UINT __id)
{
	this->__id__ = __id;
}

void VolumLine::SetLineSize(FLOAT size)
{
	__line_size__ = size;
}

void VolumLine::SetLineColor(FLOAT color[3])
{
	for(size_t i = 0; i < 3; i++)
	{
		__line_color__[i] = static_cast<DOUBLE>(color[i]);
	}
}

void VolumLine::SetLineColor(DOUBLE color[3])
{
	for(size_t i = 0; i < 3; i++)
	{
		__line_color__[i] = color[i];
	}
}

void VolumLine::SetLineColor(FLOAT r, FLOAT g, FLOAT b)
{
	__line_color__[0] = static_cast<DOUBLE>(r);
	__line_color__[1] = static_cast<DOUBLE>(g);
	__line_color__[2] = static_cast<DOUBLE>(b);
}

void VolumLine::SetLineColor(DOUBLE r, DOUBLE g, DOUBLE b)
{
	__line_color__[0] = r;
	__line_color__[1] = g;
	__line_color__[2] = b;
}

void VolumLine::GetLineColor(FLOAT color[3])
{
	for(size_t i = 0; i < 3; i++)
	{
		color[i] = static_cast<FLOAT>(__line_color__[i]);
	}
}

void VolumLine::GetLineColor(DOUBLE color[3])
{
	for(size_t i = 0; i < 3; i++)
	{
		color[i] = __line_color__[i];
	}
}

void VolumLine::GetLineColor(FLOAT & r, FLOAT & g, FLOAT & b)
{
	r = static_cast<FLOAT>(__line_color__[0]);
	g = static_cast<FLOAT>(__line_color__[1]);
	b = static_cast<FLOAT>(__line_color__[2]);
}

void VolumLine::GetLineColor(DOUBLE & r, DOUBLE & g, DOUBLE & b)
{
	r = __line_color__[0];
	g = __line_color__[1];
	b = __line_color__[2];
}

FLOAT VolumLine::GetLineSize()
{
	return __line_size__;
}

UINT VolumLine::GetLineId()
{
	return __id__;
}

Point3d VolumLine::GetHeadPoint()
{
	return __head__;
}

Point3d VolumLine::GetTaliPoint()
{
	return __tail__;
}

void VolumLine::GetHeadPoint(Point3d & point)
{
	point = __head__;
}

void VolumLine::GetTaliPoint(Point3d & point)
{
	point = __tail__;
}

void VolumLine::GetHeadPoint(DOUBLE point[3])
{
	point[0] = __head__.x;
	point[1] = __head__.y;
	point[2] = __head__.z;
}

void VolumLine::GetTaliPoint(DOUBLE point[3])
{
	point[0] = __head__.x;
	point[1] = __head__.y;
	point[2] = __head__.z;
}

void VolumLine::GetHeadPoint(DOUBLE & x, DOUBLE & y, DOUBLE & z)
{
	x = __tail__.x;
	y = __tail__.y;
	z = __tail__.z;
}

void VolumLine::GetTaliPoint(DOUBLE & x, DOUBLE & y, DOUBLE & z)
{
	x =__tail__.x;
	y =__tail__.y;
	z =__tail__.z;
}

DOUBLE VolumLine::GetLineLength()
{
	Vector3d vec(__head__, __tail__);
	return sqrt(vec.mod());
}

void VolumLine::GetLineLength(DOUBLE & length)
{
	Vector3d vec(__head__, __tail__);
	length = sqrt(vec.mod());
}

void VolumLine::__update_head_point(Point3d __hd)
{
	__head__.x = __hd.x;
	__head__.y = __hd.y;
	__head__.z = __hd.z;
}

void VolumLine::__update_tail_point(Point3d __tl)
{
	__tail__.x = __tl.x;
	__tail__.y = __tl.y;
	__tail__.z = __tl.z;
}
