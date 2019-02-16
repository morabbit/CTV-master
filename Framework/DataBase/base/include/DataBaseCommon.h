#pragma once
#ifndef __DATABASECOMMON_H
#define __DATABASECOMMON_H

#include "sqlite3.h"
#include "MysqlResultSet.h"
#include "SqliteResultSet.h"
#include <cppconn/connection.h>  
#include <cppconn/prepared_statement.h>  


typedef struct _DataBase
{
	NTSTATUS _status;
	/// mysql 
	struct _my_sql_ {
		///<@ db name
		_String db_name;
		///<@ server ip:port		
		CPCHAR url = "tcp://127.0.0.1:3306";
		///<@ server ip		
		CPCHAR server = "127.0.0.1";
		///<@ user account
		CPCHAR user = "root";
		///<@ password
		CPCHAR pwd = "123456";		
		///<@ server port 
		UINT   port = 3306;
		///<@ DB handle
		sql::Statement* m_state;
		///<@ connection handle
		std::shared_ptr<sql::Connection> _conn;
	}_mysql;
	/// sqlite
	struct _sqlite_
	{
		CPCHAR db_name;
		sqlite3* m_db;
	}_sqlite;
}_DB_;



typedef struct _DB_Result {
	NTSTATUS _status;
	
	/// mysql result
	//MYSQL_RES *_mysql_ret;
	MysqlDataSet _mysql_ret;
	/// sqlite result
	SqliteDataSet _sqlite_ret;

	_DB_Result() {};
	~_DB_Result() {};
	_DB_Result(const _DB_Result& obj)
	{
		*this = obj;
	};
	_DB_Result& operator=(const _DB_Result& __obj)
	{
		this->_status = __obj._status;
		this->_mysql_ret = __obj._mysql_ret;
		this->_sqlite_ret = __obj._sqlite_ret;
		return *this;
	}
}_DB_Result_opt_;

#endif // !__DATABASECOMMON_H
