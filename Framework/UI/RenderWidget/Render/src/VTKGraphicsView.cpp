#include "..\include\VTKGraphicsView.h"

VTKGraphicsView::VTKGraphicsView(QWidget *parent)
	: QGraphicsView(parent) {
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	
	this->pointID = 0;
	this->pathID = 0;
	this->pixLayer = 0.5;
	this->img = NULL;
	this->currentPoint = NULL;
	this->currentPath = NULL;
	this->zoom = 1;
	this->status = this->Normel;
	this->pScene = new QGraphicsScene();
	this->pix = new QGraphicsPixmapItem();
	this->ori = new QGraphicsPixmapItem();
	this->vLine = new QGraphicsLineItem();
	this->hLine = new QGraphicsLineItem();
	this->setScene(this->pScene);
	this->pointMap = new QMap<int, QGraphicsEllipseItem*>;
	this->pathMap = new QMap<int, QGraphicsLineItem*>;

	this->mouse = new QGraphicsEllipseItem();
	QPen pen = this->mouse->pen();
	pen.setWidth(0);
	pen.setColor(QColor(0, 0, 0, 0));
	this->mouse->setPen(pen);

	vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
}

VTKGraphicsView::~VTKGraphicsView() {
	this->pointMap->swap(QMap<int, QGraphicsEllipseItem*>());
	this->pointMap = Q_NULLPTR;
	this->currentPoint = Q_NULLPTR;
	this->pathMap->swap(QMap<int, QGraphicsLineItem*>());
	this->pathMap = Q_NULLPTR;
	this->currentPath = Q_NULLPTR;
	this->pScene->clear();
	delete this->pScene;
	this->pScene = Q_NULLPTR;
	delete this->img;
	this->imageFilter = Q_NULLPTR;
	this->img = Q_NULLPTR;
	this->renderObj = Q_NULLPTR;
}

void VTKGraphicsView::InitPos() {
	this->centerOn(this->pix->sceneBoundingRect().center());
	this->update();
}

void VTKGraphicsView::LoadVTKBuff() {
	this->vtkImageDataToQImage(this->renderObj->GetVtkData(this->winNum));
	if (!this->img) return;
	this->pix->setPixmap(QPixmap::fromImage(this->img->scaled(this->imageFilter->GetWidth(this->winNum), this->imageFilter->GetHeight(this->winNum))));
	this->pScene->addItem(this->pix);

	qreal winSizeRatio = (qreal)this->width() / this->height();
	qreal imgSizeRatio = (qreal)this->imageFilter->GetWidth(this->winNum) / this->imageFilter->GetHeight(this->winNum);

	if (winSizeRatio >= imgSizeRatio) {
		qreal scaleSize = (qreal)this->mapToScene(this->rect()).boundingRect().height() / this->pix->sceneBoundingRect().height();
		this->scale(scaleSize, scaleSize);
	} else {
		qreal scaleSize = (qreal)this->mapToScene(this->rect()).boundingRect().width() / this->pix->sceneBoundingRect().width();
		this->scale(scaleSize, scaleSize);
	}

	this->pix->setPos((this->mapToScene(this->rect()).boundingRect().width() - this->pix->sceneBoundingRect().width()) / 2.0,
		(this->mapToScene(this->rect()).boundingRect().height() - this->pix->sceneBoundingRect().height())/ 2.0);
	this->centerOn(this->pix->sceneBoundingRect().center());

	this->pix->setZValue(0);
	
	this->LoadVLine();
	this->LoadHLine();

	this->ChangeWidget();
	this->ChangeWidget();
}

void VTKGraphicsView::LoadVLine() {
	QPen pen = this->vLine->pen();
	switch (this->winNum) {
		case 0:pen.setColor(QColor(0, 128, 0)); break;
		case 1:pen.setColor(QColor(128, 0, 0)); break;
		case 2:pen.setColor(QColor(128, 0, 0)); break;
	}
	pen.setWidth(this->rect().width() / 300.0 / this->transform().m11());
	this->vLine->setPen(pen);

	this->vLine->setZValue(1.0);

	this->vLine->setLine(QLineF(this->pix->sceneBoundingRect().center().x(), this->mapToScene(this->rect()).boundingRect().y(),
		this->pix->sceneBoundingRect().center().x(), this->mapToScene(this->rect()).boundingRect().height()));

	this->pScene->addItem(this->vLine);
}

