#ifndef FRAMLESSRESIZABLEWINDOW_H
#define FRAMLESSRESIZABLEWINDOW_H

#include <QApplication>
#include <QScreen>
#include <QWidget>
#include <QGridLayout>
#include <QMouseEvent>
#include <QLayout>
#include <QStyle>
#include <QDebug>

enum class WindowSide {
    NONE,
    LEFT,
    TOP,
    RIGHT,
    BOTTOM,
    LEFT_TOP,
    RIGHT_TOP,
    RIGHT_BOTTOM,
    LEFT_BOTTOM
};

class FramlessResizableWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FramlessResizableWindow(QWidget *parent = nullptr);
    QWidget* getRoot() {return this->root_widget;}

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);

private:
    bool pressed;
    int fr_w;
    QGridLayout *grid_layout;
    QWidget *root_widget;
    QPointF mouse_point;
    QRect start_geom;

    void setupFrame(int frame_width);

signals:

public slots:
    void setWidget(QWidget *widget);
    void setFrameWidth(int fr_w);
    void maximized();
    void normalized();
    void minimized();
};

#endif // FRAMLESSRESIZABLEWINDOW_H
