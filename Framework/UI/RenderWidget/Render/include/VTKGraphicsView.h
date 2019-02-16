#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QPixmap>
#include <QImage>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF> 
#include <QList> 
#include <QMap> 

#include <vtkImageData.h>
#include <vtkSmartPointer.h>

#include "CommonLayer.h"

#define LEF event->buttons() == Qt::LeftButton
#define MID event->buttons() == Qt::MidButton
#define RIG event->buttons() == Qt::RightButton
#define RGB32 QImage::Format_RGB32 

class VTKGraphicsView : public QGraphicsView {
	Q_OBJECT

signals:
	void ChangeWidget();
	void ColorChange();
	void ResliceVLine(qreal);
	void ResliceHLine(qreal);
	void WheelReslice(qreal);
	void MoveLineToPoint(int);
	void UpdataPoint(int);
	void UpdataPath(int);
	void CurrentPath(int);
	void NoCurrentPath();
	
public:
	explicit VTKGraphicsView(QWidget *parent = 0);
	~VTKGraphicsView();

	void InitPos();
	void LoadVTKBuff();
	void LoadVLine();
	void LoadHLine();
	void UpdataVTKBuff();
	void SetRenderObj(VolumeRenderController*);
	void SetImageFilter(ImageFilterContorller*);
	void SetWinNum(int);
	void Scale(qreal x);
	void Move(QPointF delta);
	void UpdateLine();
	void AdjustImg(QPointF);
	void Reslice();
	void Reslice(qreal);
	void ResliceV(qreal);
	void ResliceH(qreal);
	void MarkCenter();
	void MoveToCenter();
	void AddPoint();
	void AllPathDarkness();
	void CurrentPathBright();
	void DeleteCurrentPath();
	void DeleteALLPath();
	int GetWinNum();
	qreal GetSliceV();
	qreal GetSliceH();
	int GetPathMapSize();
	int GetLastPointID();
	int GetLastPathID();
	int GetCurrentPointID();
	int GetCurrentPathID();
	qreal GetLastPathSize();
	qreal GetCurrentPathSize(int);
	void MoveLineToPointPos(int);
	void SetCurrentPath(int);
	void DelCurrentPath();
	QPointF GetCurrentPointPos();
	void SetCurrentPointPosX(int, qreal, qreal);
	void SetCurrentPointPosY(int, qreal, qreal);
	qreal GetCurrentPointX(int);
	qreal GetCurrentPointY(int);
	int GetPointMapSize();
	void ResetPathColor(int, QColor);
	qreal PixLayer();

protected:
	void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QMouseEvent*) Q_DECL_OVERRIDE; 
	void mouseMoveEvent(QMouseEvent*) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;
	void wheelEvent(QWheelEvent*) Q_DECL_OVERRIDE;
	void vtkImageDataToQImage(vtkSmartPointer<vtkImageData> imageData);
	
private:
	QGraphicsScene* pScene;
	QGraphicsPixmapItem* pix;
	QGraphicsPixmapItem* ori;
	QGraphicsLineItem* vLine;
	QGraphicsLineItem* hLine;
	QGraphicsEllipseItem* mouse;
	QImage* img;
	QPointF center;
	QPoint lastMousePos;
	int winNum;
	int status;
	qreal zoom;
	qreal pixLayer;
	enum Model{
		Normel,
		MoveVLine,
		MoveHLine,
		MovePath,
	};
	VolumeRenderController* renderObj;
	ImageFilterContorller* imageFilter;

	int pointID;
	QGraphicsEllipseItem* currentPoint;
	QMap<int, QGraphicsEllipseItem*>* pointMap;

	int pathID;
	QGraphicsLineItem* currentPath;
	QMap<int, QGraphicsLineItem*>* pathMap;
}; 