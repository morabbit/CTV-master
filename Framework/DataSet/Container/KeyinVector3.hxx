#pragma once
#ifndef __KEYINVECTOR3_H
#define __KEYINVECTOR3_H
#include <cmath>
#include "KeyinPoint3d.hxx"


template<class _Type>
class Vector3
{
public:
	Vector3();
	~Vector3();	
	Vector3(_Type tx, _Type ty, _Type tz);
	Vector3(const Vector3<_Type>& obj);
	Vector3(Point3D<_Type> head, Point3D<_Type> tail);

	Vector3<_Type>& operator+(_Type n);
	Vector3<_Type>& operator-(_Type n);
	Vector3<_Type>& operator*(_Type n);
	Vector3<_Type>& operator/(_Type n);

	Vector3<_Type>& operator+=(_Type n);
	Vector3<_Type>& operator-=(_Type n);
	Vector3<_Type>& operator*=(_Type n);
	Vector3<_Type>& operator/=(_Type n);

	Vector3<_Type>& operator=(const Vector3<_Type>& obj);

	Vector3<_Type>& operator+(const Vector3<_Type>& obj);
	Vector3<_Type>& operator-(const Vector3<_Type>& obj);
	Vector3<_Type>& operator*(const Vector3<_Type>& obj);
	Vector3<_Type>& operator/(const Vector3<_Type>& obj);

	Vector3<_Type>& operator+=(const Vector3<_Type>& obj);
	Vector3<_Type>& operator-=(const Vector3<_Type>& obj);
	Vector3<_Type>& operator*=(const Vector3<_Type>& obj);
	Vector3<_Type>& operator/=(const Vector3<_Type>& obj);

public:
	_Type mod();
	_Type dot(const Vector3<_Type>& obj);
	Vector3<_Type> cross(const Vector3<_Type>& obj);
	double cos_seta(const Vector3<_Type>& obj);
	double sin_seta(const Vector3<_Type>& obj);

	template<typename _TargetType>
	Vector3<_TargetType> TypeTransfer();

public:
	_Type x;
	_Type y;
	_Type z;
};


template<class _Type>
inline Vector3<_Type>::Vector3()
{
}

template<class _Type>
Vector3<_Type>::~Vector3()
{
}

template<class _Type>
inline Vector3<_Type>::Vector3(Point3D<_Type> head, Point3D<_Type> tail)
{
	this->x = head.x - tail.x;
	this->y = head.y - tail.y;
	this->z = head.z - tail.z;
}


template<class _Type>
Vector3<_Type>::Vector3(_Type tx, _Type ty, _Type tz)
{
	this->x = tx;
	this->y = ty;
	this->z = tz;
}

template<class _Type>
Vector3<_Type>::Vector3(const Vector3<_Type>& obj)
{
	*this = obj;
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator=(const Vector3<_Type>& obj)
{
	this->x = obj.x;
	this->y = obj.y;
	this->z = obj.z;
	return *this;
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator+(const Vector3<_Type>& obj)
{
	Vector3<_Type> v3;
	v3.x = this->x + obj.x;
	v3.y = this->y + obj.y;
	v3.z = this->z + obj.z;

	return v3;
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator-(const Vector3<_Type>& obj)
{
	Vector3<_Type> v3;
	v3.x = this->x - obj.x;
	v3.y = this->y - obj.y;
	v3.z = this->z - obj.z;

	return v3;
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator*(const Vector3<_Type>& obj)
{
	Vector3<_Type> v3;
	v3.x = this->x * obj.x;
	v3.y = this->y * obj.y;
	v3.z = this->z * obj.z;

	return v3;
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator/(const Vector3<_Type>& obj)
{
	Vector3<_Type> v3;
	v3.x = this->x / obj.x;
	v3.y = this->y / obj.y;
	v3.z = this->z / obj.z;

	return v3;
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator+=(const Vector3<_Type>& obj)
{
	return this->operator+(obj);
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator-=(const Vector3<_Type>& obj)
{
	return this->operator-(obj);
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator*=(const Vector3<_Type>& obj)
{
	return this->operator*(obj);
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator/=(const Vector3<_Type>& obj)
{
	return this->operator/(obj);
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator+(_Type n)
{
	Vector3<_Type> v3;
	v3.x = this->x + n;
	v3.y = this->y + n;
	v3.z = this->z + n;

	return v3;
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator-(_Type n)
{
	Vector3<_Type> v3;
	v3.x = this->x - n;
	v3.y = this->y - n;
	v3.z = this->z - n;

	return v3;
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator*(_Type n)
{
	Vector3<_Type> v3;
	v3.x = this->x * n;
	v3.y = this->y * n;
	v3.z = this->z * n;

	return v3;
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator/(_Type n)
{
	n = (n == (_Type)0) ? 1 : n;

	Vector3<_Type> v3;
	v3.x = this->x / n;
	v3.y = this->y / n;
	v3.z = this->z / n;

	return v3;
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator+=(_Type n)
{
	return this->operator+(n);
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator-=(_Type n)
{
	return this->operator-(n);
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator*=(_Type n)
{
	return this->operator*(n);
}

template<class _Type>
Vector3<_Type>& Vector3<_Type>::operator/=(_Type n)
{
	return this->operator/(n);
}

template<class _Type>
inline _Type Vector3<_Type>::mod()
{
	return (_Type)sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

template<class _Type>
inline _Type Vector3<_Type>::dot(const Vector3<_Type>& obj)
{
	return this->x * obj.x + this->y * obj.y + this->z * obj.z;
}


template<class _Type>
inline Vector3<_Type> Vector3<_Type>::cross(const Vector3<_Type>& obj)
{
	Vector3<_Type> v3;
	v3.x = this->y * obj.z - this->z * obj.y;
	v3.y = this->z * obj.x - this->x * obj.z;
	v3.z = this->x * obj.y - this->y *obj.x;

	return v3;
}

template<class _Type>
inline double Vector3<_Type>::cos_seta(const Vector3<_Type>& obj)
{
	return (double)this->dot(obj) / (double)(this->mod() * obj.mod());
}

template<class _Type>
inline double Vector3<_Type>::sin_seta(const Vector3<_Type>& obj)
{
	return (double)this->cross(obj).mod() / (double)(this->mod() * obj.mod());
}

template<class _Type>
template<typename _TargetType>
inline Vector3<_TargetType> Vector3<_Type>::TypeTransfer()
{
	Vector3<_TargetType> __tgt;
	__tgt.x = (_TargetType)this->x;
	__tgt.y = (_TargetType)this->y;
	__tgt.z = (_TargetType)this->z;
	return __tgt;
}


#endif // !__KEYINVECTOR3_H

