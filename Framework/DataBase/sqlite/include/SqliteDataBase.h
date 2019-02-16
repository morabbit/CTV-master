#pragma once
#ifndef __SPLITEDATABASE_H
#define __SPLITEDATABASE_H
#include "FrameworkType.h"
#include "DataBaseCommon.h"
#include "DataBaseObject.h"


class SqliteObject : public BaseDBObject
{
public:
	SqliteObject();
	~SqliteObject();

public:
	auto open_db()->NTSTATUS;
	auto close_db()->NTSTATUS;

	auto initialize_db(CPCHAR _db_name)->NTSTATUS;
	auto free_result(sql::ResultSet**, _sqlit_resutlt**)->NTSTATUS;

	auto excute(_String sql)->NTSTATUS;		

	auto select(_String sql)->SqliteDataSet&;
	auto select(CPCHAR format, ...)->SqliteDataSet&;

	auto select(_String _tbl_, Column _col_, ContentCaluse _cdt_,
				GroupBy _gpb_, Having _hv_, OrderBy _odb_) -> SqliteDataSet &;
		
};

#endif // !__SPLITEDATABASE_H
