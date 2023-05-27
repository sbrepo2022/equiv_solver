#include "inductormathmodel.h"

InductorMathModel::InductorMathModel()
    : induction(1.0)
{

}

ElementMathModel* InductorMathModel::createElementFromXmlNode(const QDomNode &dom_node)
{
    InductorMathModel *inductor_model = new InductorMathModel();

    QDomElement element_model_el = dom_node.toElement();

    bool ok;
    double induction = element_model_el.attribute("induction").toDouble(&ok);
    if (ok) {
        inductor_model->induction = induction;
    }

    inductor_model->loadConnections(dom_node);

    return inductor_model;
}

void InductorMathModel::addDataToJacobian(
    Eigen::MatrixXd &jacobian,
    const Eigen::VectorXd &values,
    TimeInfo time_info,
    int equasion_equations_number,
    int extra_equations_used
)
{
    QMap<int, int> ind_map = this->getIndicesMap();
    int index_of_I_L = equasion_equations_number + extra_equations_used;

    jacobian(index_of_I_L, index_of_I_L) += this->induction / time_info.dt;
    jacobian(index_of_I_L, ind_map[0]) += -1;
    jacobian(index_of_I_L, ind_map[1]) += 1;
    jacobian(ind_map[0], index_of_I_L) += 1;
    jacobian(ind_map[1], index_of_I_L) += -1;
}

void InductorMathModel::addDataToResidual(
    Eigen::VectorXd &residual,
    const Eigen::VectorXd &values,
    const Eigen::VectorXd &prev_values,
    TimeInfo time_info,
    int equasion_equations_number,
    int extra_equations_used
)
{
    QMap<int, int> ind_map = this->getIndicesMap();
    int index_of_I_L = equasion_equations_number + extra_equations_used;

    residual(index_of_I_L) += (this->induction / time_info.dt) * (values(index_of_I_L) - prev_values(index_of_I_L)) - (values(ind_map[0]) - values(ind_map[1]));
    residual(ind_map[0]) += values(index_of_I_L);
    residual(ind_map[1]) += -values(index_of_I_L);
}

int InductorMathModel::numberOfExtraEquations()
{
    return 1;
}

QString InductorMathModel::toString()
{
    QString str = QString("element: InductorMathModel | induction: %1\n").arg(this->induction);

    str += ElementMathModel::toString();
    return str;
}
