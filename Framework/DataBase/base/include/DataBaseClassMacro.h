#pragma once
#ifndef __DATABASECLASSMACRO_H
#define __DATABASECLASSMACRO_H
#include "MysqlResultSet.h"
#include "SqliteResultSet.h"


enum Order
{
	DESC = 1,
	ASC = 2,
};

#define FrameworkClassMacro(name)					\
class name											\
{													\
public:												\
    name(){ __used_cls__ = 0; }						\
    ~name(){}										\
    name(const name& __obj)							\
    {												\
		*this = __obj;								\
	}												\
    name& operator=(const name& __obj)				\
    {												\
		this->__column__ = _StrStm_();				\
		this->__column__ << __obj.__column__.str(); \
		this->__used_cls__ = __obj.__used_cls__;    \
		return *this;								\
	}												\
	name& operator<<(const _StrStm_& __obj)			\
    {												\
		if(__used_cls__ > 0)						\
		{		                     				\
			this->__column__ << ", "; 				\
        }		                     				\
		__used_cls__++;								\
		this->__column__ << __obj.str();			\
		return *this;								\
	}												\
	name& operator<<(const _String& __obj)			\
	{												\
		if(__used_cls__ > 0)						\
		{		                     				\
			this->__column__ << ", "; 				\
        }		                     				\
		__used_cls__++;								\
		this->__column__ << __obj;					\
		return *this;								\
	}												\
	name& operator<<(const char *& __obj)			\
	{												\
		if(__used_cls__ > 0)						\
		{		                     				\
			this->__column__ << ", "; 				\
        }		                     				\
		__used_cls__++;								\
		this->__column__ << __obj;					\
		return *this;								\
	}												\
    auto str() -> _String							\
    {												\
        return __column__.str();					\
    }												\
public:												\
    int __used_cls__;								\
	_StrStm_ __column__;							\
};


#endif // !__DATABASECLASSMACRO_H
