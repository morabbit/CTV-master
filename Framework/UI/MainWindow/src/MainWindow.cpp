#include "..\include\MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent) {
	ui.setupUi(this);

	this->showMaximized();
	this->setWindowFlags(Qt::CustomizeWindowHint);

	this->addDateWidget = new AddDateWidget();
	this->dicomWidget = new DicomWidget();
	this->saveWidget = new SaveWidget();
	this->closeDialog = new CloseDialog();

	this->loginWidget = new LoginWidget(this->ui.widget);
	this->moduleWidget = new ModuleWidget(this->ui.widget);
	this->fileWidget = new FileWidget(this->ui.widget);
	this->renderWidget = new RenderWidget(this->ui.widget);

	this->ui.gridLayout->addWidget(this->loginWidget, 0, 0, 1, 1);
	this->ui.gridLayout->addWidget(this->moduleWidget, 0, 0, 1, 1);
	this->ui.gridLayout->addWidget(this->fileWidget, 0, 0, 1, 1);
	this->ui.gridLayout->addWidget(this->renderWidget, 0, 0, 1, 1);

	this->loginWidget->show();
	this->moduleWidget->hide();
	this->fileWidget->hide();
	this->renderWidget->hide();

	this->renderObj = new VolumeRenderController();
	this->fileWidget->SetRenderObj(this->renderObj);
	this->renderWidget->SetRenderObj(this->renderObj);

	this->imageFilter = new ImageFilterContorller();
	this->fileWidget->SetImageFilter(this->imageFilter);
	this->renderWidget->SetImageFilter(this->imageFilter);

	this->routePlan = new RoutePlanning();
	this->renderWidget->SetRoutePlan(this->routePlan);

	this->sql = new DicomInfoTable();
	this->sql->CreateTable();
	this->fileWidget->SetDicomInfoSQL(this->sql);

	QString logoPath(".//Resource//MainWindow//logo.png");
	QImage logoImg;
	logoImg.load(logoPath);
	this->ui.labelLogo->clear();
	this->ui.labelLogo->setPixmap(QPixmap::fromImage(logoImg));
	this->ui.labelLogo->resize(QSize(logoImg.width(), logoImg.height()));

	QString logoNet(".//Resource//MainWindow//net.png");
	QImage netImg;
	netImg.load(logoNet);
	this->ui.labelNet->clear();
	this->ui.labelNet->setPixmap(QPixmap::fromImage(netImg));
	this->ui.labelNet->resize(QSize(netImg.width(), netImg.height()));

	QPixmap pixmapBtnBack(".//Resource//MainWindow//btnBack.png");
	this->ui.tbtnBack->setStyleSheet("QToolButton{border:Opx}");
	this->ui.tbtnBack->setIconSize(QSize(this->ui.tbtnBack->width(), this->ui.tbtnBack->height()));
	this->ui.tbtnBack->setIcon(QIcon(pixmapBtnBack));

	QPixmap pixmapBtnMin(".//Resource//MainWindow//btnMin.png");
	this->ui.tbtnMin->setStyleSheet("QToolButton{border:Opx}");
	this->ui.tbtnMin->setIconSize(QSize(this->ui.tbtnMin->width(), this->ui.tbtnMin->height()));
	this->ui.tbtnMin->setIcon(QIcon(pixmapBtnMin));

	QPixmap pixmapBtnClose(".//Resource//MainWindow//btnClose.png");
	this->ui.tbtnClose->setStyleSheet("QToolButton{border:Opx}");
	this->ui.tbtnClose->setIconSize(QSize(this->ui.tbtnClose->width(), this->ui.tbtnClose->height()));
	this->ui.tbtnClose->setIcon(QIcon(pixmapBtnClose));

	this->ui.tbtnBack->hide();

	CONNECT(this->ui.actionAddDate, TRIGGERED, addDateWidget, SHOW);
	CONNECT(this->ui.actionDicom, TRIGGERED, dicomWidget, SHOW);
	CONNECT(this->ui.actionSave, TRIGGERED, saveWidget, SHOW);

	CONNECT(this->ui.tbtnBack, CLICKED, this, back());
	CONNECT(this->ui.tbtnMin, CLICKED, this, showMinimized());
	CONNECT(this->ui.tbtnClose, CLICKED, this, BtnClose());

	CONNECT(this->loginWidget, ToLogin(bool), this, DoLogin(bool));
	CONNECT(this->closeDialog, WindowClose(), this, close());
	CONNECT(this->moduleWidget, LoadFileWidget(), this, LoadCaseFile());
	CONNECT(this->fileWidget, RenderSign(QString), this, DoRender(QString));
}

MainWindow::~MainWindow() {
	delete this->sql;
	this->sql = Q_NULLPTR;
	delete this->addDateWidget;
	this->addDateWidget = Q_NULLPTR;
	delete this->dicomWidget;
	this->dicomWidget = Q_NULLPTR;
	delete this->saveWidget;
	this->saveWidget = Q_NULLPTR;
	delete this->routePlan;
	this->routePlan = Q_NULLPTR;
	delete this->renderObj;
	this->renderObj = Q_NULLPTR;
	delete this->imageFilter;
	this->imageFilter = Q_NULLPTR;
	delete this->closeDialog;
	this->closeDialog = Q_NULLPTR;
	
	close_logger_files();
}

void MainWindow::Back() {

}

void MainWindow::DoLogin(bool isEnable) {
	if (isEnable) {
		this->loginWidget->hide();
		this->moduleWidget->show();
	} else {
		return;
	}
}

void MainWindow::LoadCaseFile() {
	this->moduleWidget->hide();
	this->fileWidget->show();
}

void MainWindow::DoRender(QString description) {
	this->ShowRender();
	this->renderWidget->Render();
}

void MainWindow::BtnClose() {
	this->closeDialog->show();
}

void MainWindow::ShowRender() {
	this->fileWidget->hide();
	this->renderWidget->show();
}
