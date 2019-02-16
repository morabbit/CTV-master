#pragma once
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QTableWidgetItem>
#include <QGraphicsTextItem> 
#include <QPixmap>
#include <QImage>
#include <QThread>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF> 
#include <QPointer> 
#include <QList> 

#include <vtkImageData.h>
#include <vtkSmartPointer.h>

#include "..\UI\db\include\UISqlMgr.h"

#include "CommonLayer.h"

#define REVERSE(a) a =!a
#define LEF event->buttons() == Qt::LeftButton
#define MID event->buttons() == Qt::MidButton
#define RIG event->buttons() == Qt::RightButton
#define RGB32 QImage::Format_RGB32 

class ImageGraphicsView : public QGraphicsView {
	Q_OBJECT

signals:

public:
	explicit ImageGraphicsView(QWidget *parent = 0);
	~ImageGraphicsView();

	void InitPos();
	void LoadVTKBuff();
	void UpdataVTKBuff();
	void SetRenderObj(VolumeRenderController*);
	void SetImageFilter(ImageFilterContorller*);
	void SetDicomInfoSQL(DicomInfoTable*);
	void Scale(qreal x);
	void Move(QPointF delta);
	void AdjustImg(QPointF);
	void Reslice();
	void Reslice(qreal);
	void MarkCenter();
	void MoveToCenter();

public slots:
	void LoadFileImg(QTableWidgetItem*);
	void ImgHorizontalMirror();
	void ImgVerticalMirror();
	void ImgRotateAntiClockWise();
	void ImgRotateClockWise();
	void ImgReset();

protected:
	void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent*) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;
	void wheelEvent(QWheelEvent*) Q_DECL_OVERRIDE;
	void SetOriLabel();
	void LoadCornerInfo();
	void LoadTopLeftCornerInfo();
	void LoadTopRightCornerInfo();
	void LoadButtomLeftCornerInfo();
	void LoadButtomRightCornerInfo();
	void LoadScaleBar();
	void UpdateFrameInfo();
	void UpdateScaleBar();
	void UpdateFitMagInfo();
	void UpdateWindowWidthAndLevelInfo();
	QImage* vtkImageDataToQImage(vtkSmartPointer<vtkImageData> imageData);

private:
	QString describe;
	QImage* img;
	QGraphicsScene* pScene;
	QGraphicsPixmapItem* pix;
	QPointF center;
	QPoint lastMousePos;
	qreal zoom;
	qreal pixLayer;
	QPixmap rule;
	VolumeRenderController* renderObj;
	ImageFilterContorller* imageFilter;
	RoutePlanning* routePlan;
	DicomInfoTable* sql;

	QGraphicsTextItem* upOri;
	QGraphicsTextItem* downOri;
	QGraphicsTextItem* leftOri;
	QGraphicsTextItem* rightOri;

	QGraphicsTextItem* Frame;
	QGraphicsTextItem* PitMag;
	QGraphicsTextItem* SeriesDescription;
	QGraphicsTextItem* ImageNo;

	QGraphicsTextItem* Name;
	QGraphicsTextItem* PID;
	QGraphicsTextItem* DOB;
	QGraphicsTextItem* SEX;

	QGraphicsTextItem* WindowWidthAndLevel;

	QGraphicsTextItem* Hospital;

	QGraphicsTextItem* ScaleNum;
	QGraphicsLineItem* ScaleBar;

	bool isFlipUpDown;
	bool isFlipLeftRight;
};