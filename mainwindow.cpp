#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "field/fieldview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->field_cursor_group = new QActionGroup(this);
    this->field_cursor_group->addAction(ui->actionSelection);
    this->field_cursor_group->addAction(ui->actionDraw);
    this->field_cursor_group->addAction(ui->actionDelete);
    this->field_cursor_group->addAction(ui->actionI);
    this->field_cursor_group->addAction(ui->actionE);
    this->field_cursor_group->addAction(ui->actionR);
    this->field_cursor_group->addAction(ui->actionC);
    this->field_cursor_group->addAction(ui->actionL);
    this->field_cursor_group->addAction(ui->actionGnd);

    field_controller = new FieldController(ui->circuitGraphicsView, this);

    connect(ui->actionI, &QAction::toggled, this, [=]() {
        CircuitBasicElementFactory el_factory(BasicElementType::I);
        field_controller->setDrawElementsMode(el_factory.model, el_factory.graphics_item);
    });
    connect(ui->actionE, &QAction::toggled, this, [=]() {
        CircuitBasicElementFactory el_factory(BasicElementType::E);
        field_controller->setDrawElementsMode(el_factory.model, el_factory.graphics_item);
    });
    connect(ui->actionR, &QAction::toggled, this, [=]() {
        CircuitBasicElementFactory el_factory(BasicElementType::R);
        field_controller->setDrawElementsMode(el_factory.model, el_factory.graphics_item);
    });
    connect(ui->actionC, &QAction::toggled, this, [=]() {
        CircuitBasicElementFactory el_factory(BasicElementType::C);
        field_controller->setDrawElementsMode(el_factory.model, el_factory.graphics_item);
    });
    connect(ui->actionL, &QAction::toggled, this, [=]() {
        CircuitBasicElementFactory el_factory(BasicElementType::L);
        field_controller->setDrawElementsMode(el_factory.model, el_factory.graphics_item);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
