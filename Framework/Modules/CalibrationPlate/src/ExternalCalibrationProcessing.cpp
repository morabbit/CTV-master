#include "pch.h"
#include "TraceLogExporter.h"
#include "FrameworkDefine.h"
#include "..\include\ExternalCalibrationProcessing.h"


ExtCalibrationProcessing::ExtCalibrationProcessing()
{
	__cnt__ = 0u;
	__dist_coeffs__ = CMat::zeros(8, 1, CV_64F);
	__camera_matrix__ = CMat::eye(3, 3, CV_64F);
}

ExtCalibrationProcessing::~ExtCalibrationProcessing()
{
}

void
ExtCalibrationProcessing::SetPointsCount(_In_ UINT num)
{
	__cnt__ = num;
}

NTSTATUS
ExtCalibrationProcessing::SolveExternalMatiexes(_In_opt_ void)
{
	try 
	{
		cv::solvePnP(__world_points__, __screen_points__,
				 __camera_matrix__, __dist_coeffs__, __rvecs__, __tvecs__);
	}
	catch(const std::exception& err) 
	{
		PRINT_DBG("input camera Internal matrix buffer is too small");
		TraceError << "solvePnP error : \n " << err.what();
		return SOLVE_PNP_FALIED;
	}
	NTSTATUS status = SUCCESSED;
	status = __check_valid_rvecs();
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);
	status = __check_valid_tvecs();
	CHECK_STATUS_AND_RETURN_STATUS_IF_FAILED(status);

	return status;
}

NTSTATUS
ExtCalibrationProcessing::SetScreenPoints(_In_ PFLOAT P2Ds)
{
	for(UINT i = 0; i < __cnt__; i++) 
	{
		try 
		{
			__screen_points__.push_back(P2F(P2Ds[i * 2], P2Ds[i * 2 + 1]));
		}
		catch(const std::exception& err)
		{
			PRINT_DBG("2D points buffer not matched with points number, buffer is too samle");
			TraceError << "2D buffer is too samle : \n " << err.what();
			return BUFFER_2D_TOO_SAMLE;
		}
	}
	return SUCCESSED;
}

NTSTATUS
ExtCalibrationProcessing::SetScreenPoints(_In_ SerialPoint2f P2Ds)
{
	if(P2Ds.size() < 5)
	{
		TraceError << "2D buffer is too samle ";
		return BUFFER_2D_TOO_SAMLE;
	}

	__screen_points__.swap(SerialPoint2f());
	__screen_points__.assign(P2Ds.begin(), P2Ds.end());

	return SUCCESSED;
}

NTSTATUS
ExtCalibrationProcessing::SetWorldPoints(_In_ PFLOAT P3Ds)
{
	for(unsigned int i = 0; i < __cnt__; i++) 
	{
		try 
		{
			__world_points__.push_back(P3F(P3Ds[i * 3], P3Ds[i * 3 + 1], P3Ds[i * 3 + 2]));
		}
		catch(const std::exception& err) 
		{
			PRINT_DBG("3D points buffer not matched with points number, buffer is too samle");
			TraceError << "3D buffer is too samle : \n " << err.what();
			return BUFFER_3D_TOO_SAMLE;
		}
	}
	return SUCCESSED;
}

NTSTATUS
ExtCalibrationProcessing::SetWorldPoints(_In_ SerialPoint3f P3Ds)
{
	if(P3Ds.size() < 5)
	{
		TraceError << "3D buffer is too samle ";
		return BUFFER_3D_TOO_SAMLE;
	}

	__world_points__.swap(SerialPoint3f());
	__world_points__.assign(P3Ds.begin(), P3Ds.end());

	return SUCCESSED;
}

NTSTATUS
ExtCalibrationProcessing::SetdistCoeffs(_In_ PDOUBLE distCoeffs)
{
	if((__dist_coeffs__.cols != 1) || (__dist_coeffs__.rows < 5))
	{
		__dist_coeffs__ = CMat::zeros(8, 1, CV_64F);
	}

	for(INT i = 0; i < 5; i++) 
	{
		try 
		{
			__dist_coeffs__.at<DOUBLE>(i, 0) = distCoeffs[i];
		}
		catch(const std::exception& err)
		{
			PRINT_DBG("input camera distortion coefficient buffer is too small");
			TraceError << "distortion coefficient error : \n " << err.what();
			return DIST_DOEFFS_BUFFER_TOO_SMALL;
		}
	}
	TraceLog << "distCs = :\n" << __dist_coeffs__;

	return SUCCESSED;
}

