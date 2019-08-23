#include "stdafx.h"
#include "glhf.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GLHF w;
	w.show();
	return a.exec();
}
