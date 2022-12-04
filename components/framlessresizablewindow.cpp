#include "framlessresizablewindow.h"

FramlessResizableWindow::FramlessResizableWindow(QWidget *parent)
    : QWidget(parent),
      pressed(false),
      fr_w(0),
      grid_layout(nullptr),
      root_widget(nullptr)
{
    this->root_widget = new QWidget();
    this->setParent(this->root_widget);
    QVBoxLayout *root_layout = new QVBoxLayout();
    root_layout->setContentsMargins(0, 0, 0, 0);
    this->root_widget->setLayout(root_layout);
    this->root_widget->layout()->addWidget(this);
    this->root_widget->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->root_widget->setAttribute(Qt::WA_TranslucentBackground, true);

    grid_layout = new QGridLayout();
    grid_layout->setSpacing(0);
    grid_layout->setContentsMargins(0, 0, 0, 0);
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (x == 1 && y == 1) continue;
            QWidget *widget = new QWidget();
            grid_layout->addWidget(widget, y, x);
            widget->setStyleSheet("background: #01000000;");
            widget->installEventFilter(this);

            if (y == 1 && (x == 0 || x == 2)) widget->setCursor(QCursor(Qt::SizeHorCursor));
            if (x == 1 && (y == 0 || y == 2)) widget->setCursor(QCursor(Qt::SizeVerCursor));
            if ((y == 0 && x == 0) || (y == 2 && x == 2)) widget->setCursor(QCursor(Qt::SizeFDiagCursor));
            if ((y == 2 && x == 0) || (y == 0 && x == 2)) widget->setCursor(QCursor(Qt::SizeBDiagCursor));

        }
    }
    this->setLayout(grid_layout);
}

bool FramlessResizableWindow::eventFilter(QObject *obj, QEvent *event)
{
    QWidget *widget = qobject_cast<QWidget*>(obj);
    if (widget == nullptr) return false;
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
        this->mouse_point = mouse_event->globalPosition();
        this->start_geom = this->root_widget->geometry();
        widget->grabMouse();
        this->pressed = true;
    }
    else if (event->type() == QEvent::MouseButtonRelease) {
        widget->releaseMouse();
        this->pressed = false;
    }
    else if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);

        if (this->pressed) {
            QPoint delta = (mouse_event->globalPosition() - this->mouse_point).toPoint();
            QRect new_geom = start_geom;
            QSize min_size = this->root_widget->minimumSize();
            QSize max_size = this->root_widget->maximumSize();

            if (widget == this->grid_layout->itemAtPosition(1, 0)->widget()) { // left
                new_geom.setX(start_geom.x() + delta.x());
                if (new_geom.width() > max_size.width()) new_geom.setX(new_geom.right() - max_size.width());
                if (new_geom.width() < min_size.width()) new_geom.setX(new_geom.right() - min_size.width());
            }
            if (widget == this->grid_layout->itemAtPosition(1, 2)->widget()) { // right
                new_geom.setWidth(start_geom.width() + delta.x());
            }
            if (widget == this->grid_layout->itemAtPosition(0, 1)->widget()) { // top
                new_geom.setY(start_geom.y() + delta.y());
                if (new_geom.height() > max_size.height()) new_geom.setY(new_geom.bottom() - max_size.height());
                if (new_geom.height() < min_size.height()) new_geom.setY(new_geom.bottom() - min_size.height());
            }
            if (widget == this->grid_layout->itemAtPosition(2, 1)->widget()) { // bottom
                new_geom.setHeight(start_geom.height() + delta.y());
            }
            if (widget == this->grid_layout->itemAtPosition(0, 0)->widget()) { // left top
                new_geom.setX(start_geom.x() + delta.x());
                new_geom.setY(start_geom.y() + delta.y());
                if (new_geom.width() > max_size.width()) new_geom.setX(new_geom.right() - max_size.width());
                if (new_geom.width() < min_size.width()) new_geom.setX(new_geom.right() - min_size.width());
                if (new_geom.height() > max_size.height()) new_geom.setY(new_geom.bottom() - max_size.height());
                if (new_geom.height() < min_size.height()) new_geom.setY(new_geom.bottom() - min_size.height());
            }
            if (widget == this->grid_layout->itemAtPosition(0, 2)->widget()) { // right top
                new_geom.setWidth(start_geom.width() + delta.x());
                new_geom.setY(start_geom.y() + delta.y());
            }
            if (widget == this->grid_layout->itemAtPosition(2, 2)->widget()) { // right bottom
                new_geom.setWidth(start_geom.width() + delta.x());
                new_geom.setHeight(start_geom.height() + delta.y());
            }
            if (widget == this->grid_layout->itemAtPosition(2, 0)->widget()) { // left bottom
                new_geom.setX(start_geom.x() + delta.x());
                new_geom.setHeight(start_geom.height() + delta.y());
            }

            QRect avail_geometry = QApplication::primaryScreen()->availableGeometry();
            if (new_geom.left() < avail_geometry.left()) new_geom.setLeft(avail_geometry.left());
            if (new_geom.right() > avail_geometry.right()) new_geom.setRight(avail_geometry.right());
            if (new_geom.top() < avail_geometry.top()) new_geom.setTop(avail_geometry.top());
            if (new_geom.bottom() > avail_geometry.bottom()) new_geom.setBottom(avail_geometry.bottom());

            this->root_widget->setGeometry(new_geom);
        }
    }
    return false;
}

void FramlessResizableWindow::setupFrame(int frame_width)
{
    for (int i = 0; i < 3; i++) this->grid_layout->setColumnMinimumWidth(i, frame_width);
    for (int i = 0; i < 3; i++) this->grid_layout->setRowMinimumHeight(i, frame_width);
}

void FramlessResizableWindow::setWidget(QWidget *widget)
{
    this->grid_layout->addWidget(widget, 1, 1);
    widget->setParent(this);
}

void FramlessResizableWindow::setFrameWidth(int fr_w) {
    this->fr_w = fr_w;
    this->setupFrame(this->fr_w);
}

void FramlessResizableWindow::maximized()
{
    this->setupFrame(0);
    this->root_widget->showMaximized();
}

void FramlessResizableWindow::normalized()
{
    this->setupFrame(this->fr_w);
    this->root_widget->showNormal();
}

void FramlessResizableWindow::minimized()
{
    this->root_widget->showMinimized();
}
