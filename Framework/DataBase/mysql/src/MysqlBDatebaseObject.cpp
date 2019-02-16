#include "pch.h"
#include "FrameworkErrorCode.h"
#include "MysqlBDatebaseObject.h"

DBConnectionPool::GC DBConnectionPool::GC::__gc__;

DBConnectionPool::DBConnectionPool()
{
}

DBConnectionPool::DBConnectionPool(CPCHAR _db_, unsigned int _max_size)
{	
	this->__db__._mysql.db_name = _db_;
	this->__db__._mysql.port    = 3306;
	this->__db__._mysql.pwd     = "123456";
	this->__db__._mysql.server  = "127.0.0.1";
	this->__db__._mysql.url     = "tcp://127.0.0.1:3306";
	this->__max_size__  = _max_size;
	this->__pool_size__ = __max_size__ / 2;
	this->__InitializeConnection();
}

DBConnectionPool::~DBConnectionPool()
{
	this->__DestoryPool();
}

void DBConnectionPool::__InitializeConnection()
{
	try {
		this->__driver__ = sql::mysql::get_driver_instance();
	}
	catch(sql::SQLException&)
	{
		perror("Get sql driver failed ");
	}
	catch(std::runtime_error&)
	{
		perror("Run error");
	}

	this->__CreateConnectionPool(__pool_size__);
}

void DBConnectionPool::__CreateConnectionPool(unsigned int _size)
{
	std::lock_guard<std::mutex> __locker(__lock__);
	for(unsigned int i = 0; i < _size; i++)
	{
		sql::Connection* __conn = this->__CreateConnect();
		sptr_conn __sptr_conn(__conn, 
							  [](sql::Connection *conn) {
			delete conn;
		});

		if(__conn)
		{
			__conn_list__.push_back(std::move(__sptr_conn));
		}
		else
		{
			__db__._status = CONNECT_MYSQL_SERVER_FAILED;
			perror("create conn error");
		}
	}
}

sql::Connection * DBConnectionPool::__CreateConnect()
{
	sql::Connection* __conn = nullptr;
	try {
		//create a conn 
		__conn = __driver__->connect(__db__._mysql.url,
									 __db__._mysql.user, 
									 __db__._mysql.pwd); 
		return __conn;
	}
	catch(sql::SQLException& )
	{
		perror("link error");
		return nullptr;
	}
	catch(std::runtime_error& )
	{
		perror("run error");
		return nullptr;
	}
}

void DBConnectionPool::__DestoryPool()
{
	for(auto & __conn: __conn_list__)
	{
		this->__DestoryOneConnection();
	}	
}

void DBConnectionPool::__DestoryOneConnection()
{
	sptr_conn && __sptr_conn = std::move(__conn_list__.front());
	try {
		__sptr_conn->close();
		__pool_size__--;
	}
	catch(sql::SQLException&e)
	{
		perror(e.what());
	}
	catch(std::exception& e)
	{
		perror(e.what());
	}
}

void DBConnectionPool::__EnlargePool(unsigned int _size)
{
	std::lock_guard<std::mutex> __locker(__lock__);
	this->__CreateConnectionPool(_size);
	__pool_size__ = __pool_size__ +  _size;
}

void DBConnectionPool::__ReducePool(unsigned int _size)
{
	std::lock_guard<std::mutex> __locker(__lock__);
	if(_size > __pool_size__)
	{
		_size = __pool_size__;
	}
	for(unsigned int i = 0; i < _size; i++)
	{
		this->__DestoryOneConnection();
	}
	__pool_size__ = __pool_size__ - _size;
}


DBConnectionPool * DBConnectionPool::GetInstance()
{
	return __m_DB_Pool__;
}

std::shared_ptr<sql::Connection> DBConnectionPool::ConnectDataBasePool()
{
	sptr_conn __sptr_conn = nullptr;
	std::lock_guard<std::mutex> __locker(__lock__);
	if(__conn_list__.size() > 0)
	{
		__sptr_conn = __conn_list__.front();
		__conn_list__.pop_front();
		if(__sptr_conn->isClosed())
		{
			__sptr_conn = sptr_conn(this->__CreateConnect());
		}
	}
	else
	{//the pool no conn
		if(__pool_size__ < __max_size__)
		{
			unsigned int __ext_size = 10;
			if(__ext_size + __pool_size__ > __max_size__)
			{
				__ext_size = __max_size__ - __pool_size__;
			}
			this->__EnlargePool(__ext_size);
			__pool_size__ = __pool_size__ + __ext_size;
			__sptr_conn = sptr_conn(this->__CreateConnect());

			if(nullptr == __sptr_conn)
			{
				__db__._status = CONNECT_MYSQL_SERVER_FAILED;
				return nullptr;
			}
		}
		else
		{
			__db__._status = DB_CONNECTION_POOL_FULL;
			return nullptr;
		}
	}
	return __sptr_conn;
}

void DBConnectionPool::DisconnectDataBasePool(sptr_conn& _conn)
{
	if(nullptr != _conn) 
	{
		std::lock_guard<std::mutex> __locker(__lock__);
		__conn_list__.push_back(_conn);
	}
}
