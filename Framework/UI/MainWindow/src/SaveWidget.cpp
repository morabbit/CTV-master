#include "..\include\SaveWidget.h"

SaveWidget::SaveWidget(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);
	this->setWindowModality(APPLICATIONMODAL);
}