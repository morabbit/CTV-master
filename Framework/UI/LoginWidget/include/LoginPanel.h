#pragma once

#include <QtWidgets/QMainWindow>
#include <qDebug>
#include "..\UI\LoginWidget\include\TwoDcode.h"
#include "..\UI\LoginWidget\include\AboutUs.h"
#include "ui_LoginPanel.h"

#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define CLICKED clicked()
#define APPLICATIONMODAL Qt::ApplicationModal
#define SHOWDIRSONLY QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
#define FILESREADABLE QDir::Files | QDir::Readable
#define NAME QDir::Name
#define EXISTINGFILES QFileDialog::ExistingFiles
#define DETAIL QFileDialog::Detail
#define REVERSE(a) a =!a

class LoginPanel : public QWidget
{
	Q_OBJECT

signals:
	void EnableLogin(bool);

public:
	LoginPanel(QWidget *parent = Q_NULLPTR);
	~LoginPanel();

private slots:
	void BtnLogin();
	void ServiceInfo();
	void ShowTwoDCode();
	void ShowAboutUsInfo();

private:
	Ui::LoginPanel ui;
	TwoDcode* twoDcode;
	AboutUs* aboutUsInfo;
	bool serviceInfoHighLight;
};
