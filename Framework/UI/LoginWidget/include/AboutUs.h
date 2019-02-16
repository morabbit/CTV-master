#pragma once

#include <QtWidgets/QMainWindow>
#include <QDialog>
#include <qDebug>
#include "ui_AboutUs.h"

#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define CLICKED clicked()
#define APPLICATIONMODAL Qt::ApplicationModal
#define SHOWDIRSONLY QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
#define FILESREADABLE QDir::Files | QDir::Readable
#define NAME QDir::Name
#define EXISTINGFILES QFileDialog::ExistingFiles
#define DETAIL QFileDialog::Detail
#define REVERSE(a) a =!a

class AboutUs : public QDialog
{
	Q_OBJECT

public:
	AboutUs(QDialog *parent = Q_NULLPTR);
	~AboutUs();

private:
	Ui::AboutUs ui;
};