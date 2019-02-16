#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SaveWidget.h"

#define APPLICATIONMODAL Qt::ApplicationModal

class SaveWidget : public QWidget {
	Q_OBJECT

public:
	SaveWidget(QWidget *parent = Q_NULLPTR);

private:
	Ui::SaveWidget ui;
};
