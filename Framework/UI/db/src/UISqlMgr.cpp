#include "../../db/include/UISqlMgr.h"
#include "FrameworkDefine.h"
#include "TraceLogExporter.h"

_String DicomInfoTable::GetTableName()
{
	return "DicomInfoTable";
}

bool DicomInfoTable::CreateTable()
{
	CHECK_STATUS_AND_RETURN_FALSE_IF_FAILED(
		this->initialize_db("Framework.db")
	);
	CHECK_STATUS_AND_RETURN_FALSE_IF_FAILED(
		this->open_db()
	);
	CHECK_STATUS_AND_RETURN_FALSE_IF_FAILED(
		this->excute("CREATE TABLE DicomInfoTable("\
		"Id INTEGER PRIMARY KEY autoincrement,"\
		"Path CHAR(200),Description CHAR(200));")
	);

	return true;
}

bool DicomInfoTable::AddDate(QString key, QString value)
{
	QByteArray keyba = key.toLocal8Bit();
	char* key_ch = keyba.data();
	QByteArray valueba = value.toLocal8Bit();
	char* value_ch = valueba.data();
	PRINT_DBG("key_ch = %s", key_ch);
	PRINT_DBG("value_ch = %s", value_ch);

	UINT dataSize = 0;
	QString tmp = SearchDate(dataSize, "Path", value);
	if (tmp == key) 
	{
		return true;
	} 
	else if (1 == dataSize)
	{
		ContentValue pair;
		pair.put("Path", key_ch);
		ContentCaluse _cdt_;
		_cdt_.equal("Description", value_ch);
		NTSTATUS status = this->update2(GetTableName(), pair, _cdt_);
		PRINT_DBG("GetTableName() = %s", GetTableName());
		PRINT_DBG("if AddDate status = %s", status);
		CHECK_STATUS_AND_RETURN_FALSE_IF_FAILED(status);
	} 
	else
	{
		ContentValue pair;
		pair.put("Path",key_ch);
		pair.put("Description", value_ch);
		NTSTATUS status = this->insert2(GetTableName(), pair);
		PRINT_DBG("else AddDate status = ", status);
		CHECK_STATUS_AND_RETURN_FALSE_IF_FAILED(status);
	}
	return false;
}

QString DicomInfoTable::SearchDate(UINT& size, QString col, QString cdt)
{
	QByteArray col_byt = col.toLocal8Bit();
	char* col_ch = col_byt.data();
	Column _col_ = Column() << col_ch;

	QByteArray cdt_byt = cdt.toLocal8Bit();
	char* cdt_ch = cdt_byt.data();
	ContentCaluse _cdt_;
	_cdt_.equal("Description", cdt_ch);

	GroupBy _gpb_ = GroupBy();
	Having _hv_ = Having();
	OrderBy _odb_ = OrderBy();

	SqliteDataSet result = select(
		GetTableName(), _col_,
		_cdt_, _gpb_,
		_hv_, _odb_
	);

	size = result.get_recode_rows();
	if(result.__result__.size() == 1) 
	{
		QString path = result.__result__[0][0].c_str();
		return path;
	}
	else 
	{
		return QString();
	}
}

bool DicomInfoTable::DeleteDate(QString value)
{
	QByteArray cdt_byt = value.toLocal8Bit();
	char* cdt_ch = cdt_byt.data();
	ContentCaluse _cdt_;
	_cdt_.equal("Description", cdt_ch);
	NTSTATUS status = this->deleting2(GetTableName(), _cdt_);
	CHECK_STATUS_AND_RETURN_FALSE_IF_FAILED(status);

	return false;
}

bool DicomInfoTable::DeleteALLDate()
{
	ContentCaluse _cdt_ = ContentCaluse();
	NTSTATUS status = this->deleting2(GetTableName(), _cdt_);
	CHECK_STATUS_AND_RETURN_FALSE_IF_FAILED(status);

	return false;
}
