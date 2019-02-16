#pragma once
#ifndef __DBCONTENTVALUES_H
#define __DBCONTENTVALUES_H
#include "DataBaseCommon.h"

class ContentValue
{
public:
	ContentValue();
	~ContentValue();
	ContentValue(const ContentValue&);
	ContentValue& operator=(const ContentValue&);

public:
	auto put(_String _key_, int _value_) -> void;
	auto put(_String _key_, bool _value_) -> void;
	auto put(_String _key_, long _value_) -> void;
	auto put(_String _key_, char _value_) -> void;
	auto put(_String _key_, short _value_) -> void;
	auto put(_String _key_, float _value_) -> void;
	auto put(_String _key_, double _value_) -> void;
	auto put(_String _key_, char* _value_) -> void;
	auto put(_String _key_, _String _value_) -> void;	
	auto put(_String _key_, long long _value_) -> void;
	auto put(_String _key_, long double _value_) -> void;
	auto put(_String _key_, unsigned int _value_) -> void;
	auto put(_String _key_, unsigned short _value_) -> void;
	auto put(_String _key_, unsigned char _value_) -> void;
	auto put(_String _key_, unsigned long _value_) -> void;
	auto put(_String _key_, unsigned long long _value_) -> void;

	auto insert_str() -> _String;
	auto update_str() -> _String;

private:
	using __IterMap = StrMap::iterator;

private:
	StrMap __values__;
};


#endif // !__DBCONTENTVALUES_H


