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

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();

	core.database_.CloseConnection();
}