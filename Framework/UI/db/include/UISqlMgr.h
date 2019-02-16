#pragma once
#ifndef __UISQLMGR
#define __UISQLMGR

#include <QString>
#include <QStringList>
#include "DataBaseCommunicator.h"
#include "SqliteDataBase.h"

class DicomInfoTable : public SqliteObject {
public:
	DicomInfoTable() {};
	~DicomInfoTable() {};
	_String GetTableName();

	bool CreateTable();
	bool AddDate(QString, QString);
	QString SearchDate(UINT& size, QString col, QString cdt);
	bool DeleteDate(QString);
	bool DeleteALLDate();
};

#endif // !__UISQLMGR
