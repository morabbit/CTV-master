#pragma once
#ifndef __DBCONTENCALUSE_H
#define __DBCONTENCALUSE_H
#include "DBContentValues.h"


class ContentCaluse
{
public:
	ContentCaluse();
	~ContentCaluse();
	ContentCaluse(const ContentCaluse& obj);
	ContentCaluse& operator=(const ContentCaluse& obj);

public:
	// like 
	auto like(_String _key_, int _value_)->ContentCaluse&;
	auto like(_String _key_, bool _value_)->ContentCaluse&;
	auto like(_String _key_, long _value_)->ContentCaluse&;
	auto like(_String _key_, char _value_)->ContentCaluse&;
	auto like(_String _key_, short _value_)->ContentCaluse&;
	auto like(_String _key_, float _value_)->ContentCaluse&;
	auto like(_String _key_, double _value_)->ContentCaluse&;
	auto like(_String _key_, char* _value_)->ContentCaluse&;
	auto like(_String _key_, _String _value_)->ContentCaluse&;
	auto like(_String _key_, long long _value_)->ContentCaluse&;
	auto like(_String _key_, long double _value_)->ContentCaluse&;
	auto like(_String _key_, unsigned int _value_)->ContentCaluse&;
	auto like(_String _key_, unsigned short _value_)->ContentCaluse&;
	auto like(_String _key_, unsigned char _value_)->ContentCaluse&;
	auto like(_String _key_, unsigned long _value_)->ContentCaluse&;
	auto like(_String _key_, unsigned long long _value_)->ContentCaluse&;

	// equal 
	auto equal(_String _key_, int _value_) -> ContentCaluse&;
	auto equal(_String _key_, bool _value_) -> ContentCaluse&;
	auto equal(_String _key_, long _value_) -> ContentCaluse&;
	auto equal(_String _key_, char _value_) -> ContentCaluse&;
	auto equal(_String _key_, short _value_) -> ContentCaluse&;
	auto equal(_String _key_, float _value_) -> ContentCaluse&;
	auto equal(_String _key_, double _value_) -> ContentCaluse&;
	auto equal(_String _key_, char* _value_) -> ContentCaluse&;
	auto equal(_String _key_, _String _value_) -> ContentCaluse&;
	auto equal(_String _key_, long long _value_) -> ContentCaluse&;
	auto equal(_String _key_, long double _value_) -> ContentCaluse&;
	auto equal(_String _key_, unsigned int _value_) -> ContentCaluse&;
	auto equal(_String _key_, unsigned short _value_) -> ContentCaluse&;
	auto equal(_String _key_, unsigned char _value_) -> ContentCaluse&;
	auto equal(_String _key_, unsigned long _value_) -> ContentCaluse&;
	auto equal(_String _key_, unsigned long long _value_) -> ContentCaluse&;

	// not equal 
	auto neq(_String _key_, int _value_) -> ContentCaluse&;
	auto neq(_String _key_, bool _value_) -> ContentCaluse&;
	auto neq(_String _key_, long _value_) -> ContentCaluse&;
	auto neq(_String _key_, char _value_) -> ContentCaluse&;
	auto neq(_String _key_, short _value_) -> ContentCaluse&;
	auto neq(_String _key_, float _value_) -> ContentCaluse&;
	auto neq(_String _key_, double _value_) -> ContentCaluse&;
	auto neq(_String _key_, char* _value_) -> ContentCaluse&;
	auto neq(_String _key_, _String _value_) -> ContentCaluse&;
	auto neq(_String _key_, long long _value_) -> ContentCaluse&;
	auto neq(_String _key_, long double _value_) -> ContentCaluse&;
	auto neq(_String _key_, unsigned int _value_) -> ContentCaluse&;
	auto neq(_String _key_, unsigned short _value_) -> ContentCaluse&;
	auto neq(_String _key_, unsigned char _value_) -> ContentCaluse&;
	auto neq(_String _key_, unsigned long _value_) -> ContentCaluse&;
	auto neq(_String _key_, unsigned long long _value_) -> ContentCaluse&;