NTSTATUS 
ExtCalibrationProcessing::SetdistCoeffs(_In_ SerialDouble distCoeffs)
{
	if((__dist_coeffs__.cols != 1) || (__dist_coeffs__.rows < 5))
	{
		__dist_coeffs__ = CMat::zeros(8, 1, CV_64F);
	}

	if(distCoeffs.size() < 5)
	{
		PRINT_DBG("input camera distortion coefficient buffer is too small");
		return DIST_DOEFFS_BUFFER_TOO_SMALL;
	}

	for(INT i = 0; i < distCoeffs.size(); i++)
	{
		try
		{
			__dist_coeffs__.at<DOUBLE>(i, 0) = distCoeffs[i];
		}
		catch(const std::exception& err)
		{
			PRINT_DBG("input camera distortion coefficient buffer is too small");
			TraceError << "distortion coefficient error : \n " << err.what();
			return DIST_DOEFFS_BUFFER_TOO_SMALL;
		}
	}
	TraceLog << "distCs = :\n" << __dist_coeffs__;

	return SUCCESSED;
}

NTSTATUS 
ExtCalibrationProcessing::SetdistCoeffs(_In_ CMat distCoeffs)
{
	if((distCoeffs.cols != 1) || (distCoeffs.rows < 5))
	{
		PRINT_DBG("input camera distortion coefficient buffer is too small");
		return DIST_DOEFFS_BUFFER_TOO_SMALL;
	}

	__dist_coeffs__ = distCoeffs;

	return SUCCESSED;
}

NTSTATUS 
ExtCalibrationProcessing::SetCameraMatrix(_In_ PDOUBLE innerMatrix)
{
	if((__camera_matrix__.cols < 3) || (__camera_matrix__.rows < 3))
	{
		__camera_matrix__ = CMat::eye(3, 3, CV_64F);
	}

	for(INT i = 0; i < __camera_matrix__.rows; i++)
	{
		for(INT j = 0; j < __camera_matrix__.cols; j++)
		{
			try 
			{
				__camera_matrix__.at<DOUBLE>(i, j) 
					= innerMatrix[i * __camera_matrix__.rows + j];
			}
			catch(const std::exception& err) 
			{
				PRINT_DBG("input camera Internal matrix buffer is too small");
				TraceLog << "Internal Matrix error : \n " << err.what();
				return INNERMATRIX_BUFFER_TOO_SMALL;
			}
		}
	}

	TraceLog << "cameraMatrix = :\n" << __camera_matrix__;

	return SUCCESSED;
}

NTSTATUS 
ExtCalibrationProcessing::SetCameraMatrix(_In_ SerialDouble innerMatrix)
{
	if((__camera_matrix__.cols < 3) || (__camera_matrix__.rows < 3))
	{
		__camera_matrix__ = CMat::eye(3, 3, CV_64F);
	}

	if(innerMatrix.size() < __camera_matrix__.rows * __camera_matrix__.cols)
	{
		PRINT_DBG("input camera Internal matrix buffer is too small");
		return INNERMATRIX_BUFFER_TOO_SMALL;
	}

	for(INT i = 0; i < __camera_matrix__.rows; i++)
	{
		for(INT j = 0; j < __camera_matrix__.cols; j++)
		{
			try
			{
				__camera_matrix__.at<DOUBLE>(i, j)
					= innerMatrix[i * __camera_matrix__.rows + j];
			}
			catch(const std::exception& err)
			{
				PRINT_DBG("input camera Internal matrix buffer is too small");
				TraceLog << "Internal Matrix error : \n " << err.what();
				return INNERMATRIX_BUFFER_TOO_SMALL;
			}
		}
	}

	TraceLog << "cameraMatrix = :\n" << __camera_matrix__;

	return SUCCESSED;
}

