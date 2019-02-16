#include "pch.h"
#include "FrameworkErrorCode.h"
#include "SqliteDataBase.h"
#include "ParseVariableparameter.h"
#include "TraceLogExporter.h"


SqliteObject::SqliteObject()
{
	m_db_obj._sqlite.m_db = nullptr;
}

SqliteObject::~SqliteObject()
{
}

NTSTATUS SqliteObject::open_db()
{
	try
	{
		int __res = sqlite3_open(m_db_obj._sqlite.db_name, &m_db_obj._sqlite.m_db);
		if(SQLITE_OK != __res)
		{
			std::cout << "failed to open "
				<< sqlite3_errmsg(m_db_obj._sqlite.m_db) << std::endl;
			m_db_obj._status = __res;
			return OPEN_SQLITE_DB_FAILED;
		}
	}
	catch(const std::exception& )
	{
		m_db_obj._status = OPEN_SQLITE_DB_EXCEPTION;
		
		return OPEN_SQLITE_DB_EXCEPTION;
	}
	

	return SUCCESSED;
}

NTSTATUS SqliteObject::close_db()
{
	try
	{
		int __res = sqlite3_close(m_db_obj._sqlite.m_db);
		if(SQLITE_OK != __res)
		{
			std::cout << "failed to close "
				<< sqlite3_errmsg(m_db_obj._sqlite.m_db) << std::endl;
			m_db_obj._status = __res;
			return SQLITE_CLOSED_FAILED;
		}
	}
	catch(const std::exception&)
	{
		m_db_obj._status = SQLITE_CLOSED_EXCEPTION;
		return SQLITE_CLOSED_EXCEPTION;
	}

	return SUCCESSED;
}

NTSTATUS SqliteObject::initialize_db(CPCHAR _db_name)
{
	if(_db_name == "")
	{
		m_db_obj._status = SQLITE_FILE_NAME_IS_NULL;
		return SQLITE_FILE_NAME_IS_NULL;
	}
	m_db_obj._sqlite.db_name = _db_name;

	return SUCCESSED;
}

auto SqliteObject::free_result(sql::ResultSet**, _sqlit_resutlt** __ret) -> NTSTATUS
{
	try
	{
		if((*__ret)->pResult != nullptr)
		{
			sqlite3_free_table((*__ret)->pResult);
		}
	}
	catch(const std::exception&)
	{
		m_db_obj._status = SQLITE_FREE_RESULT_FALIED;
		//result._sqlite_ret.errMsg = const_cast<char*>(err.what());
		return SQLITE_FREE_RESULT_FALIED;
	}

	return SUCCESSED;
}

auto SqliteObject::excute(_String sql) -> NTSTATUS
{
	try
	{
		PCHAR __err_msg = 0;
		INT __res = sqlite3_exec(m_db_obj._sqlite.m_db, 
								 sql.c_str(), 0, 0, &__err_msg);
		PRINT_DBG("excute:: res= %d",  __res);
		PRINT_DBG("excute:: sql= %s",  sql);
		if(SQLITE_OK != __res)
		{
			m_db_obj._status = SQLITE_EXCUTE_FALIED;
			return SQLITE_EXCUTE_FALIED;
		}
	}
	catch(const std::exception&)
	{
		m_db_obj._status = SQLITE_EXCUTE_EXCEPTION;
		return SQLITE_EXCUTE_EXCEPTION;
	}

	return SUCCESSED;
}

auto SqliteObject::select(_String sql) -> SqliteDataSet&
{
	SqliteDataSet* __result = new SqliteDataSet;
	_sqlit_resutlt* __P_Sqlite = new _sqlit_resutlt;
	try
	{
		INT __ret = sqlite3_get_table(m_db_obj._sqlite.m_db, sql.c_str(),
									  &__P_Sqlite->pResult, &__P_Sqlite->nrow,
									  &__P_Sqlite->ncolumn, &__P_Sqlite->errMsg);
		if(SQLITE_OK != __ret)
		{
			m_db_obj._status = SQLITE_EXCUTE_FALIED;
			__result->__err_msg__ << __P_Sqlite->errMsg;
			sqlite3_free(__P_Sqlite->errMsg);
			return *__result;
		}
		__result->set_result(nullptr, __P_Sqlite, sql);
		free_result(nullptr, &__P_Sqlite);
	}
	catch(const std::exception& err)
	{
		__result->_status = SQLITE_FREE_RESULT_FALIED;
		__result->__err_msg__ << err.what();
		return *__result;
	}	

	return *__result;
}

auto SqliteObject::select(CPCHAR fmt, ...) -> SqliteDataSet&
{
	_StrStm_ __mess;

	va_list __args;
	va_start(__args, fmt);
	__mess = ParseVariables::var_param(fmt, __args);
	va_end(__args);

	return select(__mess.str());
}

auto SqliteObject::select(_String _tbl_, Column _col_, ContentCaluse _cdt_, GroupBy _gpb_, Having _hv_, OrderBy _odb_) -> SqliteDataSet &
{
	_StrStm_ __mess;
	__mess << "select ";
	if(_col_.__used_cls__ <= 0)
	{
		__mess << " * from ";
	}
	else
	{
		__mess << _col_.str() << " from ";
	}
	__mess << _tbl_;

	if(_cdt_.__used_cls__ > 0)
	{
		__mess << _cdt_.str();
	}
	if(_hv_.__used_cls__ > 0)
	{
		__mess << " having " << _hv_.str();
	}

	if(_gpb_.__used_cls__ > 0)
	{
		__mess << " group by " << _gpb_.str();
	}
	if(_odb_.__used_cls__ > 0)
	{
		__mess << " order by " << _gpb_.str();
	}

	return select(__mess.str());
}
