#include "..\UI\RenderWidget\Info\include\PathTableWidget.h"

PathTableWidget::PathTableWidget(QWidget *parent)
	: QTableWidget(parent) {
	this->setSelectionBehavior(SELECTROWS);
	this->setSelectionMode(NOSELECTION);
	this->setEditTriggers(NOEDITTRIGGERS);

	this->selectColorDialog = new QColorDialog();
	this->selectColorDialog->hide();

	CONNECT(this, CELLCLICKED, this, CurrentPathSelected(int, int));
	CONNECT(this, CELLCLICKED, this, SelectColor(int, int));
	CONNECT(this->selectColorDialog, COLORSELECTED, this, ResetColor(QColor));
}

PathTableWidget::~PathTableWidget() {
	delete this->selectColorDialog;
	this->selectColorDialog = Q_NULLPTR;
}

void PathTableWidget::AddPath(int size, int pathID, qreal length) {
	this->setRowCount(size);
	QTableWidgetItem* item0 = new QTableWidgetItem(QString::number(pathID));
	this->setItem(size - 1, 0, item0);
	QTableWidgetItem* item1 = new QTableWidgetItem(QString::number(length) + QString("mm"));
	this->setItem(size - 1, 1, item1);
	QTableWidgetItem* item2 = new QTableWidgetItem();
	item2->setBackgroundColor(QColor(78, 26, 128));
	this->setItem(size - 1, 2, item2);
}

void PathTableWidget::DeleteCurrentPath(int pathID) {
	if (pathID < 0) return;
	for (int i = 0; i < this->rowCount(); i++) {
		if (pathID == this->item(i, 0)->text().toInt()) {
			this->removeRow(i);
		}
	}
}

void PathTableWidget::SetCurrentPath(int pathID) {
	if (pathID < 0) return;
	for (int i = 0; i < this->rowCount(); i++) {
		if (pathID == this->item(i, 0)->text().toInt()) {
			this->setCurrentCell(i, 0);
		}
	}
}

void PathTableWidget::SelectColor(int row, int col) {
	if (col != 2) return;
	this->selectColorDialog->setCurrentColor(this->item(row, 2)->backgroundColor());
	this->selectColorDialog->show();
}

void PathTableWidget::ResetColor(QColor color) {
	color.setAlpha(255);
	QTableWidgetItem* item = this->item(this->currentRow(), 2);
	item->setBackgroundColor(color);
	this->setItem(this->currentRow(), 2, item);
	int pathID = this->item(this->currentRow(), 0)->text().toInt();
	this->ResetPathColor(pathID, color);
}

void PathTableWidget::CurrentPathSelected(int row, int col) {
	int pathID = this->item(row, 0)->text().toInt();
	this->ResetCurrentPath(pathID);
}
