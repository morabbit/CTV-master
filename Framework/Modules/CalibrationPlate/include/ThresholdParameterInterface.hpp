#pragma once
#ifndef __THRESHOLDPARAMETERINTERFACE_H
#define __THRESHOLDPARAMETERINTERFACE_H


typedef struct thresholdParameter
{
public:
	thresholdParameter() 
		:__thresh__(128.0), __max_val__(255.0), __type__(8)
	{}

	thresholdParameter(
		double th, double mv, int tp
	) :
		__thresh__(th), __max_val__(mv), __type__(tp)
	{}

	thresholdParameter(const thresholdParameter &obj) 
	{ 
		*this = obj;
	};

	thresholdParameter& operator=(const thresholdParameter &obj)
	{
		this->__type__ = obj.__type__;
		this->__thresh__ = obj.__thresh__;
		this->__max_val__ = obj.__max_val__;
		return *this;
	};

public:
	int GetType() { return __type__; }
	double GetThresh() { return __thresh__; }
	double GetMaxval() { return __max_val__; }

public:
	void SetType(int tp) { __type__ = tp; }
	void SetThresh(double value) { __thresh__ = value; }
	void SetMaxval(double value) { __max_val__ = value; }

private:
	int __type__;
	double __thresh__;
	double __max_val__;

}ThresholdParam;

using TP = ThresholdParam;
#endif // !__THRESHOLDPARAMETERINTERFACE_H