	// more than 
	auto gtr(_String _key_, int _value_) -> ContentCaluse&;
	auto gtr(_String _key_, long _value_) -> ContentCaluse&;
	auto gtr(_String _key_, char _value_) -> ContentCaluse&;
	auto gtr(_String _key_, short _value_) -> ContentCaluse&;
	auto gtr(_String _key_, float _value_) -> ContentCaluse&;
	auto gtr(_String _key_, double _value_) -> ContentCaluse&;
	auto gtr(_String _key_, long long _value_) -> ContentCaluse&;
	auto gtr(_String _key_, long double _value_) -> ContentCaluse&;
	auto gtr(_String _key_, unsigned int _value_) -> ContentCaluse&;
	auto gtr(_String _key_, unsigned short _value_) -> ContentCaluse&;
	auto gtr(_String _key_, unsigned char _value_) -> ContentCaluse&;
	auto gtr(_String _key_, unsigned long _value_) -> ContentCaluse&;
	auto gtr(_String _key_, unsigned long long _value_) -> ContentCaluse&;

	// more than and equal
	auto geq(_String _key_, int _value_) -> ContentCaluse&;
	auto geq(_String _key_, long _value_) -> ContentCaluse&;
	auto geq(_String _key_, char _value_) -> ContentCaluse&;
	auto geq(_String _key_, short _value_) -> ContentCaluse&;
	auto geq(_String _key_, float _value_) -> ContentCaluse&;
	auto geq(_String _key_, double _value_) -> ContentCaluse&;
	auto geq(_String _key_, long long _value_) -> ContentCaluse&;
	auto geq(_String _key_, long double _value_) -> ContentCaluse&;
	auto geq(_String _key_, unsigned int _value_) -> ContentCaluse&;
	auto geq(_String _key_, unsigned short _value_) -> ContentCaluse&;
	auto geq(_String _key_, unsigned char _value_) -> ContentCaluse&;
	auto geq(_String _key_, unsigned long _value_) -> ContentCaluse&;
	auto geq(_String _key_, unsigned long long _value_) -> ContentCaluse&;

	// less than 
	auto ltr(_String _key_, int _value_) -> ContentCaluse&;
	auto ltr(_String _key_, long _value_) -> ContentCaluse&;
	auto ltr(_String _key_, char _value_) -> ContentCaluse&;
	auto ltr(_String _key_, short _value_) -> ContentCaluse&;
	auto ltr(_String _key_, float _value_) -> ContentCaluse&;
	auto ltr(_String _key_, double _value_) -> ContentCaluse&;
	auto ltr(_String _key_, long long _value_) -> ContentCaluse&;
	auto ltr(_String _key_, long double _value_) -> ContentCaluse&;
	auto ltr(_String _key_, unsigned int _value_) -> ContentCaluse&;
	auto ltr(_String _key_, unsigned short _value_) -> ContentCaluse&;
	auto ltr(_String _key_, unsigned char _value_) -> ContentCaluse&;
	auto ltr(_String _key_, unsigned long _value_) -> ContentCaluse&;
	auto ltr(_String _key_, unsigned long long _value_) -> ContentCaluse&;

	// less than and equal
	auto leq(_String _key_, int _value_) -> ContentCaluse&;
	auto leq(_String _key_, long _value_) -> ContentCaluse&;
	auto leq(_String _key_, char _value_) -> ContentCaluse&;
	auto leq(_String _key_, short _value_) -> ContentCaluse&;
	auto leq(_String _key_, float _value_) -> ContentCaluse&;
	auto leq(_String _key_, double _value_) -> ContentCaluse&;
	auto leq(_String _key_, long long _value_) -> ContentCaluse&;
	auto leq(_String _key_, long double _value_) -> ContentCaluse&;
	auto leq(_String _key_, unsigned int _value_) -> ContentCaluse&;
	auto leq(_String _key_, unsigned short _value_) -> ContentCaluse&;
	auto leq(_String _key_, unsigned char _value_) -> ContentCaluse&;
	auto leq(_String _key_, unsigned long _value_) -> ContentCaluse&;
	auto leq(_String _key_, unsigned long long _value_) -> ContentCaluse&;

	// between ... and ...  
	auto between(_String _key_, int _val1_, int _val2_) -> ContentCaluse&;
	auto between(_String _key_, bool _val1_, bool _val2_) -> ContentCaluse&;
	auto between(_String _key_, long _val1_, long _val2_) -> ContentCaluse&;
	auto between(_String _key_, char _val1_, char _val2_) -> ContentCaluse&;
	auto between(_String _key_, short _val1_, short _val2_) -> ContentCaluse&;
	auto between(_String _key_, float _val1_, float _val2_) -> ContentCaluse&;
	auto between(_String _key_, double _val1_, double _val2_) -> ContentCaluse&;
	auto between(_String _key_, long long _val1_, long long _val2_) -> ContentCaluse&;
	auto between(_String _key_, long double _val1_, long double _val2_) -> ContentCaluse&;
	auto between(_String _key_, unsigned int _val1_, unsigned int _val2_) -> ContentCaluse&;
	auto between(_String _key_, unsigned short _val1_, unsigned short _val2_) -> ContentCaluse&;
	auto between(_String _key_, unsigned char _val1_, unsigned char _val2_) -> ContentCaluse&;
	auto between(_String _key_, unsigned long _val1_, unsigned long _val2_) -> ContentCaluse&;
	auto between(_String _key_, unsigned long long _val1_, unsigned long long _val2_) -> ContentCaluse&;


