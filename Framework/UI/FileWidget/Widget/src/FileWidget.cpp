#include "..\include\FileWidget.h"
#include "TraceLogExporter.h"

FileWidget::FileWidget(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);

	this->imageFilterMap = new QMap<QString, ImageFilterContorller*>;

	this->ui.tableWidgetRawData->setSelectionBehavior(SELECTROWS);
	this->ui.tableWidgetRawData->setSelectionMode(SINGLESELECTION);
	this->ui.tableWidgetRawData->SetDicomInfoTable(sql);
	this->ui.btnNextStep->setEnabled(false);

	this->btnList[ 0] = this->ui.btnOutputCase;
	this->btnList[ 1] = this->ui.btnInputCase;
	this->btnList[ 2] = this->ui.btnReflashCase;
	this->btnList[ 3] = this->ui.btnPatientCaseAdd;
	this->btnList[ 4] = this->ui.btnPatientCaseEdit;
	this->btnList[ 5] = this->ui.btnPatientCaseDelete;
	this->btnList[ 6] = this->ui.btnRawDataFromPACS;
	this->btnList[ 7] = this->ui.btnRawDataFromLocal;
	this->btnList[ 8] = this->ui.btnRawDataFilter;
	this->btnList[ 9] = this->ui.btnRawDataHelp;
	this->btnList[10] = this->ui.btnCasePlanAdd;
	this->btnList[11] = this->ui.btnImgHorizontalMirror;
	this->btnList[12] = this->ui.btnImgVerticalMirror;
	this->btnList[13] = this->ui.btnImgRotateAntiClockWise;
	this->btnList[14] = this->ui.btnImgRotateClockWise;
	this->btnList[15] = this->ui.btnImgResetImg;

	this->btnNormalPixList[ 0]  = QPixmap(".//Resource//FileWidget//btnOutputCase_normal.png");
	this->btnNormalPixList[ 1]  = QPixmap(".//Resource//FileWidget//btnInputCase_normal.png");
	this->btnNormalPixList[ 2]  = QPixmap(".//Resource//FileWidget//btnReflashCase_normal.png");
	this->btnNormalPixList[ 3]  = QPixmap(".//Resource//FileWidget//btnPatientCaseAdd_normal.png");
	this->btnNormalPixList[ 4]  = QPixmap(".//Resource//FileWidget//btnPatientCaseEdit_normal.png");
	this->btnNormalPixList[ 5]  = QPixmap(".//Resource//FileWidget//btnPatientCaseDelete_normal.png");
	this->btnNormalPixList[ 6]  = QPixmap(".//Resource//FileWidget//btnRawDataFromPACS_normal.png");
	this->btnNormalPixList[ 7]  = QPixmap(".//Resource//FileWidget//btnRawDataFromLocal_normal.png");
	this->btnNormalPixList[ 8]  = QPixmap(".//Resource//FileWidget//btnRawDataFilter_normal.png");
	this->btnNormalPixList[ 9]  = QPixmap(".//Resource//FileWidget//btnRawDataHelp_normal.png");
	this->btnNormalPixList[10]  = QPixmap(".//Resource//FileWidget//btnCasePlanAdd_normal.png");
	this->btnNormalPixList[11]  = QPixmap(".//Resource//FileWidget//btnImgHorizontalMirror_normal.png");
	this->btnNormalPixList[12]  = QPixmap(".//Resource//FileWidget//btnImgVerticalMirror_normal.png");
	this->btnNormalPixList[13]  = QPixmap(".//Resource//FileWidget//btnImgHorizontalTransform_normal.png");
	this->btnNormalPixList[14]  = QPixmap(".//Resource//FileWidget//btnImgVerticalTransform_normal.png");
	this->btnNormalPixList[15]  = QPixmap(".//Resource//FileWidget//btnImgRotate_normal.png");

	this->btnPressedPixList[ 0] = QPixmap(".//Resource//FileWidget//btnOutputCase_Pressed.png");
	this->btnPressedPixList[ 1] = QPixmap(".//Resource//FileWidget//btnInputCase_Pressed.png");
	this->btnPressedPixList[ 2] = QPixmap(".//Resource//FileWidget//btnReflashCase_Pressed.png");
	this->btnPressedPixList[ 3] = QPixmap(".//Resource//FileWidget//btnPatientCaseAdd_Pressed.png");
	this->btnPressedPixList[ 4] = QPixmap(".//Resource//FileWidget//btnPatientCaseEdit_Pressed.png");
	this->btnPressedPixList[ 5] = QPixmap(".//Resource//FileWidget//btnPatientCaseDelete_Pressed.png");
	this->btnPressedPixList[ 6] = QPixmap(".//Resource//FileWidget//btnRawDataFromPACS_Pressed.png");
	this->btnPressedPixList[ 7] = QPixmap(".//Resource//FileWidget//btnRawDataFromLocal_Pressed.png");
	this->btnPressedPixList[ 8] = QPixmap(".//Resource//FileWidget//btnRawDataFilter_Pressed.png");
	this->btnPressedPixList[ 9] = QPixmap(".//Resource//FileWidget//btnRawDataHelp_Pressed.png");
	this->btnPressedPixList[10] = QPixmap(".//Resource//FileWidget//btnCasePlanAdd_Pressed.png");
	this->btnPressedPixList[11] = QPixmap(".//Resource//FileWidget//btnImgHorizontalMirror_Pressed.png");
	this->btnPressedPixList[12] = QPixmap(".//Resource//FileWidget//btnImgVerticalMirror_Pressed.png");
	this->btnPressedPixList[13] = QPixmap(".//Resource//FileWidget//btnImgHorizontalTransform_Pressed.png");
	this->btnPressedPixList[14] = QPixmap(".//Resource//FileWidget//btnImgVerticalTransform_Pressed.png");
	this->btnPressedPixList[15] = QPixmap(".//Resource//FileWidget//btnImgRotate_Pressed.png");

	this->dialogWarning = new Warning();
	this->dialogPatientCaseAdd = new PatientCaseAddDialog();
	this->dialogPatientCaseEdit = new PatientCaseEditDialog();

	for (int i = 0; i < 16; i++) {
		this->btnList[i]->setStyleSheet("QToolButton{border:Opx}");
		this->btnList[i]->setIconSize(QSize(this->btnList[i]->width(), this->btnList[i]->height()));
		this->btnList[i]->setIcon(QIcon(this->btnNormalPixList[i]));

		CONNECT(this->btnList[i], PRESSED, this, OnBtnPressed());
		CONNECT(this->btnList[i], RELEASED, this, OnBtnReleased());
	}

	CONNECT(this->ui.btnPatientCaseAdd, CLICKED, this->dialogPatientCaseAdd, SHOW);
	CONNECT(this->ui.btnPatientCaseEdit, CLICKED, this, PatientCaseEdit());
	
	CONNECT(this->ui.btnRawDataFromLocal, CLICKED, this, AddFolder());
	CONNECT(this->ui.tableWidgetRawData, ITEMCLICKED, this, ChangeFileImg(QTableWidgetItem*));

	CONNECT(this->ui.btnImgHorizontalMirror, CLICKED, this->ui.graphicsViewImg, ImgHorizontalMirror());
	CONNECT(this->ui.btnImgVerticalMirror, CLICKED, this->ui.graphicsViewImg, ImgVerticalMirror());
	CONNECT(this->ui.btnImgRotateAntiClockWise, CLICKED, this->ui.graphicsViewImg, ImgRotateAntiClockWise());
	CONNECT(this->ui.btnImgRotateClockWise, CLICKED, this->ui.graphicsViewImg, ImgRotateClockWise());
	CONNECT(this->ui.btnImgResetImg, CLICKED, this->ui.graphicsViewImg, ImgReset());

	CONNECT(this->ui.btnNextStep, CLICKED, this, Render());
}

