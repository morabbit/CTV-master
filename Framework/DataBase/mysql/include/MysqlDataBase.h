#pragma once
#ifndef __MYSQLDATABASE_H
#define __MYSQLDATABASE_H
#include "DataBaseObject.h"

class MysqlObject : public BaseDBObject
{
public:
	MysqlObject();
	~MysqlObject();

public:
	auto open_db() -> NTSTATUS;
	auto close_db() -> NTSTATUS;	

	auto initialize_db(CPCHAR _db_name)->NTSTATUS;
	auto free_result(sql::ResultSet**, _sqlit_resutlt**)->NTSTATUS;

	auto excute(_String sql) -> NTSTATUS;

	auto select(_String sql)->MysqlDataSet&;  //covariant
	auto select(CPCHAR format, ...)->MysqlDataSet&; // covariant
	auto select(_String _tbl_, Column _col_, ContentCaluse _cdt_,
				GroupBy _gpb_, Having _hv_, OrderBy _odb_)->MysqlDataSet&;
};

#endif // !__MYSQLDATABASE_H
