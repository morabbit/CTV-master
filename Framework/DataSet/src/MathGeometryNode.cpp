#include "pch.h"
#include "MathGeometryNode.h"



VolumeNode::VolumeNode()
{
	__initialize();
}

VolumeNode::~VolumeNode()
{
	//delete __next__;
}

VolumeNode::VolumeNode(const VolumeNode & obj)
{
	*this = obj;
}

VolumeNode::VolumeNode(Point3d point)
{
	__point__ = point;
	__initialize();
}

VolumeNode::VolumeNode(Point3f point)
{
	__point__ = point.TypeTransfer<DOUBLE>();
	__initialize();
}

VolumeNode::VolumeNode(FLOAT points[3])
{
	__point__.x = static_cast<DOUBLE>(points[0]);
	__point__.y = static_cast<DOUBLE>(points[1]);
	__point__.z = static_cast<DOUBLE>(points[2]);
	__initialize();
}

VolumeNode::VolumeNode(DOUBLE points[3])
{
	__point__.x = points[0];
	__point__.y = points[1];
	__point__.z = points[2];
	__initialize();
}

VolumeNode::VolumeNode(FLOAT x, FLOAT y, FLOAT z)
{
	__point__.x = static_cast<DOUBLE>(x);
	__point__.y = static_cast<DOUBLE>(y);
	__point__.z = static_cast<DOUBLE>(z);
	__initialize();
}

VolumeNode::VolumeNode(DOUBLE x, DOUBLE y, DOUBLE z)
{
	__point__.x = x;
	__point__.y = y;
	__point__.z = z;
	__initialize();
}

VolumeNode & VolumeNode::operator=(const VolumeNode & obj)
{
	this->id = obj.id;
	this->__size__ = obj.__size__;
	this->__next__ = obj.__next__;
	this->__point__ = obj.__point__;
	
	return *this;
}

void VolumeNode::UpdatePointPosition(Point3d point)
{
	__point__ = point;
}

void VolumeNode::UpdatePointPosition(Point3f point)
{
	__point__ = point.TypeTransfer<DOUBLE>();
}

void VolumeNode::UpdatePointPosition(FLOAT points[3])
{
	__point__.x = static_cast<DOUBLE>(points[0]);
	__point__.y = static_cast<DOUBLE>(points[1]);
	__point__.z = static_cast<DOUBLE>(points[2]);
}

void VolumeNode::UpdatePointPosition(DOUBLE points[3])
{
	__point__.x = points[0];
	__point__.y = points[1];
	__point__.z = points[2];
}

void VolumeNode::UpdatePointPosition(FLOAT x, FLOAT y, FLOAT z)
{
	__point__.x = static_cast<DOUBLE>(x);
	__point__.y = static_cast<DOUBLE>(y);
	__point__.z = static_cast<DOUBLE>(z);
}

void VolumeNode::UpdatePointPosition(DOUBLE x, DOUBLE y, DOUBLE z)
{
	__point__.x = x;
	__point__.y = y;
	__point__.z = z;
}

Point3d VolumeNode::GetPointPosition()
{
	return __point__;
}

void VolumeNode::GetPointPosition(Point3d & point)
{
	point = __point__;
}

void VolumeNode::GetPointPosition(DOUBLE point[3])
{
	point[0] = __point__.x;
	point[1] = __point__.y;
	point[2] = __point__.z;
}

void VolumeNode::GetPointPosition(DOUBLE & x, DOUBLE & y, DOUBLE & z)
{
	x = __point__.x;
	y = __point__.y;
	z = __point__.z;
}

void VolumeNode::SetSize(DOUBLE size)
{
	__size__ = size;
}

void VolumeNode::GetSize(DOUBLE & size)
{
	size = __size__;
}

DOUBLE VolumeNode::GetSize(void)
{
	return __size__;
}

void VolumeNode::__initialize()
{
	id = -1;
	__size__ = 16;
	__next__ = nullptr;
}
