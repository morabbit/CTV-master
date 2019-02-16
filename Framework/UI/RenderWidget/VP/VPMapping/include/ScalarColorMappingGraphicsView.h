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

#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define LEF event->buttons() == Qt::LeftButton
#define MID event->buttons() == Qt::MidButton
#define RIG event->buttons() == Qt::RightButton

class ScalarColorMappingGraphicsView : public QGraphicsView {
	Q_OBJECT

signals:
	void PointMapSize(int);
	void CurrentPoint(int);
	void CurrentPointPos(qreal);
	void ColorChanged();
	void AddPoint(int);
	void DeletePoint(int);
	void UpdatePoint(int);

public:
	explicit ScalarColorMappingGraphicsView(QWidget *parent = 0);
	~ScalarColorMappingGraphicsView();
	void AddPoint(QPoint);
	void UpdateCurrentPoint(QPoint);
	void ResetCurrentPointPos(qreal);
	void AddLineFirst(QPoint);
	void AddLineLast(QPoint);
	void SplitLine(QPoint, QVector<QGraphicsLineItem*>::iterator, int);
	void UpdateLine();
	void DeleteCurrentPoint();
	void DeleteLine(int);
	void DeleteAll();
	void CreateInfo();
	void AddInfoFirst();
	void AddInfoEnd();
	void SplitInfo(int);
	void UpdateInfoColor(int);
	void UpdateInfoPos();
	void DeleteInfo(int);
	void SetCurrentColor(QColor);
	void SetCurrentPoint(int);
	qreal GetCurrentPointPosX();
	QVector<QGraphicsEllipseItem*>* GetPointList();
	QMap<QGraphicsEllipseItem*, QColor>* GetColorInfoMap();
	void ResetChart(double**, ulong);

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
	QColor* currentColor;
	
	QVector<QGraphicsEllipseItem*>* pointMap;
	QVector<QGraphicsLineItem*>* lineMap;
	QVector<QGraphicsPolygonItem*>* infoMap;

	QMap<QGraphicsEllipseItem*, QColor>* pointColorMap;
};