void VTKGraphicsView::LoadHLine() {
	QPen pen = this->hLine->pen();
	switch (this->winNum) {
		case 0:pen.setColor(QColor(0, 0, 128)); break;
		case 1:pen.setColor(QColor(0, 0, 128)); break;
		case 2:pen.setColor(QColor(0, 128, 0)); break;
	}
	pen.setWidth(this->rect().width() / 300.0 / this->transform().m11());
	this->hLine->setPen(pen);

	this->hLine->setZValue(1.0);

	this->hLine->setLine(QLineF(this->mapToScene(this->rect()).boundingRect().x(), this->pix->sceneBoundingRect().center().y(),
		this->mapToScene(this->rect()).boundingRect().width(), this->pix->sceneBoundingRect().center().y()));

	this->pScene->addItem(this->hLine);
}

void VTKGraphicsView::UpdataVTKBuff() {
	this->vtkImageDataToQImage(this->renderObj->GetVtkData(this->winNum));
	this->pix->setPixmap(QPixmap::fromImage(this->img->scaled(this->imageFilter->GetWidth(this->winNum), this->imageFilter->GetHeight(this->winNum))));
}

void VTKGraphicsView::SetRenderObj(VolumeRenderController* renderObj) {
	this->renderObj = renderObj;
}

void VTKGraphicsView::SetImageFilter(ImageFilterContorller* imageFilter) {
	this->imageFilter = imageFilter;
}

void VTKGraphicsView::SetWinNum(int winNum) {
	this->winNum = winNum;
}

void VTKGraphicsView::Scale(qreal step) {
	qreal factor = 1.0 + step / 500.0;
	this->zoom *= factor;
	if (this->zoom < 0.01) return;
	scale(factor, factor);
}

void VTKGraphicsView::Move(QPointF delta) {
	delta *= this->transform().m11();

	this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	QPoint newCenter(this->rect().width() / 2 - delta.x() - 2, this->rect().height() / 2 - delta.y() - 2);
	this->centerOn(this->mapToScene(newCenter));

	this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}

void VTKGraphicsView::UpdateLine() {
	QPen vpen = this->vLine->pen();
	vpen.setWidth(this->rect().width() / 300.0 / this->transform().m11());
	this->vLine->setPen(vpen);

	QPen hpen = this->hLine->pen();
	hpen.setWidth(this->rect().width() / 300.0 / this->transform().m11());
	this->hLine->setPen(hpen);

	this->vLine->setLine(QLineF(this->vLine->line().x1(), this->mapToScene(this->rect()).boundingRect().y(),
		this->vLine->line().x2(), this->mapToScene(this->rect()).boundingRect().y() + this->mapToScene(this->rect()).boundingRect().height()));
	this->hLine->setLine(QLineF(this->mapToScene(this->rect()).boundingRect().x(), this->hLine->line().y1(),
		this->mapToScene(this->rect()).boundingRect().x() + this->mapToScene(this->rect()).boundingRect().width(), this->hLine->line().y2()));
}

void VTKGraphicsView::AdjustImg(QPointF mouseDelta) {
	if (qAbs(mouseDelta.x()) >= qAbs(mouseDelta.y())) {
		this->renderObj->ResetImgColorRanger(mouseDelta.x());
	} else {
		this->renderObj->ResetImgColorCenter(mouseDelta.y());
	}
	this->ColorChange();
}

void VTKGraphicsView::Reslice() {
	this->vtkImageDataToQImage(this->renderObj->GetVtkData(this->winNum));
	if (!this->img) return;
	this->pix->setPixmap(QPixmap::fromImage(this->img->scaled(this->imageFilter->GetWidth(this->winNum), this->imageFilter->GetHeight(this->winNum))));
}

