#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "field/fieldview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setupAdditionalUi();
    this->field_controller = new FieldController(ui->circuitGraphicsView, this);


    connect(ui->actionNew, &QAction::triggered, this, [=]() {
        int model_index = field_controller->addFieldModel(FieldFactory::createNew());
        QString text = QString("New %1").arg(model_index);
        int tab_index = this->field_models_tabs->addTab(text);
        this->field_models_tabs->setTabData(tab_index, QVariant(model_index));
        this->field_models_tabs->setCurrentIndex(tab_index);
    });

    connect(ui->actionSelection, &QAction::toggled, this, [=]() {
        field_controller->setSelectMode();
    });
    connect(ui->actionDraw, &QAction::toggled, this, [=]() {
        field_controller->setWireMode();
    });
    connect(ui->actionDelete, &QAction::toggled, this, [=]() {
        field_controller->setDeleteMode();
    });

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
    connect(ui->actionGnd, &QAction::toggled, this, [=]() {
        CircuitBasicElementFactory el_factory(BasicElementType::Gnd);
        field_controller->setDrawElementsMode(el_factory.model, el_factory.graphics_item);
    });

    connect(ui->actionFieldSettings, &QAction::triggered, this->field_controller, &FieldController::showFieldSettingsDialog);
    connect(ui->actionCircuitSettings, &QAction::triggered, this->field_controller, &FieldController::showCircuitSettingsDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupAdditionalUi()
{
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

    this->field_models_tabs = new QTabBar();
    this->field_models_tabs->setTabsClosable(true);
    this->field_models_tabs->setShape(QTabBar::RoundedSouth);
    this->field_models_tabs->setExpanding(false);
    this->field_models_tabs->setMovable(true);
    qobject_cast<QBoxLayout*>(this->ui->centralWidget->layout())->addWidget(this->field_models_tabs);
    connect(this->field_models_tabs, &QTabBar::currentChanged, this, &MainWindow::onModelsTabIndexChanged);
}

void MainWindow::onModelsTabIndexChanged(int tab_index)
{
    int model_index = this->field_models_tabs->tabData(tab_index).toInt();
    this->field_controller->setCurrentFieldModel(model_index);
}
