#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile style(":/theme/resources/theme/theme.qss");
    style.open(QFile::ReadOnly);
    app.setStyleSheet(style.readAll());
    style.close();

    MainWindow window;
    window.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    window.showMaximized();

    return app.exec();
}
