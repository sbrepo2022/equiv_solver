#include "windowmanagebuttons.h"
#include "ui_windowmanagebuttons.h"

WindowManageButtons::WindowManageButtons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowManageButtons)
{
    ui->setupUi(this);
}

WindowManageButtons::~WindowManageButtons()
{
    delete ui;
}
