#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "field/fieldview.h"
#include "solverssettingsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setupWindowFrame();
    ui->setupUi(this);
    this->setupAdditionalUi();
    this->frame_window->maximized();
    this->window_manage_buttons->setZoom(this->frame_window->getRoot()->isMaximized());


    this->field_controller = new FieldController(ui->circuitGraphicsView, this);
    this->solvers_providers.append(this->field_controller);
    this->current_solver_provider = this->field_controller;

    connect(this->current_solver_provider->getSolverController(), &SolverController::solved, this, &MainWindow::openDialogWithChart);

    connect(this->current_solver_provider->getSolverController(), &SolverController::errorOccured, this, [=](const QString &error_message) {
        QMessageBox::critical(this, "Solving error occured!", error_message);
    });

    connect(ui->actionNew, &QAction::triggered, this, [=]() {
        int model_index = field_controller->addFieldModel(FieldFactory::createNew());
        QString text = QString("New %1").arg(model_index);
        int tab_index = this->field_models_tabs->addTab(text);
        this->field_models_tabs->setTabData(tab_index, QVariant(model_index));
        this->field_models_tabs->setCurrentIndex(tab_index);
        this->field_controller->setCurrentFieldModel(model_index);
    });

    connect(ui->actionSelection, &QAction::toggled, this, [=](bool checked) {
        if (checked) field_controller->setSelectMode();
    });
    connect(ui->actionDraw, &QAction::toggled, this, [=](bool checked) {
        if (checked) field_controller->setWireMode();
    });
    connect(ui->actionDelete, &QAction::toggled, this, [=](bool checked) {
        if (checked) field_controller->setDeleteMode();
    });

    connect(ui->actionI, &QAction::toggled, this, [=](bool checked) {
        CircuitBasicElementFactory el_factory(BasicElementType::I);
        if (checked) field_controller->setDrawElementsMode(el_factory.model);
    });
    connect(ui->actionE, &QAction::toggled, this, [=](bool checked) {
        CircuitBasicElementFactory el_factory(BasicElementType::E);
        if (checked) field_controller->setDrawElementsMode(el_factory.model);
    });
    connect(ui->actionR, &QAction::toggled, this, [=](bool checked) {
        CircuitBasicElementFactory el_factory(BasicElementType::R);
        if (checked) field_controller->setDrawElementsMode(el_factory.model);
    });
    connect(ui->actionC, &QAction::toggled, this, [=](bool checked) {
        CircuitBasicElementFactory el_factory(BasicElementType::C);
        if (checked) field_controller->setDrawElementsMode(el_factory.model);
    });
    connect(ui->actionL, &QAction::toggled, this, [=](bool checked) {
        CircuitBasicElementFactory el_factory(BasicElementType::L);
        if (checked) field_controller->setDrawElementsMode(el_factory.model);
    });
    connect(ui->actionGnd, &QAction::toggled, this, [=](bool checked) {
        CircuitBasicElementFactory el_factory(BasicElementType::Gnd);
        if (checked) field_controller->setDrawElementsMode(el_factory.model);
    });

    connect(ui->actionRotateElementRight, &QAction::triggered, this, [=]() {
       field_controller->delegateActionTriggerToEditMode("RotateElementRight");
    });
    connect(ui->actionRotateElementLeft, &QAction::triggered, this, [=]() {
       field_controller->delegateActionTriggerToEditMode("RotateElementLeft");
    });

    connect(ui->actionSolve, &QAction::triggered, this, [=]() {
        if (this->current_solver_provider != nullptr) {
            SolverController *solver_controller = this->current_solver_provider->getSolverController();
            if (solver_controller != nullptr) {
                solver_controller->solve();
            }
        }
    });

    connect(ui->actionFieldSettings, &QAction::triggered, this->field_controller, &FieldController::showFieldSettingsDialog);
    connect(ui->actionCircuitSettings, &QAction::triggered, this->field_controller, &FieldController::showCircuitSettingsDialog);
    connect(ui->actionSolverSettings, &QAction::triggered, this, &MainWindow::showSolverSettingsDialog);

    this->setupSelectableModelView();

    this->connectDebug();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupWindowFrame()
{
    this->frame_window = new FramlessResizableWindow();
    this->frame_window->setWidget(this);
    this->frame_window->setFrameWidth(10);
    QRect screen_geom = QApplication::primaryScreen()->geometry();
    this->frame_window->getRoot()->setGeometry(screen_geom.width() / 6, screen_geom.height() / 6,
                                    screen_geom.width() / 6 * 4, screen_geom.height() / 6 * 4);
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
    connect(this->field_models_tabs, &QTabBar::tabCloseRequested, this, &MainWindow::onModelsTabRemove);


    this->window_manage_buttons = new WindowManageButtons(this);
    this->ui->menuBar->setCornerWidget(window_manage_buttons, Qt::TopRightCorner);
    connect(this->window_manage_buttons, &WindowManageButtons::minimized, this, [=]() {
        this->frame_window->minimized();
    });
    connect(this->window_manage_buttons, &WindowManageButtons::maximized, this, [=]() {
        this->frame_window->maximized();
    });
    connect(this->window_manage_buttons, &WindowManageButtons::normalized, this, [=]() {
        this->frame_window->normalized();
    });

    this->ui->menuBar->setWindowWidget(this->frame_window->getRoot());

    QLabel *logo_widget = new QLabel(this);
    logo_widget->setPixmap(QPixmap(":/logo/resources/logo/logo_32.png"));
    logo_widget->setScaledContents(true);
    this->ui->menuBar->setCornerWidget(logo_widget, Qt::TopLeftCorner);
}

