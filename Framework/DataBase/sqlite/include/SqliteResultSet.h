#pragma once

#ifndef __SQLITERESULTSET_H
#define __SQLITERESULTSET_H
#include "BasicResultSet.h"

class SqliteDataSet : public ResultSetObject
{
public:
	SqliteDataSet();
	~SqliteDataSet();
	SqliteDataSet(const SqliteDataSet& __obj);
	SqliteDataSet& operator=(const SqliteDataSet& __obj);
	SqliteDataSet(__P_Sqlite __sqlite_ret,
				  _String __sql);

public:
	auto set_result(__P_Mysql __mysql_ret,
					__P_Sqlite __sqlite_ret,
					_String __sql) -> void;
/*
	auto get_recode_rows()   -> int32_t;
	auto get_result_column() -> int32_t;	

	auto first_row() -> StrVector;
	auto last_row()  -> StrVector;
	auto get_one_row_record(int32_t __row) -> StrVector;

	auto first_col() -> StrVector;
	auto last_col()  -> StrVector;
	auto get_one_col_record(int32_t __col) -> StrVector;

	auto get_element(int32_t __row, int32_t __col) -> _String;
*/
private:
	auto __initialize( __P_Sqlite __sqlite_ret,
					  _String __sql) -> void;
	
};



#endif // !__SQLITERESULTSET_H
