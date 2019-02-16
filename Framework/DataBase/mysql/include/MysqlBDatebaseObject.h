#pragma once
#ifndef __MYSQLDATABASEOBJECT_H
#define __MYSQLDATABASEOBJECT_H

#include "DataBaseCommon.h"
#include <mysql_driver.h>  

class DBConnectionPool
{
private:
	using sptr_conn = std::shared_ptr<sql::Connection>;

public:
	static DBConnectionPool* GetInstance();
	auto ConnectDataBasePool()->sptr_conn;
	auto DisconnectDataBasePool(sptr_conn& _conn)->void;

private:
	DBConnectionPool();
	DBConnectionPool(CPCHAR _db_, unsigned int _max_size);
	~DBConnectionPool();

private:
	auto __InitializeConnection()-> void;
	auto __CreateConnectionPool(unsigned int _size)-> void;
	auto __CreateConnect() -> sql::Connection*;

	///destory connection pool
	auto __DestoryPool()->void;
	///destory one connection
	auto __DestoryOneConnection()->void;
	/// enlarge connection pool 
	auto __EnlargePool(unsigned int _size) -> void;
	/// reduce connection pool 
	auto __ReducePool(unsigned int _size) -> void;
	
private:
	static DBConnectionPool* __m_DB_Pool__;

	class GC
	{
	public:
		~GC() {
			if(nullptr != __m_DB_Pool__)
			{
				delete __m_DB_Pool__;
				__m_DB_Pool__ = nullptr;
			}
		}
		static GC  __gc__;
	};

	_DB_         __db__ ;
	sql::Driver* __driver__;
	std::mutex   __lock__;
	unsigned int __pool_size__;
	unsigned int __max_size__;
	//create conn list
	std::list<sptr_conn> __conn_list__;	
};

using _DB_Pool = DBConnectionPool;
#endif // !__MYSQLDATABASEOBJECT_H
