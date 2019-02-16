#include "pch.h"
#include "DataBaseSelectColumn.h"



SelectColumn::SelectColumn()
{
}

SelectColumn::~SelectColumn()
{
}

auto SelectColumn::put(const char * _value_) -> SelectColumn &
{
	if(__columns__.__used_cls__ > 0)
	{
		__columns__ << ", ";
	}

	__columns__ << _value_;
	__columns__.__used_cls__++;

	return *this;
}

auto SelectColumn::put(_String _value_) -> SelectColumn &
{
	if(__columns__.__used_cls__ > 0)
	{
		__columns__ << ", ";
	}
	
	__columns__ << _value_;
	__columns__.__used_cls__++;

	return *this;
}

auto SelectColumn::count(const char * _value_) -> SelectColumn &
{
	if(__columns__.__used_cls__ > 0)
	{
		__columns__ << ", ";
	}

	__columns__ <<"count(" <<  _value_ << ")" ;
	__columns__.__used_cls__++;

	return *this;
}

auto SelectColumn::count(_String _value_) -> SelectColumn &
{
	if(__columns__.__used_cls__ > 0)
	{
		__columns__ << ", ";
	}

	__columns__ << "count(" << _value_ << ")";
	__columns__.__used_cls__++;

	return *this;
}

auto SelectColumn::group_by(_String _value_) -> SelectColumn&
{
	if(__group_by__.__used_cls__ <= 0)
	{
		__group_by__ << " group by ";
	}
	__group_by__ << _value_;
	__group_by__.__used_cls__++;

	return *this;
}

auto SelectColumn::order_by(_String _value_) -> SelectColumn &
{
	if(__order_by__.__used_cls__ <= 0)
	{
		__order_by__ << " order by ";
	}
	else
	{
		__order_by__ << ", ";
	}
	__order_by__ << _value_;
	__order_by__.__used_cls__++;

	return *this;
}

auto SelectColumn::order_by(_String _value_, Order _odr_) -> SelectColumn &
{
	if(__order_by__.__used_cls__ <= 0)
	{
		__order_by__ << " order by ";
	}
	else
	{
		__order_by__ << ", ";
	}
	__order_by__ << _value_;
	__order_by__.__used_cls__++;

	if(_odr_ == Order::DESC)
	{
		__order_by__ << "desc";
	}
	else
	{
		__order_by__ << "asc";
	}

	return *this;
}

auto SelectColumn::having(_String _column_) -> SelectColumn &
{
	if(__having__.__used_cls__ > 0)
	{
		__having__.__column__ = _StrStm_();
	}
	__having__ << _column_;
	__having__.__used_cls__++;

	return *this;
}

auto SelectColumn::having(_String _column_, _String _cdt_) -> SelectColumn &
{
	if(__having__.__used_cls__ > 0)
	{
		__having__.__column__ = _StrStm_();
	}
	__having__ << _column_ << _cdt_;

	__having__.__used_cls__++;
	return *this;
}

auto SelectColumn::str() -> _String
{
	return __columns__.str();
}
