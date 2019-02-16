#include "pch.h"
#include "SqliteResultSet.h"


SqliteDataSet::SqliteDataSet()
{
	this->__row_count__ = 0;
	this->__column_count__ = 0;
}

SqliteDataSet::~SqliteDataSet()
{
}

SqliteDataSet::SqliteDataSet(const SqliteDataSet & __obj)
{
	*this = __obj;
}

SqliteDataSet & SqliteDataSet::operator=(const SqliteDataSet & __obj)
{
	this->__sql__ = __obj.__sql__;
	this->__result__ = __obj.__result__;
	this->__row_count__ = __obj.__row_count__;
	this->__column_count__ = __obj.__column_count__;

	return *this;
}

SqliteDataSet::SqliteDataSet(__P_Sqlite __sqlite_ret,
							 _String __sql)
{
	this->__row_count__ = 0;
	this->__column_count__ = 0;
	__initialize(__sqlite_ret, __sql);
}

auto SqliteDataSet::set_result(__P_Mysql __mysql_ret,
							   __P_Sqlite __sqlite_ret,
							   _String __sql) -> void
{
	this->__row_count__ = 0;
	this->__column_count__ = 0;
	__initialize(__sqlite_ret, __sql);
}
//
//auto SqliteDataSet::get_recode_rows() -> int32_t
//{
//	return __row_count__; 
//}
//
//auto SqliteDataSet::get_result_column() -> int32_t
//{
//	return __column_count__;
//}
//
//auto SqliteDataSet::first_row() -> StrVector
//{
//	if(__result__.size() <= 0)
//	{
//		return StrVector();
//	}
//
//	return __result__[0];
//}
//
//auto SqliteDataSet::last_row() -> StrVector
//{
//	if(__result__.size() <= 0)
//	{
//		return StrVector();
//	}
//
//	return __result__[__result__.size() - 1];
//}
//
//auto SqliteDataSet::get_one_row_record(int32_t __row) -> StrVector
//{
//	if(__result__.size() <= __row)
//	{
//		return StrVector();
//	}
//
//	return __result__[__row];
//}
//
//auto SqliteDataSet::first_col() -> StrVector
//{
//	return get_one_col_record(0);
//}
//
//auto SqliteDataSet::last_col() -> StrVector
//{
//	if(__result__.size() == 0)
//	{
//		return StrVector();
//	}
//
//	return get_one_col_record(__result__.size() - 1);
//}
//
//auto SqliteDataSet::get_one_col_record(int32_t __col) -> StrVector
//{
//	typedef DataMap::iterator  _Iter;
//	StrVector __col_recods;
//	for(_Iter __iter = __result__.begin(); __iter != __result__.end(); __iter++)
//	{
//		if(__iter->second.size() > __col)
//		{
//			__col_recods.push_back(__iter->second[__col]);
//		}
//		else
//		{
//			__col_recods.push_back("");
//		}
//	}
//
//	return __col_recods;
//}
//
//auto SqliteDataSet::get_element(int32_t __row, int32_t __col) -> _String
//{
//	if(__result__.size() <= __row)
//	{
//		return "";
//	}
//
//	if(__result__[__row].size() <= __col)
//	{
//		return "";
//	}
//
//	return __result__[__row][__col];
//}

void SqliteDataSet::__initialize(__P_Sqlite __sqlite_ret,
								 _String __sql)
{
	this->__sql__ = __sql;
	auto __is_count = strstr(__sql__.c_str(), "count(");
	
	__column_count__ = (uint32_t)__sqlite_ret->ncolumn;
	uint32_t __index = __column_count__;
	for(uint32_t i = 0; i < (uint32_t)(__sqlite_ret->nrow); i++)
	{
		StrVector __vec;
		for(uint32_t j = 0; j < __column_count__; j++)
		{
			_StrStm_ __mess;
			__mess << __sqlite_ret->pResult[__index++];
			__vec.push_back(__mess.str());
		}
		__result__.insert(std::make_pair(i, __vec));
	}

	if(0 != __is_count)
	{
		__row_count__ = (uint32_t)atoi(__sqlite_ret->pResult[__sqlite_ret->ncolumn]);
	}
	else
	{
		__row_count__ = (uint32_t)__sqlite_ret->nrow;
	}

}
