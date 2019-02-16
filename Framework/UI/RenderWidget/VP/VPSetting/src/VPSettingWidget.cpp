#include "..\include\VPSettingWidget.h"


VPSettingWidget::VPSettingWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->scalarOpacityMappingGraphicsView = new ScalarOpacityMappingGraphicsView(this->ui.widgetScalarColorMapping);
	this->ui.gridLayout_5->addWidget(this->scalarOpacityMappingGraphicsView, 0, 0, 1, 1);

	this->scalarColorMappingGraphicsView = new ScalarColorMappingGraphicsView(this->ui.widgetScalarColorMapping);
	this->ui.gridLayout_6->addWidget(this->scalarColorMappingGraphicsView, 0, 0, 1, 1);

	this->gradientOpacityGraphicsView = new GradientOpacityGraphicsView(this->ui.widgetGradientOpacity);
	this->ui.gridLayout_7->addWidget(this->gradientOpacityGraphicsView, 0, 0, 1, 1);

	this->selectColorDialog = new QColorDialog();
	this->selectColorDialog->hide();

	this->ui.tbtnlabelScalarColorMappingColorSelectionShow->setMinimumWidth(this->ui.tbtnlabelScalarColorMappingColorSelectionShow->height());
	this->ui.tbtnlabelScalarColorMappingColorSelectionShow->setMaximumWidth(this->ui.tbtnlabelScalarColorMappingColorSelectionShow->height());

	CONNECT(this->ui.comboBoxPreset, CURRENTINDEXCHANGED, this, ChangeRresetVPSetting(int));
	CONNECT(this->ui.horizontalSliderShift, VALUECHANGEDINT, this, ChangeRresetVPShift(int));

	CONNECT(this->ui.spinBoxScalarOpacityMappingPoint, VALUECHANGEDINT, this, ChangeScalarOpacityMappingPoint(int));
	CONNECT(this->ui.doubleSpinBoxScalarOpacityMappingX, VALUECHANGEDDOUBLE, this, ChangeScalarOpacityMappingX(double));
	CONNECT(this->ui.doubleSpinBoxScalarOpacityMappingY, VALUECHANGEDDOUBLE, this, ChangeScalarOpacityMappingY(double));

	CONNECT(this->scalarOpacityMappingGraphicsView, CurrentPoint(int), this->ui.spinBoxScalarOpacityMappingPoint, setValue(int));
	CONNECT(this->scalarOpacityMappingGraphicsView, PointMapSize(int), this, SpinBoxScalarOpacityMappingPointSetMaximum(int));
	CONNECT(this->scalarOpacityMappingGraphicsView, CurrentPointPosX(qreal), this, SetDoubleSpinBoxScalarOpacityMappingXValue(qreal));
	CONNECT(this->scalarOpacityMappingGraphicsView, CurrentPointPosY(qreal), this, SetDoubleSpinBoxScalarOpacityMappingYValue(qreal));

	CONNECT(this->scalarOpacityMappingGraphicsView, AddPoint(int), this, ScalarOpacityMappingGraphicsViewAddPoint(int));
	CONNECT(this->scalarOpacityMappingGraphicsView, DeletePoint(int), this, ScalarOpacityMappingGraphicsViewDeletePoint(int));
	CONNECT(this->scalarOpacityMappingGraphicsView, UpdatePoint(int), this, ScalarOpacityMappingGraphicsViewUpdatePoint(int));

	CONNECT(this->ui.spinBoxScalarColorMappingPoint, VALUECHANGEDINT, this, ChangeScalarColorMappingPoint(int));
	CONNECT(this->ui.doubleSpinBoxScalarColorMappingX, VALUECHANGEDDOUBLE, this, ChangeScalarColorMappingX(double));
	CONNECT(this->ui.tbtnlabelScalarColorMappingColorSelectionShow, CLICKED, this, SelectColor());
	CONNECT(this->selectColorDialog, COLORSELECTED, this, ResetColor(QColor));

	CONNECT(this->scalarColorMappingGraphicsView, CurrentPoint(int), this->ui.spinBoxScalarColorMappingPoint, setValue(int));
	CONNECT(this->scalarColorMappingGraphicsView, PointMapSize(int), this, SpinBoxScalarColorMappingPointSetMaximum(int));
	CONNECT(this->scalarColorMappingGraphicsView, CurrentPointPos(qreal), this, SetDoubleSpinBoxScalarColorMappingXValue(qreal));

	CONNECT(this->scalarColorMappingGraphicsView, AddPoint(int), this, ScalarColorMappingGraphicsViewAddPoint(int));
	CONNECT(this->scalarColorMappingGraphicsView, DeletePoint(int), this, ScalarColorMappingGraphicsViewDeletePoint(int));
	CONNECT(this->scalarColorMappingGraphicsView, UpdatePoint(int), this, ScalarColorMappingGraphicsViewUpdatePoint(int));

	CONNECT(this->ui.spinBoxGradientOpacityPoint, VALUECHANGEDINT, this, ChangeGradientOpacityPoint(int));
	CONNECT(this->ui.doubleSpinBoxGradientOpacityX, VALUECHANGEDDOUBLE, this, ChangeGradientOpacityX(double));
	CONNECT(this->ui.doubleSpinBoxGradientOpacityY, VALUECHANGEDDOUBLE, this, ChangeGradientOpacityY(double));

	CONNECT(this->gradientOpacityGraphicsView, CurrentPoint(int), this->ui.spinBoxGradientOpacityPoint, setValue(int));
	CONNECT(this->gradientOpacityGraphicsView, PointMapSize(int), this, SpinBoxGradientOpacityPointSetMaximum(int));
	CONNECT(this->gradientOpacityGraphicsView, CurrentPointPosX(qreal), this, SetDoubleSpinBoxGradientOpacityMappingXValue(qreal));
	CONNECT(this->gradientOpacityGraphicsView, CurrentPointPosY(qreal), this, SetDoubleSpinBoxGradientOpacityMappingYValue(qreal));

	CONNECT(this->gradientOpacityGraphicsView, AddPoint(int), this, GradientOpacityGraphicsViewAddPoint(int));
	CONNECT(this->gradientOpacityGraphicsView, DeletePoint(int), this, GradientOpacityGraphicsViewDeletePoint(int));
	CONNECT(this->gradientOpacityGraphicsView, UpdatePoint(int), this, GradientOpacityGraphicsViewUpdatePoint(int));

	CONNECT(this->ui.comboBoxInterpolation, CURRENTINDEXCHANGED, this, ChangeInterpolation(int));

	CONNECT(this->ui.horizontalSliderAmbient, VALUECHANGEDINT, this, SetDoubleSpinBox(int));
	CONNECT(this->ui.horizontalSliderDiffuse, VALUECHANGEDINT, this, SetDoubleSpinBox(int));
	CONNECT(this->ui.horizontalSliderSpecular, VALUECHANGEDINT, this, SetDoubleSpinBox(int));
	CONNECT(this->ui.horizontalSliderPower, VALUECHANGEDINT, this, SetDoubleSpinBox(int));

	CONNECT(this->ui.doubleSpinBoxAmbient, VALUECHANGEDDOUBLE, this, SetSlider(double));
	CONNECT(this->ui.doubleSpinBoxDiffuse, VALUECHANGEDDOUBLE, this, SetSlider(double));
	CONNECT(this->ui.doubleSpinBoxSpecular, VALUECHANGEDDOUBLE, this, SetSlider(double));
	CONNECT(this->ui.doubleSpinBoxPower, VALUECHANGEDDOUBLE, this, SetSlider(double));

	CONNECT(this->scalarColorMappingGraphicsView, ColorChanged(), this->scalarOpacityMappingGraphicsView, UpdateInfoColor());

	this->scalarOpacityMappingGraphicsView->setColorMap(this->scalarColorMappingGraphicsView);

	this->vp = new VPInfo();

	this->isUsrConfig = true;
}

