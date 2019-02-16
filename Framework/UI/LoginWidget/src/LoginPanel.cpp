#include "..\include\LoginPanel.h"

LoginPanel::LoginPanel(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->serviceInfoHighLight = false;

	this->ui.widget->setFixedSize(450, 400);
	this->ui.labelUserName->setMinimumWidth(45);
	this->ui.labelPassword->setMinimumWidth(45);
	this->ui.tbtnPasswordVisible->setMinimumWidth(70);

	this->twoDcode = new TwoDcode();
	this->aboutUsInfo = new AboutUs();

	CONNECT(this->ui.btnLogin, CLICKED, this, BtnLogin());
	CONNECT(this->ui.tbtnService, CLICKED, this, ServiceInfo());
	CONNECT(this->ui.tbtnPublicAddress, CLICKED, this, ShowTwoDCode());
	CONNECT(this->ui.tbtnAboutUs, CLICKED, this, ShowAboutUsInfo());
}

LoginPanel::~LoginPanel() {
}

void LoginPanel::BtnLogin() {
	this->EnableLogin(true);
}

void LoginPanel::ServiceInfo() {
	if (this->serviceInfoHighLight) {
		QBrush brush(QColor(51, 51, 51, 255));
		brush.setStyle(Qt::SolidPattern);

		QPalette palette;
		palette.setBrush(QPalette::Active, QPalette::WindowText, brush);

		this->ui.labelTelphoneNumber->setPalette(palette);
		this->ui.labelEmail->setPalette(palette);
	} else {
		QBrush brush(QColor(51, 124, 167, 255));
		brush.setStyle(Qt::SolidPattern);

		QPalette palette;
		palette.setBrush(QPalette::Active, QPalette::WindowText, brush);

		this->ui.labelTelphoneNumber->setPalette(palette);
		this->ui.labelEmail->setPalette(palette);
	}
	REVERSE(this->serviceInfoHighLight);
}

void LoginPanel::ShowTwoDCode() {
	this->twoDcode->setGeometry(
		this->ui.tbtnPublicAddress->mapToGlobal(this->ui.tbtnPublicAddress->pos()).x() - 260,
		this->ui.tbtnPublicAddress->mapToGlobal(this->ui.tbtnPublicAddress->pos()).y() - 100, 
		300, 300);
	this->twoDcode->show();
}

void LoginPanel::ShowAboutUsInfo() {
	this->aboutUsInfo->show();
}
