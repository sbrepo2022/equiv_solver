#include "transientanalysissolverserializer.h"

TransientAnalysisSolverSerializer::TransientAnalysisSolverSerializer(QObject *parent)
    : SolverSerializer(parent),
    current_field_model(nullptr)
{

}

QString TransientAnalysisSolverSerializer::getFileToSave()
{
    QDir tmp_dir = FileStorage::tmpDir();
    QString file_path = tmp_dir.filePath("serialization_result.xml");
    return file_path;
}

void TransientAnalysisSolverSerializer::processSerialization(QIODevice *out)
{
    if (this->current_field_model == nullptr) throw SerializationException("Current field model is nullptr!");

    QList<CircuitElementModel*> circuit_elements = this->current_field_model->getCircuitElements().values();
    QMap<int, WireModel*> wires = this->current_field_model->getWires();

    QList<GroundElementModel*> ground_elements = this->getGroundElements(circuit_elements);
    QList<QPair<WireModel*, int>> nodes = this->numerateNodes(ground_elements, wires);
    QList<ConnectedElementStruct> net_list = this->generateNetList(circuit_elements, nodes);
    this->writeToFile(out, net_list);
}




/* --- ADDITIONAL METHODS --- */


QList<GroundElementModel*> TransientAnalysisSolverSerializer::getGroundElements(const QList<CircuitElementModel*> &circuit_elements)
{
    QList<GroundElementModel*> ground_elements;
    for (CircuitElementModel *circuit_element : circuit_elements) {
        GroundElementModel *ground_element = qobject_cast<GroundElementModel*>(circuit_element);
        if (ground_element != nullptr) {
            ground_elements.append(ground_element);
        }
    }
    return ground_elements;
}

QList<QPair<WireModel*, int>> TransientAnalysisSolverSerializer::numerateNodes(const QList<GroundElementModel *> &ground_elements, const QMap<int, WireModel *> &wires)
{
    QList<QPair<WireModel*, int>> nodes; // int - содержит глобальный номер узла
    int node_number = 1;
    for (WireModel* wire : wires) {
        int current_number = this->isConnectedToGround(ground_elements, wire) ? 0 : node_number++;
        nodes.append(QPair<WireModel*, int>(wire, current_number));
    }

    return nodes;
}

bool TransientAnalysisSolverSerializer::isConnectedToGround(const QList<GroundElementModel *> &ground_elements, WireModel* wire)
{
    for (GroundElementModel *ground_element : ground_elements) {
        QHash<QPoint, InputPointData> input_points = ground_element->getInputPoints();
        if (input_points.count() == 0) continue;
        QPoint point = input_points.values()[0].getFieldPosition(ground_element->getAngle(), ground_element->getCenter());

        QHash<QPoint, int> line_endings = wire->getLinesEndings();
        if (line_endings[point] == 1) {
            return true;
        }
    }
    return false;
}

QList<ConnectedElementStruct> TransientAnalysisSolverSerializer::generateNetList(const QList<CircuitElementModel*> &circuit_elements, const QList<QPair<WireModel*, int>> &nodes)
{
    QList<ConnectedElementStruct> net_list;

    for (CircuitElementModel *circuit_element : circuit_elements) {

        QList<QPair<InputPointData, int>> input_points_numerated; // int - содержит глобальный номер узла, в InputPointData содержится локальный индекс
        QHash<QPoint, InputPointData> input_points = circuit_element->getInputPoints();
        for (InputPointData input_point : input_points) {
            QPoint point = input_point.getFieldPosition(circuit_element->getAngle(), circuit_element->getCenter());

            bool found = false;
            for (QPair<WireModel*, int> node : nodes) {
                QHash<QPoint, int> lines_endings = node.first->getLinesEndings();
                if (lines_endings[point] == 1) {
                    input_points_numerated.append(QPair<InputPointData, int>(input_point, node.second));
                    found = true;
                    break;
                }
            }

            if (! found) {
                throw SerializationException("One or more of circuit elements are not connected to node!");
            }
        }

        net_list.append(ConnectedElementStruct(circuit_element, input_points_numerated));
    }

    return net_list;
}

void TransientAnalysisSolverSerializer::writeToFile(QIODevice *out, const QList<ConnectedElementStruct> &net_list)
{
    QXmlStreamWriter xml_writer(out);
    xml_writer.setAutoFormatting(true);

    xml_writer.writeStartDocument();
    xml_writer.writeStartElement("Data");

    xml_writer.writeStartElement("SolverSettings");
    this->writeQObjectPropertiesAsXmlAttribute(xml_writer, this->properties_component);
    xml_writer.writeEndElement();

    xml_writer.writeStartElement("NetList");
    for (ConnectedElementStruct conn_el : net_list) {
        xml_writer.writeStartElement(conn_el.circuit_element->getMeta().element_type);

        PropertiesComponent *properties = conn_el.circuit_element->getPropertiesComponent();
        if (properties != nullptr) {
            this->writeQObjectPropertiesAsXmlAttribute(xml_writer, properties);
        }
        this->writeCircuitElementConnectionsToXml(xml_writer, conn_el);

        xml_writer.writeEndElement();
    }
    xml_writer.writeEndElement();

    xml_writer.writeEndElement();
    xml_writer.writeEndDocument();
}

void TransientAnalysisSolverSerializer::writeQObjectPropertiesAsXmlAttribute(QXmlStreamWriter &xml_writer, QObject *obj)
{
    const QMetaObject* meta_obj = obj->metaObject();
    int property_count = meta_obj->propertyCount();

    for (int i = 0; i < property_count; ++i) {
        QMetaProperty meta_property = meta_obj->property(i);

        const char* property_name = meta_property.name();
        QVariant property_value = obj->property(property_name);

        if (strcmp(property_name, "objectName") == 0) {
            continue;
        }

        if (property_value.canConvert<QString>()) {
            xml_writer.writeAttribute(property_name, property_value.toString());
        }
    }
}

void TransientAnalysisSolverSerializer::writeCircuitElementConnectionsToXml(QXmlStreamWriter &xml_writer, const ConnectedElementStruct &conn_el)
{
    for (QPair<InputPointData, int> input_point_numerated : conn_el.input_points_numerated) {
        xml_writer.writeEmptyElement("Connection");
        xml_writer.writeAttribute("local_node_index", QString::number(input_point_numerated.first.getIndex()));
        xml_writer.writeAttribute("global_node_index", QString::number(input_point_numerated.second));
    }
}