void VTKGraphicsView::Reslice(qreal slice) {
	if (slice <= 0) {
		this->vtkImageDataToQImage(this->renderObj->ResliceVtkData(this->winNum, 0.0));
	} else if (slice >= 1) {
		this->vtkImageDataToQImage(this->renderObj->ResliceVtkData(this->winNum, 1.0));
	} else {
		this->vtkImageDataToQImage(this->renderObj->ResliceVtkData(this->winNum, slice));
	}
	if (!this->img) return;
	this->pix->setPixmap(QPixmap::fromImage(this->img->scaled(this->imageFilter->GetWidth(this->winNum), this->imageFilter->GetHeight(this->winNum))));
	
	this->pixLayer = 1.0 - slice;
	if (this->pixLayer < 0.0) {
		this->pixLayer = 0.0;
	} else if (this->pixLayer > 1.0) {
		this->pixLayer = 1.0;
	}
	
	QMap<int, QGraphicsLineItem*>::const_iterator iterPath;
	for (iterPath = this->pathMap->constBegin(); iterPath != this->pathMap->constEnd(); iterPath++) {
		QPen pen = iterPath.value()->pen();
		QColor color = pen.color();
		if (iterPath.value()->zValue() < this->pixLayer) {
			color.setAlpha(96);
		} else {
			color.setAlpha(255);
		}
		pen.setColor(color);
		iterPath.value()->setPen(pen);

		QGraphicsEllipseItem *point1, *point2;
		point1 = this->pointMap->value(iterPath.key() * 2);
		point2 = this->pointMap->value(iterPath.key() * 2 + 1);
		QPen pen1, pen2;
		pen1 = point1->pen();
		pen2 = point2->pen();
		pen1.setColor(color);
		pen2.setColor(color);
		point1->setPen(pen1);
		point1->setBrush(QBrush(color));
		point2->setPen(pen2);
		point2->setBrush(QBrush(color));
	}
}

void VTKGraphicsView::ResliceV(qreal slice) {
	if (slice <= 0) {
		this->vLine->setLine(QLineF(this->pix->sceneBoundingRect().x(), this->vLine->line().y1(),
			this->pix->sceneBoundingRect().x(), this->vLine->line().y2()));
	} else if (slice >= 1) {
		this->vLine->setLine(QLineF(this->pix->sceneBoundingRect().width() + this->pix->sceneBoundingRect().x(), this->vLine->line().y1(),
			this->pix->sceneBoundingRect().width() + this->pix->sceneBoundingRect().x(), this->vLine->line().y2()));
	} else {
		this->vLine->setLine(QLineF(this->pix->sceneBoundingRect().width() * slice + this->pix->sceneBoundingRect().x(), this->vLine->line().y1(),
			this->pix->sceneBoundingRect().width() * slice + this->pix->sceneBoundingRect().x(), this->vLine->line().y2()));
	}
}

void VTKGraphicsView::ResliceH(qreal slice) {
	if (slice <= 0) {
		this->hLine->setLine(QLineF(this->hLine->line().x1(), this->pix->sceneBoundingRect().y(),
			this->hLine->line().x2(), this->pix->sceneBoundingRect().y()));
	} else if (slice >= 1) {
		this->hLine->setLine(QLineF(this->hLine->line().x1(), this->pix->sceneBoundingRect().height() + this->pix->sceneBoundingRect().y(),
			this->hLine->line().x2(), this->pix->sceneBoundingRect().height() + this->pix->sceneBoundingRect().y()));
	} else {
		this->hLine->setLine(QLineF(this->hLine->line().x1(), this->pix->sceneBoundingRect().height() * slice + this->pix->sceneBoundingRect().y(),
			this->hLine->line().x2(), this->pix->sceneBoundingRect().height() * slice + this->pix->sceneBoundingRect().y()));
	}
}

