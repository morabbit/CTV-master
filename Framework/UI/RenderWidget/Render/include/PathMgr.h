#pragma once

#include <QDebug>
#include <QObject>
#include <QColor>
#include <QPoint>
#include <QLine>
#include <QMap>
#include <QtCore/qmath.h>

#include "..\UI\RenderWidget\Info\include\PathTableWidget.h"
#include "VTKGraphicsView.h"
#include "CommonLayer.h"

#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))

class PathMgr : public QObject {
	Q_OBJECT

signals:
	void UpdatePointInfo(int, double, double, double);
	void DeletePoint();

public:
	PathMgr();
	~PathMgr();

	void SetRenderObj(VolumeRenderController*);
	void SetImageFilter(ImageFilterContorller*);
	void SetRoutePlan(RoutePlanning*);
	void SetPathTableWidget(PathTableWidget*);
	void SetVTKGraphicsView(VTKGraphicsView* graphicsView[3]);
	qreal GetLastPathSize();
	qreal GetCurrentPathSize(int);
	int GetLastPointID();
	int GetLastPathID();
	int GetCurrentPointID();
	int GetCurrentPathID();
	int GetPointMapSize();
	qreal GetCurrentPointX();
	qreal GetCurrentPointX(int);
	qreal GetCurrentPointY();
	qreal GetCurrentPointY(int);
	qreal GetCurrentPointZ();
	qreal GetCurrentPointZ(int);
	void GetPointPos(int, double&, double&, double&);

public slots:
	void AddPoint();
	void DeletePath();
	void DeleteALLPath();
	void MoveLineToPointPos(int);
	void UpdataPointInfo(int);
	void UpdataPathInfo(int);
	void SetCurrentPath(int);
	void DelCurrentPath();
	void ResetPathColor(int, QColor);

private:
	PathTableWidget* tableWidget;
	VTKGraphicsView* graphicsView[3];

	VolumeRenderController* renderObj;
	ImageFilterContorller* imageFilter;
	RoutePlanning* routePlan;
};