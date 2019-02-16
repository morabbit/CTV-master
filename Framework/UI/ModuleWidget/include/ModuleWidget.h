#pragma once

#include <QDir>
#include <QFileDialog>
#include <QCloseEvent> 
#include <QTableWidgetItem>
#include <QDebug>

#include "CommonLayer.h"
#include "TraceLogExporter.h"

#include "..\UI\db\include\UISqlMgr.h"
#include "ui_ModuleWidget.h"

#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define TRIGGERED triggered()
#define SHOW show()
#define CLICKED clicked()
#define PRESSED pressed()
#define RELEASED released()
#define CELLDOUBLECLICKED cellDoubleClicked(int, int)
#define SELECTROWS QAbstractItemView::SelectRows
#define SINGLESELECTION QAbstractItemView::SingleSelection
#define SHOWDIRSONLY QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
#define EXISTINGFILES QFileDialog::ExistingFiles
#define DETAIL QFileDialog::Detail


class ModuleWidget : public QWidget {
	Q_OBJECT

public:
	ModuleWidget(QWidget *parent = Q_NULLPTR);
	~ModuleWidget();
	void SetRenderObj(VolumeRenderController*);
	void SetImageFilter(ImageFilterContorller*);
	void SetDicomInfoSQL(DicomInfoTable*);

signals:
	void LoadFileWidget();

private slots:
	void SelectModule();

private:
	Ui::ModuleWidget ui;
	VolumeRenderController* renderObj;
	ImageFilterContorller* imageFilter;
	DicomInfoTable* sql;
};
