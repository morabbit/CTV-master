#include "pch.h"
#include "DBContentValues.h"


ContentValue::ContentValue()
{
}

ContentValue::~ContentValue()
{
}

ContentValue::ContentValue(const ContentValue & obj)
{
	*this = obj;
}

ContentValue & ContentValue::operator=(const ContentValue & obj)
{
	this->__values__ = obj.__values__;
	return *this;
}

void ContentValue::put(_String _key_, int _value_)
{
	_StrStm_ __val;
	__val << _value_;
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, bool _value_)
{
	_StrStm_ __val;
	__val << _value_;
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, long _value_)
{
	_StrStm_ __val;
	__val << _value_;
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, char _value_)
{
	_StrStm_ __val;
	__val << _value_;
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, short _value_)
{
	_StrStm_ __val;
	__val << _value_;
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, float _value_)
{
	_StrStm_ __val;
	__val << _value_;
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, double _value_)
{
	_StrStm_ __val;
	__val << _value_;
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, char * _value_)
{
	_StrStm_ __val;
	__val <<"\""<< _value_ << "\"";
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, _String _value_)
{
	_StrStm_ __val;
	__val << "\"" << _value_ << "\"";
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, long long _value_)
{
	_StrStm_ __val;
	__val << _value_;
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, long double _value_)
{
	_StrStm_ __val;
	__val << _value_;
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, unsigned int _value_)
{
	_StrStm_ __val;
	__val << _value_;
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, unsigned short _value_)
{
	_StrStm_ __val;
	__val << _value_;
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, unsigned char _value_)
{
	_StrStm_ __val;
	__val << _value_;
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, unsigned long _value_)
{
	_StrStm_ __val;
	__val << _value_;
	__values__.insert(std::make_pair(_key_, __val.str()));
}

void ContentValue::put(_String _key_, unsigned long long _value_)
{
	_StrStm_ __val;
	__val << _value_;
	__values__.insert(std::make_pair(_key_, __val.str()));
}

_String ContentValue::insert_str()
{	
	_StrStm_ __key, __value;
	uint32_t __index = 0, __len = (uint32_t)(__values__.size());
	for(__IterMap __it = __values__.begin(); __it != __values__.end(); __it++)
	{
		__key << __it->first.c_str();
		__value << __it->second.c_str();
		if(__index != __len - 1)
		{
			__key << ", ";
			__value << ", ";
		}
		__index++;
	}

	_StrStm_ __val;
	__val << "(" << __key.str() << ") values (" << __value.str() << ");";

	return __val.str();
}

_String ContentValue::update_str()
{
	_StrStm_ __val;
	uint32_t __index = 0, __len = (uint32_t)(__values__.size());
	for(__IterMap __it = __values__.begin(); __it != __values__.end(); __it++)
	{
		__val << __it->first << "=" << __it->second << " ";
		if((__index == __len - 1) && (__len > 1))
		{
			__val << ", ";
		}
		__index++;
	}

	return __val.str();
}
