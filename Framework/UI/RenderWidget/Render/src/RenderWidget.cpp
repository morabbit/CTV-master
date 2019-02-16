#include "..\include\RenderWidget.h"

RenderWidget::RenderWidget(QWidget *parent)
	: QWidget(parent) {
	ui.setupUi(this);

	this->isMax = false;
	this->isShowSlider = true;
	this->isShowSlider = true;
	this->isShowPlane = P3DT::Display_Volume;

	QPixmap pixmapSwitchLayer(".//Resource//RenderWidget//btnSwitchLayer_closed.jpg");
	this->btnSwitchLayer = new QToolButton(this);
	this->btnSwitchLayer->setStyleSheet("QToolButton{border:Opx}");
	this->btnSwitchLayer->setStyleSheet("QToolButton{background-color:#000000}");
	this->btnSwitchLayer->setIconSize(QSize(this->btnSwitchLayer->width(), this->btnSwitchLayer->height()));
	this->btnSwitchLayer->setIcon(QIcon(pixmapSwitchLayer));

	QPixmap pixmapSwitchSlider(".//Resource//RenderWidget//btnSwitchSlider_closed.jpg");
	this->btnSwitchSlider = new QToolButton(this);
	this->btnSwitchSlider->setStyleSheet("QToolButton{border:Opx}");
	this->btnSwitchSlider->setStyleSheet("QToolButton{background-color:#000000}");
	this->btnSwitchSlider->setIconSize(QSize(this->btnSwitchSlider->width(), this->btnSwitchSlider->height()));
	this->btnSwitchSlider->setIcon(QIcon(pixmapSwitchSlider));

	this->slider = new QSlider(this);
	this->slider->setOrientation(Qt::Horizontal);
	this->slider->setMinimum(0);
	this->slider->setMaximum(100);
	this->slider->setStyleSheet("QSlider{background-color:rgba(132, 112, 255, 255); border - style: inset; border-radius: 10px;} QSlider::handle:horizontal{background: QRadialGradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 white, stop:1 green); width: 16px; height: 16px; margin: -5px 6px - 5px 6px; border - radius: 11px; border: 3px solid #ffffff;}");

	for (int i = 0; i < 3; i++) {
		QPalette pe;
		pe.setColor(QPalette::WindowText, Qt::white);

		this->labOrientation[i] = new QLabel(this);
		this->labOrientation[i]->setStyleSheet("QLabel{border:Opx}");
		this->labOrientation[i]->setStyleSheet("background:transparent");
		this->labOrientation[i]->setAttribute(Qt::WA_TranslucentBackground);
		this->labOrientation[i]->setAlignment(Qt::AlignCenter);
		this->labOrientation[i]->setScaledContents(true);

		this->cornerInfo[i] = new QLabel(this);
		this->cornerInfo[i]->setPalette(pe);
		this->cornerInfo[i]->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		this->cornerInfo[i]->setStyleSheet("QLabel{border:Opx}");
		this->cornerInfo[i]->setStyleSheet("background:transparent");
		this->cornerInfo[i]->setAttribute(Qt::WA_TranslucentBackground);
		this->cornerInfo[i]->setScaledContents(true);

		this->pointInfo[i]= new QLabel(this);
		this->pointInfo[i]->setPalette(pe);
		this->pointInfo[i]->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		this->pointInfo[i]->setStyleSheet("QLabel{border:Opx}");
		this->pointInfo[i]->setStyleSheet("background:transparent");
		this->pointInfo[i]->setAttribute(Qt::WA_TranslucentBackground);
		this->pointInfo[i]->setScaledContents(true);
	}
	this->labOrientation[0]->setPixmap(QPixmap(".//Resource//RenderWidget//orientation_x.png"));
	this->labOrientation[1]->setPixmap(QPixmap(".//Resource//RenderWidget//orientation_y.png"));
	this->labOrientation[2]->setPixmap(QPixmap(".//Resource//RenderWidget//orientation_z.png"));

	this->LoadConcerInfo();
	
	this->graphicsView[0] = this->ui.graphicsView_x;
	this->graphicsView[1] = this->ui.graphicsView_y;
	this->graphicsView[2] = this->ui.graphicsView_z;

	this->pathMgr = new PathMgr();
	this->pathMgr->SetPathTableWidget(ui.tableWidgetPath);
	this->pathMgr->SetVTKGraphicsView(this->graphicsView);

	for (int i = 0; i < 3; i++) {
		this->graphicsView[i]->SetWinNum(i);
		CONNECT(this->graphicsView[i], ChangeWidget(), this, ChangeWidget());
		CONNECT(this->graphicsView[i], ColorChange(), this, ColorChange());
		CONNECT(this->graphicsView[i], ResliceVLine(qreal), this, ResliceV(qreal));
		CONNECT(this->graphicsView[i], ResliceHLine(qreal), this, ResliceH(qreal));
		CONNECT(this->graphicsView[i], WheelReslice(qreal), this, Reslice(qreal));
	}

	CONNECT(this->ui.vtk3dwidget, ChangeWidget3D(), this, ChangeWidget3D());
	CONNECT(this->ui.btnAdd, CLICKED, this->pathMgr, AddPoint());
	CONNECT(this->ui.btnDelete, CLICKED, this->pathMgr, DeletePath());
	CONNECT(this->ui.btnDeleteALL, CLICKED, this->pathMgr, DeleteALLPath());
	CONNECT(this->btnSwitchLayer, CLICKED, this, Show3DPlane());
	CONNECT(this->btnSwitchSlider, CLICKED, this, ShowSlider());
	CONNECT(this->slider, CHANGED, this, ChangeTransparency(int));
	CONNECT(this->pathMgr, UpdatePointInfo(int, double, double, double), this, UpdatePointInfo(int, double, double, double));
	CONNECT(this->pathMgr, DeletePoint(), this, DeletePoint());
}

