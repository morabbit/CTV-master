#pragma once

#include <QtWidgets/QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QCloseEvent> 
#include <QMessageBox> 
#include <QTableWidgetItem>

#include "ui_MainWindow.h"

#include "AddDateWidget.h"
#include "DicomWidget.h"
#include "SaveWidget.h"
#include "..\UI\FileWidget\Widget\include\FileWidget.h"
#include "..\UI\RenderWidget\Render\include\RenderWidget.h"
#include "..\UI\ModuleWidget\include\ModuleWidget.h"
#include "..\UI\LoginWidget\include\LoginWidget.h"
#include "CloseDialog.h"
#include "TraceLogExporter.h"
#include "CommonLayer.h"


#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define TRIGGERED triggered()
#define SHOW show()
#define CLICKED clicked()


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private slots:
	void Back();
	void DoLogin(bool);
	void LoadCaseFile();
	void DoRender(QString);
	void BtnClose();

protected:
	void ShowRender();

private:
	Ui::MainWindow ui;

	AddDateWidget* addDateWidget;
	DicomWidget* dicomWidget;
	SaveWidget* saveWidget;
	CloseDialog* closeDialog;

	LoginWidget* loginWidget;
	ModuleWidget* moduleWidget;
	FileWidget* fileWidget;
	RenderWidget* renderWidget;

	VolumeRenderController* renderObj;
	ImageFilterContorller* imageFilter;
	RoutePlanning* routePlan;
	DicomInfoTable* sql;
};