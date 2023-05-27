#include "voltagesourcemathmodel.h"

VoltageSourceMathModel::VoltageSourceMathModel()
    : voltage(1.0)
{

}

ElementMathModel* VoltageSourceMathModel::createElementFromXmlNode(const QDomNode &dom_node)
{
    VoltageSourceMathModel *voltage_source_model = new VoltageSourceMathModel();

    QDomElement element_model_el = dom_node.toElement();

    bool ok;
    double voltage = element_model_el.attribute("voltage").toDouble(&ok);
    if (ok) {
        voltage_source_model->voltage = voltage;
    }

    voltage_source_model->loadConnections(dom_node);

    return voltage_source_model;
}

void VoltageSourceMathModel::addDataToJacobian(
    Eigen::MatrixXd &jacobian,
    const Eigen::VectorXd &values,
    TimeInfo time_info,
    int equasion_equations_number,
    int extra_equations_used
)
{
    QMap<int, int> ind_map = this->getIndicesMap();
    int index_of_I_E = equasion_equations_number + extra_equations_used;

    jacobian(index_of_I_E, ind_map[0]) += -1;
    jacobian(index_of_I_E, ind_map[1]) += 1;
    jacobian(ind_map[0], index_of_I_E) += 1;
    jacobian(ind_map[1], index_of_I_E) += -1;
}

void VoltageSourceMathModel::addDataToResidual(
    Eigen::VectorXd &residual,
    const Eigen::VectorXd &values,
    const Eigen::VectorXd &prev_values,
    TimeInfo time_info,
    int equasion_equations_number,
    int extra_equations_used
)
{
    QMap<int, int> ind_map = this->getIndicesMap();
    int index_of_I_E = equasion_equations_number + extra_equations_used;

    residual(index_of_I_E) += (values(ind_map[1]) - values(ind_map[0])) - this->voltage;
    residual(ind_map[0]) += values(index_of_I_E);
    residual(ind_map[1]) += -values(index_of_I_E);
}

int VoltageSourceMathModel::numberOfExtraEquations()
{
    return 1;
}

QString VoltageSourceMathModel::toString()
{
    QString str = QString("element: VoltageSourceMathModel | voltage: %1\n").arg(this->voltage);

    str += ElementMathModel::toString();
    return str;
}
