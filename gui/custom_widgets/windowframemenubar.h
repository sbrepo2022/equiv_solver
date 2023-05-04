#ifndef WINDOWFRAMEMENUBAR_H
#define WINDOWFRAMEMENUBAR_H

#include <QObject>
#include <QWindow>
#include <QScreen>
#include <QWidget>
#include <QMenuBar>
#include <QMouseEvent>

class WindowFrameMenuBar : public QMenuBar
{
    Q_OBJECT
public:
    explicit WindowFrameMenuBar(QWidget *parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

private:
    QWidget *main_window;
    bool pressed;
    QPointF mouse_point;

public slots:
    void setWindowWidget(QWidget *main_window) {this->main_window = main_window;}
};

#endif // WINDOWFRAMEMENUBAR_H
