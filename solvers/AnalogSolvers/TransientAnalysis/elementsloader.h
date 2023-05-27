#ifndef ELEMENTSLOADER_H
#define ELEMENTSLOADER_H

#include <iostream>

#include <QDomDocument>
#include <QMap>
#include <QList>
#include <QString>
#include <QFile>

#include "Eigen/Dense"

#include "elementmathmodel.h"
#include "element_math_models/resistormathmodel.h"
#include "element_math_models/capacitormathmodel.h"
#include "element_math_models/inductormathmodel.h"
#include "element_math_models/currencysourcemathmodel.h"
#include "element_math_models/voltagesourcemathmodel.h"

class SolverSettings {
public:
    double analysis_time;
    double start_time_step;
    double max_correction_error;
    int max_newtons_iterations;
};

class ElementsLoader
{
private:
    QMap<QString, ElementMathModel*> registered_math_models;
    QList<ElementMathModel*> net_list;
    SolverSettings solver_settings;
    int equasion_equations_number;
    int extra_equations_number;

    void registerTypes();
    void parseSolverSettings(const QDomDocument &xml_doc);
    void parseElements(const QDomDocument &xml_doc);

public:
    ElementsLoader();
    ~ElementsLoader();

    SolverSettings getSolverSettings() { return this->solver_settings; }
    int getMatrixSize() { return this->equasion_equations_number + this->extra_equations_number; }
    void load(const char *netlist_filename);
    void get_model_jacobian(Eigen::MatrixXd &jacobian, const Eigen::VectorXd &values, TimeInfo time_info);
    void get_model_residual(Eigen::VectorXd &residual, const Eigen::VectorXd &values, const Eigen::VectorXd &prev_values, TimeInfo time_info);
    QString toString();
};

#endif // ELEMENTSLOADER_H
