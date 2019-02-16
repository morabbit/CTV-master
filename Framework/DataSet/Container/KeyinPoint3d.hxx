#pragma once
#ifndef __KEYINPOINT3D_h
#define __KEYINPOINT3D_h


template<class _Type>
struct Point3D
{
public:
	Point3D();
	Point3D(_Type tx, _Type ty, _Type tz);
	Point3D(const Point3D<_Type>& obj);
	Point3D<_Type>& operator=(const Point3D<_Type>& obj);
	
	Point3D<_Type>& operator+(_Type n);
	Point3D<_Type>& operator-(_Type n);
	Point3D<_Type>& operator*(_Type n);
	Point3D<_Type>& operator/(_Type n);

	Point3D<_Type>& operator+=(_Type n);
	Point3D<_Type>& operator-=(_Type n);
	Point3D<_Type>& operator*=(_Type n);
	Point3D<_Type>& operator/=(_Type n);

	template<typename _TargetType>
	Point3D<_TargetType> TypeTransfer();

	~Point3D();
public:
	_Type x;
	_Type y;
	_Type z;
};



template<class _Type>
inline Point3D<_Type>::Point3D()
{
	this->x = (_Type)0;
	this->y = (_Type)0;
	this->z = (_Type)0;
}

template<class _Type>
inline Point3D<_Type>::Point3D(_Type tx, _Type ty, _Type tz)
{
	this->x = tx;
	this->y = ty;
	this->z = tz;
}

template<class _Type>
inline Point3D<_Type>::Point3D(const Point3D<_Type>& obj)
{
	*this = obj;
}

template<class _Type>
inline Point3D<_Type>& Point3D<_Type>::operator=(const Point3D<_Type>& obj)
{
	this->x = obj.x;
	this->y = obj.y;
	this->z = obj.z;

	return *this;
}

template<class _Type>
inline Point3D<_Type>& Point3D<_Type>::operator+(_Type n)
{
	Point3D<_Type> p3;
	p3.x = this->x + n;
	p3.y = this->y + n;
	p3.z = this->z + n;

	return p3;
}

template<class _Type>
inline Point3D<_Type>& Point3D<_Type>::operator-(_Type n)
{
	Point3D<_Type> p3;
	p3.x = this->x - n;
	p3.y = this->y - n;
	p3.z = this->z - n;

	return p3;
}

template<class _Type>
inline Point3D<_Type>& Point3D<_Type>::operator*(_Type n)
{
	Point3D<_Type> p3;
	p3.x = this->x * n;
	p3.y = this->y * n;
	p3.z = this->z * n;

	return p3;
}

template<class _Type>
inline Point3D<_Type>& Point3D<_Type>::operator/(_Type n)
{
	n = (n == (_Type)0) ? 1 : n;

	Point3D<_Type> p3;
	p3.x = this->x / n;
	p3.y = this->y / n;
	p3.z = this->z / n;

	return p3;
}

template<class _Type>
inline Point3D<_Type>& Point3D<_Type>::operator+=(_Type n)
{
	return this->operator+(n);
}

template<class _Type>
inline Point3D<_Type>& Point3D<_Type>::operator-=(_Type n)
{
	return this->operator-(n);
}

template<class _Type>
inline Point3D<_Type>& Point3D<_Type>::operator*=(_Type n)
{
	return this->operator*(n);
}

template<class _Type>
inline Point3D<_Type>& Point3D<_Type>::operator/=(_Type n)
{
	return this->operator/(n);
}

template<class _Type>
template<typename _TargetType>
inline Point3D<_TargetType> Point3D<_Type>::TypeTransfer()
{
	Point3D<_TargetType> tgt;
	tgt.x = (_TargetType)this->x;
	tgt.y = (_TargetType)this->y;
	tgt.z = (_TargetType)this->z;
	return tgt;
}

template<class _Type>
inline Point3D<_Type>::~Point3D()
{
}

#endif // !__KEYINPOINT3D_h