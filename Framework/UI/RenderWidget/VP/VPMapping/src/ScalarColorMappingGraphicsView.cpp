#include "..\include\ScalarColorMappingGraphicsView.h"

ScalarColorMappingGraphicsView::ScalarColorMappingGraphicsView(QWidget *parent)
	: QGraphicsView(parent) {
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	this->status = this->Normel;

	this->pScene = new QGraphicsScene();
	this->setScene(this->pScene);
	this->currentPoint = NULL;

	this->pointMap = new QVector<QGraphicsEllipseItem*>;
	this->lineMap = new QVector<QGraphicsLineItem*>;
	this->infoMap = new QVector<QGraphicsPolygonItem*>;

	this->pointColorMap = new QMap<QGraphicsEllipseItem*, QColor>;

	this->currentColor = new QColor(0,0,0);

	this->mouse = new QGraphicsEllipseItem();
	QPen penMouse = this->mouse->pen();
	penMouse.setWidth(0);
	penMouse.setColor(QColor(0, 0, 0, 0));
	this->mouse->setPen(penMouse);
}

ScalarColorMappingGraphicsView::~ScalarColorMappingGraphicsView() {
	this->pointMap->swap(QVector<QGraphicsEllipseItem*>());
	this->lineMap->swap(QVector<QGraphicsLineItem*>());
	this->infoMap->swap(QVector<QGraphicsPolygonItem*>());
	this->pointColorMap->swap(QMap<QGraphicsEllipseItem*, QColor>());
	delete this->currentColor;
	this->currentColor = Q_NULLPTR;
}

void ScalarColorMappingGraphicsView::AddPoint(QPoint pos) {
	QGraphicsEllipseItem* point = new QGraphicsEllipseItem();
	QPen pen = point->pen();
	pen.setWidth(0);
	pen.setColor(Qt::black);
	point->setPen(pen);
	point->setBrush(QBrush(Qt::black));
	point->setZValue(1.0);

	if (this->pointMap->isEmpty()) {
		point->setRect(QRectF(
			this->mapToScene(pos).x() - this->rect().width() / 120.0,
			this->mapToScene(this->rect().center()).y() - this->rect().width() / 120.0,
			this->rect().width() / 60.0,
			this->rect().width() / 60.0));
		point->setStartAngle(16 * 0);
		point->setSpanAngle(16 * 360);
	} else {
		point->setRect(QRectF(
			this->mapToScene(pos).x() - this->rect().width() / 120.0,
			this->pointMap->value(0)->rect().center().y() - this->rect().width() / 120.0,
			this->rect().width() / 60.0,
			this->rect().width() / 60.0));
		point->setStartAngle(16 * 0);
		point->setSpanAngle(16 * 360);
	}

	PointMapSize(this->pointMap->size());

	this->pointColorMap->insert(point, *(this->currentColor));
	
	this->pScene->addItem(point);

	if (this->pointMap->isEmpty()) {
		this->pointMap->push_back(point);
		this->SetCurrentPoint(this->pointMap->size() - 1);
		this->CreateInfo();
	} else {
		if (this->mapToScene(pos).x() <= this->pointMap->value(0)->rect().center().x()) {
			this->pointMap->insert(0, point);
			this->SetCurrentPoint(0);
			this->AddLineFirst(pos);
		} else if (this->mapToScene(pos).x() >= this->pointMap->last()->rect().center().x()) {
			this->pointMap->push_back(point); 
			this->SetCurrentPoint(this->pointMap->size() - 1);
			this->AddLineLast(pos);
		} else {
			QVector<QGraphicsLineItem*>::iterator iter;
			for (iter = this->lineMap->begin(); iter != this->lineMap->end(); iter++) {
				if (((*iter)->line().p1().x() < this->mapToScene(pos).x() && this->mapToScene(pos).x() < (*iter)->line().p2().x()) ||
					(((*iter)->line().p2().x() < this->mapToScene(pos).x() && this->mapToScene(pos).x() < (*iter)->line().p1().x()))) {
					int index = this->lineMap->indexOf((*iter)) + 1;
					this->pointMap->insert(index, point); 
					this->SetCurrentPoint(index);
					this->SplitLine(pos, iter, index);
					break;
				}
			}
		}
	}
	this->AddPoint(this->pointMap->indexOf(this->currentPoint));
}

