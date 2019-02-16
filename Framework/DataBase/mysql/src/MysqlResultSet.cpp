#include "pch.h"
#include "MysqlResultSet.h"

MysqlDataSet::MysqlDataSet(__P_Mysql __ret, _String __sql)
{
	this->__row_count__ = 0;
	this->__column_count__ = 0;
	__initialize(__ret, __sql);
}

MysqlDataSet::MysqlDataSet()
{
}

MysqlDataSet::~MysqlDataSet()
{
}

MysqlDataSet::MysqlDataSet(const MysqlDataSet & __obj)
{
	*this = __obj;
}

MysqlDataSet & MysqlDataSet::operator=(const MysqlDataSet & __obj)
{
	this->__sql__ = __obj.__sql__;
	this->__result__ = __obj.__result__;
	this->__row_count__ = __obj.__row_count__;
	this->__column_count__ = __obj.__column_count__;

	return *this;
}

void MysqlDataSet::set_result(__P_Mysql __mysql_ret,
							  __P_Sqlite __sqlite_ret,
							  _String __sql)
{
	this->__row_count__ = 0;
	this->__column_count__ = 0;
	__initialize(__mysql_ret, __sql);
}


void MysqlDataSet::__initialize(__P_Mysql& __ret, _String __sql)
{
	using QStr = sql::SQLString;
	this->__sql__ = __sql;
	auto __is_count = strstr(__sql__.c_str(), "count(");
	sql::ResultSetMetaData* __rms = __ret->getMetaData();
	__column_count__ = __rms->getColumnCount();

	uint32_t __index = 0;
	while(__ret->next())
	{
		StrVector __vec;
		for(uint32_t i = 1; i <= __column_count__; i++)
		{
			QStr __col_value = __ret->getString(i);
			__vec.push_back(__col_value.c_str());
		}
		__result__.insert(std::make_pair(__index++, __vec));

		if(0 != __is_count)
		{
			this->__row_count__ = __ret->getInt(1);
		}
		else 
		{
			this->__row_count__++;
		}
	}
}