RenderWidget::~RenderWidget() {
	delete this->pathMgr;
	this->pathMgr = Q_NULLPTR;
	this->renderObj = Q_NULLPTR;
	this->routePlan = Q_NULLPTR;
	this->imageFilter = Q_NULLPTR;
	for (int i = 0; i < 3; i++){
		this->graphicsView[i] = Q_NULLPTR;
	}
}

void RenderWidget::SetRenderObj(VolumeRenderController* renderObj) {
	this->renderObj = renderObj;
	for (int i = 0; i < 3; i++) {
		this->graphicsView[i]->SetRenderObj(renderObj);
	}
	this->ui.vtk3dwidget->SetRenderObj(renderObj);
	this->ui.tableWidgetInfo->SetRenderObj(renderObj);
	this->ui.vpSettingWidget->SetRenderObj(renderObj);
	this->pathMgr->SetRenderObj(renderObj);
}

void RenderWidget::SetImageFilter(ImageFilterContorller * imageFilter) {
	this->imageFilter = imageFilter;
	for(int i = 0; i < 3; i++) {
		this->graphicsView[i]->SetImageFilter(imageFilter);
	}
	this->ui.tableWidgetInfo->SetImageFilter(imageFilter);
	this->pathMgr->SetImageFilter(imageFilter);
}

void RenderWidget::SetRoutePlan(RoutePlanning* routePlan) {
	this->routePlan = routePlan;
	this->pathMgr->SetRoutePlan(routePlan);
}

void RenderWidget::Render() {
	for (int i = 0; i < 3; i++) {
		this->graphicsView[i]->LoadVTKBuff();
	}
	this->ui.vtk3dwidget->LoadDate();
	this->ui.tableWidgetInfo->LoadTable();
	this->LoadLabOrientation();
	this->LoadBtnSwitchLayer();
	this->slider->hide();
	this->slider->setValue(100);
}

