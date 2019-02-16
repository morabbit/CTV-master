#pragma once
#ifndef __ORDERRINGPOINTSPROCESSING_H
#define __ORDERRINGPOINTSPROCESSING_H
#include "CalibrationPlateCommon.hpp"


class OrderingProcessing
{
public:
	OrderingProcessing();
	~OrderingProcessing();

public:
	void SetOriginPointNumber(_In_ UINT cnt);
	NTSTATUS SetSourcePoint(_In_ PFLOAT pSrcPoint);
	NTSTATUS SetSourcePoint(_In_ SerialPoint2f SrcPoint);
	NTSTATUS OrderingPoints(_Out_ SerialPoint2f& result);

	//SerialPoint2f GetOrderedPoints();
	//void GetOrderedPoints(_Out_ SerialPoint2f& result);

	//UINT GetOrderedPointsCount();
	//void GetOrderedPointsCount(_Out_ UINT& len);

private:
	NTSTATUS SegregationPointsGroup();
	NTSTATUS SetCenter1(); // 2 /3 / 4
	NTSTATUS SetCenter2(); // 2 /3 / 4
	NTSTATUS SeparatePoints(); // 2 /3 / 4

	SerialPoint2f
		PointsExtract();

	void
		GenerateResultPoints(
			_In_ POPRCI pInput,
			_Out_ SerialPoint2f& result
		);

	void 
		FinalResult(
			_In_ POPRCI pInput,
			_In_ bool AddFlip,
			_Out_ SerialPoint2f& result
	);

	NTSTATUS
		CalculateMinRegs(
			_Out_ POPRCI pInput
		);

;	NTSTATUS
		CalculateMinReg(
			_In_  SerialPoint2f  cluster1,
			_In_  SerialPoint2f  cluster2,
			_Out_ SerialPoint2f& correspondence,
			_Out_ INT*           fitNum,
			_Out_ DOUBLE*        totalError, 
			_Out_ P2F&           direction, 
			_Out_ P2F&           center
		);

	NTSTATUS
		RotatePrepare(
			_In_ SerialPoint2f   cluster1,
			_Out_ SerialPoint2f& cluster2,
			_Out_ P2F&	         clustrt1Center,
			_Out_ P2F&	         clustrt2Center,
			_Out_ CPDMatrix&     cpdCalib_1
		);

	void
		RotationRunning(
			_In_ SerialPoint2f   cluster1,
			_In_ SerialPoint2f   cluster2,
			_In_ P2F             center,
			_In_ INT             degree,
			_In_ INT             maxFit,
			_In_ DOUBLE          minError,
			_In_ CPDMatrix       cpdCalib_1,
			_Out_ SerialPoint2f& minKRT
		);

	FLOAT
		CalcClusterScale(
			_In_ SerialPoint2f cluster
		);

	P2F
		CalcClusterCenter(
			_In_ SerialPoint2f cluster
		);

	void 
		GetClusterDistanceList(
			_In_ FLOAT         dist,
			_In_ FLOAT         maxDist,
			_Out_ SerialInt&   distCnt,
			_Out_ SerialFloat& clsDistList
		);

	SerialFloat
		PairDistance(
			_In_ SerialPoint2f cluster,
			_Out_ FLOAT&       maxDistance
		);

	FLOAT
		CalculatePointsDistance(
			_In_ P2F p1,
			_In_ P2F p2
		);

	void
		RotatePoints(			
			_In_ P2F             center,
			_In_ INT             degree,
			_Out_ SerialPoint2f& OriginalKeyPoints
		);

	void
		findKeyPointsError(
			_In_ SerialPoint2f p1List,
			_In_ SerialPoint2f p2List,
			_Out_ INT*         num,
			_Out_ DOUBLE*      totalError
		);

private:
	UINT __org_cnt__;	
	CMat __center__;

	P2F __cluster_center_1__;
	P2F __cluster_center_2__;

	SerialInt __labels__;
	SerialPoint2f __org_point_vec__;
	SerialPoint2f __cluster_1__;
	SerialPoint2f __cluster_2__;
	/*SerialPoint2f __orderd_points__;*/
};

#endif // !__ORDERRINGPOINTSPROCESSING_H