void VTKGraphicsView::mousePressEvent(QMouseEvent* event) {
	this->lastMousePos = event->pos();
	if (LEF) {
		this->AllPathDarkness();
		this->currentPath = NULL;
		this->NoCurrentPath();

		this->mouse->setRect(QRectF(this->mapToScene(event->pos()).x() - this->rect().width() / 600.0 / this->transform().m11(),
									this->mapToScene(event->pos()).y() - this->rect().width() / 600.0 / this->transform().m11(),
									this->rect().width() / 100.0 / this->transform().m11(),
									this->rect().width() / 100.0 / this->transform().m11()));
		this->pScene->addItem(this->mouse);
		QList<QGraphicsItem *> list = this->pScene->collidingItems(this->mouse);
		if (list.isEmpty()) return;
		QList<QGraphicsItem *>::iterator iter;
		for (iter = list.begin(); iter != list.end(); iter++) {
			if (this->vLine == (QGraphicsLineItem*)(*iter)) {
				this->status = this->MoveVLine;
				this->setCursor(Qt::ClosedHandCursor);
			} else if (hLine == (QGraphicsLineItem*)(*iter)) {
				this->status = this->MoveHLine;
				this->setCursor(Qt::ClosedHandCursor);
			}
		}
		for (iter = list.begin(); iter != list.end(); iter++) {
			if (this->pointMap->values().contains((QGraphicsEllipseItem*)(*iter))) {
				this->currentPoint = (QGraphicsEllipseItem*)(*iter);
				this->status = this->MovePath;
				this->setCursor(Qt::ClosedHandCursor);
				this->UpdataPoint(this->GetCurrentPointID());

				if (this->pointMap->contains(this->pointMap->key(this->currentPoint) / 2)) {
					this->currentPath = pathMap->value(this->pointMap->key(this->currentPoint) / 2);
					this->CurrentPathBright();
					this->CurrentPath(this->GetCurrentPathID());
				}
			}
		}
		this->pScene->removeItem(this->mouse);
	}
}

void VTKGraphicsView::mouseMoveEvent(QMouseEvent* event) {
	QPointF mouseDelta = mapToScene(event->pos()) - mapToScene(this->lastMousePos);
	if (LEF) {
		if (this->status == this->Normel) {
			this->AdjustImg(mouseDelta);
		} else if (this->status == this->MoveVLine) {
			if (this->mapToScene(event->pos()).x() <= this->pix->sceneBoundingRect().x()) {
				this->vLine->setLine(QLineF(this->pix->sceneBoundingRect().x(), this->mapToScene(this->rect()).boundingRect().y(),
					this->pix->sceneBoundingRect().x(), this->mapToScene(this->rect()).boundingRect().y() + this->mapToScene(this->rect()).boundingRect().height()));
			} else if (this->mapToScene(event->pos()).x() >= this->pix->sceneBoundingRect().x() + this->pix->sceneBoundingRect().width()) {
				this->vLine->setLine(QLineF(this->pix->sceneBoundingRect().x() + this->pix->sceneBoundingRect().width(), this->mapToScene(this->rect()).boundingRect().y(),
					this->pix->sceneBoundingRect().x() + this->pix->sceneBoundingRect().width(), this->mapToScene(this->rect()).boundingRect().y() + this->mapToScene(this->rect()).boundingRect().height()));
			} else {
				this->vLine->setLine(QLineF(this->mapToScene(event->pos()).x(), this->mapToScene(this->rect()).boundingRect().y(),
					this->mapToScene(event->pos()).x(), this->mapToScene(this->rect()).boundingRect().y() + this->mapToScene(this->rect()).boundingRect().height()));
			}
			this->ResliceVLine(this->GetSliceV());
		} else if (this->status == this->MoveHLine) {
			if (this->mapToScene(event->pos()).y() <= this->pix->sceneBoundingRect().y()) {
				this->hLine->setLine(QLineF(this->mapToScene(this->rect()).boundingRect().x(), this->pix->sceneBoundingRect().y(),
					this->mapToScene(this->rect()).boundingRect().x() + this->mapToScene(this->rect()).boundingRect().width(), this->pix->sceneBoundingRect().y()));
			} else if (this->mapToScene(event->pos()).y() >= this->pix->sceneBoundingRect().y() + this->pix->sceneBoundingRect().height()) {
				this->hLine->setLine(QLineF(this->mapToScene(this->rect()).boundingRect().x(), this->pix->sceneBoundingRect().y() + this->pix->sceneBoundingRect().height(),
					this->mapToScene(this->rect()).boundingRect().x() + this->mapToScene(this->rect()).boundingRect().width(), this->pix->sceneBoundingRect().y() + this->pix->sceneBoundingRect().height()));
			} else {
				this->hLine->setLine(QLineF(this->mapToScene(this->rect()).boundingRect().x(), this->mapToScene(event->pos()).y(),
					this->mapToScene(this->rect()).boundingRect().x() + this->mapToScene(this->rect()).boundingRect().width(), this->mapToScene(event->pos()).y()));
			}
			this->ResliceHLine(this->GetSliceH());
		} else if (this->status == this->MovePath) {
			this->currentPoint->setRect(QRectF(this->mapToScene(event->pos()).x() - this->rect().width() / 200.0 / this->transform().m11(),
											   this->mapToScene(event->pos()).y() - this->rect().width() / 200.0 / this->transform().m11(),
											   this->rect().width() / 100.0 / this->transform().m11(),
											   this->rect().width() / 100.0 / this->transform().m11()));
			this->UpdataPoint(this->GetCurrentPointID());
			if(this->currentPath == NULL) {
				if(this->pathMap->contains(this->GetCurrentPointID() / 2)) {
					this->currentPath = this->pathMap->value(this->GetCurrentPointID() / 2);
				}
				return;
			}
			this->currentPath->setLine(this->pointMap->value(this->pathMap->key(this->currentPath) * 2)->rect().center().x(), 
									   this->pointMap->value(this->pathMap->key(this->currentPath) * 2)->rect().center().y(), 
									   this->pointMap->value(this->pathMap->key(this->currentPath) * 2 + 1)->rect().center().x(), 
									   this->pointMap->value(this->pathMap->key(this->currentPath) * 2 + 1)->rect().center().y());
			this->UpdataPath(this->GetCurrentPathID());
		}
	} else if (MID) {
		this->Move(mouseDelta);
		this->UpdateLine();
	} else if (RIG) {
		this->Scale(mouseDelta.y());
		this->UpdateLine();
	}
	this->lastMousePos = event->pos(); 
}

