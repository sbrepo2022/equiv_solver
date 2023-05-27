#include "solverssettingstab.h"
#include "ui_solverssettingstab.h"


SolversSettingsTab::SolversSettingsTab(SolverController *solver_controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SolversSettingsTab),
    solver_controller(solver_controller)
{
    ui->setupUi(this);

    // Добавление наименований в QComboBox
    const QMap<QString, SolverConnector*> solver_connectors = solver_controller->getRegisteredSolvers();
    for (QString key : solver_connectors.keys()) {
        ui->currentSolverComboBox->addItem(solver_connectors[key]->getSolverName(), QVariant(key));
        connect(ui->currentSolverComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &SolversSettingsTab::onComboBoxIndexChanged);
    }

    this->generateSettingsContent();
}

SolversSettingsTab::~SolversSettingsTab()
{
    delete ui;
}

void SolversSettingsTab::generateSettingsContent()
{
    // Создание нового layout и установка его в виджет вкладки
    QLayout *current_layout = ui->solverSettingsGroup->layout();
    if (current_layout != nullptr) {
        QLayoutItem *item;
        while ((item = current_layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete current_layout;
    }

    QVBoxLayout *new_layout = new QVBoxLayout();
    this->ui->solverSettingsGroup->setLayout(new_layout);

    // Установка контента в созданный layout
    SolverConnector *current_solver_connector = this->solver_controller->getCurrentSolver();
    SolverPropertiesComponent *solver_properties_component = current_solver_connector->getSolverPropertiesComponent();
    solver_properties_component->init();
    new_layout->addWidget(solver_properties_component->getComponentWidget());
}

void SolversSettingsTab::onComboBoxIndexChanged(int index)
{
    QString key = ui->currentSolverComboBox->itemData(index).toString();
    if (this->solver_controller->setCurrentSolver(key)) {
        this->generateSettingsContent();
    }
}
