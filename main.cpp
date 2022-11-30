#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile style(":/theme/resources/theme/theme.qss");
    style.open(QFile::ReadOnly);
    a.setStyleSheet(style.readAll());
    style.close();

    MainWindow w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();

    return a.exec();
}
