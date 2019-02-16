#pragma once
#ifndef __FRAMEWORKINITIALIZE_H
#define __FRAMEWORKINITIALIZE_H


#include "MemoryManager.h"
#include "MysqlBDatebaseObject.h"


_Pool* _Pool::__m_memory__ = new _Pool;
_Pool* gPool = _Pool::GetInstance();

/// need to set size  if project will use mysql £¬
/// also mysql service need to installed to server
_DB_Pool* _DB_Pool::__m_DB_Pool__ = new _DB_Pool("keyin", 0);

//_DB_Pool* g_DB_Pool = _DB_Pool::GetInstance();

/// initialize memory pool 


#endif // !__FRAMEWORKINITIALIZE_H
