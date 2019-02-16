#pragma once
#ifndef __DATABASESELECTCOLUMN_H
#define __DATABASESELECTCOLUMN_H

#include "DataBaseCommon.h"
#include "DataBaseClassMacro.h"


FrameworkClassMacro(Column);
FrameworkClassMacro(GroupBy);
FrameworkClassMacro(OrderBy);
FrameworkClassMacro(Having);

class SelectColumn
{
public:
	SelectColumn();
	~SelectColumn();

public:
	auto put(const char* _value_) -> SelectColumn&;
	auto put(_String _value_) -> SelectColumn&;
	
	auto count(const char* _value_) -> SelectColumn&;
	auto count(_String _value_) -> SelectColumn&;

	auto group_by(_String _value_) ->SelectColumn&;
	auto order_by(_String _value_) ->SelectColumn&;
	auto order_by(_String _value_, Order _odr_) ->SelectColumn&;

	auto having(_String _column_)->SelectColumn&;
	auto having(_String _column_, _String _cdt_)->SelectColumn&;

	template<typename __Type>
	auto having(_String _column_,_String _cdt_, __Type __num) ->SelectColumn&;

	auto str() -> _String;

private:
	Column __columns__;
	GroupBy  __group_by__;
	OrderBy __order_by__;
	Having __having__;
};


template<typename __Type>
inline auto SelectColumn::having(_String _column_, _String _cdt_, __Type __num) -> SelectColumn &
{
	if(__having__.__used_cls__ > 0)
	{
		__having__.__column__ = _StrStm_();
	}
	__having__ << "sum(" << _column_ << ")" << _cdt_ << __num;
	__having__.__used_cls__++;

	return *this;
}

#endif // !__DATABASESELECTCOLUMN_H