void RenderWidget::resizeEvent(QResizeEvent* event) {
	for (int i = 0; i < 3; i++) {
		this->labOrientation[i]->setGeometry(
			this->graphicsView[i]->pos().x(),
			this->graphicsView[i]->pos().y() + this->graphicsView[i]->height() - this->graphicsView[i]->height() / 5,
			this->graphicsView[i]->height() / 5, 
			this->graphicsView[i]->height() / 5);
		this->cornerInfo[i]->setGeometry(
			this->graphicsView[i]->pos().x(),
			this->graphicsView[i]->pos().y(), 
			this->graphicsView[i]->width() / 6, 
			this->graphicsView[i]->height() / 5);
		this->pointInfo[i]->setGeometry(
			this->graphicsView[i]->pos().x() + this->graphicsView[i]->width() - this->graphicsView[i]->width() / 6,
			this->graphicsView[i]->pos().y(), 
			this->graphicsView[i]->width() / 6, 
			this->graphicsView[i]->height() / 5);
	}
	this->btnSwitchLayer->setGeometry(this->ui.vtk3dwidget->pos().x() + this->ui.vtk3dwidget->width() - this->ui.vtk3dwidget->height() / 10,
		this->ui.vtk3dwidget->pos().y(), this->ui.vtk3dwidget->height() / 10, this->ui.vtk3dwidget->height() / 10);
	this->btnSwitchLayer->setIconSize(QSize(this->ui.vtk3dwidget->height() / 10, this->ui.vtk3dwidget->height() / 10));

	this->btnSwitchSlider->setGeometry(this->ui.vtk3dwidget->pos().x() + this->ui.vtk3dwidget->width() - this->ui.vtk3dwidget->height() / 10,
		this->ui.vtk3dwidget->pos().y() + this->ui.vtk3dwidget->height() - this->ui.vtk3dwidget->height() / 10,
		this->ui.vtk3dwidget->height() / 10, this->ui.vtk3dwidget->height() / 10);
	this->btnSwitchSlider->setIconSize(QSize(this->ui.vtk3dwidget->height() / 10, this->ui.vtk3dwidget->height() / 10));

	this->slider->setGeometry(this->ui.vtk3dwidget->pos().x() + this->ui.vtk3dwidget->width() / 3,
		this->ui.vtk3dwidget->pos().y() + this->ui.vtk3dwidget->height() - this->ui.vtk3dwidget->height() / 20,
		this->ui.vtk3dwidget->width() / 3, this->ui.vtk3dwidget->height() / 30);
}

void RenderWidget::Show3DPlane() {
	if (P3DT::Display_Volume_And_Slice == this->isShowPlane) {
		this->isShowPlane = P3DT::Remove_Slice_Image;
	} else {
		this->isShowPlane = P3DT::Display_Volume_And_Slice;
	}

	if (this->isShowPlane) {
		QPixmap pixmap(".//Resource//RenderWidget//btnSwitchLayer_opened.jpg");
		this->btnSwitchLayer->setIcon(QIcon(pixmap));
	} else {
		QPixmap pixmap(".//Resource//RenderWidget//btnSwitchLayer_closed.jpg");
		this->btnSwitchLayer->setIcon(QIcon(pixmap));
	}
	this->ui.vtk3dwidget->Show3DPlane(this->isShowPlane);
}

void RenderWidget::ShowSlider() {
	if (this->isShowSlider) {
		this->slider->show();
		this->slider->setGeometry(this->ui.vtk3dwidget->pos().x() + this->ui.vtk3dwidget->width() / 3,
			this->ui.vtk3dwidget->pos().y() + this->ui.vtk3dwidget->height() - this->ui.vtk3dwidget->height() / 20,
			this->ui.vtk3dwidget->width() / 3, this->ui.vtk3dwidget->height() / 30);
		QPixmap pixmap(".//Resource//RenderWidget//btnSwitchSlider_opened.png");
		this->btnSwitchSlider->setIcon(QIcon(pixmap));
	} else {
		this->slider->hide();
		QPixmap pixmap(".//Resource//RenderWidget//btnSwitchSlider_closed.png");
		this->btnSwitchSlider->setIcon(QIcon(pixmap));
	}
	REVERSE(this->isShowSlider);
}