void VTKGraphicsView::mouseDoubleClickEvent(QMouseEvent* event) {
	this->mouse->setRect(QRectF(this->mapToScene(event->pos()).x() - this->rect().width() / 600.0 / this->transform().m11(),
								this->mapToScene(event->pos()).y() - this->rect().width() / 600.0 / this->transform().m11(),
								this->rect().width() / 100.0 / this->transform().m11(),
								this->rect().width() / 100.0 / this->transform().m11()));
	this->pScene->addItem(this->mouse);
	QList<QGraphicsItem *> list = this->pScene->collidingItems(this->mouse);

	QList<QGraphicsItem *>::iterator iter;
	for (iter = list.begin(); iter != list.end(); iter++) {
		if (pointMap->values().contains((QGraphicsEllipseItem*)(*iter))) {
			this->pScene->removeItem(this->mouse);
			this->MoveLineToPoint(pointMap->key((QGraphicsEllipseItem*)(*iter)));
			return;
		}
	}
	this->pScene->removeItem(this->mouse);

	this->center = this->mapToScene(this->rect()).boundingRect().center();

	this->ChangeWidget();

	qreal winSizeRatio = (qreal)this->width() / this->height();
	qreal imgSizeRatio = (qreal)this->imageFilter->GetWidth(this->winNum) / this->imageFilter->GetHeight(this->winNum);

	if (winSizeRatio >= imgSizeRatio) {
		qreal scaleSize = (qreal)this->mapToScene(this->rect()).boundingRect().height() / this->pix->sceneBoundingRect().height();
		this->scale(scaleSize, scaleSize);
	} else {
		qreal scaleSize = (qreal)this->mapToScene(this->rect()).boundingRect().width() / this->pix->sceneBoundingRect().width();
		this->scale(scaleSize, scaleSize);
	}
	this->centerOn(this->center);
}

void VTKGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
	this->setCursor(Qt::ArrowCursor);
	this->status = this->Normel;
	this->currentPoint = NULL;
}

void VTKGraphicsView::wheelEvent(QWheelEvent* event) {
	int numValue = event->delta(); 
	qreal numDegrees = numValue / 8.0; 
	qreal numSteps = numDegrees / 15.0;
	qreal step = numSteps / 100.0;
	this->WheelReslice(step);
}

void VTKGraphicsView::vtkImageDataToQImage(vtkSmartPointer<vtkImageData> data) {
	if (!data) return;

	if (this->img) delete this->img;

	int width = data->GetDimensions()[0];
	int height = data->GetDimensions()[1];
	this->img = new QImage(width, height, RGB32);
	QRgb *rgbPtr = reinterpret_cast<QRgb *>(this->img->bits()) + width * (height - 1);
	unsigned char *colorsPtr = reinterpret_cast<unsigned char *>(data->GetScalarPointer());

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			*(rgbPtr++) = QColor(colorsPtr[0], colorsPtr[1], colorsPtr[2]).rgb();
			colorsPtr += data->GetNumberOfScalarComponents();
		}
		rgbPtr -= width * 2;
	}
}

