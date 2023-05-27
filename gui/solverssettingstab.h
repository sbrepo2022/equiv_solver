#ifndef SOLVERSSETTINGSTAB_H
#define SOLVERSSETTINGSTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>

#include "solver_connection/solvercontroller.h"

namespace Ui {
class SolversSettingsTab;
}

class SolversSettingsTab : public QWidget
{
    Q_OBJECT

public:
    explicit SolversSettingsTab(SolverController *solver_controller, QWidget *parent = nullptr);
    ~SolversSettingsTab();

private:
    Ui::SolversSettingsTab *ui;
    SolverController *solver_controller;

protected:
    void generateSettingsContent();

public slots:
    void onComboBoxIndexChanged(int index);
};

#endif // SOLVERSSETTINGSTAB_H
