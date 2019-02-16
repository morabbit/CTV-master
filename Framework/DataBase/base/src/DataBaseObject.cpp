#include "pch.h"
//#include "FrameworkErrorCode.h"
#include "DataBaseObject.h"
#include "TraceLogExporter.h"
#include "FrameworkDefine.h"

#include <mysql.h>
#include <mysql_connection.h>  
#include <cppconn/exception.h>  
#include <cppconn/driver.h>  
#include <cppconn/connection.h>  

BaseDBObject::~BaseDBObject()
{
}


NTSTATUS BaseDBObject::excute(CPCHAR fmt, ...)
{
	if(strstr(fmt, "select") != 0) return -1;

	_StrStm_ __mess;

	va_list __args;
	va_start(__args, fmt);
	__mess = ParseVariables::var_param(fmt, __args);
	va_end(__args);

	return excute(__mess.str());
}

NTSTATUS BaseDBObject::insert(_String sql)
{
	return excute(sql);
}

NTSTATUS BaseDBObject::insert(CPCHAR fmt, ...)
{
	_StrStm_ __mess;
	if(strstr(fmt, "insert") == 0)
	{
		__mess << " insert into ";
	}
	va_list __args;
	va_start(__args, fmt);
	__mess << ParseVariables::var_param(fmt, __args).str();
	va_end(__args);

	return insert(__mess.str());
}

NTSTATUS BaseDBObject::insert2(_String tbl, ContentValue val)
{
	_StrStm_ __mess;
	__mess << "insert into " << tbl.c_str() << val.insert_str().c_str();
	return insert(__mess.str());
}

NTSTATUS BaseDBObject::update(_String sql)
{
	return excute(sql);
}

NTSTATUS BaseDBObject::update(CPCHAR fmt, ...)
{
	_StrStm_ __mess;
	if(strstr(fmt, "update") == 0)
	{
		__mess << " update ";
	}
	va_list __args;
	va_start(__args, fmt);
	__mess = ParseVariables::var_param(fmt, __args);
	va_end(__args);

	return update(__mess.str());
}

NTSTATUS BaseDBObject::update2(_String tbl, ContentValue val, ContentCaluse caluse)
{
	if(caluse.get_count() <= 0)
	{
		m_db_obj._status = MYSQL_UPDATE_NO_CLAUSE;
		return MYSQL_UPDATE_NO_CLAUSE;
	}
	PRINT_DBG("update2 tbl = %s", tbl);
	PRINT_DBG("update2 val = %s", val.update_str());
	PRINT_DBG("update2 caluse = %s", caluse.str());
	_StrStm_ __mess;
	__mess << "update " << tbl.c_str() << " set " << val.update_str().c_str() << caluse.str();
	PRINT_DBG("update2 __mess = %s", __mess.str());

	return update(__mess.str());
}

NTSTATUS BaseDBObject::deleting(_String sql)
{
	return excute(sql);
}

NTSTATUS BaseDBObject::deleting(CPCHAR fmt, ...)
{
	_StrStm_ __mess;

	if(strstr(fmt, "delete") == 0)
	{
		__mess << " delete from ";
	}	
	va_list __args;
	va_start(__args, fmt);
	__mess = ParseVariables::var_param(fmt, __args);
	va_end(__args);

	return deleting(__mess.str());
}

auto BaseDBObject::deleting2(_String tbl, ContentCaluse caluse) -> NTSTATUS
{
	_StrStm_ __mess;
	__mess << "delete from " << tbl.c_str();

	if(caluse.get_count() > 0) // delete with condition
	{
		__mess << caluse.str();
	}

	return deleting(__mess.str());
}


NTSTATUS BaseDBObject::create_table(_String sql)
{
	return excute(sql);
}

auto BaseDBObject::create_table(uint32_t cnt, ...) -> NTSTATUS
{
	_StrStm_ __mess;
	__mess << "create table if not exists ";
	va_list __args;
	va_start(__args, cnt);

	for(uint32_t i = 0; i < cnt; i++)
	{
		const char* a = va_arg(__args, const char*);
		if(i == 0)
		{
			__mess << a << "(";
			continue;
		};
		__mess << a;
		if(i != cnt - 1) __mess << ",";
	}
	va_end(__args);

	__mess << ");";

	return create_table(__mess.str());
}

auto BaseDBObject::create_table2(_String tbl, TableColum _col_) -> NTSTATUS
{
	_StrStm_ __mess;
	__mess << "create table if not exists ";
	__mess << tbl << "(" << _col_.str() << ");";


	return create_table(__mess.str());
}

NTSTATUS BaseDBObject::alter_table(_String sql)
{
	return excute(sql);
}

NTSTATUS BaseDBObject::alter_table(uint32_t cnt, ...)
{
	_StrStm_ __mess;
	__mess << "alter table ";
	va_list __args;
	va_start(__args, cnt);
	//__mess = ParseVariables::var_param(fmt, __args);
	for(uint32_t i = 0; i < cnt; i++)
	{
		const char* __ch = va_arg(__args, const char*);
		if(i == 0)
		{
			__mess << __ch << " ";
			continue;
		}
		__mess << __ch;
		if(i != cnt - 1) __mess << ",";
	}
	va_end(__args);

	__mess << ";";

	return alter_table(__mess.str());
}