VPSettingWidget::~VPSettingWidget() {
	delete this->selectColorDialog;
	this->selectColorDialog = Q_NULLPTR;
	this->renderObj = Q_NULLPTR;

	this->FreeVPInfo();

	delete this->vp;
	this->vp = Q_NULLPTR;
}

void VPSettingWidget::SetRenderObj(VolumeRenderController* renderObj) {
	this->renderObj = renderObj;
}

void VPSettingWidget::GetVPInfo() {
	this->FreeVPInfo();

	uint size = 0;

	this->vp->ScalarOpacity = this->renderObj->GetScalarOpacity(size);
	this->vp->ScalarOpacitySize = size;

	this->vp->Map2Color = this->renderObj->GetMap2Color(size);
	this->vp->Map2ColorSize = size;

	this->vp->GrantyOpacity = this->renderObj->GetGradientOpacity(size);
	this->vp->GrantyOpacitySize = size;

	this->vp->MaterialSize = this->renderObj->GetMaterial(&(this->vp->Material));
}

void VPSettingWidget::FreeVPInfo() {
	if (!this->vp) return;

	for (ULONG i = 0; i < this->vp->ScalarOpacitySize; i++) {
		FreeMemory((&(this->vp->ScalarOpacity)[i]));
	}
	FreeMemory(&(this->vp->ScalarOpacity));

	for (uint i = 0; i < this->vp->Map2ColorSize; i++) {
		FreeMemory((&(this->vp->Map2Color)[i]));
	}
	FreeMemory(&(this->vp->Map2Color));

	for (uint i = 0; i < this->vp->GrantyOpacitySize; i++) {
		FreeMemory((&(this->vp->GrantyOpacity)[i]));
	}
	FreeMemory(&(this->vp->GrantyOpacity));

	FreeMemory(&(this->vp->Material));
}

