#pragma once

#include <QtWidgets/QMainWindow>
#include <QDialog>

#include "ui_Warning.h"


#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define TRIGGERED triggered()
#define SHOW show()
#define CLICKED clicked()


class Warning : public QDialog
{
	Q_OBJECT

public:
	Warning(QDialog *parent = Q_NULLPTR);
	~Warning();
	void SetWarningInfo(QString);

private slots:

private:
	Ui::Warning ui;
};
