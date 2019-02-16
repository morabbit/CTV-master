#pragma once

#include <QDebug>
#include <QVector>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QAbstractItemView> 

#include "CommonLayer.h"

#define SELECTROWS QAbstractItemView::SelectRows
#define SINGLESELECTION QAbstractItemView::SingleSelection
#define NOEDITTRIGGERS QAbstractItemView::NoEditTriggers

class InfoTableWidget : public QTableWidget {
	Q_OBJECT

public:
	explicit InfoTableWidget(QWidget *parent = 0);
	~InfoTableWidget();

	void SetRenderObj(VolumeRenderController*);
	void SetImageFilter(ImageFilterContorller*);
	void InitRefList();
	void LoadTable();

private:
	QVector<QString> refList;
	VolumeRenderController* renderObj;
	ImageFilterContorller* imageFilter;
};