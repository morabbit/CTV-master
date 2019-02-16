#pragma once

#include <QDebug>
#include <QColor>
#include <QVector>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QColorDialog>
#include <QAbstractItemView> 

#include "CommonLayer.h"

#define CONNECT(a, b, c, d) this->connect(a, SIGNAL(b), c, SLOT(d))
#define CELLCLICKED cellClicked(int, int)
#define COLORSELECTED colorSelected(QColor)

#define SELECTROWS QAbstractItemView::SelectRows
#define NOSELECTION QAbstractItemView::NoSelection
#define NOEDITTRIGGERS QAbstractItemView::NoEditTriggers

class PathTableWidget : public QTableWidget {
	Q_OBJECT

signals:
	void ResetCurrentPath(int);
	void ResetPathColor(int, QColor);

public:
	explicit PathTableWidget(QWidget *parent = 0);
	~PathTableWidget();

	void AddPath(int, int, qreal);
	void DeleteCurrentPath(int);
	void SetCurrentPath(int);

public slots:
	void CurrentPathSelected(int, int); 
	void SelectColor(int, int);
	void ResetColor(QColor);

private:
	QColorDialog* selectColorDialog;
};