void VTKGraphicsView::MarkCenter() {
	this->center = this->mapToScene(this->rect()).boundingRect().center();
}

void VTKGraphicsView::MoveToCenter() {
	this->centerOn(this->center);
}

void VTKGraphicsView::AddPoint() {
	QGraphicsEllipseItem* point = new QGraphicsEllipseItem();
	QPen pen = point->pen();
	pen.setWidth(0);
	pen.setColor(QColor(78, 26, 128, 255));
	point->setPen(pen);
	point->setBrush(QBrush(QColor(78, 26, 128, 255)));
	point->setRect(QRectF(this->vLine->line().x1() - this->rect().width() / 200.0 / this->transform().m11(),
						  this->hLine->line().y1() - this->rect().width() / 200.0 / this->transform().m11(),
						  this->rect().width() / 100.0 / this->transform().m11(),
						  this->rect().width() / 100.0 / this->transform().m11()));
	point->setZValue(this->pixLayer);
	pointMap->insert(this->pointID, point);
	pointID++;
	this->pScene->addItem(point);

	if (pointMap->size() > 0 && 0 == pointMap->size() % 2) {
		QGraphicsLineItem* path = new QGraphicsLineItem();
		path->setZValue((this->pointMap->value(this->pathID * 2)->zValue() + this->pointMap->value(this->pathID * 2 + 1)->zValue()) / 2.0);
		QPen pen = path->pen();
		if (path->zValue() < this->pixLayer) {
			pen.setColor(QColor(78, 26, 128, 96));
		} else {
			pen.setColor(QColor(78, 26, 128, 255));
		}
		pen.setWidth(this->rect().width() / 200.0 / this->transform().m11());
		path->setPen(pen);
		path->setLine((pointMap->end() - 1).value()->rect().center().x(), (pointMap->end() - 1).value()->rect().center().y(),
			(pointMap->end() - 2).value()->rect().center().x(), (pointMap->end() - 2).value()->rect().center().y());
		pathMap->insert(this->pathID, path);
		pathID++;
		this->pScene->addItem(path);
	}
}

void VTKGraphicsView::AllPathDarkness() {
	return;
	QMap<int, QGraphicsLineItem*>::const_iterator iter;
	for (iter = this->pathMap->constBegin(); iter != this->pathMap->constEnd(); iter++) {
		QPen pen = iter.value()->pen();
		QColor color = pen.color();
		color.setAlpha(96);
		pen.setColor(color);
		iter.value()->setPen(pen);
	}
}

void VTKGraphicsView::CurrentPathBright() {
	return;
	if (this->currentPath == NULL) return;
	QPen pen = this->currentPath->pen();
	QColor color = pen.color();
	color.setAlpha(255);
	pen.setColor(color);
	this->currentPath->setPen(pen);
}

void VTKGraphicsView::DeleteCurrentPath() {
	if (this->currentPath == NULL) return;
	QMap<int, QGraphicsLineItem*>::const_iterator iter;
	for (iter = this->pathMap->constBegin(); iter != this->pathMap->constEnd(); iter++) {
		if (this->currentPath == iter.value()) {
			this->pScene->removeItem(this->pointMap->value(iter.key() * 2));
			this->pScene->removeItem(this->pointMap->value(iter.key() * 2 + 1));
			this->pScene->removeItem(this->currentPath);

			this->pointMap->remove(iter.key() * 2);
			this->pointMap->remove(iter.key() * 2 + 1);
			this->pathMap->remove(iter.key());

			this->currentPath = NULL;

			return;
		}
	}
}

void VTKGraphicsView::DeleteALLPath() {
	QMap<int, QGraphicsLineItem*>::const_iterator iterPath;
	for (iterPath = this->pathMap->constBegin(); iterPath != this->pathMap->constEnd(); iterPath++) {
		this->pScene->removeItem(iterPath.value());
		this->currentPath = NULL;
	}
	this->pathMap->clear();

	QMap<int, QGraphicsEllipseItem*>::const_iterator iterPoint;
	for (iterPoint = this->pointMap->constBegin(); iterPoint != this->pointMap->constEnd(); iterPoint++) {
		this->pScene->removeItem(iterPoint.value());
		this->currentPoint = NULL;
	}
	this->pointMap->clear();
}

