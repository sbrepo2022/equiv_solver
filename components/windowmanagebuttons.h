#ifndef WINDOWMANAGEBUTTONS_H
#define WINDOWMANAGEBUTTONS_H

#include <QCoreApplication>
#include <QWidget>
#include <QFile>
#include <QMouseEvent>
#include <QPointF>

namespace Ui {
class WindowManageButtons;
}

class WindowManageButtons : public QWidget
{
    Q_OBJECT

public:
    explicit WindowManageButtons(QWidget *parent = nullptr);
    ~WindowManageButtons();

private:
    Ui::WindowManageButtons *ui;

signals:
    void normalized();
    void maximized();
    void minimized();

public slots:
    void setZoom(bool checked);
};

#endif // WINDOWMANAGEBUTTONS_H
