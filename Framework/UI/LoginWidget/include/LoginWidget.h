#pragma once

#include <QtWidgets/QMainWindow>
#include <qDebug>
#include "..\include\LoginPanel.h"
#include "ui_LoginWidget.h"

#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define CLICKED clicked()
#define APPLICATIONMODAL Qt::ApplicationModal
#define SHOWDIRSONLY QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
#define FILESREADABLE QDir::Files | QDir::Readable
#define NAME QDir::Name
#define EXISTINGFILES QFileDialog::ExistingFiles
#define DETAIL QFileDialog::Detail

class LoginWidget : public QWidget
{
	Q_OBJECT

signals:
	void ToLogin(bool);

public:
	LoginWidget(QWidget *parent = Q_NULLPTR);
	~LoginWidget();

private slots:
	void EnableToLogin(bool);

private:
	Ui::LoginWidget ui;
	LoginPanel* loginPanel;
	QMovie* movie;
};
