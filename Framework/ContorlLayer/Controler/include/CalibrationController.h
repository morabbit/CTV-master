#pragma once
#ifndef __CALIBRATIONCONTROLLER_H
#define __CALIBRATIONCONTROLLER_H

#include "CommonImageFilterCtl.hxx"

class CalibrationController
{
public:
	CalibrationController();
	~CalibrationController();

public:
	/// find image points
	/// debug 
	PCalibration& GetCalibration(void);
	DF& GetDevationParm();
	SP& GetSobelParm();
	TP& GetThresholdParm();
	HC& GetHullSizeParm();	
	void SetDebug(bool dbg);

	void SetPath(CPCHAR path);
	
	NTSTATUS FindImagePoints();

	/// order points
	NTSTATUS
		OrderImagePoints();

	NTSTATUS
		OrderImagePoints(
			PFLOAT points,
			UINT cnt
		);

	/// clear points 
	NTSTATUS
		ClearImagePoints(
			CMat srcImge, 
			SerialCycleInfo srcPoints
		);

	NTSTATUS
		ClearImagePoints(
			CPCHAR path,
			SerialCycleInfo srcPoints
		);

	NTSTATUS
		ClearImagePoints(
			CMat srcImge,
			SerialPoint2f srcPoints,
			PFLOAT radiuses
		);
	
	NTSTATUS
		ClearImagePoints(
			CPCHAR path,
			SerialPoint2f srcPoints,
			PFLOAT radiuses
		);

	NTSTATUS
		ClearImagePoints(
			CMat srcImge,
			PFLOAT srcPoints,
			PFLOAT radiuses,
			UINT cnt
		);

	NTSTATUS
		ClearImagePoints(
			CPCHAR path,
			PFLOAT srcPoints,
			PFLOAT radiuses,
			UINT cnt
		);


	/// External calibration

	NTSTATUS
		CameraExternalCalibration(
			UINT pointCount,
			PFLOAT p3Ds,
			PFLOAT p2Ds,
			PDOUBLE inner,
			PDOUBLE distcofs
		);
	
	/// result

	/// found points
	NTSTATUS
		GetResultPoints(
			PFLOAT * p_points,
			PFLOAT * p_radiuses,
			UINT& cnt
		);

	SerialCycleInfo GetPointsInfo(void);
	void GetPointsInfo(SerialCycleInfo& info);

	PFLOAT GetRadiuses(void);
	void GetRadiuses(PFLOAT* pRadiuses);

	PFLOAT GetPoints(void);
	void GetPoints(PFLOAT* pPoints);

	UINT GetPointsCount(void);
	void GetPointsCount(UINT& cnt);

	SerialPoint2f GetPointsVec(void);
	void GetPointsVec(SerialPoint2f& result);

	/// order points
	PFLOAT GetOrderedPoints(void);
	void GetOrderedPoints(PFLOAT* pPoints);

	UINT GetOrderPointsCount(void);
	void GetOrderPointsCount(UINT& cnt);

	SerialPoint2f GetOrderPointsVec(void);
	void GetOrderPointsVec(SerialPoint2f& result);

	/// cleared points 
	CMat GetClearredPointsImage(void);
	void GetClearredPointsImage(CMat& result);

	PUCHAR GetResultImageBuffer(void);
	NTSTATUS GetResultImageBuffer(PUCHAR& result);

	/// external calibration 
	UINT GetOutterMatrixSize(void);
	void GetOutterMatrixSize(UINT& len);

	FLOAT GetMeanSquaredError(void);
	void  GetMeanSquaredError(FLOAT& err);

	PDOUBLE GetOutterMatrixArray(void);
	void GetOutterMatrixArray(PDOUBLE& result);
	SerialDouble GetOutterMatrixVector(void);
	void GetOutterMatrixVector(SerialDouble& result);

private:
	void __Initialize(void);
	
	void __WriteParameter2File(void);

	void
		__ReInitializeResultContainer(void);

	void 
		__DisplayThresholdImage(
			CMat thresh
		);

	void
		__DisplayFinalCycleMessage(void);

	NTSTATUS 
		__BasicImageProcessing(
			CMat& thresh
		);

	NTSTATUS
		__GenerateResultPoints(PFLOAT& __p_points);

	NTSTATUS
		__GenerateResultRadiuses(PFLOAT& __p_radiuses);
	
	NTSTATUS
		__GenerateOrderedResultPoint(PFLOAT& __p_points);

private:
	bool __dbg__;

	CPCHAR __path;
	UINT __p_cnt__;
	FLOAT __error__;
	CMat __cleared_img__;
	CMat __ext_outter__;

	SerialCycleInfo __infos__;
	SerialPoint2f __points_vec__;
	SerialPoint2f __ordered_vec__;
	ImageProcessing* processer;
	OrderingProcessing* __orderring__;
	ClearPointProcessing* __clearing__;
	ExtCalibrationProcessing* __extener__;
	PCalibration __calibrator__;
};


#endif // !__CALIBRATIONCONTROLLER_H