void VPSettingWidget::ResetVP() {
	this->isUsrConfig = false;

	this->scalarColorMappingGraphicsView->DeleteAll();
	this->scalarColorMappingGraphicsView->ResetChart(this->vp->Map2Color, this->vp->Map2ColorSize);

	this->scalarOpacityMappingGraphicsView->DeleteAll();
	this->scalarOpacityMappingGraphicsView->ResetChart(this->vp->ScalarOpacity, this->vp->ScalarOpacitySize);

	this->gradientOpacityGraphicsView->DeleteAll();
	this->gradientOpacityGraphicsView->ResetChart(this->vp->GrantyOpacity, this->vp->GrantyOpacitySize);

	this->ui.horizontalSliderAmbient->setValue((this->vp->Material)[0] * 100);
	this->ui.horizontalSliderDiffuse->setValue((this->vp->Material)[1] * 100);
	this->ui.horizontalSliderSpecular->setValue((this->vp->Material)[2] * 100);
	this->ui.horizontalSliderPower->setValue((this->vp->Material)[3] * 2);

	this->isUsrConfig = true;
}

void VPSettingWidget::ChangeRresetVPSetting(int index) {

	this->renderObj->RemoveAllScalarOpacityPoint();
	this->renderObj->RemoveAllGradientOpacityPoint();
	this->renderObj->RemoveAllColorisePoint();

	switch (index) {
		case  0: { this->renderObj->SetCTAAAVPInfo();                   break; }
		case  1: { this->renderObj->SetCTAAA2VPInfo();                  break; }
		case  2: { this->renderObj->SetCTBoneVPInfo();                  break; }
		case  3: { this->renderObj->SetCTBonesVPInfo();                 break; }
		case  4: { this->renderObj->SetCTCardiacVPInfo();               break; }
		case  5: { this->renderObj->SetCTCardiac2VPInfo();              break; }
		case  6: { this->renderObj->SetCTCardiac3VPInfo();              break; }
		case  7: { this->renderObj->SetCTChestContrastEnhancedVPInfo(); break; }
		case  8: { this->renderObj->SetCTChestVesselsVPInfo();          break; }
		case  9: { this->renderObj->SetCTCoronaryArteriesVPInfo();      break; }
		case 10: { this->renderObj->SetCTCoronaryArteries2VPInfo();     break; }
		case 11: { this->renderObj->SetCTCoronaryArteries3VPInfo();     break; }
		case 12: { this->renderObj->SetCTCroppedVolumeBoneVPInfo();     break; }
		case 13: { this->renderObj->SetCTFatVPInfo();                   break; }
		case 14: { this->renderObj->SetCTLiverVasculatureVPInfo();      break; }
		case 15: { this->renderObj->SetCTLungVPInfo();                  break; }
		case 16: { this->renderObj->SetCTMIPVPInfo();                   break; }
		case 17: { this->renderObj->SetCTMuscleVPInfo();                break; }
		case 18: { this->renderObj->SetCTPulmonaryArteriesVPInfo();     break; }
		case 19: { this->renderObj->SetCTSoftTissueVPInfo();            break; }
		case 20: { this->renderObj->SetMRAngioVPInfo();                 break; }
		case 21: { this->renderObj->SetMRDefaultVPInfo();               break; }
		case 22: { this->renderObj->SetMRMIPVPInfo();                   break; }
		case 23: { this->renderObj->SetMRT2BrainVPInfo();               break; }
		case 24: { this->renderObj->SetDTIFABrainVPInfo();              break; }
	}

	this->GetVPInfo();
	this->ResetVP();
}

