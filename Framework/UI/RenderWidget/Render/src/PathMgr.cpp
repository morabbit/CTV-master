#include "..\include\PathMgr.h"

PathMgr::PathMgr() {
}

PathMgr::~PathMgr() {
	this->tableWidget = NULL;
	for (int i = 0; i < 3; i++) {
		this->graphicsView[i] = Q_NULLPTR;
	}
	this->renderObj = Q_NULLPTR;
	this->routePlan = Q_NULLPTR;
	this->imageFilter = Q_NULLPTR;
}

void PathMgr::SetRenderObj(VolumeRenderController* renderObj) {
	this->renderObj = renderObj;
}

void PathMgr::SetImageFilter(ImageFilterContorller * imageFilter) {
	this->imageFilter = imageFilter;
}

void PathMgr::SetRoutePlan(RoutePlanning* routePlan) {
	this->routePlan = routePlan;
}

void PathMgr::SetPathTableWidget(PathTableWidget* tableWidget) {
	this->tableWidget = tableWidget;
	CONNECT(this->tableWidget, ResetCurrentPath(int), this, SetCurrentPath(int));
	CONNECT(this->tableWidget, ResetPathColor(int, QColor), this, ResetPathColor(int, QColor));
}

void PathMgr::SetVTKGraphicsView(VTKGraphicsView* graphicsView[3]) {
	for (int i = 0; i < 3; i++) {
		this->graphicsView[i] = graphicsView[i];
		CONNECT(this->graphicsView[i], MoveLineToPoint(int), this, MoveLineToPointPos(int));
		CONNECT(this->graphicsView[i], UpdataPoint(int), this, UpdataPointInfo(int));
		CONNECT(this->graphicsView[i], UpdataPath(int), this, UpdataPathInfo(int));
		CONNECT(this->graphicsView[i], CurrentPath(int), this, SetCurrentPath(int));
		CONNECT(this->graphicsView[i], NoCurrentPath(), this, DelCurrentPath());
	}
}

qreal PathMgr::GetLastPathSize() {
	qreal length = 0.0;
	for (int i = 0; i < 3; i++) {
		length += qPow(this->graphicsView[i]->GetLastPathSize(), 2.0);
	}
	return length;
}

qreal PathMgr::GetCurrentPathSize(int pathID) {
	qreal length = 0.0;
	for (int i = 0; i < 3; i++) {
		length += qPow(this->graphicsView[i]->GetCurrentPathSize(pathID), 2.0);
	}
	return length;
}

int PathMgr::GetLastPointID() {
	return this->graphicsView[0]->GetLastPointID();
}

int PathMgr::GetLastPathID() {
	return this->graphicsView[0]->GetLastPathID();
}

int PathMgr::GetCurrentPointID() {
	return this->graphicsView[0]->GetCurrentPointID();
}

int PathMgr::GetCurrentPathID() {
	return this->graphicsView[0]->GetCurrentPathID();
}

int PathMgr::GetPointMapSize() {
	return this->graphicsView[0]->GetPointMapSize();
}

qreal PathMgr::GetCurrentPointX() {
	return 1.0 - this->graphicsView[1]->GetCurrentPointPos().x();
}

qreal PathMgr::GetCurrentPointX(int pointID) {
	return 1.0 - this->graphicsView[1]->GetCurrentPointX(pointID);
}

qreal PathMgr::GetCurrentPointY() {
	return 1.0 - this->graphicsView[0]->GetCurrentPointPos().x();
}

qreal PathMgr::GetCurrentPointY(int pointID) {
	return 1.0 - this->graphicsView[0]->GetCurrentPointX(pointID);
}

qreal PathMgr::GetCurrentPointZ() {
	return 1.0 - this->graphicsView[0]->GetCurrentPointPos().y();
}

qreal PathMgr::GetCurrentPointZ(int pointID) {
	return 1.0 - this->graphicsView[0]->GetCurrentPointY(pointID);
}

void PathMgr::GetPointPos(int pointID, double& x, double& y, double& z) {
	DOUBLE origin[3];
	DOUBLE spacing[3];
	UINT imageSize[3];
	this->imageFilter->GetOrigin(origin);
	this->imageFilter->GetSpacing(spacing);
	this->imageFilter->GetImageSize(imageSize);
	x = this->GetCurrentPointX(pointID) * imageSize[0] * spacing[0] + origin[0];
	y = this->GetCurrentPointY(pointID) * imageSize[1] * spacing[1] + origin[1];
	z = this->GetCurrentPointZ(pointID) * imageSize[2] * spacing[2] + origin[2];
}

void PathMgr::MoveLineToPointPos(int pointID) {
	for (int i = 0; i < 3; i++) {
		this->graphicsView[i]->MoveLineToPointPos(pointID);
	}
}

