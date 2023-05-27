#ifndef INDUCTORMATHMODEL_H
#define INDUCTORMATHMODEL_H

#include "elementmathmodel.h"

class InductorMathModel : public ElementMathModel
{
public:
    InductorMathModel();

    virtual QString getTypeName() { return QString("Inductor"); }
    virtual ElementMathModel* createElementFromXmlNode(const QDomNode &dom_node);

    virtual void addDataToJacobian(
        Eigen::MatrixXd &jacobian,
        const Eigen::VectorXd &values,
        TimeInfo time_info,
        int equasion_equations_number,
        int extra_equations_used
    );

    virtual void addDataToResidual(
        Eigen::VectorXd &residual,
        const Eigen::VectorXd &values,
        const Eigen::VectorXd &prev_values,
        TimeInfo time_info,
        int equasion_equations_number,
        int extra_equations_used
    );

    virtual int numberOfExtraEquations();
    virtual QString toString();

private:
    double induction;
};

#endif // INDUCTORMATHMODEL_H
