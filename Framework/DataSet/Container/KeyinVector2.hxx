#pragma once
#ifndef __KEYINVECTOR2_H
#define __KEYINVECTOR2_H

#include <cmath>
#include "KeyInPoint2d.hxx"

template<class _Type>
class Vector2
{
public:
	Vector2();
	~Vector2();
	Vector2(_Type tx, _Type ty);
	Vector2(const Vector2<_Type>& obj);
	Vector2(const Point2D<_Type>& obj1, const Point2D<_Type>& obj2);

	Vector2<_Type>& operator=(const Vector2<_Type>& obj);
	Vector2<_Type>& operator+(const Vector2<_Type>& obj);
	Vector2<_Type>& operator-(const Vector2<_Type>& obj);
	Vector2<_Type>& operator*(const Vector2<_Type>& obj);
	Vector2<_Type>& operator/(const Vector2<_Type>& obj);

	Vector2<_Type>& operator+=(const Vector2<_Type>& obj);
	Vector2<_Type>& operator-=(const Vector2<_Type>& obj);
	Vector2<_Type>& operator*=(const Vector2<_Type>& obj);
	Vector2<_Type>& operator/=(const Vector2<_Type>& obj);

	Vector2<_Type>& operator+(_Type n);
	Vector2<_Type>& operator-(_Type n);
	Vector2<_Type>& operator*(_Type n);
	Vector2<_Type>& operator/(_Type n);

	Vector2<_Type>& operator+=(_Type n);
	Vector2<_Type>& operator-=(_Type n);
	Vector2<_Type>& operator*=(_Type n);
	Vector2<_Type>& operator/=(_Type n);
	
	template<typename _TargetType>
	Vector2<_TargetType> TypeTransfer();

public:
	_Type mod();
	_Type dot(const Vector2<_Type>& obj);
	_Type cross(const Vector2<_Type>& obj);
	double cos_seta(const Vector2<_Type>& obj);
	
public:
	_Type x;
	_Type y;
};

template<class _Type>
Vector2<_Type>::Vector2()
{
}

template<class _Type>
Vector2<_Type>::Vector2(_Type tx, _Type ty)
{
	this->x = tx;
	this->y = ty;
}

template<class _Type>
Vector2<_Type>::Vector2(const Vector2<_Type>& obj)
{
	*this = obj;
}

template<class _Type>
inline Vector2<_Type>::Vector2(const Point2D<_Type>& obj1, const Point2D<_Type>& obj2)
{
	this->x = obj1.x - obj2.x;
	this->y = obj1.y - obj2.y;
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator=(const Vector2<_Type>& obj)
{
	if(this == &obj) return *this;
	memset(this, 0, sizeof(Vector2<_Type>));
	memcpy(this, &obj, sizeof(Vector2<_Type>));
	return *this;
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator+(const Vector2<_Type>& obj)
{
	Vector2<_Type> v2;
	v2.x = this->x + obj.x;
	v2.y = this->y + obj.y;

	return v2;
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator-(const Vector2<_Type>& obj)
{
	Vector2<_Type> v2;
	v2.x = this->x - obj.x;
	v2.y = this->y - obj.y;

	return v2;
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator*(const Vector2<_Type>& obj)
{
	Vector2<_Type> v2;
	v2.x = this->x * obj.x;
	v2.y = this->y * obj.y;

	return v2;
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator/(const Vector2<_Type>& obj)
{
	Vector2<_Type> v2;
	v2.x = this->x / obj.x;
	v2.y = this->y / obj.y;

	return v2;
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator+=(const Vector2<_Type>& obj)
{
	return this->operator+(obj);
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator-=(const Vector2<_Type>& obj)
{
	return this->operator-(obj);
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator*=(const Vector2<_Type>& obj)
{
	return this->operator*(obj);
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator/=(const Vector2<_Type>& obj)
{
	return this->operator/(obj);
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator+(_Type n)
{
	Vector2<_Type> v2;
	v2.x = this->x + n;
	v2.y = this->y + n;

	return v2;
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator-(_Type n)
{
	Vector2<_Type> v2;
	v2.x = this->x - n;
	v2.y = this->y - n;

	return v2;
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator*(_Type n)
{
	Vector2<_Type> v2;
	v2.x = this->x * n;
	v2.y = this->y * n;

	return v2;
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator/(_Type n)
{
	Vector2<_Type> v2;
	v2.x = this->x / n;
	v2.y = this->y / n;

	return v2;
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator+=(_Type n)
{
	return this->operator+(n);
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator-=(_Type n)
{
	return this->operator-(n);
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator*=(_Type n)
{
	return this->operator*(n);
}

template<class _Type>
Vector2<_Type>& Vector2<_Type>::operator/=(_Type n)
{
	return this->operator/(n);
}

template<class _Type>
_Type Vector2<_Type>::mod()
{
	return (_Type)sqrt(pow(this->x, 2) + pow(this->y, 2));
}

template<class _Type>
_Type Vector2<_Type>::dot(const Vector2<_Type>& obj)
{
	return this->x * obj.x + this->y * obj.y;
}

template<class _Type>
_Type Vector2<_Type>::cross(const Vector2<_Type>& obj)
{
	return this->x * obj.y - obj.x * this->y;
}

template<class _Type>
double Vector2<_Type>::cos_seta(const Vector2<_Type>& obj)
{
	return (double)this->dot(obj) / (double)(this->mod() * obj.mod());
}

template<class _Type>
Vector2<_Type>::~Vector2()
{
}

template<class _Type>
template<typename _TargetType>
inline Vector2<_TargetType> Vector2<_Type>::TypeTransfer()
{
	Vector2<_TargetType> __tgt;
	__tgt.x = (_TargetType)this->x;
	__tgt.y = (_TargetType)this->y;
	return __tgt;
}

#endif // !__KEYINVECTOR2_H