void RenderWidget::ChangeWidget() {
	this->HideAllLabAndBtn();
	if (!isMax) {
		this->ui.gridLayout->setRowStretch(0, 0);
		this->ui.gridLayout->setRowStretch(1, 0);
		this->ui.gridLayout->setColumnStretch(0, 0);
		this->ui.gridLayout->setColumnStretch(1, 0);
		for (int i = 0; i < 3; i++) {
			this->graphicsView[i]->hide();
		}
		this->ui.vtk3dwidget->hide();
		((VTKGraphicsView*)this->sender())->show();
		this->LoadLabOrientation(((VTKGraphicsView*)this->sender())->GetWinNum());
	} else {
		this->ui.gridLayout->setRowStretch(0, 1);
		this->ui.gridLayout->setRowStretch(1, 1);
		this->ui.gridLayout->setColumnStretch(0, 1);
		this->ui.gridLayout->setColumnStretch(1, 1);
		for (int i = 0; i < 3; i++) {
			this->graphicsView[i]->show();
		}
		this->ui.vtk3dwidget->show();
		this->LoadLabOrientation();
		this->LoadBtnSwitchLayer();
	}
	REVERSE(this->isMax);
}

void RenderWidget::ChangeWidget3D() {
	this->HideAllLabAndBtn();
	if (!isMax) {
		this->ui.gridLayout->setRowStretch(0, 0);
		this->ui.gridLayout->setRowStretch(1, 0);
		this->ui.gridLayout->setColumnStretch(0, 0);
		this->ui.gridLayout->setColumnStretch(1, 0);
		for (int i = 0; i < 3; i++) {
			this->graphicsView[i]->hide();
		}
		this->ui.vtk3dwidget->hide();
		this->ui.vtk3dwidget->show();
		this->LoadBtnSwitchLayer();
	} else {
		this->ui.gridLayout->setRowStretch(0, 1);
		this->ui.gridLayout->setRowStretch(1, 1);
		this->ui.gridLayout->setColumnStretch(0, 1);
		this->ui.gridLayout->setColumnStretch(1, 1);
		for (int i = 0; i < 3; i++) {
			this->graphicsView[i]->show();
		}
		this->ui.vtk3dwidget->show();
		this->LoadLabOrientation();
		this->LoadBtnSwitchLayer();
	}
	REVERSE(this->isMax);
}

void RenderWidget::ColorChange() {
	for (int i = 0; i < 3; i++) {
		this->graphicsView[i]->Reslice();
	}
}

void RenderWidget::ResliceV(qreal slice) {
	int winNum = ((VTKGraphicsView*)this->sender())->GetWinNum();
	switch (winNum) {
		case 0: {
			this->graphicsView[1]->Reslice(slice);
			this->graphicsView[2]->ResliceH(slice);
			break;
		}
		case 1: {
			this->graphicsView[0]->Reslice(slice);
			this->graphicsView[2]->ResliceV(slice);
			break;
		}
		case 2: {
			this->graphicsView[0]->Reslice(slice);
			this->graphicsView[1]->ResliceV(slice);
			break;
		}
	}
}

void RenderWidget::ResliceH(qreal slice) {
	int winNum = ((VTKGraphicsView*)this->sender())->GetWinNum();
	switch (winNum) {
		case 0: {
			this->graphicsView[2]->Reslice(slice);
			this->graphicsView[1]->ResliceH(slice);
			break;
		}
		case 1: {
			this->graphicsView[2]->Reslice(slice);
			this->graphicsView[0]->ResliceH(slice);
			break;
		}
		case 2: {
			this->graphicsView[1]->Reslice(slice);
			this->graphicsView[0]->ResliceV(slice);
			break;
		}
	}
}

