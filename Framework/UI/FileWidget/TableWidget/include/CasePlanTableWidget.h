#pragma once

#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QTableWidget>
#include <QContextMenuEvent>

#include "CommonLayer.h"
#include "..\UI\db\include\UISqlMgr.h"

#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define TRIGGERED triggered()

class CasePlanTableWidget : public QTableWidget {
	Q_OBJECT

public:
	explicit CasePlanTableWidget(QWidget *parent = 0);
	~CasePlanTableWidget();
	void SetDicomInfoTable(DicomInfoTable*);

protected:
	void contextMenuEvent(QContextMenuEvent*) Q_DECL_OVERRIDE;

private slots:
	void Top();
	void Up();
	void Down();
	void Bottom();
	void Delete();
	void Clear();

private:
	QMenu* menu;
	QAction* actionTop;
	QAction* actionUp;
	QAction* actionDown;
	QAction* actionBottom;
	QAction* actionDelete;
	QAction* actionClear;
	DicomInfoTable* sql;
};