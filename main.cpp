#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    qDebug() << "Current directory: " << QCoreApplication::applicationDirPath();
    MainWindow w;
    w.show();
    return app.exec();
}
