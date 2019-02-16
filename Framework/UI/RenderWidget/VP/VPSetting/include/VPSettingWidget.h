#pragma once

#include <QtWidgets/QMainWindow>
#include <QColorDialog>
#include <QColor>
#include <QSlider>
#include <QtGlobal>
#include <QDebug>
#include <string>
#include "ui_VPSettingWidget.h"
#include "..\UI\RenderWidget\VP\VPMapping\include\ScalarColorMappingGraphicsView.h"
#include "..\UI\RenderWidget\VP\VPMapping\include\ScalarOpacityMappingGraphicsView.h"
#include "..\UI\RenderWidget\VP\VPMapping\include\GradientOpacityGraphicsView.h"
#include "CommonLayer.h"

#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define CLICKED clicked()
#define VALUECHANGEDINT valueChanged(int)
#define VALUECHANGEDDOUBLE valueChanged(double)
#define CURRENTINDEXCHANGED currentIndexChanged(int)
#define COLORSELECTED colorSelected(QColor)

class VPSettingWidget : public QWidget
{
	Q_OBJECT

public:
	VPSettingWidget(QWidget *parent = Q_NULLPTR);
	~VPSettingWidget();
	void SetRenderObj(VolumeRenderController*);
	void GetVPInfo();
	void FreeVPInfo();
	void ResetVP();

private slots:
	void ChangeRresetVPSetting(int);
	void ChangeRresetVPShift(int);
	void ChangeScalarOpacityMappingPoint(int);
	void ChangeScalarOpacityMappingX(double);
	void ChangeScalarOpacityMappingY(double);
	void ChangeScalarColorMappingPoint(int);
	void ChangeScalarColorMappingX(double);
	void ChangeGradientOpacityPoint(int);
	void ChangeGradientOpacityX(double);
	void ChangeGradientOpacityY(double);
	void ChangeInterpolation(int);
	void SetDoubleSpinBox(int);
	void SetSlider(double); 
	void SelectColor();
	void ResetColor(QColor);

	void SpinBoxScalarColorMappingPointSetMaximum(int);
	void SetDoubleSpinBoxScalarColorMappingXValue(qreal);

	void SpinBoxScalarOpacityMappingPointSetMaximum(int);
	void SetDoubleSpinBoxScalarOpacityMappingXValue(qreal);
	void SetDoubleSpinBoxScalarOpacityMappingYValue(qreal);

	void SpinBoxGradientOpacityPointSetMaximum(int);
	void SetDoubleSpinBoxGradientOpacityMappingXValue(qreal);
	void SetDoubleSpinBoxGradientOpacityMappingYValue(qreal);

	void ScalarOpacityMappingGraphicsViewAddPoint(int);
	void ScalarOpacityMappingGraphicsViewDeletePoint(int);
	void ScalarOpacityMappingGraphicsViewUpdatePoint(int);

	void ScalarColorMappingGraphicsViewAddPoint(int);
	void ScalarColorMappingGraphicsViewDeletePoint(int);
	void ScalarColorMappingGraphicsViewUpdatePoint(int);

	void GradientOpacityGraphicsViewAddPoint(int);
	void GradientOpacityGraphicsViewDeletePoint(int);
	void GradientOpacityGraphicsViewUpdatePoint(int);

private:
	Ui::VPSettingWidget ui;

	QColorDialog* selectColorDialog;

	VolumeRenderController* renderObj;

	ScalarOpacityMappingGraphicsView* scalarOpacityMappingGraphicsView;
	ScalarColorMappingGraphicsView* scalarColorMappingGraphicsView;
	GradientOpacityGraphicsView* gradientOpacityGraphicsView;

	VPInfo* vp;

	bool isUsrConfig;
};
