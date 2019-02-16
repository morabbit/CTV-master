#pragma once
#ifndef __DATABASEPROFILES_H
#define __DATABASEPROFILES_H
#include "FrameworkType.h"
//#include <mysql.h>
//#include "sqlite3.h"

//#include <mysql_connection.h>  
//#include <mysql_driver.h>  
//#include <cppconn/exception.h>  
//#include <cppconn/driver.h>  
//#include <cppconn/connection.h>  
//#include <cppconn/resultset.h>  

//#include <cppconn/prepared_statement.h>  
//#include <cppconn/statement.h>  
#include <mutex>
#include <list>  

struct _sqlit_resutlt
{
	int  nrow;
	int  ncolumn;
	char *errMsg;
	char **pResult;
};

#endif // !__DATABASEPROFILES_H
