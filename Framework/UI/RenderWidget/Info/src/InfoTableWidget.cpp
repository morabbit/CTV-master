#include "..\UI\RenderWidget\Info\include\InfoTableWidget.h"

InfoTableWidget::InfoTableWidget(QWidget *parent)
	: QTableWidget(parent) {
	this->InitRefList();
	this->setSelectionBehavior(SELECTROWS);
	this->setSelectionMode(SINGLESELECTION);
	this->setEditTriggers(NOEDITTRIGGERS);
}

InfoTableWidget::~InfoTableWidget() {
	this->renderObj = Q_NULLPTR;
	this->imageFilter = Q_NULLPTR;
}

void InfoTableWidget::InitRefList() {
	this->refList = {
		QStringLiteral("Frame"),
		QStringLiteral("医院名称"),
		QStringLiteral("系列编号"),
		QStringLiteral("当前图号"),
		QStringLiteral("病人编号"),
		QStringLiteral("出生日期"),
		QStringLiteral("性别"),
		QStringLiteral("姓名"),
		QStringLiteral("日期"),
		QStringLiteral("电压(KVP)"),
		QStringLiteral("电流(mA)"),
	};
}

void InfoTableWidget::LoadTable() {
	this->setRowCount(this->refList.size());
	for (int i = 0; i < this->refList.size(); i++) {
		this->setItem(i, 0, new QTableWidgetItem(this->refList[i]));
	}
	_StrStm_ __msg[4];
	DciomObject* head = this->imageFilter->GetDicomHeader();
	__msg[0] << head->dz;
	__msg[1] << head->imageNO;
	__msg[2] << head->kvp;
	__msg[3] << head->electricCurrent;
	this->setItem(0,  1, new QTableWidgetItem(QString::number(head->dz)));
	this->setItem(1,  1, new QTableWidgetItem(QString(head->institution.c_str())));
	this->setItem(2,  1, new QTableWidgetItem(QString(__msg[0].str().c_str())));
	this->setItem(3,  1, new QTableWidgetItem(QString(__msg[1].str().c_str())));
	this->setItem(4,  1, new QTableWidgetItem(QString(head->patientId.c_str())));
	this->setItem(5,  1, new QTableWidgetItem(QString(head->patientBirthDate.c_str())));
	this->setItem(6,  1, new QTableWidgetItem(QString(head->patientSex.c_str())));
	this->setItem(7,  1, new QTableWidgetItem(QString(head->patientName.c_str())));
	this->setItem(8,  1, new QTableWidgetItem(QString(head->InstanceCreationDate.c_str())));
	this->setItem(9,  1, new QTableWidgetItem(QString(__msg[2].str().c_str())));
	this->setItem(10,  1, new QTableWidgetItem(QString(__msg[3].str().c_str())));
}

void InfoTableWidget::SetRenderObj(VolumeRenderController* renderObj) {
	this->renderObj = renderObj;
}

void InfoTableWidget::SetImageFilter(ImageFilterContorller *imageFilter) {
	this->imageFilter = imageFilter;
}
