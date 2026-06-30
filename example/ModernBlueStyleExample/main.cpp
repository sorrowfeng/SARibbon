#include "ModernBlueStyleWindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	ModernBlueStyleWindow window;
	window.show();

	return app.exec();
}
