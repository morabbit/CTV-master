#include "..\include\AddDateWidget.h"


AddDateWidget::AddDateWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowModality(APPLICATIONMODAL);

	CONNECT(this->ui.btnChooseDir, CLICKED, this, ChooseDirDialog());
	CONNECT(this->ui.btnChooseFile, CLICKED, this, ChooseFileDialog());
	CONNECT(this->ui.btnReset, CLICKED, this, ResetTableWidget());
	CONNECT(this->ui.btnOK, CLICKED, this, SendFilePath());
	CONNECT(this->ui.btnCancel, CLICKED, this, close());
}

void AddDateWidget::ChooseDirDialog() {
	QString path = QFileDialog::getExistingDirectory(this, QStringLiteral("Open Directory"), ".", SHOWDIRSONLY);
	QDir dir(path);
	QStringList nameFilters;
	QStringList fileNames = dir.entryList(nameFilters, FILESREADABLE, NAME);
	int rowIndex = this->ui.tableWidget->rowCount();
	int count = 0;
	this->ui.tableWidget->setRowCount(rowIndex + fileNames.count());

	for (auto tmp : fileNames) {
		QTableWidgetItem *item = new QTableWidgetItem(path + "/" + tmp);
		this->ui.tableWidget->setItem(rowIndex + count, 0, item);
		count++;
	}
}

void AddDateWidget::ChooseFileDialog() {
	QFileDialog *fileDialog = new QFileDialog(this);
	fileDialog->setWindowTitle(QStringLiteral("open file"));
	fileDialog->setDirectory(".");
	fileDialog->setNameFilter(QStringLiteral("ALL Files(*.*)"));
	fileDialog->setFileMode(EXISTINGFILES);
	fileDialog->setViewMode(DETAIL);
	QStringList fileNames;
	if (fileDialog->exec()) {
		fileNames = fileDialog->selectedFiles();
	}

	int rowIndex = this->ui.tableWidget->rowCount();
	int count = 0;
	this->ui.tableWidget->setRowCount(rowIndex + fileNames.count());

	for (auto tmp : fileNames) {
		QTableWidgetItem *item = new QTableWidgetItem(tmp);
		this->ui.tableWidget->setItem(rowIndex + count, 0, item);
		count++;
	}
}

void AddDateWidget::ResetTableWidget() {
	this->ui.tableWidget->clearContents();
	this->ui.tableWidget->setRowCount(0);
}

void AddDateWidget::SendFilePath() {
	std::vector<std::string> fileNames;
	for (int i = 0; i < this->ui.tableWidget->rowCount(); i++) {
		fileNames.push_back((this->ui.tableWidget->item(i, 0)->text()).toStdString());
	}
	this->close();
}
