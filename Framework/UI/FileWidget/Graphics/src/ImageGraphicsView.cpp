#include "..\include\ImageGraphicsView.h"

ImageGraphicsView::ImageGraphicsView(QWidget *parent)
	: QGraphicsView(parent) {
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	this->describe = "";

	this->isFlipUpDown = false;
	this->isFlipLeftRight = false;

	this->pixLayer = 0.5;
	this->zoom = 1;
	this->pScene = new QGraphicsScene();
	this->setScene(this->pScene);

	this->rule = QPixmap(".//Resource//FileWidget//scaleBar.png");
	
	vtkSmartPointer<vtkImageData> image = vtkSmartPointer<vtkImageData>::New();
}

ImageGraphicsView::~ImageGraphicsView() {
	this->pScene->clear();
	delete this->pScene;
	this->pScene = Q_NULLPTR;
	this->img = Q_NULLPTR;
	this->renderObj = Q_NULLPTR;
	this->imageFilter = Q_NULLPTR;

	this->upOri = Q_NULLPTR;
	this->downOri = Q_NULLPTR;
	this->leftOri = Q_NULLPTR;
	this->rightOri = Q_NULLPTR;

	this->Frame = Q_NULLPTR;
	this->PitMag = Q_NULLPTR;
	this->SeriesDescription = Q_NULLPTR;
	this->ImageNo = Q_NULLPTR;

	this->Name = Q_NULLPTR;
	this->PID = Q_NULLPTR;
	this->DOB = Q_NULLPTR;
	this->SEX = Q_NULLPTR;

	this->WindowWidthAndLevel = Q_NULLPTR;

	this->Hospital = Q_NULLPTR;

	this->ScaleBar = Q_NULLPTR;
}

void ImageGraphicsView::InitPos() {
	this->centerOn(this->pix->sceneBoundingRect().center());
	this->update();
}

void ImageGraphicsView::LoadVTKBuff() {
	this->pix = new QGraphicsPixmapItem();
	this->pix->setZValue(.0);

	this->img = this->vtkImageDataToQImage(this->renderObj->GetVtkData(2));
	if (!this->img) return;
	this->pix->setPixmap(QPixmap::fromImage(this->img->scaled(this->imageFilter->GetWidth(2), this->imageFilter->GetHeight(2))));
	this->pScene->addItem(this->pix);

	qreal winSizeRatio = (qreal)this->width() / this->height();
	qreal imgSizeRatio = (qreal)this->imageFilter->GetWidth(2) / this->imageFilter->GetHeight(2);

	if (winSizeRatio >= imgSizeRatio) {
		qreal scaleSize = (qreal)this->mapToScene(this->rect()).boundingRect().height() / this->pix->sceneBoundingRect().height();
		this->scale(scaleSize, scaleSize);
	}
	else {
		qreal scaleSize = (qreal)this->mapToScene(this->rect()).boundingRect().width() / this->pix->sceneBoundingRect().width();
		this->scale(scaleSize, scaleSize);
	}

	this->pix->setPos((this->mapToScene(this->rect()).boundingRect().width() - this->pix->sceneBoundingRect().width()) / 2.0,
		(this->mapToScene(this->rect()).boundingRect().height() - this->pix->sceneBoundingRect().height()) / 2.0);
	this->centerOn(this->pix->sceneBoundingRect().center());
}

void ImageGraphicsView::UpdataVTKBuff() {
	this->img = this->vtkImageDataToQImage(this->renderObj->GetVtkData(2));
	this->pix->setPixmap(QPixmap::fromImage(this->img->scaled(this->imageFilter->GetWidth(2), this->imageFilter->GetHeight(2))));
}

void ImageGraphicsView::SetRenderObj(VolumeRenderController* renderObj) {
	this->renderObj = renderObj;
}

void ImageGraphicsView::SetImageFilter(ImageFilterContorller* imageFilter) {
	this->imageFilter = imageFilter;
}

