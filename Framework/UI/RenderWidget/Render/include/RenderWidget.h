#pragma once

#include <QtWidgets/QMainWindow>
#include <QMouseEvent>
#include <QToolButton>
#include <QPixmap>
#include <QLabel>
#include <QIcon>
#include <QSlider>
#include <QThread>
#include <QDebug>
#include "VTKGraphicsView.h"
#include "VTKShow3DWidget.h"
#include "..\UI\RenderWidget\Info\include\PathTableWidget.h"
#include "PathMgr.h"
#include "ui_RenderWidget.h"

#include "CommonLayer.h"

#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define REVERSE(a) a =!a
#define CLICKED clicked()
#define TRIGGERED triggered()
#define CHANGED valueChanged(int)

class RenderWidget : public QWidget {
	Q_OBJECT

public:
	RenderWidget(QWidget *parent = Q_NULLPTR);
	~RenderWidget();
	void SetRenderObj(VolumeRenderController*);
	void SetImageFilter(ImageFilterContorller*);
	void SetRoutePlan(RoutePlanning*);
	void Render();

protected:
	void resizeEvent(QResizeEvent*);

private slots:
	void Show3DPlane();
	void ShowSlider();
	void ChangeWidget();
	void ChangeWidget3D();
	void ColorChange();
	void ResliceV(qreal);
	void ResliceH(qreal);
	void Reslice(qreal);
	void LoadConcerInfo();
	void LoadLabOrientation();
	void LoadLabOrientation(int);
	void LoadBtnSwitchLayer();
	void HideAllLabAndBtn();
	void ChangeTransparency(int);
	void UpdatePointInfo(int, double, double, double);
	void DeletePoint();

private:
	Ui::RenderWidget ui;
	bool isMax;
	bool isShowSlider;
	P3DT isShowPlane;
	QToolButton* btnSwitchLayer;
	QToolButton* btnSwitchSlider;
	QSlider* slider;
	QLabel* labOrientation[3];
	QLabel* cornerInfo[3];
	QLabel* pointInfo[3];
	VTKGraphicsView* graphicsView[3];
	VolumeRenderController* renderObj;
	ImageFilterContorller* imageFilter;
	RoutePlanning* routePlan;
	PathMgr* pathMgr;
};