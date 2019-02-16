#pragma once

#include <QVTKWidget.h>

#include "CommonLayer.h"


class VTKShow3DWidget : public QVTKWidget {
	Q_OBJECT

signals:
	void ChangeWidget3D();

public:
	explicit VTKShow3DWidget(QWidget *parent = 0);
	~VTKShow3DWidget();

	void LoadDate();
	void SetRenderObj(VolumeRenderController*);
	void Show3DPlane(P3DT);

protected:
	void mouseDoubleClickEvent(QMouseEvent*) Q_DECL_OVERRIDE;

private slots:

private:
	VolumeRenderController* renderObj;
};