void ImageGraphicsView::SetDicomInfoSQL(DicomInfoTable* sql) {
	this->sql = sql;
}

void ImageGraphicsView::Scale(qreal step) {
	qreal factor = 1.0 + step / 500.0;
	this->zoom *= factor;
	if (this->zoom < 0.01) return;
	this->pix->setTransformOriginPoint(this->pix->boundingRect().center().x(), this->pix->boundingRect().center().y());
	this->pix->setScale(this->zoom);
}

void ImageGraphicsView::Move(QPointF delta) {
	this->pix->moveBy(delta.x(), delta.y());
}

void ImageGraphicsView::AdjustImg(QPointF mouseDelta) {
	if (qAbs(mouseDelta.x()) >= qAbs(mouseDelta.y())) {
		this->renderObj->ResetImgColorRanger(mouseDelta.x());
	}
	else {
		this->renderObj->ResetImgColorCenter(mouseDelta.y());
	}
	this->Reslice();
}

void ImageGraphicsView::Reslice() {
	this->img = this->vtkImageDataToQImage(this->renderObj->GetVtkData(2));
	if (!this->img) return;
	this->pix->setPixmap(QPixmap::fromImage(this->img->scaled(this->imageFilter->GetWidth(2), this->imageFilter->GetHeight(2))));
}

void ImageGraphicsView::Reslice(qreal slice) {
	if (slice <= 0) {
		this->pixLayer = 0.0;
		this->img = this->vtkImageDataToQImage(this->renderObj->ResliceVtkData(2, 0.0));
	}
	else if (slice >= 1) {
		this->pixLayer = 1.0;
		this->img = this->vtkImageDataToQImage(this->renderObj->ResliceVtkData(2, 1.0));
	}
	else {
		this->img = this->vtkImageDataToQImage(this->renderObj->ResliceVtkData(2, slice));
	}
	if (!this->img) return;
	this->pix->setPixmap(QPixmap::fromImage(this->img->scaled(this->imageFilter->GetWidth(2), this->imageFilter->GetHeight(2))));
}

void ImageGraphicsView::mousePressEvent(QMouseEvent* event) {
	this->lastMousePos = event->pos();
}

void ImageGraphicsView::mouseMoveEvent(QMouseEvent* event) {
	QPointF mouseDelta = mapToScene(event->pos()) - mapToScene(this->lastMousePos);
	if (LEF) {
		this->AdjustImg(mouseDelta);
		this->UpdateWindowWidthAndLevelInfo();
	} else if (MID) {
		this->Move(mouseDelta);
	} else if (RIG) {
		this->Scale(mouseDelta.y());
		this->UpdateFitMagInfo();
		this->UpdateScaleBar();
	}
	this->lastMousePos = event->pos();
}

void ImageGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
	this->setCursor(Qt::ArrowCursor);
}

void ImageGraphicsView::wheelEvent(QWheelEvent* event) {
	int numValue = event->delta();
	qreal numDegrees = numValue / 8.0;
	qreal numSteps = numDegrees / 15.0;
	qreal step = numSteps / 100.0;
	this->pixLayer += step;
	this->Reslice(this->pixLayer);
	this->UpdateFrameInfo();
}

