#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "Source\GUI\Models\activity_model.h"

namespace Ui 
{
	class MainWindowClass;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(ActivityModel *activity_model, QWidget *parent = Q_NULLPTR);
	~MainWindow();

private:
	//Ui::MainWindowClass ui; //TODO delete me
	Ui::MainWindowClass *ui;
};

#endif // MAINWINDOW_H
