#include "..\include\TwoDcode.h"

TwoDcode::TwoDcode(QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	this->setModal(true);

	this->setFixedSize(this->width(), this->height());

	CONNECT(this->ui.toolButton, CLICKED, this, hide());
}

TwoDcode::~TwoDcode() {
}