int VTKGraphicsView::GetWinNum() {
	return this->winNum;
}

qreal VTKGraphicsView::GetSliceV() {
	return (this->vLine->line().x1() - this->pix->sceneBoundingRect().x()) / (this->pix->sceneBoundingRect().width());
}

qreal VTKGraphicsView::GetSliceH() {
	return (this->hLine->line().y1() - this->pix->sceneBoundingRect().y()) / (this->pix->sceneBoundingRect().height());
}

int VTKGraphicsView::GetPathMapSize() {
	return this->pathMap->size();
}

int VTKGraphicsView::GetLastPointID() {
	return (pointMap->end() - 1).key();
}

int VTKGraphicsView::GetLastPathID() {
	return (pathMap->end() - 1).key();
}

int VTKGraphicsView::GetCurrentPointID() {
	if (this->currentPoint == NULL) return -1;
	return pointMap->key(this->currentPoint);
}

int VTKGraphicsView::GetCurrentPathID() {
	if (this->currentPath == NULL) return -1;
	return pathMap->key(this->currentPath);
}

qreal VTKGraphicsView::GetLastPathSize() {
	return (pathMap->end() - 1).value()->line().length();
}

qreal VTKGraphicsView::GetCurrentPathSize(int pathID) {
	return pathMap->value(pathID)->line().length();
}

void VTKGraphicsView::MoveLineToPointPos(int pointID) {
	this->ResliceV((this->pointMap->value(pointID)->rect().center().x() - this->pix->sceneBoundingRect().x()) / (this->pix->sceneBoundingRect().width()));
	this->ResliceH((this->pointMap->value(pointID)->rect().center().y() - this->pix->sceneBoundingRect().y()) / (this->pix->sceneBoundingRect().height()));
	this->ResliceVLine(this->GetSliceV());
	this->ResliceHLine(this->GetSliceH());
}

void VTKGraphicsView::SetCurrentPath(int pathID) {
	if (pathID < 0) return;
	if (pathID == this->GetCurrentPathID()) return;
	this->AllPathDarkness();
	this->currentPath = this->pathMap->value(pathID);
	this->CurrentPathBright();
}

void VTKGraphicsView::DelCurrentPath() {
	this->AllPathDarkness();
	this->currentPath = NULL;
}

QPointF VTKGraphicsView::GetCurrentPointPos() {
	QPointF pos = QPointF((this->currentPoint->rect().center().x() - this->pix->sceneBoundingRect().x()) / (this->pix->sceneBoundingRect().width()),
						  (this->currentPoint->rect().center().y() - this->pix->sceneBoundingRect().y()) / (this->pix->sceneBoundingRect().height()));
	return pos;
}

void VTKGraphicsView::SetCurrentPointPosX(int pathID, qreal slice, qreal z){
	this->pointMap->value(pathID)->setRect(QRectF(
		this->pix->sceneBoundingRect().width() * slice + this->pix->sceneBoundingRect().x(),
		this->pointMap->value(pathID)->rect().y(),
		this->rect().width() / 100.0 / this->transform().m11(),
		this->rect().width() / 100.0 / this->transform().m11()));
	this->pointMap->value(pathID)->setZValue(1.0 - z);

	if (this->currentPath == NULL) return;
	this->currentPath->setLine(this->pointMap->value(this->pathMap->key(this->currentPath) * 2)->rect().center().x(),
		this->pointMap->value(this->pathMap->key(this->currentPath) * 2)->rect().center().y(),
		this->pointMap->value(this->pathMap->key(this->currentPath) * 2 + 1)->rect().center().x(),
		this->pointMap->value(this->pathMap->key(this->currentPath) * 2 + 1)->rect().center().y());
	this->currentPath->setZValue((this->pointMap->value(this->GetCurrentPathID() * 2)->zValue() + this->pointMap->value(this->GetCurrentPathID() * 2 + 1)->zValue()) / 2.0);
	QPen pen = this->currentPath->pen();
	QColor color = pen.color();
	if (this->currentPath->zValue() < this->pixLayer) {
		color.setAlpha(96);
	}
	else {
		color.setAlpha(255);
	}
	pen.setColor(color);
	this->currentPath->setPen(pen);

	QGraphicsEllipseItem *point1, *point2;
	point1 = this->pointMap->value(this->GetCurrentPathID() * 2);
	point2 = this->pointMap->value(this->GetCurrentPathID() * 2 + 1);
	QPen pen1, pen2;
	pen1 = point1->pen();
	pen2 = point2->pen();
	pen1.setColor(color);
	pen2.setColor(color);
	point1->setPen(pen1);
	point1->setBrush(QBrush(color));
	point2->setPen(pen2);
	point2->setBrush(QBrush(color));
}

