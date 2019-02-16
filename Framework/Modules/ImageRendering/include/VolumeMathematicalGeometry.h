#pragma once
#ifndef __VOLUMEMATHEMATICALGEOMETRY_H
#define __VOLUMEMATHEMATICALGEOMETRY_H

#include <vtkLine.h>
#include <vtkActor.h>
#include <vtkSphereSource.h>
#include <vtkLineSource.h>
#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkUnstructuredGrid.h>

#include "ContainerDefine.h"
#include "FrameWorkType.h"

enum PaintType
{
	PaintTypeDefault   = -1, 
	PaintTypeLine      =  1,
	PaintTypeHeadPoint =  2,
	PaintTypeTailPoint =  3,
};

class MathematicalGeometry
{
public:
	MathematicalGeometry();
	~MathematicalGeometry();
	MathematicalGeometry(const MathematicalGeometry&);
	MathematicalGeometry& operator=(const MathematicalGeometry&);

public:
	void SetPoint(Point3f, bool);
	void SetPoint(Point3d, bool);
	void SetPoint(FLOAT[3], bool);
	void SetPoint(DOUBLE[3], bool);
	void SetPoint(FLOAT, FLOAT, FLOAT, bool);
	void SetPoint(DOUBLE, DOUBLE, DOUBLE, bool);

	void InitializeLineActor();
	void InitializePoint1Actor();
	void InitializePoint2Actor();

	vtkSmartPointer<vtkActor> GetLineActor();
	vtkSmartPointer<vtkActor> GetPoint1Actor();
	vtkSmartPointer<vtkActor> GetPoint2Actor();
	
	NTSTATUS UpdatePoint(Point3f, UINT);
	NTSTATUS UpdatePoint(Point3d, UINT);
	NTSTATUS UpdatePoint(FLOAT[3], UINT);
	NTSTATUS UpdatePoint(DOUBLE[3], UINT);
	NTSTATUS UpdatePoint(FLOAT, FLOAT, FLOAT, UINT);
	NTSTATUS UpdatePoint(DOUBLE, DOUBLE, DOUBLE, UINT);

	NTSTATUS RefreshLine();
	NTSTATUS GetStatus();

	_String GetErrorMessage();

	DOUBLE GetDistance();
	DOUBLE GetDistance2();

	void GetPoint1(Point3d& point);
	void GetPoint2(Point3d& point);

	void GetPoint1(DOUBLE point[3]);
	void GetPoint2(DOUBLE point[3]);

	void GetPoint1(DOUBLE& x, DOUBLE& y, DOUBLE& z);
	void GetPoint2(DOUBLE& x, DOUBLE& y, DOUBLE& z);

	void SetColor(FLOAT color[3], PaintType ptp=PaintTypeDefault);
	void SetColor(DOUBLE color[3], PaintType ptp=PaintTypeDefault);

	void SetColor(FLOAT r, FLOAT g, FLOAT b, PaintType ptp=PaintTypeDefault);
	void SetColor(DOUBLE r, DOUBLE g, DOUBLE b, PaintType ptp=PaintTypeDefault);

	void GetColor(DOUBLE color[3], PaintType ptp = PaintTypeDefault);
	void GetColor(DOUBLE& r, DOUBLE& g, DOUBLE& b, PaintType ptp = PaintTypeDefault);

	void SetLineSize(FLOAT size);
	void GetLineSize(FLOAT& size);
	FLOAT GetLineSize(void);

private:
	void __set_point1();
	void __set_point2();

private:
	bool __p1_flag__;
	bool __p2_flag__;

	UINT __points_count__;

	Point3d __point_1__;
	Point3d __point_2__;
	
	_StrStm_ __err_msg__;
	NTSTATUS __status__;
		
	//vtkSmartPointer<vtkPoints> __points__;
	vtkSmartPointer<vtkLineSource> __line__;
	vtkSmartPointer<vtkActor> __line_actor__;
	vtkSmartPointer<vtkActor> __point1_actor__;
	vtkSmartPointer<vtkActor> __point2_actor__;
	vtkSmartPointer<vtkSphereSource> __sphere1__;
	vtkSmartPointer<vtkSphereSource> __sphere2__;
	//vtkSmartPointer<vtkCellArray> __vertices__;
};

#endif // !__VOLUMEMATHEMATICALGEOMETRY_H