FileWidget::~FileWidget() {
	this->renderObj = Q_NULLPTR;
	this->imageFilter = Q_NULLPTR;
	this->sql = Q_NULLPTR;

	this->imageFilterMap->swap(QMap<QString, ImageFilterContorller*>());
	this->imageFilterMap = Q_NULLPTR;
}

void FileWidget::OnBtnPressed() {
	for (int i = 0; i < 16; i++) {
		if ((QToolButton*)this->sender() == this->btnList[i]) {
			this->btnList[i]->setStyleSheet("QToolButton{border:Opx}");
			this->btnList[i]->setIcon(QIcon(this->btnPressedPixList[i]));
			break;
		}
	}
}

void FileWidget::OnBtnReleased() {
	for (int i = 0; i < 16; i++) {
		if ((QToolButton*)this->sender() == this->btnList[i]) {
			this->btnList[i]->setStyleSheet("QToolButton{border:Opx}");
			this->btnList[i]->setIcon(QIcon(this->btnNormalPixList[i]));
			break;
		}
	}
}

void FileWidget::AddFolder() {
	QString path = QFileDialog::getExistingDirectory(this, QStringLiteral("Open Directory"), ".", SHOWDIRSONLY);
	if (path.isEmpty()) return;
	QByteArray pathByteArray = path.toLocal8Bit();
	char* pathChar = pathByteArray.data();

	ImageFilterContorller* tempImageFilter = new ImageFilterContorller();
	tempImageFilter->SetPath(std::move(pathChar));
	NTSTATUS status = tempImageFilter->ReadImage(3);
	if (!(status == SUCCESSED)) return;
	QString description = tempImageFilter->GetDisplayName().c_str();
	if (description.isEmpty()) {
		return;
	} else {
		if (!this->imageFilterMap->contains(description)) {
			this->imageFilterMap->insert(description, tempImageFilter);
			this->imageFilter->operator=(*tempImageFilter);
		} else {
			return;
		}
	}

	this->sql->AddDate(path, description);

	if (this->ui.tableWidgetRawData->findItems(description, Qt::MatchCaseSensitive).length()) return;

	int rowIndex = this->ui.tableWidgetRawData->rowCount();
	this->ui.tableWidgetRawData->setRowCount(rowIndex + 1);
	QTableWidgetItem *item = new QTableWidgetItem(description);
	this->ui.tableWidgetRawData->setItem(rowIndex, 0, item);

	this->ui.graphicsViewImg->LoadFileImg(item);
	
	this->ui.btnNextStep->setEnabled(true);
}

