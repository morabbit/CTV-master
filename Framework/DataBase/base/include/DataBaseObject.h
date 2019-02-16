#pragma once
#ifndef __DATABASEOBJECT_H
#define __DATABASEOBJECT_H
#include "DBContentValues.h"
#include "DBContentClause.h"
#include "DataBaseSelectColumn.h"
#include "ParseVariableparameter.h"
#include "CreateTableColum.h"

class BaseDBObject
{
public:
	typedef enum DB_Operator
	{
		Add = 1,
		Change ,
		Modify,
		Drop,
	}_Optr;

public:
	virtual ~BaseDBObject();

public:
	virtual auto open_db() -> NTSTATUS = 0;
	virtual auto close_db()  -> NTSTATUS = 0;

	virtual auto initialize_db(CPCHAR _db_name)->NTSTATUS = 0;
	virtual auto free_result(sql::ResultSet**, _sqlit_resutlt**)->NTSTATUS = 0;

	virtual auto excute(_String sql) -> NTSTATUS = 0;
	
	virtual auto select(_String sql)->ResultSetObject& = 0;
	virtual auto select(CPCHAR format, ...)->ResultSetObject& = 0;
	virtual auto select(_String _tbl_, Column _col_, ContentCaluse _cdt_,
						GroupBy _gpb_, Having _hv_, OrderBy _odb_)->ResultSetObject& = 0;
	
	virtual auto excute(CPCHAR fmt, ...) -> NTSTATUS;

	virtual auto insert(_String sql)->NTSTATUS;
	virtual auto insert(CPCHAR fmt, ...)->NTSTATUS;
	virtual auto insert2(_String tbl, ContentValue val)->NTSTATUS;

	virtual auto update(_String sql)->NTSTATUS ;	
	virtual auto update(CPCHAR fmt, ...)->NTSTATUS;
	virtual auto update2(_String tbl, ContentValue val, ContentCaluse caluse)->NTSTATUS;

	virtual auto deleting(_String sql)->NTSTATUS;
	virtual auto deleting(CPCHAR fmt, ...)->NTSTATUS;
	virtual auto deleting2(_String tbl, ContentCaluse caluse)->NTSTATUS;

	virtual auto create_table(_String sql)->NTSTATUS;
	virtual auto create_table(uint32_t cnt, ...)->NTSTATUS ;
	virtual auto create_table2(_String sql, TableColum _col_)->NTSTATUS;
	

	virtual auto alter_table(_String sql)->NTSTATUS ;
	virtual auto alter_table(uint32_t cnt, ...)->NTSTATUS ;

public:
	_DB_ m_db_obj;
};


#endif // !__DATABASEOBJECT_H

