#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QFont>

#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Display.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Display-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Display-Light.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Display-Semibold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Display-Semilight.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Small.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Small-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Small-Light.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Small-Semibold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Small-Semilight.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Text.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Text-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Text-Light.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Text-Semibold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/font/Segoe-UI-Variable-Static-Text-Semilight.ttf");

    QFile style(":/theme/resources/theme/theme.css");
    style.open(QFile::ReadOnly);
    app.setStyleSheet(style.readAll());
    style.close();


    MainWindow window;

    return app.exec();
}
