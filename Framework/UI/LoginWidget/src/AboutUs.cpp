#include "..\include\AboutUs.h"

AboutUs::AboutUs(QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	this->setModal(true);

	this->setFixedSize(this->width(), this->height());

	CONNECT(this->ui.tbtnClose, CLICKED, this, hide());
}

AboutUs::~AboutUs() {
}