#include "transientanalysissolverresult.h"

TransientAnalysisSolverResult::TransientAnalysisSolverResult(QObject *parent) : SolverResult(parent)
{

}


void TransientAnalysisSolverResult::loadResult()
{
    this->line_series = this->readDataFromCSV();
}

QList<QLineSeries*> TransientAnalysisSolverResult::readDataFromCSV()
{
    QFile file(result_file);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return QList<QLineSeries*>();
    }

    QList<QLineSeries*> series_list;
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList values = line.split(',');

        for (int i = 1; i < values.size(); i++) {
            if (series_list.size() < i)
                series_list.append(new QLineSeries());

            qreal y = values[i].toDouble();
            qreal x = values[0].toDouble();
            series_list[i - 1]->append(x, y);
        }
    }

    file.close();
    return series_list;
}
