#include "..\include\DicomWidget.h"

DicomWidget::DicomWidget(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);
	this->setWindowModality(APPLICATIONMODAL);

	CONNECT(this->ui.btnImport, CLICKED, this, ImportFile());
}

void DicomWidget::ImportFile() {
	QString path = QFileDialog::getExistingDirectory(this, QStringLiteral("Open Directory"), ".", SHOWDIRSONLY);
}
