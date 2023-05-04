#include <QtTest>
#include <QHash>
#include <QList>

#include "../gui/field/wire/wiremodel.h"

// add necessary includes here

class WireTests : public QObject
{
    Q_OBJECT

private slots:
    void test_recalculateWireStructure_case1();
    void test_recalculateWireStructure_case2();
    void test_recalculateWireStructure_case3();
    void test_recalculateWireStructure_case4();
    void test_recalculateWireStructure_case5();
    void test_recalculateWireStructure_case6();
    void test_recalculateWireStructure_case7();

    void test_recalculateWireStructure_case8();
    void test_recalculateWireStructure_case9();
    void test_recalculateWireStructure_case10();
    void test_recalculateWireStructure_case11();
    void test_recalculateWireStructure_case12();
    void test_recalculateWireStructure_case13();
};

void WireTests::test_recalculateWireStructure_case1()
{
    // Горизонтальный тест

    QHash<QPoint, int> line_endings;
    QList<QLine> lines_list;

    lines_list << QLine(QPoint(0, 0), QPoint(0, 10)) << QLine(QPoint(0, 10), QPoint(0, 20));
    QList<QLine> result_lines = WireModel::recalculateWireStructure(lines_list, &line_endings);

    QCOMPARE(result_lines[0], QLine(QPoint(0, 0), QPoint(0, 20)));
    int sum = 0;
    for (int val : line_endings.values()) {
        if (val > 2) sum++;
    }
    QVERIFY2(sum == 0, "Zero collision points");
    QVERIFY2(result_lines.count() == 1, "1 line");
}

void WireTests::test_recalculateWireStructure_case2()
{
    // Вертикальный тест

    QHash<QPoint, int> line_endings;
    QList<QLine> lines_list;

    lines_list << QLine(QPoint(0, 0), QPoint(10, 0)) << QLine(QPoint(10, 0), QPoint(20, 0));
    QList<QLine> result_lines = WireModel::recalculateWireStructure(lines_list, &line_endings);

    QCOMPARE(result_lines[0], QLine(QPoint(0, 0), QPoint(20, 0)));
    int sum = 0;
    for (int val : line_endings.values()) {
        if (val > 2) sum++;
    }
    QVERIFY2(sum == 0, "Zero collision points");
    QVERIFY2(result_lines.count() == 1, "1 line");
}

void WireTests::test_recalculateWireStructure_case3()
{
    // Тест уголком

    QHash<QPoint, int> line_endings;
    QList<QLine> lines_list;

    lines_list << QLine(QPoint(0, 0), QPoint(10, 0)) << QLine(QPoint(10, 0), QPoint(10, 10));
    QList<QLine> result_lines = WireModel::recalculateWireStructure(lines_list, &line_endings);

    QVERIFY(result_lines[0] == QLine(QPoint(0, 0), QPoint(10, 0)) && result_lines[1] == QLine(QPoint(10, 0), QPoint(10, 10)));
    int sum = 0;
    for (int val : line_endings.values()) {
        if (val > 2) sum++;
    }
    QVERIFY2(sum == 0, "Zero collision points");
    QVERIFY2(result_lines.count() == 2, "2 line");
}

void WireTests::test_recalculateWireStructure_case4()
{
    // Тест тремя линиями

    QHash<QPoint, int> line_endings;
    QList<QLine> lines_list;

    lines_list << QLine(QPoint(0, 0), QPoint(0, 10)) << QLine(QPoint(0, 10), QPoint(0, 20)) << QLine(QPoint(0, 20), QPoint(0, 30));
    QList<QLine> result_lines = WireModel::recalculateWireStructure(lines_list, &line_endings);

    QCOMPARE(result_lines[0], QLine(QPoint(0, 0), QPoint(0, 30)));
    int sum = 0;
    for (int val : line_endings.values()) {
        if (val > 2) sum++;
    }
    QVERIFY2(sum == 0, "Zero collision points");
    QVERIFY2(result_lines.count() == 1, "1 line");
}

void WireTests::test_recalculateWireStructure_case5()
{
    // Тест наложения (горизонтальный)

    QHash<QPoint, int> line_endings;
    QList<QLine> lines_list;

    lines_list << QLine(QPoint(0, 0), QPoint(15, 0)) << QLine(QPoint(10, 0), QPoint(20, 0)) << QLine(QPoint(16, 0), QPoint(30, 0));
    QList<QLine> result_lines = WireModel::recalculateWireStructure(lines_list, &line_endings);

    QCOMPARE(result_lines[0], QLine(QPoint(0, 0), QPoint(30, 0)));
    int sum = 0;
    for (int val : line_endings.values()) {
        if (val > 2) sum++;
    }
    QVERIFY2(sum == 0, "Zero collision points");
    QVERIFY2(result_lines.count() == 1, "1 line");
}

