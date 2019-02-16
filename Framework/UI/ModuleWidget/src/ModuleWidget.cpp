#include "..\include\ModuleWidget.h"

ModuleWidget::ModuleWidget(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);

	CONNECT(this->ui.tbtnSW, CLICKED, this, SelectModule());
}

ModuleWidget::~ModuleWidget() {
}

void ModuleWidget::SetRenderObj(VolumeRenderController *renderObj) {
	this->renderObj = renderObj;
}

void ModuleWidget::SetImageFilter(ImageFilterContorller *imageFilter) {
	this->imageFilter = imageFilter;
}

void ModuleWidget::SetDicomInfoSQL(DicomInfoTable *sql) {
	this->sql = sql;
}

void ModuleWidget::SelectModule() {
	this->LoadFileWidget();
}