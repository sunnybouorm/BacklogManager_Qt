#include "Source/GUI/Windows/MainWindow/mainwindow.h"
#include "Source/GUI/Models/activity_model.h"
#include "../../ProxyModelFilters/activity_view_proxy_model_filter.h"

#include "ui_mainwindow.h"

void setupAcitvityView(QTableView *view, ActivityModel *activity_model) {
	ActivityViewSortFilterProxyModel *proxy_model = 
		new ActivityViewSortFilterProxyModel(view, activity_model);
	view->horizontalHeader()->setSectionsClickable(false);
	view->setModel(proxy_model);
	view->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

	proxy_model->sort(0, Qt::AscendingOrder);
}

MainWindow::MainWindow(ActivityModel *activity_model, QWidget *parent):
	QMainWindow(parent), 
	ui(new Ui::MainWindowClass)
{
	ui->setupUi(this);

	auto view = ui->ActivityView;
	setupAcitvityView(view, activity_model);
}

MainWindow::~MainWindow()
{
	delete ui;
}