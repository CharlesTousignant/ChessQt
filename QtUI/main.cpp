#include "echecswindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EchecsWindow w;
    w.show();
    return a.exec();
}
