#include "..\include\Warning.h"

Warning::Warning(QDialog *parent)
	: QDialog(parent) {
	ui.setupUi(this);

	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	this->setModal(true);

	this->setFixedSize(this->width(), this->height());

	CONNECT(this->ui.btnOK, CLICKED, this, hide());
}

Warning::~Warning() {
}

void Warning::SetWarningInfo(QString info) {
	this->ui.labelInfo->setText(info);
}
