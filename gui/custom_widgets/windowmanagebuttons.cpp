#include "windowmanagebuttons.h"
#include "ui_windowmanagebuttons.h"

WindowManageButtons::WindowManageButtons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowManageButtons)
{
    ui->setupUi(this);

    QFile style(":/theme/custom_widgets/windowmanagebuttons.css");
    style.open(QFile::ReadOnly);
    this->setStyleSheet(style.readAll());
    style.close();

    connect(this->ui->minimize, &QPushButton::clicked, this, &WindowManageButtons::minimized);
    connect(this->ui->close, &QPushButton::clicked, qApp, &QCoreApplication::quit, Qt::QueuedConnection);
    connect(this->ui->zoom, &QPushButton::toggled, [this] (bool checked) {
        if (checked)
            emit this->maximized();
        else
            emit this->normalized();
    });
}

WindowManageButtons::~WindowManageButtons()
{
    delete ui;
}

void WindowManageButtons::setZoom(bool checked)
{
    this->ui->zoom->setChecked(checked);
}
