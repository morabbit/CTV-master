#pragma once

#ifndef __SOBELPARAMETERINTERFACE_H
#define __SOBELPARAMETERINTERFACE_H


#ifndef CV_8U
#define CV_8U   0
#endif

#ifndef CV_8S
#define CV_8S   1
#endif //CV_8S

#ifndef CV_16U
#define CV_16U  2
#endif // CV_16U

#ifndef CV_16S
#define CV_16S  3
#endif // !CV_16S

#ifndef CV_32S
#define CV_32S  4
#endif // !CV_32S

#ifndef CV_32F
#define CV_32F  5
#endif // !CV_32F

#ifndef CV_64F
#define CV_64F  6
#endif // !CV_64F

#ifndef CV_USRTYPE1
#define CV_USRTYPE1 7
#endif // !CV_USRTYPE1



typedef struct sobelParammeter 
{
public:
	sobelParammeter()
		:__depth__(CV_32F), __dx__(1),
		__dy__(1), __ksize__(3), __scale__(1.0){}

	sobelParammeter(
		int dx, int dy, int ksize,
		int depth, double sl
	) :
		__depth__(depth), __dx__(dx), __dy__(dy),
		__ksize__(ksize), __scale__(sl) {}

	sobelParammeter(const sobelParammeter& obj) 
	{
		*this = obj; 
	};

	sobelParammeter& operator=(const sobelParammeter& obj)
	{
		this->__scale__ = obj.__scale__;
		this->__depth__ = obj.__depth__;
		this->__ksize__ = obj.__ksize__;
		this->__dx__ = obj.__dx__;
		this->__dy__ = obj.__dy__;
		return *this;
	};

public:
	int GetDx() { return __dx__; }
	int GetDy() { return __dy__; }
	int GetDdepth() { return __depth__; }
	int GetKsize() { return __ksize__; }
	double GetScale() { return __scale__; }

public:
	void SetDx(int dx) { __dx__ = dx; }
	void SetDy(int dy) { __dy__ = dy; }
	void SetDepth(int depth) { __depth__ = depth; }
	void SetKsize(int ksize) { __ksize__ = ksize; }
	void SetScale(double value) { __scale__ = value; }

private:	
	int __depth__;
	int __dx__;
	int __dy__;
	int __ksize__; // kenel size about sobel
	double __scale__;
	
}SobelParam;

using SP = SobelParam;
/*
double scale = 1, double delta = 0,
						 int borderType = BORDER_DEFAULT
*/
#endif // !__SOBELPARAMETERINTERFACE_H