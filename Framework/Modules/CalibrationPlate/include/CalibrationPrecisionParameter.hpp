#pragma once
#ifndef __CALIBRATIONPRECISIONPARAMETER_HPP
#define __CALIBRATIONPRECISIONPARAMETER_HPP

#include "SobleParameterInterface.hpp"
#include "DevicationFilterInterface.hpp"
#include "ThresholdParameterInterface.hpp"
#include "HullControlParameterInterface.hpp"

typedef struct CalibrationParameters 
{
public:
	//***Sobel param***//
	SP m_sobel;

	//***threshold param***//
	TP m_thresh;

	//** deviation param**//
	DF m_dvt;

	//** Hull Control param**//
	HC m_hull;

public:
	~CalibrationParameters() 
	{};

	CalibrationParameters(const CalibrationParameters& obj) 
	{
		*this = obj;
	};

	CalibrationParameters& operator=(const CalibrationParameters& obj)
	{
		this->m_sobel = obj.m_sobel;
		this->m_thresh = obj.m_thresh;
		this->m_dvt = obj.m_dvt;
		this->m_hull = obj.m_hull;

		return *this;
	};

	CalibrationParameters() 
		:m_sobel(), m_thresh(), m_dvt(), m_hull()
	{}

	CalibrationParameters(int Internal)
		:m_sobel(), m_thresh(),
		m_dvt(DF(10, 650, 1.5, 6.0, 16.0, 4)), m_hull()
	{}

}Calibration, *PCalibration;

#endif // !__CALIBRATIONPRECISIONPARAMETER_HPP