void VPSettingWidget::ChangeRresetVPShift(int value) {
	qDebug() << "ChangeRresetVPShift = " << value << endl;
}

void VPSettingWidget::ChangeScalarOpacityMappingPoint(int value) {
	this->scalarOpacityMappingGraphicsView->SetCurrentPoint(value);
}

void VPSettingWidget::ChangeScalarOpacityMappingX(double value) {
	value = (value + qreal(4000.0)) * (this->scalarOpacityMappingGraphicsView->mapToScene(this->scalarOpacityMappingGraphicsView->rect()).boundingRect().width()) / qreal(8000.0) + this->scalarOpacityMappingGraphicsView->mapToScene(this->scalarOpacityMappingGraphicsView->rect()).boundingRect().left();
	if (qAbs(value - this->scalarOpacityMappingGraphicsView->GetCurrentPointPosX()) < 0.01) return;
	this->scalarOpacityMappingGraphicsView->ResetCurrentPointPosX(value);
}

void VPSettingWidget::ChangeScalarOpacityMappingY(double value) {
	if (qAbs(value - this->scalarOpacityMappingGraphicsView->GetCurrentPointPosY()) < 0.01) return;
	this->scalarOpacityMappingGraphicsView->ResetCurrentPointPosY(value); 
}

void VPSettingWidget::ChangeScalarColorMappingPoint(int value) {
	this->scalarColorMappingGraphicsView->SetCurrentPoint(value);
}

void VPSettingWidget::ChangeScalarColorMappingX(double value) {
	value = (value + qreal(4000.0)) * (this->scalarColorMappingGraphicsView->mapToScene(this->scalarColorMappingGraphicsView->rect()).boundingRect().width()) / qreal(8000.0) + this->scalarColorMappingGraphicsView->mapToScene(this->scalarColorMappingGraphicsView->rect()).boundingRect().left();
	if(qAbs(value - this->scalarColorMappingGraphicsView->GetCurrentPointPosX()) < 0.01) return;
	this->scalarColorMappingGraphicsView->ResetCurrentPointPos(value);
}

