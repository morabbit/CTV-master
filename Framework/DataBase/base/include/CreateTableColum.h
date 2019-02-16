#pragma once
#ifndef __CREATETABLECOLUM_H
#define __CREATETABLECOLUM_H
#include "FrameworkType.h"

class TableColum
{
public:
	TableColum();
	~TableColum();
	TableColum(const TableColum&);
	TableColum& operator=(const TableColum&);

	auto put(
		char* _value_, 
		_String _type_, 
		bool __bNotNull = true,
		bool __bunique = false,
		_String _default_ = "",
		bool __bPrimaryKey = false,
		bool __bAutoIcs = false
	) -> void;

	auto put(
		_String _value_,
		_String _type_,
		bool __bNotNull = true,
		bool __bunique = false,
		_String _default_ = "",		
		bool __bPrimaryKey=false,
		bool __bAutoIcs = false
	) -> void;

	auto str()->_String;
public:
	int __used_cls__;

private:
	bool __pmy_key__;
	_StrStm_ __caluse__;
};


#endif // !__CREATETABLECOLUM_H
