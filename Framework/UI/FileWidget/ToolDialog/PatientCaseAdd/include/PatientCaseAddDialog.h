#pragma once

#include <QtWidgets/QMainWindow>
#include <QDialog>

#include "ui_PatientCaseAddDialog.h"


#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define TRIGGERED triggered()
#define SHOW show()
#define CLICKED clicked()


class PatientCaseAddDialog : public QDialog
{
	Q_OBJECT

public:
	PatientCaseAddDialog(QDialog *parent = Q_NULLPTR);
	~PatientCaseAddDialog();

private slots:

private:
	Ui::PatientCaseAddDialog ui;
};