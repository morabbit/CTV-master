#pragma once
#ifndef __BASICRESULTSET_H
#define __BASICRESULTSET_H
#include "DataBaseProfiles.h"
#include <cppconn/resultset.h>  
class ResultSetObject
{
public:
	using __P_Mysql = sql::ResultSet*;
	using __P_Sqlite = _sqlit_resutlt * ;
public:
	~ResultSetObject();

	virtual auto set_result(__P_Mysql __mysql_ret, 
							__P_Sqlite __sqlite_ret,
							_String __sql) -> void = 0;

public:
	auto get_recode_rows()   -> int32_t;
	auto get_result_column() -> int32_t;	

	auto first_row() -> StrVector;
	auto last_row()  -> StrVector;
	auto get_one_row_record(int32_t __row) -> StrVector;

	auto first_col() -> StrVector;
	auto last_col()  -> StrVector;
	auto get_one_col_record(int32_t __col) -> StrVector;

	auto get_element(int32_t __row, int32_t __col) -> _String;

public:
	NTSTATUS _status;

	_String __sql__;

	uint32_t __row_count__;
	uint32_t __column_count__;

	DataMap __result__;

	_StrStm_ __err_msg__;
};

#endif // !__BASICRESULTSET_H