void ImageGraphicsView::SetOriLabel() {
	this->upOri = new QGraphicsTextItem();
	this->downOri = new QGraphicsTextItem();
	this->leftOri = new QGraphicsTextItem();
	this->rightOri = new QGraphicsTextItem();

	this->upOri->setPlainText("A");
	this->downOri->setPlainText("P");
	this->leftOri->setPlainText("R");
	this->rightOri->setPlainText("L");

	this->upOri->setDefaultTextColor(QColor(255, 255, 255));
	this->downOri->setDefaultTextColor(QColor(255, 255, 255));
	this->leftOri->setDefaultTextColor(QColor(255, 255, 255));
	this->rightOri->setDefaultTextColor(QColor(255, 255, 255));

	QFont font;
	font.setPixelSize(16.0 / this->transform().m11());
	this->upOri->setFont(font);
	this->downOri->setFont(font);
	this->leftOri->setFont(font);
	this->rightOri->setFont(font);

	this->upOri->setPos((this->mapToScene(this->rect()).boundingRect().width() - this->upOri->boundingRect().width()) / 2, this->mapToScene(this->rect()).boundingRect().top() + this->upOri->boundingRect().height() + 120 / this->transform().m11());
	this->downOri->setPos((this->mapToScene(this->rect()).boundingRect().width() - this->downOri->boundingRect().width()) / 2, this->mapToScene(this->rect()).boundingRect().bottom() - 120 / this->transform().m11());
	this->leftOri->setPos(this->mapToScene(this->rect()).boundingRect().left() + 80 / this->transform().m11(), (this->mapToScene(this->rect()).boundingRect().height() - this->leftOri->boundingRect().height()) / 2);
	this->rightOri->setPos(this->mapToScene(this->rect()).boundingRect().right() - this->rightOri->boundingRect().width() - 80 / this->transform().m11(), (this->mapToScene(this->rect()).boundingRect().height() - this->rightOri->boundingRect().height()) / 2);

	this->upOri->setZValue(0.5);
	this->downOri->setZValue(0.5);
	this->leftOri->setZValue(0.5);
	this->rightOri->setZValue(0.5);

	this->pScene->addItem(this->upOri);
	this->pScene->addItem(this->downOri);
	this->pScene->addItem(this->leftOri);
	this->pScene->addItem(this->rightOri);
}

void ImageGraphicsView::LoadCornerInfo() {
	this->LoadTopLeftCornerInfo();
	this->LoadTopRightCornerInfo();
	this->LoadButtomLeftCornerInfo();
	this->LoadButtomRightCornerInfo();
}

void ImageGraphicsView::LoadTopLeftCornerInfo() {
	this->Frame = new QGraphicsTextItem();
	this->PitMag = new QGraphicsTextItem();
	this->SeriesDescription = new QGraphicsTextItem();
	this->ImageNo = new QGraphicsTextItem();
	
	DciomObject* head = this->imageFilter->GetDicomHeader();
	this->Frame->setPlainText(QString("Frame: ") + QString::number((int)(this->pixLayer * head->nz)) + QString("/") + QString::number(head->nz));
	this->PitMag->setPlainText(QString("PitMag: ") + QString::number(this->zoom * 100.0) + QString("%"));
	this->SeriesDescription->setPlainText(QString("SeriesDescription: ") + QString(head->seriesDescription.c_str()));
	this->ImageNo->setPlainText(QString("ImageNo: ")+ QString::number(head->imageNO));

	this->Frame->setDefaultTextColor(QColor(255, 255, 255));
	this->PitMag->setDefaultTextColor(QColor(255, 255, 255));
	this->SeriesDescription->setDefaultTextColor(QColor(255, 255, 255));
	this->ImageNo->setDefaultTextColor(QColor(255, 255, 255));

	QFont font;
	font.setPixelSize(16.0 / this->transform().m11());
	this->Frame->setFont(font);
	this->PitMag->setFont(font);
	this->SeriesDescription->setFont(font);
	this->ImageNo->setFont(font);

	this->Frame->setPos(0, this->mapToScene(this->rect()).boundingRect().top() + 16 / this->transform().m11());
	this->PitMag->setPos(0, this->mapToScene(this->rect()).boundingRect().top() + 32 / this->transform().m11());
	this->SeriesDescription->setPos(0, this->mapToScene(this->rect()).boundingRect().top() + 48 / this->transform().m11());
	this->ImageNo->setPos(0, this->mapToScene(this->rect()).boundingRect().top() + 64 / this->transform().m11());

	this->Frame->setZValue(1.0);
	this->PitMag->setZValue(1.0);
	this->SeriesDescription->setZValue(1.0);
	this->ImageNo->setZValue(1.0);

	this->pScene->addItem(this->Frame);
	this->pScene->addItem(this->PitMag);
	this->pScene->addItem(this->SeriesDescription);
	this->pScene->addItem(this->ImageNo);
}