void WireTests::test_recalculateWireStructure_case6()
{
    // Тест наложения (вертикальный)

    QHash<QPoint, int> line_endings;
    QList<QLine> lines_list;

    lines_list << QLine(QPoint(0, 5), QPoint(0, 25)) << QLine(QPoint(0, 10), QPoint(0, 20)) << QLine(QPoint(0, 10), QPoint(0, 30));
    QList<QLine> result_lines = WireModel::recalculateWireStructure(lines_list, &line_endings);

    QCOMPARE(result_lines[0], QLine(QPoint(0, 5), QPoint(0, 30)));
    int sum = 0;
    for (int val : line_endings.values()) {
        if (val > 2) sum++;
    }
    QVERIFY2(sum == 0, "Zero collision points");
    QVERIFY2(result_lines.count() == 1, "1 line");
}

void WireTests::test_recalculateWireStructure_case7()
{
    // перекрестия (три конца в одной точке)

    QHash<QPoint, int> line_endings;
    QList<QLine> lines_list;

    lines_list << QLine(QPoint(0, 0), QPoint(0, 10)) << QLine(QPoint(0, 10), QPoint(0, 20)) << QLine(QPoint(0, 10), QPoint(10, 10));
    QList<QLine> result_lines = WireModel::recalculateWireStructure(lines_list, &line_endings);

    QPoint intersection = QPoint(0, 0);
    for (QPoint key : line_endings.keys()) {
        if (line_endings[key] > 2) intersection = key;
    }
    QCOMPARE(intersection, QPoint(0, 10));
}

void WireTests::test_recalculateWireStructure_case8()
{
    // перпендикуляр (полное пересечение)

    QHash<QPoint, int> line_endings;
    QList<QLine> lines_list;

    lines_list << QLine(QPoint(0, 10), QPoint(20, 10)) << QLine(QPoint(10, 0), QPoint(10, 20));
    QList<QLine> result_lines = WireModel::recalculateWireStructure(lines_list, &line_endings);

    QVERIFY(result_lines.count() == 2);
}

void WireTests::test_recalculateWireStructure_case9()
{
    // перпендикуляр (пересечение 1)

    QHash<QPoint, int> line_endings;
    QList<QLine> lines_list;

    lines_list << QLine(QPoint(0, 0), QPoint(0, 20)) << QLine(QPoint(0, 10), QPoint(10, 10));
    QList<QLine> result_lines = WireModel::recalculateWireStructure(lines_list, &line_endings);

    QPoint intersection = QPoint(0, 0);
    for (QPoint key : line_endings.keys()) {
        if (line_endings[key] > 2) intersection = key;
    }
    QCOMPARE(intersection, QPoint(0, 10));
}

void WireTests::test_recalculateWireStructure_case10()
{
    // перпендикуляр (пересечение 2)

    QHash<QPoint, int> line_endings;
    QList<QLine> lines_list;

    lines_list << QLine(QPoint(10, 0), QPoint(10, 20)) << QLine(QPoint(0, 10), QPoint(10, 10));
    QList<QLine> result_lines = WireModel::recalculateWireStructure(lines_list, &line_endings);

    QPoint intersection = QPoint(0, 0);
    for (QPoint key : line_endings.keys()) {
        if (line_endings[key] > 2) intersection = key;
    }
    QCOMPARE(intersection, QPoint(10, 10));
}

void WireTests::test_recalculateWireStructure_case11()
{
    // перпендикуляр (пересечение 3)

    QHash<QPoint, int> line_endings;
    QList<QLine> lines_list;

    lines_list << QLine(QPoint(0, 0), QPoint(20, 0)) << QLine(QPoint(10, 0), QPoint(10, 10));
    QList<QLine> result_lines = WireModel::recalculateWireStructure(lines_list, &line_endings);

    QPoint intersection = QPoint(0, 0);
    for (QPoint key : line_endings.keys()) {
        if (line_endings[key] > 2) intersection = key;
    }
    QCOMPARE(intersection, QPoint(10, 0));
}

void WireTests::test_recalculateWireStructure_case12()
{
    // перпендикуляр (пересечение 4)

    QHash<QPoint, int> line_endings;
    QList<QLine> lines_list;

    lines_list << QLine(QPoint(0, 10), QPoint(20, 10)) << QLine(QPoint(10, 0), QPoint(10, 10));
    QList<QLine> result_lines = WireModel::recalculateWireStructure(lines_list, &line_endings);

    QPoint intersection = QPoint(0, 0);
    for (QPoint key : line_endings.keys()) {
        if (line_endings[key] > 2) intersection = key;
    }
    QCOMPARE(intersection, QPoint(10, 10));
}

void WireTests::test_recalculateWireStructure_case13()
{
    // перпендикуляр (пересечение 5)

    QHash<QPoint, int> line_endings;
    QList<QLine> lines_list;

    lines_list << QLine(QPoint(10, 30), QPoint(10, 10)) << QLine(QPoint(40, 20), QPoint(10, 20));
    QList<QLine> result_lines = WireModel::recalculateWireStructure(lines_list, &line_endings);

    QPoint intersection = QPoint(0, 0);
    for (QPoint key : line_endings.keys()) {
        if (line_endings[key] > 2) intersection = key;
    }
    QCOMPARE(intersection, QPoint(10, 20));
}

QTEST_APPLESS_MAIN(WireTests)

#include "tst_wiretests.moc"
