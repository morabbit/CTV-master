#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QLinearGradient>
#include <QPixmap>
#include <QImage>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QRectF> 
#include <QList> 
#include <QMap>

#include "ScalarColorMappingGraphicsView.h"

#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define LEF event->buttons() == Qt::LeftButton
#define MID event->buttons() == Qt::MidButton
#define RIG event->buttons() == Qt::RightButton

class ScalarOpacityMappingGraphicsView : public QGraphicsView {
	Q_OBJECT

signals:
	void PointMapSize(int);
	void CurrentPoint(int);
	void CurrentPointPosX(qreal);
	void CurrentPointPosY(qreal);
	void AddPoint(int);
	void DeletePoint(int);
	void UpdatePoint(int);

public:
	explicit ScalarOpacityMappingGraphicsView(QWidget *parent = 0);
	~ScalarOpacityMappingGraphicsView();
	void setColorMap(ScalarColorMappingGraphicsView*);
	void AddPoint(QPoint);
	void UpdateCurrentPoint(QPoint);
	void ResetCurrentPointPosX(qreal);
	void ResetCurrentPointPosY(qreal);
	void AddLineFirst(QPoint);
	void AddLineLast(QPoint);
	void SplitLine(QPoint, QVector<QGraphicsLineItem*>::iterator, int);
	void UpdateLine();
	void DeleteCurrentPoint();
	void DeleteLine(int);
	void DeleteAll();
	void CreateBackground();
	void CreateInfo();
	void AddInfoFirst();
	void AddInfoEnd();
	void SplitInfo(int);
	void UpdateInfoColor(int);
	void UpdateInfoPos();
	void DeleteInfo(int);
	void SetCurrentPoint(int);
	qreal GetCurrentPointPosX();
	qreal GetCurrentPointPosY();
	QColor GetPointColor(QGraphicsEllipseItem*);
	QVector<QGraphicsEllipseItem*>* GetPointList();
	QMap<QGraphicsEllipseItem*, QColor>* GetColorInfoMap();
	void ResetChart(double**, ulong);

public slots:
	void UpdateInfoColor();

protected:
	void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QMouseEvent*) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent*) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;
	void wheelEvent(QWheelEvent*) Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent*) Q_DECL_OVERRIDE;

private:
	int status;
	enum Model {
		Normel,
		AddNewPoint,
		MoveCurrentPoint,
	};

	QGraphicsScene* pScene;
	QGraphicsEllipseItem* mouse;
	QGraphicsEllipseItem* currentPoint;
	QGraphicsPolygonItem* background;
	
	QVector<QGraphicsEllipseItem*>* pointMap;
	QVector<QGraphicsLineItem*>* lineMap;
	QVector<QGraphicsPolygonItem*>* infoMap;

	QMap<QGraphicsEllipseItem*, QColor>* pointColorMap;

	ScalarColorMappingGraphicsView* scalarColorMappingGraphicsView;
};
