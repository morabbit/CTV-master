#include "pch.h"
#include "CreateTableColum.h"


TableColum::TableColum()
{
	__pmy_key__ = false;
}

TableColum::~TableColum()
{
}

TableColum::TableColum(const TableColum & obj)
{
	*this = obj;
}

TableColum & TableColum::operator=(const TableColum & obj)
{
	this->__caluse__ = _StrStm_();
	this->__caluse__ << obj.__caluse__.str();
	this->__pmy_key__ = obj.__pmy_key__;
	this->__used_cls__ = obj.__used_cls__;

	return *this;
}

auto TableColum::put(char* _value_, _String _type,
					  bool __bNotNull, bool __bUnique,
					 _String _default_, bool __bPrimaryKey, bool __bAutoIcs) -> void
{
	if(__used_cls__ > 0)
	{
		__caluse__ << ", ";
	}

	_String __not_null = " ";
	if(true == __bNotNull)
	{
		__not_null = " NOT NULL ";
	}

	_String __unique = "";
	if(true == __bUnique)
	{
		__unique = " UNIQUE ";
	}

	_String __dft = "";
	if(_default_.size() > 0)
	{
		__dft = " DEFAULT " + _default_;
	}

	_String __prime_k = " ";
	if((false == __pmy_key__)&&(true == __bPrimaryKey))
	{
		__dft = "";
		__not_null = "";
		__prime_k == " PRIMARY KEY ";
	}	
	_String __aics = "";
	if(true == __bAutoIcs)
	{
		__aics = " autoincrement ";
	}
	__used_cls__++;
	__caluse__ << _value_ << " " << _type << __prime_k
		<< __aics << __not_null << __unique << __dft;
}

auto TableColum::put(_String _value_, _String _type_, 
					  bool __bNotNull, bool __bUnique, 
					 _String _default_, bool __bPrimaryKey, bool __bAutoIcs) -> void
{
	if(__used_cls__ > 0)
	{
		__caluse__ << ", ";
	}
	_String __not_null = " ";
	if(true == __bNotNull)
	{
		__not_null = " NOT NULL ";
	}

	_String __unique = "";
	if(true == __bUnique)
	{
		__unique = " UNIQUE ";
	}

	_String __dft = "";
	if(_default_.size() > 0)
	{
		__dft = " DEFAULT " + _default_;
	}

	_String __prime_k = " ";
	if((false == __pmy_key__) && (true == __bPrimaryKey))
	{
		__dft = "";
		__not_null = "";
		__prime_k == " PRIMARY KEY ";
	}	

	_String __aics = "";
	if(true == __bAutoIcs)
	{
		__aics = " autoincrement ";
	}

	__used_cls__++;
	__caluse__ << _value_ << " " << _type_ << __prime_k
		       << __aics << __not_null << __unique << __dft;
}

auto TableColum::str() -> _String
{
	return __caluse__.str();
}