void ScalarColorMappingGraphicsView::UpdateCurrentPoint(QPoint position) {
	QPointF pos = this->mapToScene(position);

	if (this->pointMap->indexOf(this->currentPoint) > 0 && pos.x() < this->pointMap->value(this->pointMap->indexOf(this->currentPoint) - 1)->rect().center().x()) {
		pos.setX(this->pointMap->value(this->pointMap->indexOf(this->currentPoint) - 1)->rect().center().x());
	} else if (this->pointMap->indexOf(this->currentPoint) < this->pointMap->size() - 1 && pos.x() > this->pointMap->value(this->pointMap->indexOf(this->currentPoint) + 1)->rect().center().x()) {
		pos.setX(this->pointMap->value(this->pointMap->indexOf(this->currentPoint) + 1)->rect().center().x());
	} else if (this->pointMap->indexOf(this->currentPoint) == 0 && pos.x() < this->mapToScene(this->rect()).boundingRect().left()) {
		pos.setX(this->mapToScene(this->rect()).boundingRect().left());
	} else if (this->pointMap->indexOf(this->currentPoint) == this->pointMap->size() - 1 && pos.x() > this->mapToScene(this->rect()).boundingRect().right()) {
		pos.setX(this->mapToScene(this->rect()).boundingRect().right());
	}
	pos.setY(this->mapToScene(this->rect().center()).y());

	this->currentPoint->setRect(QRectF(
		pos.x() - this->rect().width() / 120.0,
		pos.y() - this->rect().width() / 120.0,
		this->rect().width() / 60.0,
		this->rect().width() / 60.0));

	CurrentPointPos(this->currentPoint->rect().center().x());

	this->UpdateLine();
	this->UpdateInfoPos();

	this->UpdatePoint(this->pointMap->indexOf(this->currentPoint));
}

void ScalarColorMappingGraphicsView::ResetCurrentPointPos(qreal posX) {
	if (!this->currentPoint) return;

	QPointF pos = this->currentPoint->rect().center();

	if (this->pointMap->indexOf(this->currentPoint) > 0 && posX < this->pointMap->value(this->pointMap->indexOf(this->currentPoint) - 1)->rect().center().x()) {
		pos.setX(this->pointMap->value(this->pointMap->indexOf(this->currentPoint) - 1)->rect().center().x());
	} else if (this->pointMap->indexOf(this->currentPoint) < this->pointMap->size() - 1 && posX > this->pointMap->value(this->pointMap->indexOf(this->currentPoint) + 1)->rect().center().x()) {
		pos.setX(this->pointMap->value(this->pointMap->indexOf(this->currentPoint) + 1)->rect().center().x());
	} else if (this->pointMap->indexOf(this->currentPoint) == 0 && posX < this->mapToScene(this->rect()).boundingRect().left()) {
		pos.setX(this->mapToScene(this->rect()).boundingRect().left());
	} else if (this->pointMap->indexOf(this->currentPoint) == this->pointMap->size() - 1 && posX > this->mapToScene(this->rect()).boundingRect().right()) {
		pos.setX(this->mapToScene(this->rect()).boundingRect().right());
	} else {
		pos.setX(posX);
	}

	this->currentPoint->setRect(QRectF(
		pos.x() - this->rect().width() / 120.0,
		pos.y() - this->rect().width() / 120.0,
		this->rect().width() / 60.0,
		this->rect().width() / 60.0));

	CurrentPointPos(this->currentPoint->rect().center().x());

	this->UpdateLine();
	this->UpdateInfoPos();

	this->UpdatePoint(this->pointMap->indexOf(this->currentPoint));
}

void ScalarColorMappingGraphicsView::AddLineFirst(QPoint pos) {
	QGraphicsLineItem* line = new QGraphicsLineItem();
	QPen pen = line->pen();
	pen.setColor(QColor(0, 0, 0, 0));
	pen.setWidth(3);
	line->setPen(pen);
	line->setLine(QLineF(QPointF(this->mapToScene(pos).x(), this->pointMap->value(1)->rect().center().y()), this->pointMap->value(1)->rect().center()));
	line->setZValue(0.5);
	this->pScene->addItem(line);
	this->lineMap->insert(0, line);
	this->AddInfoFirst();
}

void ScalarColorMappingGraphicsView::AddLineLast(QPoint pos) {
	QGraphicsLineItem* line = new QGraphicsLineItem();
	QPen pen = line->pen();
	pen.setColor(QColor(0, 0, 0, 0));
	pen.setWidth(3);
	line->setPen(pen);
	line->setLine(QLineF(this->pointMap->value(this->pointMap->size() - 2)->rect().center(), QPointF(this->mapToScene(pos).x(), this->pointMap->last()->rect().center().y())));
	line->setZValue(0.5); 
	this->pScene->addItem(line);
	this->lineMap->push_back(line);
	this->AddInfoEnd();
}

