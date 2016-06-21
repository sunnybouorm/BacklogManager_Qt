/*
* main.cpp : Defines the entry point for the console application.
* Exclude the other main.cpp from build when executing the program
* If unit testing then exclude this file from build and include the other one.
*/
#include "../Source/main.h"

int main(int argc, char *argv[])
{
	//Initialize database
	Core core;
	core.database_.OpenConnection();

	//Initialize GUI
	QApplication a(argc, argv);

	ActivityModel *activity_model = new ActivityModel(Q_NULLPTR);
	MainWindow w(activity_model);
	w.show();

	core.database_.CloseConnection();
	return a.exec();

	delete activity_model;
}
