#pragma once
#ifndef __DEVICATIONFILTERINTERFACE_H
#define __DEVICATIONFILTERINTERFACE_H


typedef struct deviationFilter
{
public:
	deviationFilter() 
		:__min_cnt__(10), __max_cnt__(650), __dvt__(5.0),
		__min_r__(2.3f), __max_r__(15.0f), __zoom__(4){}

	deviationFilter(
		int min, int max, float dev, 
		float min_r, float max_r, int zo
	) :
		__min_cnt__(min), __max_cnt__(max), __dvt__(dev),
		__min_r__(min_r), __max_r__(max_r), __zoom__(zo) {}

	deviationFilter(const deviationFilter& obj) 
	{
		*this = obj; 
	};

	deviationFilter& operator=(const deviationFilter& obj) 
	{
		this->__zoom__ = obj.__zoom__;
		this->__max_r__ = obj.__max_r__;
		this->__min_r__ = obj.__min_r__;
		this->__dvt__ = obj.__dvt__;
		this->__min_cnt__ = obj.__min_cnt__;
		this->__max_cnt__ = obj.__max_cnt__;
		return *this;
	};

public:
	int GetZoom() { return __zoom__; }
	float GetDeviation() { return __dvt__; }
	float GetMinRadius() { return __min_r__; }
	float GetMaxRadius() { return __max_r__; }
	int GetMinContoursSize() { return __min_cnt__; }
	int GetMaxContoursSize() { return __max_cnt__; }

public:
	void SetZoom(int z0) { __zoom__ = z0; }
	void SetDeviation(float dev) { __dvt__ = dev; }
	void SetMinRadius(float min_r) { __min_r__ = min_r; }
	void SetMaxRadius(float max_r) { __max_r__ = max_r; }
	void SetMinContoursSize(int min) { __min_cnt__ = min; }
	void SetMaxContoursSize(int max) { __max_cnt__ = max; }

private:
	int __zoom__;
	int __min_cnt__;// min counter size
	int __max_cnt__;
	float __dvt__; // deviation
	float __min_r__; // min radiuse
	float __max_r__;

}DeviationFilter;

using DF = DeviationFilter;
#endif // !__DEVICATIONFILTERINTERFACE_H
