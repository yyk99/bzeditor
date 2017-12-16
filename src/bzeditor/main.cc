//
//
//

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
	//Q_INIT_RESOURCE(application);

	QApplication app(argc, argv);
	MainWindow mainWin;

	mainWin.show();
	return app.exec();
}

// end of file
