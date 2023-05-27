#include "elementsloader.h"

ElementsLoader::ElementsLoader()
    : equasion_equations_number(0),
      extra_equations_number(0)
{

}

void ElementsLoader::load(const char *netlist_filename)
{
    QFile file(netlist_filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // throw;
    }

    QDomDocument xml_document;
    if (!xml_document.setContent(&file)) {
        file.close();
        // throw;
    }

    file.close();

    this->registerTypes();
    this->parseSolverSettings(xml_document);
    this->parseElements(xml_document);
}

ElementsLoader::~ElementsLoader()
{
    for (ElementMathModel *math_model : this->registered_math_models) {
        delete math_model;
    }
}

void ElementsLoader::registerTypes()
{
    ResistorMathModel *resistor = new ResistorMathModel();
    CapacitorMathModel *capacitor = new CapacitorMathModel();
    InductorMathModel *inductor = new InductorMathModel();
    CurrencySourceMathModel *currency_source = new CurrencySourceMathModel();
    VoltageSourceMathModel *voltage_source = new VoltageSourceMathModel();

    this->registered_math_models.insert(resistor->getTypeName(), resistor);
    this->registered_math_models.insert(capacitor->getTypeName(), capacitor);
    this->registered_math_models.insert(inductor->getTypeName(), inductor);
    this->registered_math_models.insert(currency_source->getTypeName(), currency_source);
    this->registered_math_models.insert(voltage_source->getTypeName(), voltage_source);
}

void ElementsLoader::parseSolverSettings(const QDomDocument &xml_doc)
{
    QDomElement root_el = xml_doc.firstChildElement();

    QDomElement solver_settings_el = root_el.firstChildElement("SolverSettings");
    bool ok;

    double analysis_time = solver_settings_el.attribute("analysis_time").toDouble(&ok);
    if (ok) {
        this->solver_settings.analysis_time = analysis_time;
    }

    double start_time_step = solver_settings_el.attribute("start_time_step").toDouble(&ok);
    if (ok) {
        this->solver_settings.start_time_step = start_time_step;
    }

    double max_correction_error = solver_settings_el.attribute("max_correction_error").toDouble(&ok);
    if (ok) {
        this->solver_settings.max_correction_error = max_correction_error;
    }

    int max_newtons_iterations = solver_settings_el.attribute("max_newtons_iterations").toDouble(&ok);
    if (ok) {
        this->solver_settings.max_newtons_iterations = max_newtons_iterations;
    }
}

void ElementsLoader::parseElements(const QDomDocument &xml_doc)
{
    QDomElement root_el = xml_doc.firstChildElement();

    QDomElement net_list_tag = root_el.firstChildElement("NetList");
    for (QString type_name : this->registered_math_models.keys()) {
        QDomNodeList element_tags = net_list_tag.elementsByTagName(type_name);

        for (int i = 0; i < element_tags.length(); i++) {
            ElementMathModel *element_model = this->registered_math_models[type_name]->createElementFromXmlNode(element_tags.item(i));
            this->net_list.append(element_model);

            QList<int> element_nodes_indices = element_model->getIndicesMap().values();
            int max_node_number = *std::max_element(element_nodes_indices.begin(), element_nodes_indices.end());
            if (this->equasion_equations_number < max_node_number + 1) {
                this->equasion_equations_number = max_node_number + 1;
            }
            this->extra_equations_number += element_model->numberOfExtraEquations();
        }
    }
}

void ElementsLoader::get_model_jacobian(Eigen::MatrixXd &jacobian, const Eigen::VectorXd &values, TimeInfo time_info)
{
    int matrix_size = this->getMatrixSize();
    jacobian.resize(matrix_size, matrix_size);
    jacobian.setZero(matrix_size, matrix_size);

    int extra_equations_used = 0;
    for (ElementMathModel *element_model : this->net_list) {
        element_model->addDataToJacobian(jacobian, values, time_info, this->equasion_equations_number, extra_equations_used);
        extra_equations_used += element_model->numberOfExtraEquations();
    }
}

void ElementsLoader::get_model_residual(Eigen::VectorXd &residual, const Eigen::VectorXd &values, const Eigen::VectorXd &prev_values, TimeInfo time_info)
{
    int vector_size = this->getMatrixSize();
    residual.resize(vector_size);
    residual.setZero(vector_size);

    int extra_equations_used = 0;
    for (ElementMathModel *element_model : this->net_list) {
        element_model->addDataToResidual(residual, values, prev_values, time_info, this->equasion_equations_number, extra_equations_used);
        extra_equations_used += element_model->numberOfExtraEquations();
    }

    residual = -residual;
}

QString ElementsLoader::toString() {
    QString str;

    str += "Elements loaded:\n";

    for (ElementMathModel *element_model : this->net_list) {
        str += element_model->toString();
    }

    return str;
}