void VPSettingWidget::ChangeGradientOpacityPoint(int value) {
	this->gradientOpacityGraphicsView->SetCurrentPoint(value);
}

void VPSettingWidget::ChangeGradientOpacityX(double value) {
	value = (value + qreal(4000.0)) * (this->gradientOpacityGraphicsView->mapToScene(this->gradientOpacityGraphicsView->rect()).boundingRect().width()) / qreal(8000.0) + this->gradientOpacityGraphicsView->mapToScene(this->gradientOpacityGraphicsView->rect()).boundingRect().left();
	if (qAbs(value - this->gradientOpacityGraphicsView->GetCurrentPointPosX()) < 0.01) return;
	this->gradientOpacityGraphicsView->ResetCurrentPointPosX(value);
}

void VPSettingWidget::ChangeGradientOpacityY(double value) {
	if (qAbs(value - this->gradientOpacityGraphicsView->GetCurrentPointPosY()) < 0.01) return;
	this->gradientOpacityGraphicsView->ResetCurrentPointPosY(value);
}

void VPSettingWidget::ChangeInterpolation(int index) {
	this->renderObj->UpdateInteractorType((IT)index);
}

void VPSettingWidget::SetDoubleSpinBox(int value) {
	if ((QSlider*)this->sender() == this->ui.horizontalSliderAmbient) {
		if (this->ui.doubleSpinBoxAmbient->value() == (((qreal)value) / 100.0)) return;
		this->ui.doubleSpinBoxAmbient->setValue(((qreal)value) / 100.0);
		this->renderObj->UpdateVolumPropertyAmbient(((qreal)value) / 100.0);
	} else if ((QSlider*)this->sender() == this->ui.horizontalSliderDiffuse) {
		if (this->ui.horizontalSliderDiffuse->value() == (((qreal)value) / 100.0))return;
		this->ui.doubleSpinBoxDiffuse->setValue(((qreal)value) / 100.0);
		this->renderObj->UpdateVolumPropertyDiffuse(((qreal)value) / 100.0);
	} else if ((QSlider*)this->sender() == this->ui.horizontalSliderSpecular) {
		if (this->ui.horizontalSliderSpecular->value() == (((qreal)value) / 100.0)) return;
		this->ui.doubleSpinBoxSpecular->setValue(((qreal)value) / 100.0);
		this->renderObj->UpdateVolumPropertySpecular(((qreal)value) / 100.0);
	} else if ((QSlider*)this->sender() == this->ui.horizontalSliderPower) {
		if (this->ui.horizontalSliderPower->value() == (((qreal)value) / 100.0)) return;
		this->ui.doubleSpinBoxPower->setValue(((qreal)value) / 2.0);
		this->renderObj->UpdateVolumPropertyPower(((qreal)value) / 2.0);
	}
}

void VPSettingWidget::SetSlider(double value) {
	if ((QDoubleSpinBox*)this->sender() == this->ui.doubleSpinBoxAmbient) {
		if (this->ui.horizontalSliderAmbient->value() == ((int)(value * 100))) return;
		this->ui.horizontalSliderAmbient->setValue((int)(value * 100));
		this->renderObj->UpdateVolumPropertyAmbient(value);
	} else if ((QDoubleSpinBox*)this->sender() == this->ui.doubleSpinBoxDiffuse) {
		if (this->ui.horizontalSliderDiffuse->value() == ((int)(value * 100))) return;
		this->ui.horizontalSliderDiffuse->setValue((int)(value * 100));
		this->renderObj->UpdateVolumPropertyDiffuse(value);
	} else if ((QDoubleSpinBox*)this->sender() == this->ui.doubleSpinBoxSpecular) {
		if (this->ui.horizontalSliderSpecular->value() == ((int)(value * 100))) return;
		this->ui.horizontalSliderSpecular->setValue((int)(value * 100));
		this->renderObj->UpdateVolumPropertySpecular(value);
	} else if ((QDoubleSpinBox*)this->sender() == this->ui.doubleSpinBoxPower) {
		if (this->ui.horizontalSliderPower->value() == ((int)(value * 2))) return;
		this->ui.horizontalSliderPower->setValue((int)(value * 2));
		this->renderObj->UpdateVolumPropertyPower(value);
	}
}

