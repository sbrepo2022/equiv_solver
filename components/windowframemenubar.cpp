#include "windowframemenubar.h"

WindowFrameMenuBar::WindowFrameMenuBar(QWidget *parent)
    : QMenuBar(parent),
      pressed(false)
{
}

void WindowFrameMenuBar::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        this->grabMouse();
        this->pressed = true;
        this->mouse_point = event->globalPos();
    }
    this->setFocus();

    QMenuBar::mousePressEvent(event);
}

void WindowFrameMenuBar::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && this->pressed) {
        const QPointF delta = event->globalPos() - this->mouse_point;
        this->mouse_point = event->globalPos();

        if (this->main_window != nullptr) {
            if (! this->main_window->isMaximized()) {
                this->main_window->move(this->main_window->pos() + delta.toPoint());
            }
        }
    }

    QMenuBar::mouseMoveEvent(event);
}

void WindowFrameMenuBar::mouseReleaseEvent(QMouseEvent *event)
{
    this->releaseMouse();
    this->pressed = false;

    QMenuBar::mouseReleaseEvent(event);
}

void WindowFrameMenuBar::focusOutEvent(QFocusEvent *event)
{
    this->releaseMouse();
    this->pressed = false;

    Q_UNUSED(event);
}
