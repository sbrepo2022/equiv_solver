#include "currencysourcemathmodel.h"

CurrencySourceMathModel::CurrencySourceMathModel()
    : currency(1.0)
{

}

ElementMathModel* CurrencySourceMathModel::createElementFromXmlNode(const QDomNode &dom_node)
{
    CurrencySourceMathModel *currency_source_model = new CurrencySourceMathModel();

    QDomElement element_model_el = dom_node.toElement();

    bool ok;
    double currency = element_model_el.attribute("currency").toDouble(&ok);
    if (ok) {
        currency_source_model->currency = currency;
    }

    currency_source_model->loadConnections(dom_node);

    return currency_source_model;
}

void CurrencySourceMathModel::addDataToJacobian(
    Eigen::MatrixXd &jacobian,
    const Eigen::VectorXd &values,
    TimeInfo time_info,
    int equasion_equations_number,
    int extra_equations_used
)
{

}

void CurrencySourceMathModel::addDataToResidual(
    Eigen::VectorXd &residual,
    const Eigen::VectorXd &values,
    const Eigen::VectorXd &prev_values,
    TimeInfo time_info,
    int equasion_equations_number,
    int extra_equations_used
)
{
    QMap<int, int> ind_map = this->getIndicesMap();

    residual(ind_map[0]) += this->currency;
    residual(ind_map[1]) += -this->currency;
}

int CurrencySourceMathModel::numberOfExtraEquations()
{
    return 0;
}

QString CurrencySourceMathModel::toString()
{
    QString str = QString("element: CurrencySourceMathModel | currency: %1\n").arg(this->currency);

    str += ElementMathModel::toString();
    return str;
}