void VPSettingWidget::SelectColor() {
	this->selectColorDialog->setCurrentColor(this->ui.tbtnlabelScalarColorMappingColorSelectionShow->palette().color(QPalette::Background));
	this->selectColorDialog->show();
}

void VPSettingWidget::ResetColor(QColor color) {
	QString sty = QString("QToolButton{background-color:rgb(")+ QString::number(color.red()) + "," + QString::number(color.green()) + "," + QString::number(color.blue()) + ");}";
	this->ui.tbtnlabelScalarColorMappingColorSelectionShow->setStyleSheet(sty);
	this->scalarColorMappingGraphicsView->SetCurrentColor(color);
}

void VPSettingWidget::SpinBoxScalarColorMappingPointSetMaximum(int value) {
	this->ui.spinBoxScalarColorMappingPoint->setMaximum(value);
}

void VPSettingWidget::SetDoubleSpinBoxScalarColorMappingXValue(qreal xPos) {
	QRectF rect = this->scalarColorMappingGraphicsView->mapToScene(this->scalarColorMappingGraphicsView->rect()).boundingRect();
	xPos = (xPos - rect.left()) / (rect.right() - rect.left()) * 8000.0 - 4000.0;
	if (qAbs(xPos - this->ui.doubleSpinBoxScalarColorMappingX->value()) < 0.01) return;
	this->ui.doubleSpinBoxScalarColorMappingX->setValue(xPos);
}

void VPSettingWidget::SpinBoxScalarOpacityMappingPointSetMaximum(int value) {
	this->ui.spinBoxScalarOpacityMappingPoint->setMaximum(value);
}

void VPSettingWidget::SetDoubleSpinBoxScalarOpacityMappingXValue(qreal xPos) {
	QRectF rect = this->scalarOpacityMappingGraphicsView->mapToScene(this->scalarOpacityMappingGraphicsView->rect()).boundingRect();
	xPos = (xPos - rect.left()) / (rect.right() - rect.left()) * 8000.0 - 4000.0;
	if (qAbs(xPos - this->ui.doubleSpinBoxScalarOpacityMappingX->value()) < 0.01) return;
	this->ui.doubleSpinBoxScalarOpacityMappingX->setValue(xPos); 
}

void VPSettingWidget::SetDoubleSpinBoxScalarOpacityMappingYValue(qreal yPos) {
	if (qAbs(yPos - this->ui.doubleSpinBoxScalarOpacityMappingY->value()) < 0.01) return;
	this->ui.doubleSpinBoxScalarOpacityMappingY->setValue(yPos);
}

void VPSettingWidget::SpinBoxGradientOpacityPointSetMaximum(int value) {
	this->ui.spinBoxGradientOpacityPoint->setMaximum(value);
}

void VPSettingWidget::SetDoubleSpinBoxGradientOpacityMappingXValue(qreal xPos) {
	QRectF rect = this->gradientOpacityGraphicsView->mapToScene(this->gradientOpacityGraphicsView->rect()).boundingRect();
	xPos = (xPos - rect.left()) / (rect.right() - rect.left()) * 8000.0 - 4000.0;
	if (qAbs(xPos - this->ui.doubleSpinBoxGradientOpacityX->value()) < 0.01) return;
	this->ui.doubleSpinBoxGradientOpacityX->setValue(xPos);
}

void VPSettingWidget::SetDoubleSpinBoxGradientOpacityMappingYValue(qreal yPos) {
	if (qAbs(yPos - this->ui.doubleSpinBoxGradientOpacityY->value()) < 0.01) return;
	this->ui.doubleSpinBoxGradientOpacityY->setValue(yPos);
}

