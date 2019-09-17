#include <QApplication>
#include <QObject>
#include "qinstrument.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QInstrument q;

	q.show();
	return app.exec();
}
