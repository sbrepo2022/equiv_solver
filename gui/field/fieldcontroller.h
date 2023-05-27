#ifndef FIELDCONTROLLER_H
#define FIELDCONTROLLER_H

#include <QObject>
#include <QMap>
#include <QDebug>

#include "field/fieldview.h"
#include "field/fieldmodel.h"
#include "field/circuit/circuitelementmodel.h"
#include "field/circuit/circuitelementfactory.h"
#include "field/wire/wiremodel.h"

#include "field/edit_modes/fieldeditmodecontroller.h"
#include "field/edit_modes/fieldselectmodecontroller.h"
#include "field/edit_modes/fieldwiremodecontroller.h"
#include "field/edit_modes/fielddeletemodecontroller.h"
#include "field/edit_modes/fielddrawelementmodecontroller.h"

#include "solver_connection/analog_solver_connection/analogsolvercontroller.h"
#include "solver_connection/solverprovider.h"

enum class FieldEditMode {
    SELECT,
    WIRE,
    DELETE,
    DRAW_ELEMENT,
};

class FieldController : public QObject, public SolverProvider
{
    Q_OBJECT

public:
    explicit FieldController(FieldView *field_view, QObject *parent = nullptr);
    ~FieldController();

    // solver provider method
    SolverController* getSolverController() {
        return this->analog_solver_controller;
    }

    // operations with field models
    int addFieldModel(FieldModel *field_model); // returning local index
    FieldModel* removeFieldModel(int id);
    void setCurrentFieldModel(int id);
    FieldModel* getCurrentFieldModel();
    FieldModel* getFieldModelByid(int id) {return this->field_models[id];}

    // get setting parameters
    QSizeF getGridSize() {
        FieldModel *field_model = this->getCurrentFieldModel();
        if (field_model != nullptr) return field_model->getGridSize();
        return QSizeF(0, 0);
    }
    QSizeF getCellSize() {return this->cell_size;}

    // operations with editing mode
    void detachFieldModel();
    void attachFieldModel();
    void setSelectMode();
    void setWireMode();
    void setDeleteMode();
    void setDrawElementsMode(CircuitElementModel *model);
    void delegateActionTriggerToEditMode(QString action_name);

private:
    FieldView *field_view;
    AnalogSolverController *analog_solver_controller;
    FieldEditMode edit_mode = FieldEditMode::SELECT;

    // field model
    QMap<int, FieldModel*> field_models;
    int current_field_model_id;
    QSizeF cell_size;

    // edit mode
    FieldEditModeController *edit_mode_controller;
    QMap<FieldEditMode, FieldEditModeController*> avail_edit_modes;

    void registerEditModes();
    void connectWithGraphicsItem(FieldGraphicsItem*);

signals:
    void gridSizeChanged(QSize);
    void cellSizeChanged(QSizeF);
    void selectableModelSelected(SelectableModelComponentsKeeper*);

public slots:
    // change settings slots
    void setGridSize(const QSize &grid_size) {
        if (this->current_field_model_id >= 0) this->field_models[this->current_field_model_id]->setGridSize(grid_size);
        emit gridSizeChanged(grid_size);
    }
    void setCellSize(const QSizeF &cell_size) {
        this->cell_size = cell_size;
        emit cellSizeChanged(cell_size);
    }
    void updateScene();

    // show dialogs slots
    void showFieldSettingsDialog();
    void showCircuitSettingsDialog();


// -- DEBUG --
signals:
    void graphicsItemDebugChanged(bool);
};

#endif // FIELDCONTROLLER_H
