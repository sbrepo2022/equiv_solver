#ifndef ELEMENTMATHMODEL_H
#define ELEMENTMATHMODEL_H

#include <QMap>
#include <QList>
#include <QDomNode>

#include "Eigen/Dense"

class TimeInfo {
public:
    double t;
    double dt;
};

class ElementMathModel
{
private:
    // Первый int - локальный индекс, второй int - соответствующий локальному глобальный индекс
    QMap<int, int> local_to_global_indices;

public:
    ElementMathModel();
    virtual ~ElementMathModel();

    QMap<int, int> getIndicesMap() { return this->local_to_global_indices; }

    virtual QString getTypeName() = 0;
    virtual ElementMathModel* createElementFromXmlNode(const QDomNode &dom_node) = 0;

    virtual void addDataToJacobian(
        Eigen::MatrixXd &jacobian,
        const Eigen::VectorXd &values,
        TimeInfo time_info,
        int equasion_equations_number,
        int extra_equations_used
    ) = 0;

    virtual void addDataToResidual(
        Eigen::VectorXd &residual,
        const Eigen::VectorXd &values,
        const Eigen::VectorXd &prev_values,
        TimeInfo time_info,
        int equasion_equations_number,
        int extra_equations_used
    ) = 0;

    virtual int numberOfExtraEquations() = 0;
    virtual QString toString();

protected:
    void loadConnections(const QDomNode &dom_node);
};

#endif // ELEMENTMATHMODEL_H