void VTKGraphicsView::SetCurrentPointPosY(int pathID, qreal slice, qreal z) {
	this->pointMap->value(pathID)->setRect(QRectF(
		this->pointMap->value(pathID)->rect().x(),
		this->pix->sceneBoundingRect().height() * slice + this->pix->sceneBoundingRect().y(),
		this->rect().width() / 100.0 / this->transform().m11(),
		this->rect().width() / 100.0 / this->transform().m11()));
	this->pointMap->value(pathID)->setZValue(1.0 - z);

	if (this->currentPath == NULL) return;
	this->currentPath->setLine(this->pointMap->value(this->pathMap->key(this->currentPath) * 2)->rect().center().x(),
		this->pointMap->value(this->pathMap->key(this->currentPath) * 2)->rect().center().y(),
		this->pointMap->value(this->pathMap->key(this->currentPath) * 2 + 1)->rect().center().x(),
		this->pointMap->value(this->pathMap->key(this->currentPath) * 2 + 1)->rect().center().y());
	this->currentPath->setZValue((this->pointMap->value(this->GetCurrentPathID() * 2)->zValue() + this->pointMap->value(this->GetCurrentPathID() * 2 + 1)->zValue()) / 2.0);
	QPen pen = this->currentPath->pen();
	QColor color = pen.color();
	if (this->currentPath->zValue() < this->pixLayer) {
		color.setAlpha(96);
	}
	else {
		color.setAlpha(255);
	}
	pen.setColor(color);
	this->currentPath->setPen(pen);

	QGraphicsEllipseItem *point1, *point2;
	point1 = this->pointMap->value(this->GetCurrentPathID() * 2);
	point2 = this->pointMap->value(this->GetCurrentPathID() * 2 + 1);
	QPen pen1, pen2;
	pen1 = point1->pen();
	pen2 = point2->pen();
	pen1.setColor(color);
	pen2.setColor(color);
	point1->setPen(pen1);
	point1->setBrush(QBrush(color));
	point2->setPen(pen2);
	point2->setBrush(QBrush(color));
}

qreal VTKGraphicsView::GetCurrentPointX(int pointID) {
	return (this->pointMap->value(pointID)->rect().center().x() - this->pix->sceneBoundingRect().x()) / (this->pix->sceneBoundingRect().width());
}

qreal VTKGraphicsView::GetCurrentPointY(int pointID) {
	return (this->pointMap->value(pointID)->rect().center().y() - this->pix->sceneBoundingRect().y()) / (this->pix->sceneBoundingRect().height());
}

int VTKGraphicsView::GetPointMapSize() {
	return this->pointMap->size();
}

void VTKGraphicsView::ResetPathColor(int pathID, QColor color) {
	if (pathID < 0) return;
	if (pathID != this->GetCurrentPathID()) {
		this->currentPath = this->pathMap->value(pathID);
	}
	QPen pen = this->currentPath->pen();
	int alpha = pen.color().alpha();
	color.setAlpha(alpha);
	pen.setColor(color);
	this->currentPath->setPen(pen);

	QGraphicsEllipseItem *point1, *point2;
	point1 = this->pointMap->value(pathID * 2);
	point2 = this->pointMap->value(pathID * 2 + 1);
	QPen pen1, pen2;
	pen1 = point1->pen();
	pen2 = point2->pen();
	pen1.setColor(color);
	pen2.setColor(color);
	point1->setPen(pen1);
	point1->setBrush(QBrush(color));
	point2->setPen(pen2);
	point2->setBrush(QBrush(color));
}

qreal VTKGraphicsView::PixLayer(){
	return this->pixLayer;
}