void VPSettingWidget::ScalarOpacityMappingGraphicsViewAddPoint(int index) {
	if (!this->isUsrConfig) return;

	QVector<QGraphicsEllipseItem*>* list = this->scalarOpacityMappingGraphicsView->GetPointList();
	QMap<QGraphicsEllipseItem*, QColor>* map = this->scalarOpacityMappingGraphicsView->GetColorInfoMap();

	if (list->isEmpty() || map->isEmpty()) return;

	QRectF rect = this->scalarOpacityMappingGraphicsView->mapToScene(this->scalarOpacityMappingGraphicsView->rect()).boundingRect();

	double info[2] = { 0 };
	info[0] = (list->value(index)->rect().center().x() - rect.left()) / (rect.right() - rect.left()) * 8000.0 - 4000.0;
	info[1] = map->value(list->value(index)).alphaF();

	this->renderObj->AddScalarOpacity(info);
}

void VPSettingWidget::ScalarOpacityMappingGraphicsViewDeletePoint(int index) {
	if (!this->isUsrConfig) return;

	QVector<QGraphicsEllipseItem*>* list = this->scalarOpacityMappingGraphicsView->GetPointList();

	if (list->isEmpty()) return;

	QRectF rect = this->scalarOpacityMappingGraphicsView->mapToScene(this->scalarOpacityMappingGraphicsView->rect()).boundingRect();

	this->renderObj->RemoveOneScalarOpacityPoint((list->value(index)->rect().center().x() - rect.left()) / (rect.right() - rect.left()) * 8000.0 - 4000.0);
}

void VPSettingWidget::ScalarOpacityMappingGraphicsViewUpdatePoint(int index) {
	if (!this->isUsrConfig) return;

	QVector<QGraphicsEllipseItem*>* list = this->scalarOpacityMappingGraphicsView->GetPointList();
	QMap<QGraphicsEllipseItem*, QColor>* map = this->scalarOpacityMappingGraphicsView->GetColorInfoMap();

	if (list->isEmpty() || map->isEmpty()) return;

	QRectF rect = this->scalarOpacityMappingGraphicsView->mapToScene(this->scalarOpacityMappingGraphicsView->rect()).boundingRect();

	double info[2] = { 0 };
	info[0] = (list->value(index)->rect().center().x() - rect.left()) / (rect.right() - rect.left()) * 8000.0 - 4000.0;
	info[1] = map->value(list->value(index)).alphaF();

	this->renderObj->UpdateOneScalarOpacity(info[0], info);
}

void VPSettingWidget::ScalarColorMappingGraphicsViewAddPoint(int index) {
	if (!this->isUsrConfig) return;

	QVector<QGraphicsEllipseItem*>* list = this->scalarColorMappingGraphicsView->GetPointList();
	QMap<QGraphicsEllipseItem*, QColor>* map = this->scalarColorMappingGraphicsView->GetColorInfoMap();

	if (list->isEmpty() || map->isEmpty()) return;

	QRectF rect = this->scalarColorMappingGraphicsView->mapToScene(this->scalarColorMappingGraphicsView->rect()).boundingRect();

	double info[4] = { 0 };
	info[0] = (list->value(index)->rect().center().x() - rect.left()) / (rect.right() - rect.left()) * 8000.0 - 4000.0;
	info[1] = map->value(list->value(index)).redF();
	info[2] = map->value(list->value(index)).greenF();
	info[3] = map->value(list->value(index)).blueF();

	this->renderObj->AddVolumColor(info);
}

