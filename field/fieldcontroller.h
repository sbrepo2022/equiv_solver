#ifndef FIELDCONTROLLER_H
#define FIELDCONTROLLER_H

#include <QObject>
#include <QDebug>

#include "fieldview.h"
#include "fieldmodel.h"
#include "circuit/circuitelementmodel.h"
#include "circuit/circuitelementfactory.h"

enum FieldEditMode {
    SELECT,
    WIRE,
    DELETE,
    DRAW_ELEMENT,
};

class FieldController : public QObject
{
    Q_OBJECT

public:
    explicit FieldController(FieldView *field_view, QObject *parent = nullptr);

    // operations with field models
    int addFieldModel(FieldModel *field_model); // returning local index
    FieldModel* removeFieldModel(int index);
    void setCurrentFieldModel(int index);
    FieldModel* getFieldModelByIndex(int index) {return this->field_models[index];}

    // get setting parameters
    QSizeF getGridSize() {return this->field_models[this->current_field_model_ind]->getGridSize();}
    QSizeF getCellSize() {return this->cell_size;}

    void setDrawElementsMode(CircuitElementModel *model, CircuitElementGraphicsItem *graphics_item);
    void setSelectMode();
    void setWireMode();
    void setDeleteMode();

private:
    FieldView *field_view;
    FieldEditMode edit_mode = FieldEditMode::SELECT;

    QList<FieldModel*> field_models;
    int current_field_model_ind;
    QSizeF cell_size;

    CircuitElementModel *buffer_element;
    CircuitElementGraphicsItem *buffer_graphics_item;

    void connectWithGraphicsItem(FieldGraphicsItem*);
    void cleanLastModeEffects();

signals:
    void gridSizeChanged(QSize);
    void cellSizeChanged(QSizeF);

public slots:
    // change settings slots
    void setGridSize(const QSize &grid_size) {
        if (this->current_field_model_ind >= 0) this->field_models[this->current_field_model_ind]->setGridSize(grid_size);
        emit gridSizeChanged(grid_size);
    }
    void setCellSize(const QSizeF &cell_size) {
        this->cell_size = cell_size;
        emit cellSizeChanged(cell_size);
    }
    void updateScene();

    // events processing slots
    void gridCellHover(const QPoint &pos);
    void gridItemEnter();
    void gridItemLeave();
    void gridCellPressed(const QPoint &pos);

    // show dialogs slots
    void showFieldSettingsDialog();
    void showCircuitSettingsDialog();
};

#endif // FIELDCONTROLLER_H