	// condition 
	auto And() -> ContentCaluse&;
	auto And(_String _cdt_) -> ContentCaluse&;
	auto And(_String _cdt1_, _String _cdt2_) -> ContentCaluse&;	

	auto and_all() -> ContentCaluse&;
	auto or_all() -> ContentCaluse&;

	auto Or() -> ContentCaluse&;
	auto Or(_String _cdt_) -> ContentCaluse&;
	auto Or(_String _cdt1_, _String _cdt2_) -> ContentCaluse&;

	auto in(_String _column_, _String _vals_)->ContentCaluse&;
	auto not_in(_String _column_, _String _vals_)->ContentCaluse&;

	auto limited(const char* fmt, ...)->_String;

	// get string
	auto str() -> _String;
	// auto 
	auto get_count() -> int;
private:
	template<typename _Type>
	auto __like(_String _key_, _Type _value_)->ContentCaluse&;

	template<typename _Type>
	auto __equal(_String _key_, _Type _value_) -> ContentCaluse&;

	template<typename _Type>
	auto __gtr(_String _key_, _Type _value_) -> ContentCaluse&;

	template<typename _Type>
	auto __geq(_String _key_, _Type _value_) -> ContentCaluse&;

	template<typename _Type>
	auto __ltr(_String _key_, _Type _value_) -> ContentCaluse&;

	template<typename _Type>
	auto __leq(_String _key_, _Type _value_)->ContentCaluse&;

	template<typename _Type>
	auto __neq(_String _key_, _Type _value_)->ContentCaluse&;

	template<typename _Type>
	auto __between(_String _column_, _Type _val1_, _Type _val2_)->ContentCaluse&;

	auto __condition(_String _key_, _String _cdt, _String _value_) -> ContentCaluse&;

public:
		int __used_cls__;

private:
	_StrStm_ __caluse__;
	
};


template<typename _Type>
inline auto ContentCaluse::__like(_String _key_, _Type _value_) -> ContentCaluse &
{
	_StrStm_ __val;
	__val << _value_;
	return __condition(_key_, "like", __val.str());
}

template<typename _Type>
inline auto ContentCaluse::__equal(_String _key_, _Type _value_) -> ContentCaluse &
{
	_StrStm_ __val;
	__val << _value_;

	return __condition(_key_, "=", __val.str());
}

template<typename _Type>
inline auto ContentCaluse::__gtr(_String _key_, _Type _value_) -> ContentCaluse &
{
	_StrStm_ __val;
	__val << _value_;

	return __condition(_key_, ">", __val.str());
}

template<typename _Type>
inline auto ContentCaluse::__geq(_String _key_, _Type _value_) -> ContentCaluse &
{
	_StrStm_ __val;
	__val << _value_;

	return __condition(_key_, ">=", __val.str());
}

template<typename _Type>
inline auto ContentCaluse::__ltr(_String _key_, _Type _value_) -> ContentCaluse &
{
	_StrStm_ __val;
	__val << _value_;

	return __condition(_key_, "<", __val.str());
}

template<typename _Type>
inline auto ContentCaluse::__leq(_String _key_, _Type _value_) -> ContentCaluse &
{
	_StrStm_ __val;
	__val << _value_;

	return __condition(_key_, "<=", __val.str());
}

template<typename _Type>
inline auto ContentCaluse::__neq(_String _key_, _Type _value_) -> ContentCaluse &
{
	_StrStm_ __val;
	__val << _value_;

	return __condition(_key_, "!=", __val.str());
}

template<typename _Type>
inline auto ContentCaluse::__between(_String _column_, _Type _val1_, _Type _val2_) -> ContentCaluse &
{
	__used_cls__++;
	__caluse__ << "(" << _column_ << " between " << _val1_ << " and " << _val2_ << ")";

	return *this;
}


#endif // !__DBCONTENCALUSE_H