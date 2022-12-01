#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile style(":/theme/resources/theme/theme.css");
    style.open(QFile::ReadOnly);
    app.setStyleSheet(style.readAll());
    style.close();

    QFont font("Inter");
    font.setStyleHint(QFont::SansSerif);
    font.setPointSize(8);
    //QApplication::setFont(font);

    MainWindow window;
    window.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    window.showMaximized();

    return app.exec();
}
