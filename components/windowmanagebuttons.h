#ifndef WINDOWMANAGEBUTTONS_H
#define WINDOWMANAGEBUTTONS_H

#include <QWidget>

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
};

#endif // WINDOWMANAGEBUTTONS_H