void ScalarColorMappingGraphicsView::SplitLine(QPoint pos, QVector<QGraphicsLineItem*>::iterator iter, int index) {
	QGraphicsLineItem* line1 = new QGraphicsLineItem();
	QPen pen1 = line1->pen();
	pen1.setColor(QColor(0, 0, 0, 0));
	pen1.setWidth(3);
	line1->setPen(pen1); 
	line1->setZValue(0.5);
	line1->setLine(QLineF(this->pointMap->value(index - 1)->rect().center(), QPointF(this->mapToScene(pos).x(), this->pointMap->value(index + 1)->rect().center().y())));

	QGraphicsLineItem* line2 = new QGraphicsLineItem();
	QPen pen2 = line2->pen();
	pen2.setColor(QColor(0, 0, 0, 0));
	pen2.setWidth(3);
	line2->setPen(pen2);
	line2->setZValue(0.5);
	line2->setLine(QLineF(QPointF(this->mapToScene(pos).x(), this->pointMap->value(index + 1)->rect().center().y()), this->pointMap->value(index + 1)->rect().center()));

	this->pScene->removeItem(this->lineMap->value(index - 1));
	this->lineMap->erase(iter);

	this->pScene->addItem(line1);
	this->lineMap->insert(index - 1, line1);

	this->pScene->addItem(line2);
	this->lineMap->insert(index, line2);

	this->SplitInfo(index);
}

void ScalarColorMappingGraphicsView::UpdateLine() {
	if (this->lineMap->isEmpty()) return;

	int index = this->pointMap->indexOf(this->currentPoint);

	if (index > 0) {
		QLineF line = this->lineMap->value(index - 1)->line();
		line.setP2(this->currentPoint->rect().center());
		this->lineMap->value(index - 1)->setLine(line);
	}

	if (index < this->pointMap->size() - 1) {
		QLineF line = this->lineMap->value(index)->line();
		line.setP1(this->currentPoint->rect().center());
		this->lineMap->value(index)->setLine(line);
	}
}

void ScalarColorMappingGraphicsView::DeleteCurrentPoint() {
	if (!this->currentPoint) return;

	this->DeletePoint(this->pointMap->indexOf(this->currentPoint));

	int index = this->pointMap->indexOf(this->currentPoint);
	this->pScene->removeItem(this->currentPoint);
	this->pointMap->erase(this->pointMap->begin() + index);

	this->pointColorMap->remove(this->currentPoint);

	this->currentPoint = NULL;

	if (this->pointMap->size() == 0) {
		this->DeleteAll();
		emit PointMapSize(0);
		return;
	}

	PointMapSize(this->pointMap->size() - 1);

	this->DeleteLine(index);
}

void ScalarColorMappingGraphicsView::DeleteLine(int index) {
	if (this->lineMap->isEmpty()) return;
	if (index == 0) {
		this->pScene->removeItem(this->lineMap->value(0));
		this->lineMap->erase(this->lineMap->begin());
	} else if (index == this->pointMap->size()) {
		this->pScene->removeItem(this->lineMap->last());
		this->lineMap->erase(this->lineMap->end() - 1);
	} else {
		this->pScene->removeItem(this->lineMap->value(index));
		this->pScene->removeItem(this->lineMap->value(index - 1));
		this->lineMap->erase(this->lineMap->begin() + index);
		this->lineMap->erase(this->lineMap->begin() + index - 1);

		QGraphicsLineItem* line = new QGraphicsLineItem();
		QPen pen = line->pen();
		pen.setColor(QColor(0, 0, 0, 0));
		pen.setWidth(3);
		line->setPen(pen);
		line->setLine(QLineF(this->pointMap->value(index - 1)->rect().center(), this->pointMap->value(index)->rect().center()));
		line->setZValue(0.5);
		this->pScene->addItem(line);
		this->lineMap->insert(index - 1, line);
	}
	this->DeleteInfo(index);
}

