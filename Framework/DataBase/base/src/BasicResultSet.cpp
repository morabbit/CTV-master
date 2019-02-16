#include "pch.h"
#include "BasicResultSet.h"


ResultSetObject::~ResultSetObject()
{
}


int32_t ResultSetObject::get_result_column()
{
	return __column_count__;
}

int32_t ResultSetObject::get_recode_rows()
{
	return __row_count__;
}

StrVector ResultSetObject::first_row()
{
	if(__result__.size() <= 0)
	{
		return StrVector();
	}

	return __result__[0];
}

StrVector ResultSetObject::last_row()
{
	if(__result__.size() <= 0)
	{
		return StrVector();
	}

	return __result__[(uint32_t)(__result__.size() - 1)];
}

StrVector ResultSetObject::get_one_row_record(int32_t __row)
{
	if(__result__.size() <= __row)
	{
		return StrVector();
	}

	return __result__[__row];
}

StrVector ResultSetObject::first_col()
{
	return get_one_col_record(0);
}

StrVector ResultSetObject::last_col()
{
	if(__result__.size() == 0)
	{
		return StrVector();
	}

	return get_one_col_record((uint32_t)(__result__.size() - 1));
}

StrVector ResultSetObject::get_one_col_record(int32_t __col)
{
	typedef DataMap::iterator  _Iter;
	StrVector __col_recods;
	for(_Iter __iter = __result__.begin(); __iter != __result__.end(); __iter++)
	{
		if(__iter->second.size() > __col)
		{
			__col_recods.push_back(__iter->second[__col]);
		}
		else
		{
			__col_recods.push_back("");
		}
	}

	return __col_recods;
}

_String ResultSetObject::get_element(int32_t __row, int32_t __col)
{
	if(__result__.size() <= __row)
	{
		return "";
	}

	if(__result__[__row].size() <= __col)
	{
		return "";
	}

	return __result__[__row][__col];
}