void PathMgr::UpdataPointInfo(int pointID) {
	if (pointID < 0) return;
	int winNum = ((VTKGraphicsView*)this->sender())->GetWinNum();
	qreal deltaX = this->graphicsView[winNum]->GetCurrentPointPos().x();
	qreal deltaY = this->graphicsView[winNum]->GetCurrentPointPos().y();
	switch (winNum) {
		case 0: {
			this->graphicsView[1]->SetCurrentPointPosY(pointID, deltaY, deltaX);
			this->graphicsView[2]->SetCurrentPointPosY(pointID, deltaX, deltaY);
			break;
		}
		case 1: {
			this->graphicsView[0]->SetCurrentPointPosY(pointID, deltaY, deltaX);
			this->graphicsView[2]->SetCurrentPointPosX(pointID, deltaX, deltaY);
			break;
		}
		case 2: {
			this->graphicsView[0]->SetCurrentPointPosX(pointID, deltaY, deltaX);
			this->graphicsView[1]->SetCurrentPointPosX(pointID, deltaX, deltaY);
			break;
		}
	}
	double x, y, z;
	this->GetPointPos(pointID, x, y, z);
	this->routePlan->UpdatePoint(x, y, z, pointID);
	this->renderObj->Update();
	this->UpdataPathInfo(pointID / 2);

	this->UpdatePointInfo(pointID, x, y, z);
}

void PathMgr::UpdataPathInfo(int pathID) {
	for (int i = 0; i < this->tableWidget->rowCount(); i++) {
		if (this->tableWidget->item(i, 0)->text().toInt() == pathID) {
			this->tableWidget->item(i, 1)->setText(QString::number(this->routePlan->GetDistance(pathID)) + QString("mm"));
		}
	}
}

void PathMgr::SetCurrentPath(int PathID) {
	for (int i = 0; i < 3; i++) {
		this->graphicsView[i]->SetCurrentPath(PathID);
	}
	this->tableWidget->SetCurrentPath(PathID);
}

void PathMgr::DelCurrentPath(){
	for (int i = 0; i < 3; i++) {
		this->graphicsView[i]->DelCurrentPath();
	}
}

void PathMgr::ResetPathColor(int pathID, QColor color) {
	for (int i = 0; i < 3; i++) {
		this->graphicsView[i]->ResetPathColor(pathID, color);
	}
	double r = color.redF();
	double g = color.greenF();
	double b = color.blueF();
	this->routePlan->SetColor(r, g, b, pathID);
	this->renderObj->Update();
}

void PathMgr::AddPoint() {
	for (int i = 0; i < 3; i++) {
		this->graphicsView[i]->AddPoint();
	}
	if(this->graphicsView[0]->GetPathMapSize() != this->tableWidget->rowCount()) {
		this->tableWidget->AddPath(this->graphicsView[0]->GetPathMapSize(), this->graphicsView[0]->GetLastPathID(), this->routePlan->GetDistance(this->graphicsView[0]->GetLastPathID()));
	}
	bool isNeedAddLine = (this->GetPointMapSize() % 2 != 0);
	if(isNeedAddLine) {
		this->routePlan->SetLineId(this->GetLastPointID() / 2);
	}
	double x, y, z;
	this->GetPointPos(this->GetLastPointID(), x, y, z);
	this->routePlan->SetPoint(x, y, z, this->GetLastPointID());
	if(isNeedAddLine) {
		this->renderObj->AddActor(this->routePlan->GetPoint1Actor(this->GetLastPointID() / 2));
	} else {
		this->renderObj->AddActor(this->routePlan->GetPoint2Actor(this->GetLastPointID() / 2));
		
		this->renderObj->AddActor(this->routePlan->GetLineActor(this->GetLastPointID() / 2));
	}

	this->UpdatePointInfo(this->GetLastPointID(), x, y, z);
}

void PathMgr::DeletePath() {
	int pathID = this->graphicsView[0]->GetCurrentPathID();
	if (pathID < 0) return;
	this->tableWidget->DeleteCurrentPath(pathID);
	for (int i = 0; i < 3; i++) {
		this->graphicsView[i]->DeleteCurrentPath();
	}
	this->renderObj->RemoveActor(this->routePlan->GetPoint1Actor(pathID));
	this->renderObj->RemoveActor(this->routePlan->GetPoint2Actor(pathID));
	this->renderObj->RemoveActor(this->routePlan->GetLineActor(pathID));
	this->routePlan->RemoveLine(pathID);
	this->DeletePoint();
}

void PathMgr::DeleteALLPath() {
	this->tableWidget->clearContents();
	this->tableWidget->setRowCount(0);
	for (int i = 0; i < 3; i++) {
		this->graphicsView[i]->DeleteALLPath();
	}
	this->renderObj->RemoveAllMathActor(this->routePlan->GetAllActor());
	this->routePlan->RemoveAllLine();
	this->DeletePoint();
}