void ScalarColorMappingGraphicsView::DeleteAll() {
	QVector<QGraphicsEllipseItem*>::iterator iterPoint;
	for (iterPoint = this->pointMap->begin(); iterPoint != this->pointMap->end(); iterPoint++) {
		this->pScene->removeItem(*iterPoint);
	}
	this->pointMap->swap(QVector<QGraphicsEllipseItem*>());
	this->pointMap->clear();

	QVector<QGraphicsLineItem*>::iterator iterLine;
	for (iterLine = this->lineMap->begin(); iterLine != this->lineMap->end(); iterLine++) {
		this->pScene->removeItem(*iterLine);
	}
	this->lineMap->swap(QVector<QGraphicsLineItem*>());
	this->lineMap->clear();

	QVector<QGraphicsPolygonItem*>::iterator iterInfo;
	for (iterInfo = this->infoMap->begin(); iterInfo != this->infoMap->end(); iterInfo++) {
		this->pScene->removeItem(*iterInfo);
	}
	this->infoMap->swap(QVector<QGraphicsPolygonItem*>());
	this->infoMap->clear();
}

void ScalarColorMappingGraphicsView::CreateInfo() {
	QGraphicsPolygonItem* infoFirst = new QGraphicsPolygonItem();
	QPolygonF polygonFirst;
	polygonFirst
		<< this->mapToScene(this->rect().topLeft()) 
		<< QPointF(this->pointMap->value(0)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
		<< QPointF(this->pointMap->value(0)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y())
		<< this->mapToScene(this->rect().bottomLeft());
	infoFirst->setPolygon(polygonFirst);
	QPen penInfoFirst = infoFirst->pen();
	penInfoFirst.setWidth(0);
	penInfoFirst.setColor(QColor(0, 0, 0, 0));
	infoFirst->setPen(penInfoFirst);
	infoFirst->setBrush(QBrush(*currentColor));
	infoFirst->setZValue(0.0);

	QGraphicsPolygonItem* infoEnd = new QGraphicsPolygonItem();
	QPolygonF polygonEnd;
	polygonEnd
		<< QPointF(this->pointMap->value(0)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
		<< this->mapToScene(this->rect().topRight())
		<< this->mapToScene(this->rect().bottomRight())
		<< QPointF(this->pointMap->value(0)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y()) ;
	infoEnd->setPolygon(polygonEnd);
	QPen penInfoEnd = infoEnd->pen();
	penInfoEnd.setWidth(0);
	penInfoEnd.setColor(QColor(0, 0, 0, 0));
	infoEnd->setPen(penInfoEnd);
	infoEnd->setBrush(QBrush(*currentColor));
	infoEnd->setZValue(0.0);

	this->pScene->addItem(infoFirst);
	this->infoMap->push_back(infoFirst);

	this->pScene->addItem(infoEnd);
	this->infoMap->push_back(infoEnd);

	this->ColorChanged();
}

void ScalarColorMappingGraphicsView::AddInfoFirst() {
	this->pScene->removeItem(this->infoMap->value(0));
	this->infoMap->erase(this->infoMap->begin());

	QGraphicsPolygonItem* infoFirst = new QGraphicsPolygonItem();
	QPolygonF polygonFirst;
	polygonFirst
		<< this->mapToScene(this->rect().topLeft())
		<< QPointF(this->pointMap->value(0)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
		<< QPointF(this->pointMap->value(0)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y())
		<< this->mapToScene(this->rect().bottomLeft());
	infoFirst->setPolygon(polygonFirst);
	QPen penInfoFirst = infoFirst->pen();
	penInfoFirst.setWidth(0);
	penInfoFirst.setColor(QColor(0, 0, 0, 0));
	infoFirst->setPen(penInfoFirst);
	infoFirst->setBrush(QBrush(this->pointColorMap->value(this->pointMap->value(0))));
	infoFirst->setZValue(0.0);

	QGraphicsPolygonItem* infoSecond = new QGraphicsPolygonItem();
	QPolygonF polygonSecond;
	polygonSecond
		<< QPointF(this->pointMap->value(0)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
		<< QPointF(this->pointMap->value(1)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
		<< QPointF(this->pointMap->value(1)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y())
		<< QPointF(this->pointMap->value(0)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y());
	infoSecond->setPolygon(polygonSecond);
	QPen penInfoSecond = infoSecond->pen();
	penInfoSecond.setWidth(0);
	penInfoSecond.setColor(QColor(0,0,0,0));
	infoSecond->setPen(penInfoSecond);
	QLinearGradient linear(this->pointMap->value(0)->rect().center(), this->pointMap->value(1)->rect().center());
	linear.setColorAt(0, this->pointColorMap->value(this->pointMap->value(0)));
	linear.setColorAt(1, this->pointColorMap->value(this->pointMap->value(1)));
	linear.setSpread(QGradient::PadSpread);
	infoSecond->setBrush(QBrush(linear));
	infoSecond->setZValue(0.0);

	this->pScene->addItem(infoFirst);
	this->infoMap->insert(0, infoFirst);

	this->pScene->addItem(infoSecond);
	this->infoMap->insert(1, infoSecond);

	this->ColorChanged();
}

void ScalarColorMappingGraphicsView::AddInfoEnd() {
	this->pScene->removeItem(this->infoMap->last());
	this->infoMap->erase(this->infoMap->end() - 1);

	QGraphicsPolygonItem* infoSecond = new QGraphicsPolygonItem();
	QPolygonF polygonSecond;
	polygonSecond
		<< QPointF(this->pointMap->value(this->pointMap->size() - 2)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
		<< QPointF(this->pointMap->last()->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
		<< QPointF(this->pointMap->last()->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y())
		<< QPointF(this->pointMap->value(this->pointMap->size() - 2)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y());
	infoSecond->setPolygon(polygonSecond);
	QPen penInfoSecond = infoSecond->pen();
	penInfoSecond.setWidth(0);
	penInfoSecond.setColor(QColor(0, 0, 0, 0));
	infoSecond->setPen(penInfoSecond);
	QLinearGradient linear(this->pointMap->value(this->pointMap->size() - 2)->rect().center(), this->pointMap->last()->rect().center());
	linear.setColorAt(0, this->pointColorMap->value(this->pointMap->value(this->pointMap->size() - 2)));
	linear.setColorAt(1, this->pointColorMap->value(this->pointMap->last()));
	linear.setSpread(QGradient::PadSpread);
	infoSecond->setBrush(QBrush(linear));
	infoSecond->setZValue(0.0);

	QGraphicsPolygonItem* infoEnd = new QGraphicsPolygonItem();
	QPolygonF polygonEnd;
	polygonEnd
		<< QPointF(this->pointMap->last()->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
		<< this->mapToScene(this->rect().topRight())
		<< this->mapToScene(this->rect().bottomRight())
		<< QPointF(this->pointMap->last()->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y());
	infoEnd->setPolygon(polygonEnd);
	QPen penInfoEnd = infoEnd->pen();
	penInfoEnd.setWidth(0);
	penInfoEnd.setColor(QColor(0, 0, 0, 0));
	infoEnd->setPen(penInfoEnd);
	infoEnd->setBrush(QBrush(this->pointColorMap->value(this->pointMap->last())));
	infoEnd->setZValue(0.0);

	this->pScene->addItem(infoSecond);
	this->infoMap->push_back(infoSecond);

	this->pScene->addItem(infoEnd);
	this->infoMap->push_back(infoEnd);

	this->ColorChanged();
}

void ScalarColorMappingGraphicsView::SplitInfo(int index) {
	this->pScene->removeItem(this->infoMap->value(index));
	this->infoMap->erase(this->infoMap->begin() + index);

	QGraphicsPolygonItem* infoFirst = new QGraphicsPolygonItem();
	QPolygonF polygonFirst;
	polygonFirst
		<< QPointF(this->pointMap->value(index - 1)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
		<< QPointF(this->pointMap->value(index)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
		<< QPointF(this->pointMap->value(index)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y())
		<< QPointF(this->pointMap->value(index - 1)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y());
	infoFirst->setPolygon(polygonFirst);
	QPen penInfoFirst = infoFirst->pen();
	penInfoFirst.setWidth(0);
	penInfoFirst.setColor(QColor(0, 0, 0, 0));
	infoFirst->setPen(penInfoFirst);

	QLinearGradient linearFirst(this->pointMap->value(index - 1)->rect().center(), this->pointMap->value(index)->rect().center());
	linearFirst.setColorAt(0, this->pointColorMap->value(this->pointMap->value(index - 1)));
	linearFirst.setColorAt(1, this->pointColorMap->value(this->pointMap->value(index)));
	linearFirst.setSpread(QGradient::PadSpread);

	infoFirst->setBrush(QBrush(linearFirst));
	infoFirst->setZValue(0.0);

	QGraphicsPolygonItem* infoEnd = new QGraphicsPolygonItem();
	QPolygonF polygonEnd;
	polygonEnd
		<< QPointF(this->pointMap->value(index)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
		<< QPointF(this->pointMap->value(index + 1)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
		<< QPointF(this->pointMap->value(index + 1)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y())
		<< QPointF(this->pointMap->value(index)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y());
	infoEnd->setPolygon(polygonEnd);
	QPen penInfoEnd = infoEnd->pen();
	penInfoEnd.setWidth(0);
	penInfoEnd.setColor(QColor(0, 0, 0, 0));
	infoEnd->setPen(penInfoEnd);

	QLinearGradient linearEnd(this->pointMap->value(index)->rect().center(), this->pointMap->value(index + 1)->rect().center());
	linearEnd.setColorAt(0, this->pointColorMap->value(this->pointMap->value(index)));
	linearEnd.setColorAt(1, this->pointColorMap->value(this->pointMap->value(index + 1)));
	linearEnd.setSpread(QGradient::PadSpread);

	infoEnd->setBrush(QBrush(linearEnd));
	infoEnd->setZValue(0.0);

	this->pScene->addItem(infoFirst);
	this->infoMap->insert(index, infoFirst);

	this->pScene->addItem(infoEnd);
	this->infoMap->insert(index + 1, infoEnd);

	this->ColorChanged();
}

void ScalarColorMappingGraphicsView::UpdateInfoColor(int index) {
	if (this->infoMap->isEmpty()) return;

	QGraphicsPolygonItem* infoFirst = this->infoMap->value(index);
	QGraphicsPolygonItem* infoEnd = this->infoMap->value(index + 1);
	
	if (index == 0) {
		infoFirst->setBrush(QBrush(this->pointColorMap->value(this->pointMap->value(index))));
	} else {
		QLinearGradient linearFirst(this->pointMap->value(index - 1)->rect().center(), this->pointMap->value(index)->rect().center());
		linearFirst.setColorAt(0, this->pointColorMap->value(this->pointMap->value(index - 1)));
		linearFirst.setColorAt(1, this->pointColorMap->value(this->pointMap->value(index)));
		linearFirst.setSpread(QGradient::PadSpread);
		infoFirst->setBrush(QBrush(linearFirst));
	}

	if (index == this->pointMap->size() - 1) {
		infoEnd->setBrush(QBrush(this->pointColorMap->value(this->pointMap->value(index))));
	} else {
		QLinearGradient linearEnd(this->pointMap->value(index)->rect().center(), this->pointMap->value(index + 1)->rect().center());
		linearEnd.setColorAt(0, this->pointColorMap->value(this->pointMap->value(index)));
		linearEnd.setColorAt(1, this->pointColorMap->value(this->pointMap->value(index + 1)));
		linearEnd.setSpread(QGradient::PadSpread);
		infoEnd->setBrush(QBrush(linearEnd));
	}

	this->ColorChanged();
}

void ScalarColorMappingGraphicsView::UpdateInfoPos() {
	if (this->infoMap->isEmpty()) return;

	int index = this->pointMap->indexOf(this->currentPoint);

	QGraphicsPolygonItem* infoFirst = this->infoMap->value(index);
	QGraphicsPolygonItem* infoEnd = this->infoMap->value(index + 1);
	QPolygonF polygonFirst;
	QPolygonF polygonEnd;

	if (index == 0) {
		polygonFirst
			<< this->mapToScene(this->rect().topLeft())
			<< QPointF(this->pointMap->value(0)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
			<< QPointF(this->pointMap->value(0)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y())
			<< this->mapToScene(this->rect().bottomLeft());
		infoFirst->setPolygon(polygonFirst);
		infoFirst->setBrush(QBrush(this->pointColorMap->value(this->pointMap->value(index))));
	}
	else {
		polygonFirst
			<< QPointF(this->pointMap->value(index - 1)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
			<< QPointF(this->pointMap->value(index)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
			<< QPointF(this->pointMap->value(index)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y())
			<< QPointF(this->pointMap->value(index - 1)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y());
		infoFirst->setPolygon(polygonFirst);

		QLinearGradient linearFirst(this->pointMap->value(index - 1)->rect().center(), this->pointMap->value(index)->rect().center());
		linearFirst.setColorAt(0, this->pointColorMap->value(this->pointMap->value(index - 1)));
		linearFirst.setColorAt(1, this->pointColorMap->value(this->pointMap->value(index)));
		linearFirst.setSpread(QGradient::PadSpread);
		infoFirst->setBrush(QBrush(linearFirst));
	}

	if (index == this->pointMap->size() - 1) {
		polygonEnd
			<< QPointF(this->pointMap->value(0)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
			<< this->mapToScene(this->rect().topRight())
			<< this->mapToScene(this->rect().bottomRight())
			<< QPointF(this->pointMap->value(0)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y());
		infoEnd->setPolygon(polygonEnd);
		infoEnd->setBrush(QBrush(this->pointColorMap->value(this->pointMap->value(index))));
	}
	else {
		polygonEnd
			<< QPointF(this->pointMap->value(index)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
			<< QPointF(this->pointMap->value(index + 1)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
			<< QPointF(this->pointMap->value(index + 1)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y())
			<< QPointF(this->pointMap->value(index)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y());
		infoEnd->setPolygon(polygonEnd);

		QLinearGradient linearEnd(this->pointMap->value(index)->rect().center(), this->pointMap->value(index + 1)->rect().center());
		linearEnd.setColorAt(0, this->pointColorMap->value(this->pointMap->value(index)));
		linearEnd.setColorAt(1, this->pointColorMap->value(this->pointMap->value(index + 1)));
		linearEnd.setSpread(QGradient::PadSpread);
		infoEnd->setBrush(QBrush(linearEnd));
	}

	this->ColorChanged();
}

void ScalarColorMappingGraphicsView::DeleteInfo(int index) {
	if (this->infoMap->isEmpty()) return;
	if (this->infoMap->size() == 2) {
		QVector<QGraphicsPolygonItem*>::iterator iterInfo;
		for (iterInfo = this->infoMap->begin(); iterInfo != this->infoMap->end(); iterInfo++) {
			this->pScene->removeItem(*iterInfo);
		}
		this->infoMap->swap(QVector<QGraphicsPolygonItem*>());
		this->infoMap->clear();
	} else if (index == 0) {
		this->pScene->removeItem(this->infoMap->value(0));
		this->pScene->removeItem(this->infoMap->value(1));
		this->infoMap->erase(this->infoMap->begin());
		this->infoMap->erase(this->infoMap->begin());

		QGraphicsPolygonItem* infoFirst = new QGraphicsPolygonItem();
		QPolygonF polygonFirst;
		polygonFirst
			<< this->mapToScene(this->rect().topLeft())
			<< QPointF(this->pointMap->value(0)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
			<< QPointF(this->pointMap->value(0)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y())
			<< this->mapToScene(this->rect().bottomLeft());
		infoFirst->setPolygon(polygonFirst);
		QPen penInfoFirst = infoFirst->pen();
		penInfoFirst.setWidth(0);
		penInfoFirst.setColor(QColor(0, 0, 0, 0));
		infoFirst->setPen(penInfoFirst);
		infoFirst->setBrush(QBrush(this->pointColorMap->value(this->pointMap->value(0))));
		infoFirst->setZValue(0.0);

		this->pScene->addItem(infoFirst);
		this->infoMap->push_back(infoFirst);
	} else if (index == this->pointMap->size()) {
		this->pScene->removeItem(this->infoMap->last());
		this->infoMap->erase(this->infoMap->end() - 1);
		this->pScene->removeItem(this->infoMap->last());
		this->infoMap->erase(this->infoMap->end() - 1);

		QGraphicsPolygonItem* infoEnd = new QGraphicsPolygonItem();
		QPolygonF polygonEnd;
		polygonEnd
			<< QPointF(this->pointMap->last()->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
			<< this->mapToScene(this->rect().topRight())
			<< this->mapToScene(this->rect().bottomRight())
			<< QPointF(this->pointMap->last()->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y());
		infoEnd->setPolygon(polygonEnd);
		QPen penInfoEnd = infoEnd->pen();
		penInfoEnd.setWidth(0);
		penInfoEnd.setColor(QColor(0, 0, 0, 0));
		infoEnd->setPen(penInfoEnd);
		infoEnd->setBrush(QBrush(this->pointColorMap->value(this->pointMap->last())));
		infoEnd->setZValue(0.0);

		this->pScene->addItem(infoEnd);
		this->infoMap->push_back(infoEnd);
	} else {
		this->pScene->removeItem(this->infoMap->value(index));
		this->pScene->removeItem(this->infoMap->value(index + 1));
		this->infoMap->erase(this->infoMap->begin() + index);
		this->infoMap->erase(this->infoMap->begin() + index);

		QGraphicsPolygonItem* info = new QGraphicsPolygonItem();
		QPolygonF polygon;
		polygon
			<< QPointF(this->pointMap->value(index - 1)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
			<< QPointF(this->pointMap->value(index)->rect().center().x(), this->mapToScene(this->rect().topRight()).y())
			<< QPointF(this->pointMap->value(index)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y())
			<< QPointF(this->pointMap->value(index - 1)->rect().center().x(), this->mapToScene(this->rect().bottomRight()).y());
		info->setPolygon(polygon);
		QPen penInfo = info->pen();
		penInfo.setWidth(0);
		penInfo.setColor(QColor(0, 0, 0, 0));
		info->setPen(penInfo);

		QLinearGradient linear(this->pointMap->value(index - 1)->rect().center(), this->pointMap->value(index)->rect().center());
		linear.setColorAt(0, this->pointColorMap->value(this->pointMap->value(index - 1)));
		linear.setColorAt(1, this->pointColorMap->value(this->pointMap->value(index)));
		linear.setSpread(QGradient::PadSpread);

		info->setBrush(QBrush(linear));
		info->setZValue(0.0);

		this->pScene->addItem(info);
		this->infoMap->insert(index, info);
	}

	this->ColorChanged();
}

void ScalarColorMappingGraphicsView::SetCurrentColor(QColor color) {
	*(this->currentColor) = color;
	if (this->currentPoint) {
		(*(this->pointColorMap))[this->currentPoint] = color;
		int index = this->pointMap->indexOf(this->currentPoint);
		this->UpdateInfoColor(index);
		this->UpdatePoint(this->pointMap->indexOf(this->currentPoint));
	}
}

void ScalarColorMappingGraphicsView::SetCurrentPoint(int index) {
	if (index > this->pointMap->size() - 1) return;
	if (this->currentPoint) {
		QPen penOld = this->currentPoint->pen();
		penOld.setColor(Qt::black);
		penOld.setWidth(3);
		this->currentPoint->setPen(penOld);
	}
	this->currentPoint = this->pointMap->value(index);
	QPen pen = this->currentPoint->pen();
	pen.setColor(Qt::blue);
	pen.setWidth(3);
	this->currentPoint->setPen(pen);
	this->CurrentPoint(index);
	this->CurrentPointPos(this->currentPoint->rect().center().x());
}

qreal ScalarColorMappingGraphicsView::GetCurrentPointPosX() {
	if (!this->currentPoint) return 0;
	return this->currentPoint->rect().center().x();
}

QVector<QGraphicsEllipseItem*>* ScalarColorMappingGraphicsView::GetPointList() {
	return this->pointMap;
}

QMap<QGraphicsEllipseItem*, QColor>* ScalarColorMappingGraphicsView::GetColorInfoMap() {
	return this->pointColorMap;
}

void ScalarColorMappingGraphicsView::ResetChart(double** element, ulong size) {
	for (int i = 0; i < size; i++) {
		QColor color;
		color.setRedF(element[i][1]);
		color.setGreenF(element[i][2]);
		color.setBlueF(element[i][3]);
		this->SetCurrentColor(color);

		QPointF point;
		point.setX((element[i][0] + qreal(4000.0)) * (this->mapToScene(this->rect()).boundingRect().width()) / qreal(8000.0) + this->mapToScene(this->rect()).boundingRect().left());
		point.setY(this->rect().center().y());

		this->AddPoint(this->mapFromScene(point));
	}
	this->SetCurrentColor(QColor(0, 0, 0));
}

void ScalarColorMappingGraphicsView::mousePressEvent(QMouseEvent* event) {
	if (LEF) {
		this->mouse->setRect(QRectF(
			this->mapToScene(event->pos()).x() - this->rect().width() / 120.0,
			this->mapToScene(event->pos()).y() - this->rect().width() / 120.0,
			this->rect().width() / 60.0,
			this->rect().width() / 60.0));
		this->pScene->addItem(this->mouse);
		QList<QGraphicsItem*> list = this->pScene->collidingItems(this->mouse);
		if (!list.isEmpty()) {
			QList<QGraphicsItem*>::iterator iter;
			for (iter = list.begin(); iter != list.end(); iter++) {
				if (this->pointMap->contains((QGraphicsEllipseItem*)(*iter))) {
					this->SetCurrentPoint(this->pointMap->indexOf((QGraphicsEllipseItem*)(*iter)));
					this->pScene->removeItem(this->mouse); 
					this->status = this->MoveCurrentPoint;
					return;
				}
			}
		} 
		this->AddPoint(event->pos());
		this->pScene->removeItem(this->mouse);
		this->status = this->AddNewPoint;
	}
}

void ScalarColorMappingGraphicsView::mouseDoubleClickEvent(QMouseEvent* event) {
}

void ScalarColorMappingGraphicsView::mouseMoveEvent(QMouseEvent* event) {
	if (this->status == this->Normel) return;
	this->UpdateCurrentPoint(event->pos());
}

void ScalarColorMappingGraphicsView::mouseReleaseEvent(QMouseEvent* event) {
	this->status = this->Normel;
}

void ScalarColorMappingGraphicsView::wheelEvent(QWheelEvent* event) {
}

void ScalarColorMappingGraphicsView::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Delete) {
		if (!this->currentPoint) return;
		this->DeleteCurrentPoint();
	}
}