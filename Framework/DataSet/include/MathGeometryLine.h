#pragma once
#ifndef __MATHGEOMETRYLINE_H
#define __MATHGEOMETRYLINE_H
#include "MathGeometryNode.h"


class VolumLine
{
public:
	VolumLine();
	~VolumLine();
	VolumLine(const VolumLine&);
	VolumLine& operator=(const VolumLine&);

#ifdef _PointStory
	VolumLine(Point3d __hd, Point3d __tl);
	VolumLine(Point3f __hd, Point3f __tl);
	
	VolumLine(FLOAT __points[6]);
	VolumLine(DOUBLE __points[6]);

	VolumLine(FLOAT __hd[3], FLOAT __tl[3]);
	VolumLine(DOUBLE __hd[3], DOUBLE __tl[3]);
	
	VolumLine(FLOAT x1, FLOAT y1, FLOAT z1, FLOAT x2, FLOAT y2, FLOAT z2);
	VolumLine(DOUBLE x1,DOUBLE y1,DOUBLE z1,DOUBLE x2,DOUBLE y2,DOUBLE z2);	
	
	void UpdatePoint(Point3d point, bool isHead);
	void UpdatePoint(Point3f point, bool isHead);

	void UpdatePoint(FLOAT  points[3], bool isHead);
	void UpdatePoint(DOUBLE points[3], bool isHead);	

	void UpdatePoint(FLOAT x, FLOAT y, FLOAT z, bool isHead);
	void UpdatePoint(DOUBLE x, DOUBLE y, DOUBLE z, bool isHead);
#endif // DEBUG

	void SetLineId(INT);
	void SetHeadId(INT);
	void SetTailId(INT);

	INT GetLineId();
	INT GetHeadId();
	INT GetTailId();

	void SetLineSize(FLOAT size);
	FLOAT GetLineSize();

	void SetLineColor(FLOAT color[3]);
	void SetLineColor(DOUBLE color[3]);

	void SetLineColor(FLOAT r, FLOAT g, FLOAT b);
	void SetLineColor(DOUBLE r, DOUBLE g, DOUBLE b);

	void GetLineColor(FLOAT color[3]);
	void GetLineColor(DOUBLE color[3]);
	
	void GetLineColor(FLOAT& r, FLOAT& g, FLOAT& b);
	void GetLineColor(DOUBLE& r, DOUBLE& g, DOUBLE& b);

#ifdef _PointStory
	VolumeNode* GetHeadPoint();
	VolumeNode* GetTaliPoint();

	void GetHeadPoint(VolumeNode*);
	void GetTaliPoint(VolumeNode*);

	void GetHeadPoint(Point3d& point);
	void GetTaliPoint(Point3d& point);

	void GetHeadPoint(DOUBLE point[3]);
	void GetTaliPoint(DOUBLE point[3]);

	void GetHeadPoint(DOUBLE& x, DOUBLE& y, DOUBLE& z);
	void GetTaliPoint(DOUBLE& x, DOUBLE& y, DOUBLE& z);
#endif

	DOUBLE GetLineLength();
	void GetLineLength(DOUBLE& length);
	
	bool CheckHeadId(INT id);
	bool CheckTailId(INT id);
	bool CheckCurrentId(INT id);

private:
	void initialize();
	void __update_head_point(Point3d);
	void __update_tail_point(Point3d);

private:	
	INT __id__;

#ifdef _PointStory
	VolumeNode* __head__;
	VolumeNode* __tail__;
#else 
	NodeId* __head_id__;
	NodeId* __tail_id__;
#endif

	FLOAT __line_size__;
	DOUBLE __line_color__[3];
};


#endif // !__MATHGEOMETRY_H
