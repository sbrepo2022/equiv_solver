#ifndef TRANSIENTANALYSISSOLVERSERIALIZER_H
#define TRANSIENTANALYSISSOLVERSERIALIZER_H

#include <QPair>
#include <QXmlStreamWriter>

#include "solver_connection/solverserializer.h"
#include "solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverpropertiescomponent.h"
#include "field/fieldmodel.h"
#include "field/wire/wiremodel.h"
#include "field/circuit/circuitelementmodel.h"
#include "field/circuit/standart_circuit_elements/groundelementmodel.h"
#include "filestorage.h"

class ConnectedElementStruct {
public:
    ConnectedElementStruct(CircuitElementModel *circuit_element, const QList<QPair<InputPointData, int>> &input_points_numerated)
        : circuit_element(circuit_element), input_points_numerated(input_points_numerated) {}

    CircuitElementModel *circuit_element;
    QList<QPair<InputPointData, int>> input_points_numerated;
};

class TransientAnalysisSolverSerializer : public SolverSerializer
{
    Q_OBJECT

public:
    explicit TransientAnalysisSolverSerializer(QObject *parent = nullptr);

    void setTransientAnalysisSolverPropertiesComponent(TransientAnalysisSolverPropertiesComponent *properties_component) {
        this->properties_component = properties_component;
    }

    QString getFileToSave();

    void setCurrentFieldModel(FieldModel *field_model) {
        this->current_field_model = field_model;
    }

    void processSerialization(QIODevice *out);

private:
    FieldModel *current_field_model;
    TransientAnalysisSolverPropertiesComponent *properties_component;

    QList<GroundElementModel*> getGroundElements(const QList<CircuitElementModel*> &circuit_elements);
    QList<QPair<WireModel*, int>> numerateNodes(const QList<GroundElementModel*> &ground_elements, const QMap<int, WireModel*> &wires);
    bool isConnectedToGround(const QList<GroundElementModel*> &ground_elements, WireModel* wire);
    QList<ConnectedElementStruct> generateNetList(const QList<CircuitElementModel*> &circuit_elements, const QList<QPair<WireModel*, int>> &nodes);

    // XML write
    void writeToFile(QIODevice *out, const QList<ConnectedElementStruct> &net_list);
    void writeQObjectPropertiesAsXmlAttribute(QXmlStreamWriter &xml_writer, QObject *obj);
    void writeCircuitElementConnectionsToXml(QXmlStreamWriter &xml_writer, const ConnectedElementStruct &conn_el);

    // Tests
    void runTests();
};

#endif // TRANSIENTANALYSISSOLVERSERIALIZER_H
