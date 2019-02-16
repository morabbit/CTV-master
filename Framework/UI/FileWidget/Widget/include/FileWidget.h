#pragma once

#include <QDir>
#include <QFileDialog>
#include <QCloseEvent> 
#include <QTableWidgetItem>
#include <QMap> 
#include <QDebug>

#include "..\UI\FileWidget\TableWidget\include\RawDataTableWidget.h"
#include "..\UI\FileWidget\ToolDialog\PatientCaseAdd\include\PatientCaseAddDialog.h"
#include "..\UI\FileWidget\ToolDialog\PatientCaseEdit\include\PatientCaseEditDialog.h"
#include "..\UI\FileWidget\ToolDialog\Warning\include\Warning.h"
#include "..\..\UI\db\include\UISqlMgr.h"
#include "CommonLayer.h"
#include "ui_FileWidget.h"

#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define TRIGGERED triggered()
#define SHOW show()
#define CLICKED clicked()
#define PRESSED pressed()
#define RELEASED released()
#define ITEMCLICKED itemClicked(QTableWidgetItem*)
#define CELLCLICKED cellClicked(int, int)
#define CELLDOUBLECLICKED cellDoubleClicked(int, int)
#define SELECTROWS QAbstractItemView::SelectRows
#define SINGLESELECTION QAbstractItemView::SingleSelection
#define SHOWDIRSONLY QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
#define EXISTINGFILES QFileDialog::ExistingFiles
#define DETAIL QFileDialog::Detail


class FileWidget : public QWidget {
	Q_OBJECT

public:
	FileWidget(QWidget *parent = Q_NULLPTR);
	~FileWidget();
	void SetRenderObj(VolumeRenderController*);
	void SetImageFilter(ImageFilterContorller*);
	void SetDicomInfoSQL(DicomInfoTable*);

signals:
	void RenderSign(QString);

private slots:
	void OnBtnPressed();
	void OnBtnReleased();
	void AddFolder();
	void Render();
	void PatientCaseEdit();
	void ChangeFileImg(QTableWidgetItem*);

private:
	Ui::FileWidget ui;
	VolumeRenderController* renderObj;
	ImageFilterContorller* imageFilter;
	QMap<QString, ImageFilterContorller*>* imageFilterMap;
	DicomInfoTable* sql;

	Warning* dialogWarning;
	PatientCaseAddDialog* dialogPatientCaseAdd;
	PatientCaseEditDialog* dialogPatientCaseEdit;

	QToolButton* btnList[16];
	QPixmap btnNormalPixList[16];
	QPixmap btnPressedPixList[16];
};