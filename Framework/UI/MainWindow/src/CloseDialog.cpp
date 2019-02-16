#include "..\include\CloseDialog.h"

CloseDialog::CloseDialog(QDialog *parent)
	: QDialog(parent) {
	ui.setupUi(this);

	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	this->setModal(true);

	this->setFixedSize(this->width(), this->height());

	CONNECT(this->ui.btnOK, CLICKED, this, BtnOK());
	CONNECT(this->ui.btnCancel, CLICKED, this, hide());
}

CloseDialog::~CloseDialog() {
}

void CloseDialog::BtnOK() {
	this->hide();
	this->WindowClose();
}