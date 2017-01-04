#pragma once
#include <QtWidgets/QApplication>
//#include "testShrinkGif.h"
#include "smart_zip_qt.h"



int main(int argc, char *argv[])
{
	/*testShrinkGif tsg;
	tsg.run("14.gif",50,0.99);*/
	QApplication a(argc, argv);
	Smart_Zip_QT w;
	w.show();
	return a.exec();
	return 0;
}
