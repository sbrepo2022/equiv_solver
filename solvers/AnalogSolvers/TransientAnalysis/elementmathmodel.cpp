#include "elementmathmodel.h"

ElementMathModel::ElementMathModel()
{

}

ElementMathModel::~ElementMathModel()
{

}

void ElementMathModel::loadConnections(const QDomNode &dom_node)
{
    // if (! dom_node.isElement()) throw;
    QDomElement element_model_el = dom_node.toElement();
    QDomNodeList connections_tags = element_model_el.elementsByTagName("Connection");

    for (int i = 0; i < connections_tags.length(); i++) {
        QDomNode connection_tag = connections_tags.item(i);
        if (! connection_tag.isElement()) continue;

        bool ok;
        QDomElement connection_el = connection_tag.toElement();

        int local_node_index = connection_el.attribute("local_node_index").toInt(&ok);
        if (!ok) continue;

        int global_node_index = connection_el.attribute("global_node_index").toInt(&ok);
        if (!ok) continue;

        this->local_to_global_indices.insert(local_node_index, global_node_index);
    }
}

QString ElementMathModel::toString()
{
    QString str = "Connections:\n";
    for (int local_index : this->local_to_global_indices.keys()) {
        str += QString("local index: %1 | global index: %2\n").arg(local_index).arg(this->local_to_global_indices[local_index]);
    }
    str += "\n---\n\n";
    return str;
}