void RenderWidget::Reslice(qreal step) {
	int winNum = ((VTKGraphicsView*)this->sender())->GetWinNum();
	switch (winNum) {
		case 0: {
			step += this->graphicsView[1]->GetSliceV();
			this->graphicsView[1]->ResliceV(step);
			this->graphicsView[2]->ResliceV(step);
			this->graphicsView[0]->Reslice(step);
			break;
		}
		case 1: {
			step += this->graphicsView[2]->GetSliceH();
			this->graphicsView[0]->ResliceV(step);
			this->graphicsView[2]->ResliceH(step);
			this->graphicsView[1]->Reslice(step);
			break;
		}
		case 2: {
			step += this->graphicsView[0]->GetSliceH();
			this->graphicsView[0]->ResliceH(step);
			this->graphicsView[1]->ResliceH(step);
			this->graphicsView[2]->Reslice(step);
			break;
		}
	}
}

void RenderWidget::LoadConcerInfo() {
	//DciomObject* head = this->imageFilter->GetDicomHeader();

	//this->cornerInfo[0]->setText(
	//	QString("Frame: ") + QString::number((int)(this->graphicsView[0]->PixLayer() * head->nz)) + QString("/") + QString::number(head->nz) + QString("\n") +
	//	QString("SeriesDescription: ") + QString(head->seriesDescription.c_str()) + QString("\n") +
	//	QString("ImageNo: ") + QString::number(head->imageNO)
	//);

	//this->cornerInfo[1]->setText(
	//
	//);

	//this->cornerInfo[2]->setText(
	//
	//);

	//for (int i = 0; i < 3; i++) {
	//	this->pointInfo[i]->setText(
	//		QString("PointID: ") + QString::number(pointID) + QString("\n") +
	//		QString("X: ") + QString::number(x) + QString("\n") +
	//		QString("Y: ") + QString::number(y) + QString("\n") +
	//		QString("Z: ") + QString::number(z) + QString("\n"));
	//}
}

void RenderWidget::LoadLabOrientation() {
	for (int i = 0; i < 3; i++) {
		this->labOrientation[i]->setGeometry(
			this->graphicsView[i]->pos().x(), 
			this->graphicsView[i]->pos().y() + this->graphicsView[i]->height() - this->graphicsView[i]->height() / 5,
			this->graphicsView[i]->height() / 5, 
			this->graphicsView[i]->height() / 5);
		this->cornerInfo[i]->setGeometry(
			this->graphicsView[i]->pos().x(),
			this->graphicsView[i]->pos().y(),
			this->graphicsView[i]->width() / 6,
			this->graphicsView[i]->height() / 5);
		this->pointInfo[i]->setGeometry(
			this->graphicsView[i]->pos().x() + this->graphicsView[i]->width() - this->graphicsView[i]->width() / 6,
			this->graphicsView[i]->pos().y(), 
			this->graphicsView[i]->width() / 6, 
			this->graphicsView[i]->height() / 5);
		this->labOrientation[i]->show();
		this->cornerInfo[i]->show();
		this->pointInfo[i]->show();
	}
}

void RenderWidget::LoadLabOrientation(int index) {
	this->labOrientation[index]->setGeometry(
		this->graphicsView[index]->pos().x(),
		this->graphicsView[index]->pos().y() + this->graphicsView[index]->height() - this->graphicsView[index]->height() / 5,
		this->graphicsView[index]->height() / 5, 
		this->graphicsView[index]->height() / 5);
	this->cornerInfo[index]->setGeometry(
		this->graphicsView[index]->pos().x(),
		this->graphicsView[index]->pos().y(),
		this->graphicsView[index]->width() / 6,
		this->graphicsView[index]->height() / 5);
	this->pointInfo[index]->setGeometry(
		this->graphicsView[index]->pos().x() + this->graphicsView[index]->width() - this->graphicsView[index]->width() / 6,
		this->graphicsView[index]->pos().y(),
		this->graphicsView[index]->width() / 6,
		this->graphicsView[index]->height() / 5);
	this->labOrientation[index]->show();
	this->cornerInfo[index]->show();
	this->pointInfo[index]->show();
}