void VPSettingWidget::ScalarColorMappingGraphicsViewDeletePoint(int index) {
	if (!this->isUsrConfig) return;

	QVector<QGraphicsEllipseItem*>* list = this->scalarColorMappingGraphicsView->GetPointList();

	if (list->isEmpty()) return;

	QRectF rect = this->scalarColorMappingGraphicsView->mapToScene(this->scalarColorMappingGraphicsView->rect()).boundingRect();

	this->renderObj->RemoveOneColorPoint((list->value(index)->rect().center().x() - rect.left()) / (rect.right() - rect.left()) * 8000.0 - 4000.0);
}

void VPSettingWidget::ScalarColorMappingGraphicsViewUpdatePoint(int index) {
	if (!this->isUsrConfig) return;

	QVector<QGraphicsEllipseItem*>* list = this->scalarColorMappingGraphicsView->GetPointList();
	QMap<QGraphicsEllipseItem*, QColor>* map = this->scalarColorMappingGraphicsView->GetColorInfoMap();

	if (list->isEmpty() || map->isEmpty()) return;

	QRectF rect = this->scalarColorMappingGraphicsView->mapToScene(this->scalarColorMappingGraphicsView->rect()).boundingRect();

	double info[4] = { 0 };
	info[0] = (list->value(index)->rect().center().x() - rect.left()) / (rect.right() - rect.left()) * 8000.0 - 4000.0;
	info[1] = map->value(list->value(index)).redF();
	info[2] = map->value(list->value(index)).greenF();
	info[3] = map->value(list->value(index)).blueF();

	this->renderObj->UpdateOneVolumColor(info[0], info);
}

void VPSettingWidget::GradientOpacityGraphicsViewAddPoint(int index) {
	if (!this->isUsrConfig) return;

	QVector<QGraphicsEllipseItem*>* list = this->gradientOpacityGraphicsView->GetPointList();
	QMap<QGraphicsEllipseItem*, QColor>* map = this->gradientOpacityGraphicsView->GetColorInfoMap();

	if (list->isEmpty() || map->isEmpty()) return;

	QRectF rect = this->gradientOpacityGraphicsView->mapToScene(this->gradientOpacityGraphicsView->rect()).boundingRect();

	double info[2] = { 0 };
	info[0] = (list->value(index)->rect().center().x() - rect.left()) / (rect.right() - rect.left()) * 8000.0 - 4000.0;
	info[1] = map->value(list->value(index)).alphaF();

	this->renderObj->AddGradientOpacity(info);
}

void VPSettingWidget::GradientOpacityGraphicsViewDeletePoint(int index) {
	if (!this->isUsrConfig) return;

	QVector<QGraphicsEllipseItem*>* list = this->gradientOpacityGraphicsView->GetPointList();
	QMap<QGraphicsEllipseItem*, QColor>* map = this->gradientOpacityGraphicsView->GetColorInfoMap();

	if (list->isEmpty() || map->isEmpty()) return;

	QRectF rect = this->gradientOpacityGraphicsView->mapToScene(this->gradientOpacityGraphicsView->rect()).boundingRect();

	this->renderObj->RemoveOneGradientOpacityPoint((list->value(index)->rect().center().x() - rect.left()) / (rect.right() - rect.left()) * 8000.0 - 4000.0);
}

void VPSettingWidget::GradientOpacityGraphicsViewUpdatePoint(int index) {
	if (!this->isUsrConfig) return;

	QVector<QGraphicsEllipseItem*>* list = this->gradientOpacityGraphicsView->GetPointList();
	QMap<QGraphicsEllipseItem*, QColor>* map = this->gradientOpacityGraphicsView->GetColorInfoMap();

	if (list->isEmpty() || map->isEmpty()) return;

	QRectF rect = this->gradientOpacityGraphicsView->mapToScene(this->gradientOpacityGraphicsView->rect()).boundingRect();

	double info[2] = { 0 };
	info[0] = (list->value(index)->rect().center().x() - rect.left()) / (rect.right() - rect.left()) * 8000.0 - 4000.0;
	info[1] = map->value(list->value(index)).alphaF();

	this->renderObj->UpdateOneGradientOpacity(info[0], info);
}
