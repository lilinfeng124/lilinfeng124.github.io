#include "testlogclass.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	testlogclass w;
	w.show();
	return a.exec();
}
