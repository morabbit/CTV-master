#pragma once
#ifndef __KEYINPOINT2D_h
#define __KEYINPOINT2D_h

template<class _Type>
struct Point2D
{
public :
	Point2D();
	Point2D(_Type tx, _Type ty);
	Point2D(const Point2D<_Type>& obj);
	Point2D<_Type>& operator=(const Point2D<_Type>& obj);

	Point2D<_Type>& operator+(_Type n);
	Point2D<_Type>& operator-(_Type n);
	Point2D<_Type>& operator*(_Type n);
	Point2D<_Type>& operator/(_Type n);
	
	Point2D<_Type>& operator+=(_Type n);
	Point2D<_Type>& operator-=(_Type n);
	Point2D<_Type>& operator*=(_Type n);
	Point2D<_Type>& operator/=(_Type n);

	template<typename _TargetType>
	Point2D<_TargetType> TypeTransfer();

	~Point2D();
public:
	_Type x;
	_Type y;
};


template<class _Type>
inline Point2D<_Type>::Point2D()
{
	this->x = (_Type)0;
	this->y = (_Type)0;
}

template<class _Type>
inline Point2D<_Type>::Point2D(_Type tx, _Type ty)
{
	this->x = tx;
	this->y = ty;
}

template<class _Type>
inline Point2D<_Type>::Point2D(const Point2D<_Type>& obj)
{
	*this = obj;
}

template<class _Type>
inline Point2D<_Type>& Point2D<_Type>::operator=(const Point2D<_Type>& obj)
{
	if(this == &obj) return *this;
	memset(this, 0, sizeof(Point2D<_Type>));
	memcpy(this, &obj, sizeof(Point2D<_Type>));
	return *this;
}

template<class _Type>
inline Point2D<_Type>& Point2D<_Type>::operator+(_Type n)
{
	Point2D<_Type> p2;
	p2.x = this->x + n;
	p2.y = this->y + n;

	return p2;
}

template<class _Type>
inline Point2D<_Type>& Point2D<_Type>::operator-(_Type n)
{
	Point2D<_Type> p2;
	p2.x = this->x - n;
	p2.y = this->y - n;

	return p2;
}

template<class _Type>
inline Point2D<_Type>& Point2D<_Type>::operator*(_Type n)
{
	Point2D<_Type> p2;
	p2.x = this->x * n;
	p2.y = this->y * n;

	return p2;
}

template<class _Type>
inline Point2D<_Type>& Point2D<_Type>::operator/(_Type n)
{
	Point2D<_Type> p2;
	n = (n == (_Type)0) ? 1 : n;
	p2.x = this->x / n;
	p2.y = this->y / n;

	return p2;
}

template<class _Type>
inline Point2D<_Type>& Point2D<_Type>::operator+=(_Type n)
{
	return this->operator+(n);
}

template<class _Type>
inline Point2D<_Type>& Point2D<_Type>::operator-=(_Type n)
{
	return this->operator-(n);
}

template<class _Type>
inline Point2D<_Type>& Point2D<_Type>::operator*=(_Type n)
{
	return this->operator*(n);
}

template<class _Type>
inline Point2D<_Type>& Point2D<_Type>::operator/=(_Type n)
{
	return this->operator/(n);
}

template<class _Type>
inline Point2D<_Type>::~Point2D()
{
}

template<class _Type>
template<typename _TargetType>
inline Point2D<_TargetType> Point2D<_Type>::TypeTransfer()
{
	Point2D<_TargetType> __tgt;
	__tgt.x = (_TargetType)this->x;
	__tgt.y = (_TargetType)this->y;
	return __tgt;
}
#endif // !__KEYINPOINT2D_h


