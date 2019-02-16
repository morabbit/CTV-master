#pragma once

#include <QtWidgets/QMainWindow>
#include <qDebug>
#include <QFileDialog>
#include <QDir>
#include "ui_AddDateWidget.h"

#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define CLICKED clicked()
#define APPLICATIONMODAL Qt::ApplicationModal
#define SHOWDIRSONLY QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
#define FILESREADABLE QDir::Files | QDir::Readable
#define NAME QDir::Name
#define EXISTINGFILES QFileDialog::ExistingFiles
#define DETAIL QFileDialog::Detail

class AddDateWidget : public QWidget
{
	Q_OBJECT

public:
	AddDateWidget(QWidget *parent = Q_NULLPTR);

private slots:
	void ChooseDirDialog();
	void ChooseFileDialog();
	void ResetTableWidget();
	void SendFilePath();

private:
	Ui::AddDateWidget ui;
};

