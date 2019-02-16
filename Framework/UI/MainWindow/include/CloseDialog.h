#pragma once

#include <QtWidgets/QMainWindow>
#include <QDialog>

#include "ui_CloseDialog.h"


#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define TRIGGERED triggered()
#define SHOW show()
#define CLICKED clicked()


class CloseDialog : public QDialog
{
	Q_OBJECT

signals:
	void WindowClose();

public:
	CloseDialog(QDialog *parent = Q_NULLPTR);
	~CloseDialog();

private slots:
	void BtnOK();

private:
	Ui::CloseDialog ui;
};