void RenderWidget::LoadBtnSwitchLayer() {
	this->btnSwitchLayer->setGeometry(this->ui.vtk3dwidget->pos().x() + this->ui.vtk3dwidget->width() - this->ui.vtk3dwidget->height() / 10,
		this->ui.vtk3dwidget->pos().y(), this->ui.vtk3dwidget->height() / 10, this->ui.vtk3dwidget->height() / 10);
	this->btnSwitchLayer->setIconSize(QSize(this->ui.vtk3dwidget->height() / 10, this->ui.vtk3dwidget->height() / 10));
	this->btnSwitchLayer->show();

	this->btnSwitchSlider->setGeometry(this->ui.vtk3dwidget->pos().x() + this->ui.vtk3dwidget->width() - this->ui.vtk3dwidget->height() / 10,
		this->ui.vtk3dwidget->pos().y() + this->ui.vtk3dwidget->height() - this->ui.vtk3dwidget->height() / 10,
		this->ui.vtk3dwidget->height() / 10, this->ui.vtk3dwidget->height() / 10);
	this->btnSwitchSlider->setIconSize(QSize(this->ui.vtk3dwidget->height() / 10, this->ui.vtk3dwidget->height() / 10));
	this->btnSwitchSlider->show();

	this->slider->setGeometry(this->ui.vtk3dwidget->pos().x() + this->ui.vtk3dwidget->width() / 3,
		this->ui.vtk3dwidget->pos().y() + this->ui.vtk3dwidget->height() - this->ui.vtk3dwidget->height() / 20,
		this->ui.vtk3dwidget->width() / 3, this->ui.vtk3dwidget->height() / 30);
	if (!this->isShowSlider) {
		this->slider->show();
		this->slider->setGeometry(this->ui.vtk3dwidget->pos().x() + this->ui.vtk3dwidget->width() / 3,
			this->ui.vtk3dwidget->pos().y() + this->ui.vtk3dwidget->height() - this->ui.vtk3dwidget->height() / 20,
			this->ui.vtk3dwidget->width() / 3, this->ui.vtk3dwidget->height() / 30);
		QPixmap pixmap(".//Resource//RenderWidget//btnSwitchSlider_opened.png");
		this->btnSwitchSlider->setIcon(QIcon(pixmap));
	}
	else {
		this->slider->hide();
		QPixmap pixmap(".//Resource//RenderWidget//btnSwitchSlider_closed.png");
		this->btnSwitchSlider->setIcon(QIcon(pixmap));
	}
}

void RenderWidget::HideAllLabAndBtn() {
	for (int i = 0; i < 3; i++) {
		this->labOrientation[i]->hide(); 
		this->cornerInfo[i]->hide();
		this->pointInfo[i]->hide();
	}
	this->btnSwitchLayer->hide();
	this->btnSwitchSlider->hide();
	this->slider->hide();
}

void RenderWidget::ChangeTransparency(int pos) {
	this->renderObj->SetVolumScalarOpacityPercentage(pos);
}

void RenderWidget::UpdatePointInfo(int pointID, double x, double y, double z) {
	for (int i = 0; i < 3; i++) {
		this->pointInfo[i]->setText(
			QString("PointID: ") + QString::number(pointID) + QString("\n") + 
			QString("X: ") + QString::number(x) + QString("\n") +
			QString("Y: ") + QString::number(y) + QString("\n") +
			QString("Z: ") + QString::number(z) + QString("\n"));
	}
}

void RenderWidget::DeletePoint() {
	for (int i = 0; i < 3; i++) {
		this->pointInfo[i]->clear();
	}
}
