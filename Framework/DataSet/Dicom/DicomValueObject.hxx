#pragma once
#ifndef __DICOMVALUEOBJECT_HXX
#define __DICOMVALUEOBJECT_HXX

#include "BasicDicomObject.hxx"

template<typename _Type>
struct DicomValue : public DciomObject
{
public:
	using Supper = DciomObject;

public:
	DicomValue() {};
	~DicomValue() {};
	DicomValue(const DicomValue<_Type>& _obj);
	using Supper::operator=;
	DicomValue<_Type>& operator=(const DicomValue<_Type>& _obj);

public:
	_Type* value;
};

template<typename _Type>
inline DicomValue<_Type>::DicomValue(const DicomValue<_Type> & _obj)
{
	*this = _obj;
}

template<typename _Type>
inline DicomValue<_Type>&
DicomValue<_Type>::operator=(const DicomValue<_Type> & _obj)
{	
	Supper::operator=(_obj);
	value = _obj.value;

	return *this;
}


typedef DicomValue<short>  ShortDicomVO;
typedef DicomValue<unsigned short>  UShortDicomVO;

typedef DicomValue<char>  CharDicomValue;
typedef DicomValue<unsigned char>  UCharDicomVO;

typedef DicomValue<float>  FloatDicomValue;
typedef DicomValue<double>  DoubleDicomVO;

typedef DicomValue<int>  IntDicomValue;
typedef DicomValue<unsigned int>  UIntDicomVO;

#endif // !__DICOMVALUEOBJECT_HXX
