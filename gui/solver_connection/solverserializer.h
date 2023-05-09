#ifndef SOLVERSERIALIZER_H
#define SOLVERSERIALIZER_H

#include <QObject>
#include <QFile>

class SolverSerializer : public QObject
{
    Q_OBJECT
public:
    explicit SolverSerializer(QObject *parent = nullptr);

    // Метод должен возвращать файл, в который будет производиться сохранение
    virtual QString getFileToSave() = 0;

public slots:
    QString serialize() {
        QString filename = this->getFileToSave();
        QFile file_to_save = QFile(filename);
        if (!file_to_save.open(QIODevice::WriteOnly | QIODevice::Text))
            return "";

        this->processSerialization(file_to_save);

        return filename;
    }

    virtual void processSerialization(const QFile &file_to_save) = 0;
};

#endif // SOLVERSERIALIZER_H
