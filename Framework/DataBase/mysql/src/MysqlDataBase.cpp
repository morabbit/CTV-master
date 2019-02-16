#include "pch.h"
#include "FrameworkDefine.h"
#include "MysqlDataBase.h"
#include "MysqlBasicObjectManager.h"
#include "MysqlBDatebaseObject.h"
#include "ParseVariableparameter.h"


MysqlObject::MysqlObject()
{
	m_db_obj._mysql.m_state = nullptr;
}

MysqlObject::~MysqlObject()
{
	if(nullptr != m_db_obj._mysql.m_state)
	{
		delete m_db_obj._mysql.m_state;
	}
}

NTSTATUS MysqlObject::open_db()
{	
	_DB_Pool* __pool = _DB_Pool::GetInstance();
	m_db_obj._mysql._conn = __pool->ConnectDataBasePool();

	if(nullptr == m_db_obj._mysql._conn)
	{
		m_db_obj._status = INITIALIZE_MYSQL_FAILED;
		return INITIALIZE_MYSQL_FAILED;
	}

	m_db_obj._mysql.m_state =
		m_db_obj._mysql._conn->createStatement();

	return SUCCESSED;
}

NTSTATUS MysqlObject::close_db()
{
	_DB_Pool* __pool = _DB_Pool::GetInstance();
	__pool->DisconnectDataBasePool(m_db_obj._mysql._conn);

	return SUCCESSED;
}

NTSTATUS MysqlObject::initialize_db(CPCHAR _db_name)
{
	if(_db_name == "")
	{
		m_db_obj._status = MYSQL_DB_NAME_IS_NULL;
		return MYSQL_DB_NAME_IS_NULL;
	}
	_StrStm_ __str;
	__str << "use " << _db_name;
	m_db_obj._mysql.m_state->execute(__str.str().c_str());

	return SUCCESSED;
}

NTSTATUS MysqlObject::free_result(sql::ResultSet** __ret, _sqlit_resutlt**)
{
	if(nullptr == *__ret)
	{
		m_db_obj._status = MYSQL_RESULT_NULL;
		return MYSQL_RESULT_NULL;
	}

	delete *__ret;

	return SUCCESSED;
}

NTSTATUS MysqlObject::excute(_String sql)
{
	try
	{
		int __rt = m_db_obj._mysql.m_state->executeUpdate(sql.c_str());
		if(__rt != 0)
		{
			m_db_obj._status = EXCUTE_MYSQL_FAILED;
			return EXCUTE_MYSQL_FAILED;
		}
	}
	catch(const std::exception& )
	{
		m_db_obj._status = SQL_STATEMENT_SYNTAX_ERROR;
		return SQL_STATEMENT_SYNTAX_ERROR;
	}

	return SUCCESSED;
}

MysqlDataSet& MysqlObject::select(_String sql)
{
	_DB_Result_opt_ __ret;

	sql::ResultSet* __result = m_db_obj._mysql.m_state->executeQuery(sql.c_str());

	MysqlDataSet* __result_set = new MysqlDataSet;
	__result_set->set_result(__result, nullptr, sql);

	free_result(&__result, nullptr);

	return *__result_set;
}

MysqlDataSet& MysqlObject::select(CPCHAR fmt, ...)
{
	_StrStm_ __mess;

	va_list __args;
	va_start(__args, fmt);
	__mess = ParseVariables::var_param(fmt, __args);
	va_end(__args);

	return select(__mess.str());
}

auto MysqlObject::select(_String _tbl_, Column _col_, ContentCaluse _cdt_,
						 GroupBy _gpb_, Having _hv_, OrderBy _odb_) -> MysqlDataSet &
{
	_StrStm_ __mess;
	__mess << "select " ;
	if(_col_.__used_cls__ <= 0)
	{
		__mess << " * from ";
	}
	else
	{
		__mess << _col_.str() <<" from ";
	}
	__mess << _tbl_ << " ";

	if(_cdt_.__used_cls__ > 0)
	{
		__mess << _cdt_.str();
	}
	if(_hv_.__used_cls__ >= 0)
	{
		__mess << " having " << _hv_.str();
	}

	if(_gpb_.__used_cls__ >= 0)
	{
		__mess << " group by " << _gpb_.str();
	}
	if(_odb_.__used_cls__ >= 0)
	{
		__mess << " order by " << _gpb_.str();
	}

	return select(__mess.str());
}
