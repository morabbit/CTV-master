#include "pch.h"
#include "MathGeometryLine.h"


VolumLine::VolumLine()
{
#ifdef _PointStory
	__head__ = new VolumeNode;
	__tail__ = new VolumeNode;
#else
	__head_id__ = new NodeId;
	__tail_id__ = new NodeId;
#endif
	initialize();
}

VolumLine::~VolumLine()
{
#ifdef _PointStory
	if(nullptr != __head__)
	{
		delete __head__;
	}

	if(nullptr != __head__)
	{
		delete __tail__;
	}
#else
	if(nullptr != __head_id__)
	{
		delete __head_id__;
	}

	if(nullptr != __tail_id__)
	{
		delete __tail_id__;
	}
#endif	
}

VolumLine::VolumLine(const VolumLine& __obj)
{
	*this = __obj;
}

#ifdef _PointStory
VolumLine::VolumLine(Point3d __hd, Point3d __tl)
{
	__head_id__ = new NodeId;
	__tail_id__ = new NodeId;
	__head__ = new VolumeNode(__hd);
	__tail__ = new VolumeNode(__tl);
	initialize();
}

VolumLine::VolumLine(Point3f __hd, Point3f __tl)
{
	__head_id__ = new NodeId;
	__tail_id__ = new NodeId;
	__head__ = new VolumeNode(__hd);
	__tail__ = new VolumeNode(__tl);
	initialize();
}

VolumLine::VolumLine(FLOAT __points[6])
{
	__head_id__ = new NodeId;
	__tail_id__ = new NodeId;
	__head__ = new VolumeNode(__points[0], __points[1], __points[2]);
	__tail__ = new VolumeNode(__points[3], __points[4], __points[5]);
	initialize();
}

VolumLine::VolumLine(DOUBLE __points[6])
{
	__head_id__ = new NodeId;
	__tail_id__ = new NodeId;
	__head__ = new VolumeNode(__points[0], __points[1], __points[2]);
	__tail__ = new VolumeNode(__points[3], __points[4], __points[5]);
	initialize();
}

VolumLine::VolumLine(FLOAT __hd[3], FLOAT __tl[3])
{
	__head_id__ = new NodeId;
	__tail_id__ = new NodeId;
	__head__ = new VolumeNode(__hd);
	__tail__ = new VolumeNode(__tl);
	initialize();
}

VolumLine::VolumLine(DOUBLE __hd[3], DOUBLE __tl[3])
{
	__head_id__ = new NodeId;
	__tail_id__ = new NodeId;
	__head__ = new VolumeNode(__hd);
	__tail__ = new VolumeNode(__tl);
	initialize();
}

VolumLine::VolumLine(FLOAT x1, FLOAT y1, FLOAT z1,
					 FLOAT x2, FLOAT y2, FLOAT z2)
{
	__head_id__ = new NodeId;
	__tail_id__ = new NodeId;
	__head__ = new VolumeNode(x1, y1, z1);
	__tail__ = new VolumeNode(x2, y2, z2);
	initialize();
}

VolumLine::VolumLine(DOUBLE x1, DOUBLE y1, DOUBLE z1,
					 DOUBLE x2, DOUBLE y2, DOUBLE z2)
{
	__head_id__ = new NodeId;
	__tail_id__ = new NodeId;
	__head__ = new VolumeNode(x1, y1, z1);
	__tail__ = new VolumeNode(x2, y2, z2);
	initialize();
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
#endif

VolumLine & VolumLine::operator=(const VolumLine& __obj)
{
#ifdef _PointStory
	this->__head__ = __obj.__head__;
	this->__tail__= __obj.__tail__;
#else
	this->__head_id__ = __obj.__head_id__;
	this->__tail_id__ = __obj.__tail_id__;
#endif

	this->__id__ = __obj.__id__;
	this->__line_size__ = __obj.__line_size__;
	this->__line_color__[0] = __obj.__line_color__[0];
	this->__line_color__[1] = __obj.__line_color__[1];
	this->__line_color__[2] = __obj.__line_color__[2];

	return *this;
}

void VolumLine::SetLineId(INT __id)
{
	this->__id__ = __id;
}

void VolumLine::SetHeadId(INT id)
{
#ifdef _PointStory
	__head__->id = id;
#else
	__head_id__->id = id;
#endif
}

void VolumLine::SetTailId(INT id)
{
#ifdef _PointStory
	__tail__->id = id;
#else
	__tail_id__->id = id;
#endif
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

INT VolumLine::GetLineId()
{
	return __id__;
}

INT VolumLine::GetHeadId()
{
#ifdef _PointStory
	return __head__->id;
#else
	return __head_id__->id;
#endif
}

INT VolumLine::GetTailId()
{
#ifdef _PointStory
	return __tail__->id;
#else
	return __tail_id__->id;
#endif
}

#ifdef _PointStory
VolumeNode* VolumLine::GetHeadPoint()
{
	return __head__;
}

VolumeNode* VolumLine::GetTaliPoint()
{
	return __tail__;
}

void VolumLine::GetHeadPoint(VolumeNode * head)
{
	head = __head__;
}

void VolumLine::GetTaliPoint(VolumeNode * tail)
{
	tail = __tail__;
}

void VolumLine::GetHeadPoint(Point3d & point)
{
	__head__->GetPointPosition(point);
}

void VolumLine::GetTaliPoint(Point3d & point)
{
	__tail__->GetPointPosition(point);
}

void VolumLine::GetHeadPoint(DOUBLE point[3])
{
	__head__->GetPointPosition(point);
}

void VolumLine::GetTaliPoint(DOUBLE point[3])
{
	__tail__->GetPointPosition(point);
}

void VolumLine::GetHeadPoint(DOUBLE & x, DOUBLE & y, DOUBLE & z)
{
	__head__->GetPointPosition(x, y, z);
}

void VolumLine::GetTaliPoint(DOUBLE & x, DOUBLE & y, DOUBLE & z)
{
	__tail__->GetPointPosition(x, y, z);
}

DOUBLE VolumLine::GetLineLength()
{
	Vector3d vec(__head__->GetPointPosition(), __tail__->GetPointPosition());
	return sqrt(vec.mod());
}

void VolumLine::GetLineLength(DOUBLE & length)
{
	Vector3d vec(__head__->GetPointPosition(), __tail__->GetPointPosition());
	length = sqrt(vec.mod());
}
#endif

bool VolumLine::CheckCurrentId(INT id)
{
	return (id == __id__);
}

bool VolumLine::CheckHeadId(INT id)
{
#ifdef _PointStory
	return (id == __head__->id);
#else
	return (id == __head_id__->id);
#endif
}

bool VolumLine::CheckTailId(INT id)
{
#ifdef _PointStory
	return (id == __tail__->id);
#else
	return (id == __tail_id__->id);
#endif
}

void VolumLine::initialize()
{
	__line_size__ = 5.0;
	__line_color__[0] = 180.0;
	__line_color__[1] = 0.0;
	__line_color__[2] = 210.0;
#ifdef _PointStory
	__head__->__next__ = __tail__;
	__tail__->__next__ = __head__;
#else
	__head_id__->next = __tail_id__;
	__tail_id__->next = __head_id__;
#endif
}

#ifdef _PointStory
void VolumLine::__update_head_point(Point3d __hd)
{
	__head__->UpdatePointPosition(__hd);
}

void VolumLine::__update_tail_point(Point3d __tl)
{
	__tail__->UpdatePointPosition(__tl);
}
#endif