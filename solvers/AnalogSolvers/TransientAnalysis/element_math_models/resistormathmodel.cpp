#include "resistormathmodel.h"

ResistorMathModel::ResistorMathModel()
    : resistance(1.0)
{

}

ElementMathModel* ResistorMathModel::createElementFromXmlNode(const QDomNode &dom_node)
{
    ResistorMathModel *resistor_model = new ResistorMathModel();

    QDomElement element_model_el = dom_node.toElement();

    bool ok;
    double resistance = element_model_el.attribute("resistance").toDouble(&ok);
    if (ok) {
        resistor_model->resistance = resistance;
    }

    resistor_model->loadConnections(dom_node);

    return resistor_model;
}

void ResistorMathModel::addDataToJacobian(
    Eigen::MatrixXd &jacobian,
    const Eigen::VectorXd &values,
    TimeInfo time_info,
    int equasion_equations_number,
    int extra_equations_used
)
{
    QMap<int, int> ind_map = this->getIndicesMap();

    jacobian(ind_map[0], ind_map[0]) += 1/this->resistance;
    jacobian(ind_map[0], ind_map[1]) += -1/this->resistance;
    jacobian(ind_map[1], ind_map[0]) += -1/this->resistance;
    jacobian(ind_map[1], ind_map[1]) += 1/this->resistance;
}

void ResistorMathModel::addDataToResidual(
    Eigen::VectorXd &residual,
    const Eigen::VectorXd &values,
    const Eigen::VectorXd &prev_values,
    TimeInfo time_info,
    int equasion_equations_number,
    int extra_equations_used
)
{
    QMap<int, int> ind_map = this->getIndicesMap();

    residual(ind_map[0]) += (values(ind_map[0]) - values(ind_map[1])) * (1/this->resistance);
    residual(ind_map[1]) += -(values(ind_map[0]) - values(ind_map[1])) * (1/this->resistance);
}

int ResistorMathModel::numberOfExtraEquations()
{
    return 0;
}

QString ResistorMathModel::toString()
{
    QString str = QString("element: ResistorMathModel | resistance: %1\n").arg(this->resistance);

    str += ElementMathModel::toString();
    return str;
}
