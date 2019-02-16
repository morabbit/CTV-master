#pragma once
#ifndef __CAMERAEXTERNALCALIBRATIONPROCESSING_H
#define __CAMERAEXTERNALCALIBRATIONPROCESSING_H

#include "CalibrationPlateCommon.hpp"


class ExtCalibrationProcessing
{
public:
	ExtCalibrationProcessing();
	~ExtCalibrationProcessing();

public:
	void 
		SetPointsCount(
			_In_ UINT num
		);

	NTSTATUS 
		SolveExternalMatiexes(
			_In_opt_ void
		);

	NTSTATUS 
		SetScreenPoints(
			_In_ PFLOAT P2Ds
		);

	NTSTATUS
		SetScreenPoints(
			_In_ SerialPoint2f P2Ds
		);

	NTSTATUS 
		SetWorldPoints(
			_In_ PFLOAT P3Ds
		);

	NTSTATUS
		SetWorldPoints(
			_In_ SerialPoint3f P3Ds
		);

	NTSTATUS
		SetdistCoeffs(
			_In_ PDOUBLE distCoeffs
		);

	NTSTATUS
		SetdistCoeffs(
			_In_ SerialDouble distCoeffs
		);

	NTSTATUS
		SetdistCoeffs(
			_In_ CMat distCoeffs
		);

	NTSTATUS 
		SetCameraMatrix(
			_In_ PDOUBLE innerMatrix
		);

	NTSTATUS
		SetCameraMatrix(
			_In_ SerialDouble innerMatrix
		);

	NTSTATUS
		SetCameraMatrix(
			_In_ CMat innerMatrix
		);

	NTSTATUS
		GenerateRotationMatrix(
			_Out_ CMat& outter
		);

	NTSTATUS
		GenerateMeanSquaredError(
			_Out_ FLOAT& outter
		);

private:
	INT
		__check_valid_matrix(
			_In_ CMat mat
		);

	NTSTATUS
		__check_valid_rvecs(
			_In_opt_ void
		);

	NTSTATUS
		__check_valid_tvecs(
			_In_opt_ void
		);

private:
	UINT __cnt__;
	
	CMat __rvecs__;
	CMat __tvecs__;
	CMat __dist_coeffs__;
	CMat __camera_matrix__;	
	
	SerialPoint3f __world_points__;
	SerialPoint2f __screen_points__;
};

#endif // !__CAMERAEXTERNALCALIBRATIONPROCESSING_H
