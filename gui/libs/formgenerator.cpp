#include "formgenerator.h"

FormGenerator::FormGenerator(QObject *parent) : QObject(parent) {}

void FormGenerator::generateForm(QWidget *parent_widget, QFormLayout *layout, const QList<QMap<QString, QVariant>> &widget_properties, QObject *props_owner) {
    for (int i = 0; i < widget_properties.size(); i++) {
        QMap<QString, QVariant> prop_elem = widget_properties[i];
        QVariant prop_val = props_owner->property(prop_elem["name"].toString().toStdString().c_str());
        QWidget *field = nullptr;

        // adding property components
        if (strcmp(prop_val.typeName(), "bool") == 0) {
            QCheckBox *check = new QCheckBox(parent_widget);
            check->setChecked(prop_val.toBool());
            connect(check, &QCheckBox::stateChanged, props_owner, [=](bool val) {
                props_owner->setProperty(prop_elem["name"].toString().toStdString().c_str(), val);
            });
            field = check;
        }
        else if (strcmp(prop_val.typeName(), "int") == 0) {
            QSpinBox *spin = new QSpinBox(parent_widget);
            if (prop_elem.find("min") != prop_elem.end())
                spin->setMinimum(prop_elem["min"].toInt());
            if (prop_elem.find("max") != prop_elem.end())
                spin->setMaximum(prop_elem["max"].toInt());
            spin->setValue(prop_val.toInt());
            connect(spin, &QSpinBox::valueChanged, props_owner, [=](int val) {
                props_owner->setProperty(prop_elem["name"].toString().toStdString().c_str(), val);
            });
            field = spin;
        }
        else if (strcmp(prop_val.typeName(), "double") == 0) {
            QDoubleSpinBox *spin = new QDoubleSpinBox(parent_widget);
            if (prop_elem.find("min") != prop_elem.end())
                spin->setMinimum(prop_elem["min"].toDouble());
            if (prop_elem.find("max") != prop_elem.end())
                spin->setMaximum(prop_elem["max"].toDouble());
            if (prop_elem.find("decimals") != prop_elem.end())
                spin->setDecimals(prop_elem["decimals"].toInt());
            spin->setValue(prop_val.toDouble());
            connect(spin, &QDoubleSpinBox::valueChanged, props_owner, [=](double val) {
                props_owner->setProperty(prop_elem["name"].toString().toStdString().c_str(), val);
            });
            field = spin;
        }
        else if (strcmp(prop_val.typeName(), "QString") == 0) {
            if (prop_elem.find("field_type") != prop_elem.end()) {
                if (prop_elem["field_type"].toString() == "list") {
                    QComboBox *combo = new QComboBox(parent_widget);
                    if (prop_elem.find("variants") != prop_elem.end()) {
                        combo->addItems(prop_elem["variants"].toStringList());
                    }
                    connect(combo, &QComboBox::currentTextChanged, props_owner, [=](const QString &val) {
                        props_owner->setProperty(prop_elem["name"].toString().toStdString().c_str(), val);
                    });
                    field = combo;
                }
                else {
                    QLineEdit *line = new QLineEdit(parent_widget);
                    line->setText(prop_val.toString());
                    connect(line, &QLineEdit::textChanged, props_owner, [=](const QString &val) {
                        props_owner->setProperty(prop_elem["name"].toString().toStdString().c_str(), val);
                    });
                    field = line;
                }
            }
        }
        else {
            field = new QLabel("incorrect property type", parent_widget);
        }

        QString label_str = (prop_elem.find("title") != prop_elem.end()) ? prop_elem["title"].toString() : prop_elem["name"].toString();
        label_str = label_str.replace(0, 1, label_str.at(0).toUpper());
        layout->addRow(new QLabel(label_str.toStdString().c_str()), field);
    }
}

FormGenerator::~FormGenerator() {}
