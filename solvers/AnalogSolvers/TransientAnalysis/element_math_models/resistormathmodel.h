#ifndef RESISTORMATHMODEL_H
#define RESISTORMATHMODEL_H

#include "elementmathmodel.h"

class ResistorMathModel : public ElementMathModel
{
public:
    ResistorMathModel();

    virtual QString getTypeName() { return QString("Resistor"); }
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
    double resistance;
};

#endif // RESISTORMATHMODEL_H
