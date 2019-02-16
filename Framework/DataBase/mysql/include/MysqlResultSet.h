#pragma once
#ifndef __MYSQLRESULTSET_H
#define __MYSQLRESULTSET_H
#include "BasicResultSet.h"

class MysqlDataSet : public ResultSetObject
{

public:
	MysqlDataSet(__P_Mysql __ret, _String __sql);
	MysqlDataSet();
	~MysqlDataSet();
	MysqlDataSet(const MysqlDataSet& __obj);
	MysqlDataSet& operator=(const MysqlDataSet& __obj);

public:
	auto set_result(__P_Mysql __mysql_ret,
					__P_Sqlite __sqlite_ret,
					_String __sql) -> void;

private:
	auto __initialize(__P_Mysql& __ret, _String __sql) -> void;

};


#endif // !__MYSQLRESULTSET_H