void ImageGraphicsView::LoadTopRightCornerInfo() {
	this->Name = new QGraphicsTextItem();
	this->PID = new QGraphicsTextItem();
	this->DOB = new QGraphicsTextItem();
	this->SEX = new QGraphicsTextItem();

	DciomObject* head = this->imageFilter->GetDicomHeader();
	this->Name->setPlainText(QString(head->patientName.c_str()));
	this->PID->setPlainText(QString("PID: ") + QString(head->patientId.c_str()));
	this->DOB->setPlainText(QString("DOB: ") + QString(head->patientBirthDate.c_str()));
	this->SEX->setPlainText(QString("SEX: ") + QString(head->patientSex.c_str()));

	this->Name->setDefaultTextColor(QColor(255, 255, 255));
	this->PID->setDefaultTextColor(QColor(255, 255, 255));
	this->DOB->setDefaultTextColor(QColor(255, 255, 255));
	this->SEX->setDefaultTextColor(QColor(255, 255, 255));

	QFont font;
	font.setPixelSize(16.0 / this->transform().m11());
	this->Name->setFont(font);
	this->PID->setFont(font);
	this->DOB->setFont(font);
	this->SEX->setFont(font);

	this->Name->setPos(this->mapToScene(this->rect()).boundingRect().right() - 240 / this->transform().m11(), this->mapToScene(this->rect()).boundingRect().top() + 16 / this->transform().m11());
	this->PID->setPos(this->mapToScene(this->rect()).boundingRect().right() - 240 / this->transform().m11(), this->mapToScene(this->rect()).boundingRect().top() + 32 / this->transform().m11());
	this->DOB->setPos(this->mapToScene(this->rect()).boundingRect().right() - 240 / this->transform().m11(), this->mapToScene(this->rect()).boundingRect().top() + 48 / this->transform().m11());
	this->SEX->setPos(this->mapToScene(this->rect()).boundingRect().right() - 240 / this->transform().m11(), this->mapToScene(this->rect()).boundingRect().top() + 64 / this->transform().m11());

	this->Name->setZValue(1.0);
	this->PID->setZValue(1.0);
	this->DOB->setZValue(1.0);
	this->SEX->setZValue(1.0);

	this->pScene->addItem(this->Name);
	this->pScene->addItem(this->PID);
	this->pScene->addItem(this->DOB);
	this->pScene->addItem(this->SEX);
}

void ImageGraphicsView::LoadButtomLeftCornerInfo() {
	this->WindowWidthAndLevel = new QGraphicsTextItem();

	DciomObject* head = this->imageFilter->GetDicomHeader();
	this->WindowWidthAndLevel->setPlainText(QString("W: ") + QString::number(this->renderObj->GetImgColorRanger()) + QString("  ") + QString("C: ") + QString::number(this->renderObj->GetImgColorCenter()));

	this->WindowWidthAndLevel->setDefaultTextColor(QColor(255, 255, 255));

	QFont font;
	font.setPixelSize(16.0 / this->transform().m11());
	this->WindowWidthAndLevel->setFont(font);

	this->WindowWidthAndLevel->setPos(0, this->mapToScene(this->rect()).boundingRect().bottom() - 6);

	this->WindowWidthAndLevel->setZValue(1.0);

	this->pScene->addItem(this->WindowWidthAndLevel);
}

