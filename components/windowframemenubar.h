#ifndef WINDOWFRAMEMENUBAR_H
#define WINDOWFRAMEMENUBAR_H

#include <QObject>
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
    virtual void leaveEvent(QEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

private:
    bool pressed;
    QPointF mouse_point;

signals:
    void moved(QPoint pos);
    void normalized();

public slots:
};

#endif // WINDOWFRAMEMENUBAR_H
