#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QScreen>
#include <QMainWindow>
#include <QLabel>
#include <QActionGroup>
#include <QTabBar>
#include <QBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "custom_widgets/framlessresizablewindow.h"
#include "field/fieldcontroller.h"
#include "field/fieldfactory.h"
#include "custom_widgets/windowmanagebuttons.h"
#include "custom_widgets/windowframemenubar.h"
#include "dock_widgets_controllers/selectablemodelview.h"

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
    FramlessResizableWindow *frame_window;
    WindowManageButtons *window_manage_buttons;
    QActionGroup *field_cursor_group;
    QTabBar *field_models_tabs;

    FieldController *field_controller;
    SelectableModelView *selectable_model_controller;

    void setupWindowFrame();
    void setupAdditionalUi();
    void setupSelectableModelView();

public slots:
    void onModelsTabIndexChanged(int tab_index);
    void onModelsTabRemove(int tab_index);

private:
    void connectDebug();
};

#endif // MAINWINDOW_H
