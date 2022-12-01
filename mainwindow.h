#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QActionGroup>
#include <QTabBar>
#include <QBoxLayout>
#include <QPushButton>

#include "field/fieldcontroller.h"
#include "field/fieldfactory.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QActionGroup *field_cursor_group;
    QTabBar *field_models_tabs;

    FieldController *field_controller;

    void setupAdditionalUi();

public slots:
    void onModelsTabIndexChanged(int tab_index);
    void onModelsTabRemove(int tab_index);

private:
    void connectDebug();
};

#endif // MAINWINDOW_H
