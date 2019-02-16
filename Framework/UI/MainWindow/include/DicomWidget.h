#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include "ui_DicomWidget.h"

#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define CLICKED clicked()
#define APPLICATIONMODAL Qt::ApplicationModal
#define SHOWDIRSONLY QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks


class DicomWidget : public QWidget {
	Q_OBJECT

public:
	DicomWidget(QWidget *parent = Q_NULLPTR);

private slots:
	void ImportFile();

private:
	Ui::DicomWidget ui;
};

