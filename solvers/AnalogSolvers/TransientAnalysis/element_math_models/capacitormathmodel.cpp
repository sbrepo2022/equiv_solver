#include "capacitormathmodel.h"

CapacitorMathModel::CapacitorMathModel()
    : capacity(1.0)
{

}

ElementMathModel* CapacitorMathModel::createElementFromXmlNode(const QDomNode &dom_node)
{
    CapacitorMathModel *capacitor_model = new CapacitorMathModel();

    QDomElement element_model_el = dom_node.toElement();

    bool ok;
    double capacity = element_model_el.attribute("capacity").toDouble(&ok);
    if (ok) {
        capacitor_model->capacity = capacity;
    }

    capacitor_model->loadConnections(dom_node);

    return capacitor_model;
}

void CapacitorMathModel::addDataToJacobian(
    Eigen::MatrixXd &jacobian,
    const Eigen::VectorXd &values,
    TimeInfo time_info,
    int equasion_equations_number,
    int extra_equations_used
)
{
    QMap<int, int> ind_map = this->getIndicesMap();

    jacobian(ind_map[0], ind_map[0]) += this->capacity / time_info.dt;
    jacobian(ind_map[0], ind_map[1]) += -this->capacity / time_info.dt;
    jacobian(ind_map[1], ind_map[0]) += -this->capacity / time_info.dt;
    jacobian(ind_map[1], ind_map[1]) += this->capacity / time_info.dt;
}

void CapacitorMathModel::addDataToResidual(
    Eigen::VectorXd &residual,
    const Eigen::VectorXd &values,
    const Eigen::VectorXd &prev_values,
    TimeInfo time_info,
    int equasion_equations_number,
    int extra_equations_used
)
{
    QMap<int, int> ind_map = this->getIndicesMap();

    residual(ind_map[0]) += (values(ind_map[0]) - values(ind_map[1])) * (this->capacity / time_info.dt) - (prev_values(ind_map[0]) - prev_values(ind_map[1])) * (this->capacity / time_info.dt);
    residual(ind_map[1]) += -((values(ind_map[0]) - values(ind_map[1])) * (this->capacity / time_info.dt) - (prev_values(ind_map[0]) - prev_values(ind_map[1])) * (this->capacity / time_info.dt));
}

int CapacitorMathModel::numberOfExtraEquations()
{
    return 0;
}

QString CapacitorMathModel::toString()
{
    QString str = QString("element: CapacitorMathModel | capacity: %1\n").arg(this->capacity);

    str += ElementMathModel::toString();
    return str;
}