void ImageGraphicsView::LoadButtomRightCornerInfo() {
	this->Hospital = new QGraphicsTextItem();

	DciomObject* head = this->imageFilter->GetDicomHeader();
	this->Hospital->setPlainText(QString(head->institution.c_str()));

	this->Hospital->setDefaultTextColor(QColor(255, 255, 255));

	QFont font;
	font.setPixelSize(16.0 / this->transform().m11());
	this->Hospital->setFont(font);

	this->Hospital->setPos(this->mapToScene(this->rect()).boundingRect().right() - this->Hospital->boundingRect().width(), this->mapToScene(this->rect()).boundingRect().bottom() - 6);

	this->Hospital->setZValue(1.0);

	this->pScene->addItem(this->Hospital);
}

void ImageGraphicsView::LoadScaleBar() {
	this->ScaleBar = new QGraphicsLineItem();

	qreal len = 200.0 * this->pix->boundingRect().height() * this->zoom / this->imageFilter->GetHeight(2);

	QPen pen = this->ScaleBar->pen();
	pen.setColor(QColor(255, 255, 255));
	pen.setWidth(1);
	this->ScaleBar->setPen(pen);
	this->ScaleBar->setLine(QLineF(
		this->mapToScene(this->rect()).boundingRect().right() - 60.0 / this->transform().m11(), this->mapToScene(this->rect()).boundingRect().center().y() - len / 2.0,
		this->mapToScene(this->rect()).boundingRect().right() - 60.0 / this->transform().m11(), this->mapToScene(this->rect()).boundingRect().center().y() + len / 2.0
	));
	this->ScaleBar->setZValue(1.0);
	this->pScene->addItem(this->ScaleBar);

	this->ScaleNum = new QGraphicsTextItem();
	this->ScaleNum->setPlainText("200mm");
	this->ScaleNum->setDefaultTextColor(QColor(255, 255, 255));
	QFont font;
	font.setPixelSize(16.0 / this->transform().m11());
	this->ScaleNum->setFont(font);
	this->ScaleNum->setPos(this->mapToScene(this->rect()).boundingRect().right() - this->ScaleNum->boundingRect().width() / 2 - 60 / this->transform().m11(), this->ScaleBar->line().p1().y() - this->ScaleNum->boundingRect().height());
	this->ScaleNum->setZValue(1.0);
	this->pScene->addItem(this->ScaleNum);
}

void ImageGraphicsView::UpdateFrameInfo() {
	DciomObject* head = this->imageFilter->GetDicomHeader();
	this->Frame->setPlainText(QString("Frame: ") + QString::number((int)(this->pixLayer * head->nz)) + QString("/") + QString::number(head->nz));
}

void ImageGraphicsView::UpdateScaleBar() {
	qreal len = 200.0 * this->pix->boundingRect().height() * this->zoom / this->imageFilter->GetHeight(2);
	this->ScaleBar->setLine(QLineF(
		this->mapToScene(this->rect()).boundingRect().right() - 60.0 / this->transform().m11(), this->mapToScene(this->rect()).boundingRect().center().y() - len / 2.0,
		this->mapToScene(this->rect()).boundingRect().right() - 60.0 / this->transform().m11(), this->mapToScene(this->rect()).boundingRect().center().y() + len / 2.0
	));
	this->ScaleNum->setPos(this->mapToScene(this->rect()).boundingRect().right() - this->ScaleNum->boundingRect().width() / 2 - 60.0 / this->transform().m11(), this->ScaleBar->line().p1().y() - this->ScaleNum->boundingRect().height());
}

void ImageGraphicsView::UpdateFitMagInfo() {
	DciomObject* head = this->imageFilter->GetDicomHeader();
	this->PitMag->setPlainText(QString("PitMag: ") + QString::number(this->zoom * 100.0) + QString("%"));
}

void ImageGraphicsView::UpdateWindowWidthAndLevelInfo() {
	DciomObject* head = this->imageFilter->GetDicomHeader();
	this->WindowWidthAndLevel->setPlainText(QString("W: ") + QString::number(this->renderObj->GetImgColorRanger()) + QString("  ") + QString("C: ") + QString::number(this->renderObj->GetImgColorCenter()));
}

