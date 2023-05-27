#include "solverserializer.h"

SolverSerializer::SolverSerializer(QObject *parent) : QObject(parent)
{

}

QString SolverSerializer::serialize() {
    QString filename = this->getFileToSave();
    QFile file_to_save = QFile(filename);
    if (!file_to_save.open(QIODevice::WriteOnly | QIODevice::Text))
        return "";

    try {
        this->processSerialization(&file_to_save);
    }
    catch (...) {
        file_to_save.close();
        throw;
    }

    file_to_save.close();
    return filename;
}
