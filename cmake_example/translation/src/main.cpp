#include <QTranslator>

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load("japanese");
    app.installTranslator(&translator);

    MainWindow w;
    w.show();

    return app.exec();
}