QImage* ImageGraphicsView::vtkImageDataToQImage(vtkSmartPointer<vtkImageData> data) {
	if (!data) return NULL;

	int width = data->GetDimensions()[0];
	int height = data->GetDimensions()[1];
	this->img = new QImage(width, height, RGB32);
	QImage tempImg(width, height, RGB32);
	QRgb *rgbPtr = reinterpret_cast<QRgb *>(tempImg.bits()) + width * (height - 1);
	unsigned char *colorsPtr = reinterpret_cast<unsigned char *>(data->GetScalarPointer());

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			*(rgbPtr++) = QColor(colorsPtr[0], colorsPtr[1], colorsPtr[2]).rgb();
			colorsPtr += data->GetNumberOfScalarComponents();
		}
		rgbPtr -= width * 2;
	}

	*this->img = tempImg.mirrored(this->isFlipLeftRight, this->isFlipUpDown);

	return this->img;
}

void ImageGraphicsView::MarkCenter() {
	this->center = this->mapToScene(this->rect()).boundingRect().center();
}

void ImageGraphicsView::MoveToCenter() {
	this->centerOn(this->center);
}

void ImageGraphicsView::ImgHorizontalMirror() {
	QString temp = this->leftOri->toPlainText();
	this->leftOri->setPlainText(this->rightOri->toPlainText());
	this->rightOri->setPlainText(temp);

	REVERSE(this->isFlipLeftRight);
	this->UpdataVTKBuff();
}

void ImageGraphicsView::ImgVerticalMirror() {
	QString temp = this->upOri->toPlainText();
	this->upOri->setPlainText(this->downOri->toPlainText());
	this->downOri->setPlainText(temp);

	REVERSE(this->isFlipUpDown);
	this->UpdataVTKBuff();
}

void ImageGraphicsView::ImgRotateAntiClockWise() {
	QString temp = this->upOri->toPlainText();
	this->upOri->setPlainText(this->rightOri->toPlainText());
	this->rightOri->setPlainText(this->downOri->toPlainText());
	this->downOri->setPlainText(this->leftOri->toPlainText());
	this->leftOri->setPlainText(temp);

	this->pix->setTransformOriginPoint(this->pix->boundingRect().center().x(), this->pix->boundingRect().center().y());
	this->pix->setRotation(this->pix->rotation() - 90);
}

void ImageGraphicsView::ImgRotateClockWise() {
	QString temp = this->upOri->toPlainText();
	this->upOri->setPlainText(this->leftOri->toPlainText());
	this->leftOri->setPlainText(this->downOri->toPlainText());
	this->downOri->setPlainText(this->rightOri->toPlainText());
	this->rightOri->setPlainText(temp);

	this->pix->setTransformOriginPoint(this->pix->boundingRect().center().x(), this->pix->boundingRect().center().y());
	this->pix->setRotation(this->pix->rotation() + 90);
}

void ImageGraphicsView::ImgReset() {
	this->isFlipUpDown = false;
	this->isFlipLeftRight = false;

	this->pix->setTransformOriginPoint(this->pix->boundingRect().center().x(), this->pix->boundingRect().center().y());
	this->pix->setRotation(0);

	this->upOri->setPlainText("A");
	this->downOri->setPlainText("P");
	this->leftOri->setPlainText("R");
	this->rightOri->setPlainText("L");

	this->UpdataVTKBuff();
}

void ImageGraphicsView::LoadFileImg(QTableWidgetItem* item) {
	UINT dataSize = 0;

	if (this->describe == item->text()) return;
	QString path = this->sql->SearchDate(dataSize, "Path", item->text());
	this->describe = item->text();

	this->renderObj->SetVtkImageData(this->imageFilter->GetVtkImageData());
	this->renderObj->Reflash();

	this->pScene->clear();

	this->LoadVTKBuff();

	this->SetOriLabel();
	this->LoadCornerInfo();
	this->LoadScaleBar();
}
