#ifndef SOLVERSERIALIZER_H
#define SOLVERSERIALIZER_H

#include <QObject>
#include <QFile>
#include <exception>

class SerializationException : std::exception {
public:
    SerializationException(const char* message) : m_message(message) {}

    const char* what() const noexcept override {
        return m_message;
    }

private:
    const char* m_message;
};

class SolverSerializer : public QObject
{
    Q_OBJECT
public:
    explicit SolverSerializer(QObject *parent = nullptr);

    // Метод должен возвращать файл, в который будет производиться сохранение
    virtual QString getFileToSave() = 0;

public slots:
    QString serialize();

    virtual void processSerialization(QIODevice *out) = 0;
};

#endif // SOLVERSERIALIZER_H
