#pragma once

#include <QtWidgets/QMainWindow>
#include <QDialog>

#include "ui_PatientCaseEditDialog.h"


#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define TRIGGERED triggered()
#define SHOW show()
#define CLICKED clicked()


class PatientCaseEditDialog : public QDialog
{
	Q_OBJECT

public:
	PatientCaseEditDialog(QDialog *parent = Q_NULLPTR);
	~PatientCaseEditDialog();

private slots:

private:
	Ui::PatientCaseEditDialog ui;
};