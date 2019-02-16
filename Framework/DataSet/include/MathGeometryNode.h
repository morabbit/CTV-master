#pragma once
#ifndef __MATHGEOMETRYNODE_H
#define __MATHGEOMETRYNODE_H

#include "FrameworkType.h"
#include "ContainerDefine.h"

struct NodeId
{
public:
	NodeId()
	{ 
		id = -1;
		next = nullptr;
	};

	~NodeId() 
	{
		if(nullptr != next)
		{
			delete next;
		}
	};

public:
	INT id;
	NodeId*  next;
};


class VolumeNode
{
public:
	VolumeNode();
	~VolumeNode();
	VolumeNode(const VolumeNode& obj);
	VolumeNode(Point3d point);
	VolumeNode(Point3f point);
	VolumeNode(FLOAT  points[3]);
	VolumeNode(DOUBLE  points[3]);
	VolumeNode(FLOAT x, FLOAT y, FLOAT z);
	VolumeNode(DOUBLE x, DOUBLE y, DOUBLE z);
	VolumeNode& operator=(const VolumeNode& obj);

	void UpdatePointPosition(Point3d point);
	void UpdatePointPosition(Point3f point);
	void UpdatePointPosition(FLOAT  points[3]);
	void UpdatePointPosition(DOUBLE  points[3]);
	void UpdatePointPosition(FLOAT x, FLOAT y, FLOAT z);
	void UpdatePointPosition(DOUBLE x, DOUBLE y, DOUBLE z);
	
	Point3d GetPointPosition();
	void GetPointPosition(Point3d& point);	
	void GetPointPosition(DOUBLE point[3]);
	void GetPointPosition(DOUBLE& x, DOUBLE& y, DOUBLE& z);

	void SetSize(DOUBLE size);
	void GetSize(DOUBLE& size);
	DOUBLE GetSize(void);

private:
	void __initialize();

public:
	INT id;	
	VolumeNode* __next__;

private:
	DOUBLE __size__;
	Point3d __point__;
};

#endif // !__MATHGEOMETRYNODE_H
