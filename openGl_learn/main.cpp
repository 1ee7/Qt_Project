#include "mainwindow.h"
#include "openglwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//    glutInit( & argc, argv );

    QApplication a(argc, argv);
    OpenglWidget w;
//  MainWindow w;
    w.show();

    return a.exec();
}