void FileWidget::SetRenderObj(VolumeRenderController* renderObj) {
	this->renderObj = renderObj;
	this->ui.graphicsViewImg->SetRenderObj(renderObj);
}

void FileWidget::SetImageFilter(ImageFilterContorller* imageFilter) {
	this->imageFilter = imageFilter;
	this->ui.graphicsViewImg->SetImageFilter(imageFilter);
}

void FileWidget::SetDicomInfoSQL(DicomInfoTable* sql) {
	this->sql = sql;
	this->ui.graphicsViewImg->SetDicomInfoSQL(sql);
}

void FileWidget::Render() {
	if (this->ui.tableWidgetRawData->rowCount() <= 0) return;
	int row = this->ui.tableWidgetRawData->currentRow();
	if (row <= 0) row = 0;
	QString description = this->ui.tableWidgetRawData->item(row, 0)->text();
	if (description.isEmpty()) return;
	this->RenderSign(description);
}

void FileWidget::PatientCaseEdit() {
	if (this->ui.tableWidgetPatientCase->currentRow() < 0) {
		this->dialogWarning->show();
	} else {
		this->dialogPatientCaseEdit->show();
	}
}

void FileWidget::ChangeFileImg(QTableWidgetItem* item) {
	if (this->imageFilterMap->contains(item->text())) {
		this->imageFilter->operator=(*this->imageFilterMap->value(item->text()));
		this->ui.graphicsViewImg->LoadFileImg(item);
	}
}
