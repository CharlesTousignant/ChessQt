#include <QApplication>
#include "../Headers/ChessWindow.h"
#include "gtest/gtest.h"

using namespace std;

int main(int argc, char *argv[])
{	
	testing::InitGoogleTest();
	RUN_ALL_TESTS();
	QApplication app(argc, argv);
	vue::EchecsWindow w;
	w.show();
	return app.exec();
}
