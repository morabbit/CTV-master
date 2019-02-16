#include "..\include\LoginWidget.h"

LoginWidget::LoginWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->loginPanel = new LoginPanel(this);
	this->ui.gridLayout->addWidget(this->loginPanel, 0, 0, 1, 1);

	CONNECT(this->loginPanel, EnableLogin(bool), this, EnableToLogin(bool));
}

LoginWidget::~LoginWidget() {
}

void LoginWidget::EnableToLogin(bool isEnable) {
	this->ToLogin(isEnable);
}