NTSTATUS 
ExtCalibrationProcessing::SetCameraMatrix(_In_ CMat innerMatrix)
{
	if((innerMatrix.cols != 1) || (innerMatrix.rows < 5))
	{
		PRINT_DBG("input camera Internal matrix buffer is too small");
		return INNERMATRIX_BUFFER_TOO_SMALL;
	}

	__camera_matrix__ = innerMatrix;

	return SUCCESSED;
}

NTSTATUS 
ExtCalibrationProcessing::GenerateRotationMatrix(_Out_ CMat& outter)
{
	cv::Mat __RMatrix(3, 3, CV_64F);
	cv::Rodrigues(__rvecs__, __RMatrix);
	if(__check_valid_matrix(__RMatrix) == -1)
	{
		return ROTATION_MATRIX_INCLUDE_NAN;
	}

	cv::Mat_<DOUBLE> exMatrix(4, 4);
	try
	{
		exMatrix
			<<
			__RMatrix.at<DOUBLE>(0, 0), __RMatrix.at<DOUBLE>(1, 0),
			__RMatrix.at<DOUBLE>(2, 0), __tvecs__.at<DOUBLE>(0, 0),
			__RMatrix.at<DOUBLE>(0, 1), __RMatrix.at<DOUBLE>(1, 1),
			__RMatrix.at<DOUBLE>(2, 1), __tvecs__.at<DOUBLE>(0, 1),
			__RMatrix.at<DOUBLE>(0, 2), __RMatrix.at<DOUBLE>(1, 2),
			__RMatrix.at<DOUBLE>(2, 2), __tvecs__.at<DOUBLE>(0, 2),
			0, 0, 0, 1;
	}
	catch(const std::exception& err)
	{
		PRINT_DBG("input camera Internal matrix buffer is too small");
		TraceError << "input to Mat_<double>(4,4) error : \n " << err.what();
		return MATRIX_REDIRECT_FAILED;
	}
	outter = exMatrix;
	TraceLog << "ex = :\n" << outter;
	TraceLog << "RMatrix = :\n" << __RMatrix;

	if(this->__check_valid_matrix(outter) == -1)
	{
		return OUTER_MATRIX_INCLUDE_NAN;
	}
	
	return SUCCESSED;
}

NTSTATUS 
ExtCalibrationProcessing::GenerateMeanSquaredError(_Out_ FLOAT& outter)
{
	SerialPoint2f imagePoints2;
	try 
	{
		projectPoints(__world_points__, __rvecs__, __tvecs__,
					  __camera_matrix__, __dist_coeffs__, imagePoints2);
	}
	catch(const std::exception& err)
	{
		PRINT_DBG("project Points error with those input");
		TraceError << "project Points error : \n " << err.what();
		return PROJECT_POINTS_FAILED;
	}

	DOUBLE err = norm(CMat(__screen_points__), CMat(imagePoints2), CV_L2);
	if(__screen_points__.size() == 0) outter = 0.0;
	else outter = (FLOAT)std::sqrt(err*err / (FLOAT)__screen_points__.size());
	outter = isnan(outter) ? 0.0f : outter;

	TraceLog << "error = :\n" << outter;

	return SUCCESSED;
}


INT 
ExtCalibrationProcessing::__check_valid_matrix(_In_ CMat mat)
{
	for(INT i = 0; i < mat.rows; i++) 
	{
		for(INT j = 0; j < mat.cols; j++)
		{
			if(true == isnan(mat.at<DOUBLE>(i, j)))
			{
				return -1;
			}
		}
	}
	return 0;
}

NTSTATUS 
ExtCalibrationProcessing::__check_valid_rvecs(_In_opt_ void)
{
	if(this->__check_valid_matrix(__rvecs__) == -1)
	{
		return ROTATION_VECTOR_INCLUDE_NAN;
	}
	return SUCCESSED;
}

NTSTATUS
ExtCalibrationProcessing::__check_valid_tvecs(_In_opt_ void)
{
	if(this->__check_valid_matrix(__tvecs__) == -1)
	{
		return TRANSLATION_VECTOR_INCLUDE_NAN;
	}
	return SUCCESSED;
}