void MainWindow::setupSelectableModelView()
{
    this->selectable_model_controller = new SelectableModelView(this->ui->dockWidgetPropertiesContents);
    connect(this->field_controller, &FieldController::selectableModelSelected,
            this->selectable_model_controller, &SelectableModelView::onSelectableModelSelected);
}

void MainWindow::onModelsTabIndexChanged(int tab_index)
{
    int model_index = this->field_models_tabs->tabData(tab_index).toInt();
    this->field_controller->setCurrentFieldModel(model_index);
}

void MainWindow::onModelsTabRemove(int tab_index)
{
    int model_index = this->field_models_tabs->tabData(tab_index).toInt();
    this->field_controller->removeFieldModel(model_index);
    this->field_models_tabs->removeTab(tab_index);
}

void MainWindow::showSolverSettingsDialog()
{
    SolversSettingsDialog dialog(this->solvers_providers, this->current_solver_provider);
    switch (dialog.exec()) {
    case QDialog::Accepted:
        break;

    case QDialog::Rejected:
        break;
    }
}

void MainWindow::openDialogWithChart(const SolverResult &result)
{
    if (result.doneOk()) {
        QDialog *dialog = new QDialog();
        dialog->resize(800, 600);

        QVBoxLayout *layout = new QVBoxLayout();
        dialog->setLayout(layout);

        QChart *chart = new QChart();
        QChartView *chartView = new QChartView(chart);
        layout->addWidget(chartView);

        QList<QLineSeries*> series_list = result.getLineSeries();
        for (auto series : series_list) {
            chart->addSeries(series);
        }

        for (int i = 0; i < series_list.size(); i++) {
            QPen pen = series_list[i]->pen();
            pen.setWidth(3);
            series_list[i]->setPen(pen);
        }

        chart->createDefaultAxes();

        QValueAxis *axisX = qobject_cast<QValueAxis*>(chart->axisX());
        QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axisY());

        double padding = 0.01;  // Добавить 1% от диапазона оси

        double minX = axisX->min() - padding * (axisX->max() - axisX->min());
        double maxX = axisX->max() + padding * (axisX->max() - axisX->min());

        double minY = axisY->min() - padding * (axisY->max() - axisY->min());
        double maxY = axisY->max() + padding * (axisY->max() - axisY->min());

        axisX->setRange(minX, maxX);
        axisY->setRange(minY, maxY);

        dialog->exec();
    }
}


//---------------------------TESTS-------------------------------//


void MainWindow::connectDebug()
{
    connect(ui->actionGraphicsItemDebug, &QAction::toggled, field_controller, &FieldController::graphicsItemDebugChanged);
}


