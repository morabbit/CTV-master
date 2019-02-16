#include "..\include\VTKShow3DWidget.h"

VTKShow3DWidget::VTKShow3DWidget(QWidget *parent)
	: QVTKWidget(parent) {

}

VTKShow3DWidget::~VTKShow3DWidget() {
	this->renderObj = Q_NULLPTR;
}

void VTKShow3DWidget::LoadDate() {
	vtkSmartPointer<vtkRenderWindow> renderWindow = this->renderObj->Rendering3DPlane(this->GetInteractor(), P3DT::Display_Volume);
}

void VTKShow3DWidget::SetRenderObj(VolumeRenderController* renderObj) {
	this->renderObj = renderObj;
	vtkSmartPointer<vtkRenderWindow> renderWindow = renderObj->GetEmptyRenderWindow();
	this->SetRenderWindow(renderWindow);
}

void VTKShow3DWidget::Show3DPlane(P3DT isShowPlane) {
	this->renderObj->ChangeRendering3DPlane(isShowPlane);
}

void VTKShow3DWidget::mouseDoubleClickEvent(QMouseEvent* event) {
	this->ChangeWidget3D();
}
