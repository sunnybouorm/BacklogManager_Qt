#include "Source/GUI/Windows/MainWindow/mainwindow.h"
#include "Source/GUI/Models/activity_model.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(ActivityModel *activity_model, QWidget *parent):
	QMainWindow(parent), 
	ui(new Ui::MainWindowClass)
{
	ui->setupUi(this);

	auto view = ui->ActivityList;
	view->setModel(activity_model);
}

MainWindow::~MainWindow()
{
	delete ui;
}