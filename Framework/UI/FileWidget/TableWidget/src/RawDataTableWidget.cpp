#include "..\include\RawDataTableWidget.h"

RawDataTableWidget::RawDataTableWidget(QWidget *parent)
	: QTableWidget(parent) {
	this->setColumnCount(1);
	this->menu = new QMenu();
	this->actionTop = this->menu->addAction(QStringLiteral("ÖÃ¶¥"));
	this->actionUp = this->menu->addAction(QStringLiteral("ÉÏÒÆ"));
	this->actionDown = this->menu->addAction(QStringLiteral("ÏÂÒÆ"));
	this->actionBottom = this->menu->addAction(QStringLiteral("ÖÃµ×"));
	this->actionDelete = this->menu->addAction(QStringLiteral("É¾³ý"));
	this->actionClear = this->menu->addAction(QStringLiteral("Çå¿Õ"));
	CONNECT(this->actionTop, TRIGGERED, this, Top());
	CONNECT(this->actionUp, TRIGGERED, this, Up());
	CONNECT(this->actionDown, TRIGGERED, this, Down());
	CONNECT(this->actionBottom, TRIGGERED, this, Bottom());
	CONNECT(this->actionDelete, TRIGGERED, this, Delete());
	CONNECT(this->actionClear, TRIGGERED, this, Clear());
}

RawDataTableWidget::~RawDataTableWidget() {
	delete this->menu;
	this->menu = NULL;
	this->sql = NULL;
}

void RawDataTableWidget::SetDicomInfoTable(DicomInfoTable *sql) {
	this->sql = sql;
}

void RawDataTableWidget::contextMenuEvent(QContextMenuEvent* event) {
	if (this->itemAt(event->pos()) != NULL) {
		this->menu->exec(QCursor::pos());
	}
}
void RawDataTableWidget::Top() {
	int columns = this->columnCount();
	if (0 == this->currentRow()) return;
	for (int i = this->currentRow(); i > 0; i--) {
		int nCurrRow = i;
		int nPrevRow = i - 1;
		QTableWidgetItem* CurrItem = this->item(nCurrRow, 0);
		QTableWidgetItem* PrevItem = this->item(nPrevRow, 0);
		QString CurrText = CurrItem->text();
		QString PrevText = PrevItem->text();
		QVector<QTableWidgetItem*>m_CurrItemVector;
		QVector<QTableWidgetItem*>m_PrevItemVector;
		for (int i = 1; i < columns; i++) m_CurrItemVector.push_back(this->takeItem(nCurrRow, i));
		for (int i = 1; i < columns; i++) m_PrevItemVector.push_back(this->takeItem(nCurrRow, i));
		for (int i = 1; i < columns; i++) this->setItem(nPrevRow, i, m_CurrItemVector[i - 1]);
		for (int i = 1; i < columns; i++) this->setItem(nCurrRow, i, m_PrevItemVector[i - 1]);
		this->setCurrentCell(nPrevRow, 0);
		CurrItem->setText(PrevText);
		PrevItem->setText(CurrText);
	}
}

void RawDataTableWidget::Up() {
	int columns = this->columnCount();
	int nCurrRow = this->currentRow();
	if (0 == nCurrRow) return;
	int nPrevRow = nCurrRow - 1;
	QTableWidgetItem* CurrItem = this->item(nCurrRow, 0);
	QTableWidgetItem* PrevItem = this->item(nPrevRow, 0);
	QString CurrText = CurrItem->text();
	QString PrevText = PrevItem->text();
	QVector<QTableWidgetItem*>m_CurrItemVector;
	QVector<QTableWidgetItem*>m_PrevItemVector;
	for (int i = 1; i < columns; i++) m_CurrItemVector.push_back(this->takeItem(nCurrRow, i));
	for (int i = 1; i < columns; i++) m_PrevItemVector.push_back(this->takeItem(nCurrRow, i));
	for (int i = 1; i < columns; i++) this->setItem(nPrevRow, i, m_CurrItemVector[i - 1]);
	for (int i = 1; i < columns; i++) this->setItem(nCurrRow, i, m_PrevItemVector[i - 1]);
	this->setCurrentCell(nPrevRow, 0);
	CurrItem->setText(PrevText);
	PrevItem->setText(CurrText);
}

void RawDataTableWidget::Down() {
	int rows = this->rowCount();
	int columns = this->columnCount();
	int nCurrRow = this->currentRow();
	if (rows - 1 == nCurrRow) return;
	int nNextRow = nCurrRow + 1;
	QVector<QTableWidgetItem*> m_CurrItemVector;
	QVector<QTableWidgetItem*> m_NextItemVector;
	QTableWidgetItem* CurrItem = this->item(nCurrRow, 0);
	QTableWidgetItem* NextItem = this->item(nNextRow, 0);
	QString CurrText = CurrItem->text();
	QString NextText = NextItem->text();
	for (int i = 1; i < columns; i++) m_CurrItemVector.push_back(this->takeItem(nCurrRow, i));
	for (int i = 1; i < columns; i++) m_NextItemVector.push_back(this->takeItem(nNextRow, i));
	for (int i = 1; i < columns; i++) this->setItem(nNextRow, i, m_CurrItemVector[i - 1]);
	for (int i = 1; i < columns; i++) this->setItem(nCurrRow, i, m_NextItemVector[i - 1]);
	this->setCurrentCell(nNextRow, 0);
	CurrItem->setText(NextText);
	NextItem->setText(CurrText);
}

void RawDataTableWidget::Bottom() {
	int columns = this->columnCount();
	if (this->rowCount() - 1 == this->currentRow()) return;
	for (int i = this->currentRow(); i < this->rowCount() - 1; i++) {
		int nCurrRow = i;
		int nNextRow = i + 1;
		QVector<QTableWidgetItem*>m_CurrItemVector;
		QVector<QTableWidgetItem*>m_NextItemVector;
		QTableWidgetItem* CurrItem = this->item(nCurrRow, 0);
		QTableWidgetItem* NextItem = this->item(nNextRow, 0);
		QString CurrText = CurrItem->text();
		QString NextText = NextItem->text();
		for (int i = 1; i < columns; i++) m_CurrItemVector.push_back(this->takeItem(nCurrRow, i));
		for (int i = 1; i < columns; i++) m_NextItemVector.push_back(this->takeItem(nNextRow, i));
		for (int i = 1; i < columns; i++) this->setItem(nNextRow, i, m_CurrItemVector[i - 1]);
		for (int i = 1; i < columns; i++) this->setItem(nCurrRow, i, m_NextItemVector[i - 1]);
		this->setCurrentCell(nNextRow, 0);
		CurrItem->setText(NextText);
		NextItem->setText(CurrText);
	}
}

void RawDataTableWidget::Delete() {
	this->sql->DeleteDate(this->currentItem()->text());
	this->removeRow(this->currentRow());
}

void RawDataTableWidget::Clear() {
	this->sql->DeleteALLDate();
	this->clearContents();
	this->setRowCount(0);
}