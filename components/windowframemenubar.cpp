#include "windowframemenubar.h"

WindowFrameMenuBar::WindowFrameMenuBar(QWidget *parent)
    : QMenuBar(parent),
      pressed(false)
{

}

void WindowFrameMenuBar::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        this->pressed = true;
        this->mouse_point = event->screenPos();
        event->accept();
    }
    this->setFocus();

    QMenuBar::mousePressEvent(event);
}

void WindowFrameMenuBar::mouseMoveEvent(QMouseEvent *event)
{
    if (! (event->buttons() & Qt::LeftButton)) this->pressed = false;
    if (this->pressed) {
        const QPointF delta = event->screenPos() - this->mouse_point;
        this->mouse_point = event->screenPos();
        event->accept();

        emit this->normalized();
        emit this->moved(delta.toPoint());
    }

    QMenuBar::mouseMoveEvent(event);
}

void WindowFrameMenuBar::mouseReleaseEvent(QMouseEvent *event)
{
    this->pressed = false;
    event->accept();

    QMenuBar::mouseReleaseEvent(event);
}

void WindowFrameMenuBar::leaveEvent(QEvent *event)
{
    this->pressed = false;

    Q_UNUSED(event);
}

void WindowFrameMenuBar::focusOutEvent(QFocusEvent *event)
{
    this->pressed = false;

    Q_UNUSED(event);
}
