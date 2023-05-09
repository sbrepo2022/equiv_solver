#include "wiremodel.h"
#include <cmath>

WireGraphicsItem::WireGraphicsItem(QObject *parent) : FieldGraphicsItem(parent)
{
    this->init();
}

WireGraphicsItem::WireGraphicsItem(const WireGraphicsItem &obj) : FieldGraphicsItem(obj)
{
    this->init();

    this->line_color = obj.line_color;
    this->line_hover_color = obj.line_hover_color;
    this->disable_color = obj.disable_color;
    this->line_width = obj.line_width;
    this->center = obj.center;
    this->setVisibility(obj.isVisible());
}

WireGraphicsItem::~WireGraphicsItem()
{

}

void WireGraphicsItem::init()
{
    this->line_color = QColor(0, 0, 0);
    this->line_hover_color = QColor(220, 20, 0);
    this->disable_color = QColor(50, 50, 50);
    this->line_width = 4;
}

void WireGraphicsItem::attachFieldElementModel()
{
    WireModel *model = this->getModel<WireModel>();
    if (model == nullptr) return;

    connect(model, &WireModel::wireChanged, this, &WireGraphicsItem::paramsUpdated);
    this->setCenter(QPoint(0, 0));
}

void WireGraphicsItem::detachFieldElementModel()
{
    WireModel *model = this->getModel<WireModel>();
    if (model == nullptr) return;

    disconnect(model, &WireModel::wireChanged, this, &WireGraphicsItem::paramsUpdated);
}

QRectF WireGraphicsItem::boundingRect() const  // ????
{
    qreal cell_width = this->cell_size.width();
    qreal cell_height = this->cell_size.height();
    QRect cells_rect = this->getModel<WireModel>()->getCellsRect();
    return QRectF(
        QPointF(
            (cells_rect.left() - 1) * cell_width,
            (cells_rect.top() - 1) * cell_height
        ),
        QPointF(
            (cells_rect.left() + cells_rect.width()) * cell_width,
            (cells_rect.top() + cells_rect.height()) * cell_height
        )
    );
}

QPainterPath WireGraphicsItem::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    QList<QLineF> lines_list_f = this->getTransformedLines();

    for (int i = 0; i < lines_list_f.count(); i++) {
        QPainterPath line_path = this->calcPathForLine(lines_list_f[i]);
        path = path.united(line_path);
    }

    return path;
}

int WireGraphicsItem::getLineIndexByCoordinate(QPointF in_item_pos) const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    QList<QLineF> lines_list_f = this->getTransformedLines();

    for (int i = 0; i < lines_list_f.count(); i++) {
        QPainterPath line_path = this->calcPathForLine(lines_list_f[i]);
        if (line_path.contains(in_item_pos))
            return i;
    }
    return -1;
}

void WireGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);

    emit hoverEntered(this);
}

void WireGraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverMoveEvent(event);

    cursor_pos_cache = event->pos();

    if (this->mark_hovered) {
        this->update();
    }

    emit hoverMoved(this, event);
}

void WireGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event);

    emit hoverLeaved(this);
}

void WireGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    emit mousePressed(this, event);
}

QPointF WireGraphicsItem::updatedPos() {
    return QPointF(this->cell_size.width() * (0.5 + this->center.x()), this->cell_size.height() * (0.5 + this->center.y()));
}

QList<QLineF> WireGraphicsItem::getTransformedLines() const
{
    QList<QLine> lines_list;
    if (this->getModel<WireModel>() != nullptr) lines_list = this->getModel<WireModel>()->getLinesList();
    QList<QLineF> lines_list_f;
    QTransform transform;
    transform = transform.scale(this->cell_size.width(),this->cell_size.height());
    for (int i = 0; i < lines_list.count(); i++) {
        QLineF line_f = transform.map(lines_list[i]);
        lines_list_f.append(line_f);
    }
    return lines_list_f;
}

QHash<QPointF, int> WireGraphicsItem::getTransformedLinesEndings() const
{
    QHash<QPoint, int> lines_endings;
    if (this->getModel<WireModel>() != nullptr) lines_endings = this->getModel<WireModel>()->getLinesEndings();
    QHash<QPointF, int> lines_endings_f;
    QTransform transform;
    transform = transform.scale(this->cell_size.width(),this->cell_size.height());
    for (QPoint point : lines_endings.keys()) {
        QPointF point_f = transform.map(point);
        lines_endings_f[point_f] = lines_endings[point];
    }
    return lines_endings_f;
}

QPainterPath WireGraphicsItem::calcPathForLine(QLineF line_f) const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    // Умножение длины вектора нормали на 0.95 необходимо для возможности размещять элементы сбоку линий
    qreal dist = (this->cell_size.width() + this->cell_size.height()) / 2 * 0.95;

    QPointF a = line_f.p2() - line_f.p1();
    QPointF n = QPointF(-a.y(), a.x());
    if (n.manhattanLength() != 0.0) n = n / n.manhattanLength();
    if (a.manhattanLength() != 0.0) a = a / a.manhattanLength();

    // Уменьшение длины коллизии линии на 0.05 необходимо для возможности состыковки линии с элементами
    QVector<QPointF> bounding_points = {
        line_f.p2() + n * dist - a * 0.05,
        line_f.p1() + n * dist + a * 0.05,
        line_f.p1() - n * dist + a * 0.05,
        line_f.p2() - n * dist - a * 0.05,
    };
    QPolygonF bounding_polygon(bounding_points);
    path.addPolygon(bounding_polygon);

    return path;
}

void WireGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen_lines(this->mark_collided ? this->disable_color : this->line_color, this->line_width, Qt::SolidLine, Qt::SquareCap);
    QPen pen_lines_hovered(this->mark_hovered || this->mark_selected ? this->line_hover_color : this->line_color, this->line_width, Qt::SolidLine, Qt::SquareCap);

    int hovered_line_index = this->getLineIndexByCoordinate(cursor_pos_cache);
    QList<QLineF> lines_list_f = this->getTransformedLines();

    for (int i = 0; i < lines_list_f.count(); i++) {
        if (i == hovered_line_index) {
            painter->setPen(pen_lines_hovered);
        }
        else {
            painter->setPen(pen_lines);
        }
        painter->drawLine(lines_list_f[i]);
    }

    QPen pen_points(this->line_hover_color, this->line_width * 2, Qt::SolidLine, Qt::SquareCap);
    QHash<QPointF, int> line_endings_f = this->getTransformedLinesEndings();
    painter->setPen(pen_points);
    for (QPointF point : line_endings_f.keys()) {
        if (line_endings_f[point] > 2) {
            painter->drawPoint(point);
        }
    }

    QPointF lines_center = this->boundingRect().center();
    if (this->mark_collided) {
        forbidden_renderer.render(painter, QRectF(-this->cell_size.width() / 2 * 4 + lines_center.x(), -this->cell_size.height() / 2 * 4 + lines_center.y(),
                                                  this->cell_size.width() * 4, this->cell_size.height() * 4));
    }

    if (this->debug) {
        QPen debugLines(QColor(255, 0, 0), 1, Qt::DashLine, Qt::SquareCap);
        painter->setPen(debugLines);
        painter->drawRect(this->boundingRect());
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void WireGraphicsItem::setCellSize(const QSizeF &cell_size) {
    FieldGraphicsItem::setCellSize(cell_size);
    this->setPos(this->updatedPos());
}

void WireGraphicsItem::setCenter(const QPoint &center) {
    this->center = center;
    this->setPos(this->updatedPos());
}

void WireGraphicsItem::setLineHoverColor(const QColor &line_hovered_color)
{
    this->line_hover_color = line_hovered_color;
    this->paramsUpdated();
}

void WireGraphicsItem::setLineColor(const QColor &line_color)
{
    this->line_color = line_color;
    this->paramsUpdated();
}

void WireGraphicsItem::setLineWidth(qreal line_width)
{
    this->line_width = line_width;
    this->paramsUpdated();
}


void WireGraphicsItem::setVisibility(bool visible) {
    if (visible) {
        this->show();
    }
    else {
        this->hide();
    }
}



WireModel::WireModel(QObject *parent) : FieldElementModel(parent)
{
    this->cells_rect = QRect(0, 0, 0, 0);
    this->setGraphicsItem(FieldElementModel::createGraphicsItem<WireGraphicsItem>(this));
}

WireModel::WireModel(const WireModel &obj) : FieldElementModel(obj.parent())
{
    this->cells_rect = obj.cells_rect;
    this->lines_list = obj.lines_list;
    this->setGraphicsItem(obj.cloneGraphicsItem<WireGraphicsItem>(this));
}

WireModel::~WireModel()
{

}

QList<WireModel*> WireModel::removeWireLine(int line_index)
{
    QList<QList<QLine>> lines_groups;

    if (line_index >= this->lines_list.count()) return QList<WireModel*>();

    this->lines_list.removeAt(line_index);
    if (this->lines_list.count() == 0) return QList<WireModel*>();

    lines_groups = this->regroupWire(this->lines_list);

    // создание моделей
    QList<WireModel*> result;
    for (QList<QLine> lines_list : lines_groups) {
        WireModel* new_wire_model = new WireModel(*(this));
        new_wire_model->setLinesList(lines_list);
        result.append(new_wire_model);
    }

    return result;
}

QList<QList<QLine>> WireModel::regroupWire(const QList<QLine> &lines)
{
    QList<QList<QLine>> result;

    for (QLine line : lines) {
        int group1_index = -1;
        int group2_index = -1;

        for (int i = 0; i < result.count(); i++) {
            for (QLine group_line : result[i]) {
                if (line.p1() == group_line.p1() || line.p1() == group_line.p2()) {
                    group1_index = i;
                }
                if (line.p2() == group_line.p1() || line.p2() == group_line.p2()) {
                    group2_index = i;
                }
            }
        }

        if (group1_index == -1 && group2_index == -1) { // соприкосновения не найдены
            QList<QLine> new_group;
            new_group << line;
            result.append(new_group);
        }
        if (group1_index != -1 && group2_index == -1) { // присоединение к группе 1
            result[group1_index].append(line);
        }
        if (group1_index == -1 && group2_index != -1) { // присоединение к группе 2
            result[group2_index].append(line);
        }
        if (group1_index != -1 && group2_index != -1) { // замыкание на 1 группу с двух сторон или объединение двух групп
            result[group1_index].append(line);
            if (group1_index != group2_index) {
                QList<QLine> group2 = result[group2_index];
                result[group1_index].append(group2);
                result.removeAt(group2_index);
            }
        }
    }

    return result;
}

QList<QLine> WireModel::recalculateWireStructure(const QList<QLine> &lines, QHash<QPoint, int> *lines_endings)
{
    QList<QLine> result_lines = lines;

    *lines_endings = WireModel::countLineEndings(result_lines);

    // Объединение отрезков лежащих на одной прямой и пересекающихся/соприкасающихся
    QLine line1, line2, line_new;
    for (int axis = 0; axis <= 1; axis++) {
        for (int i = 0; i < result_lines.count(); i++) {
            for (int j = 0; j < result_lines.count(); j++) {
                if (i == j) continue;
                line1 = result_lines[i];
                line2 = result_lines[j];

                // Проверка наложений/состыковок вдоль X/Y
                if (WireModel::mergeOverlappingLines(*lines_endings, line1, line2, &line_new, axis)) {
                    result_lines[i] = line_new;
                    result_lines.removeAt(j);
                    j--;
                    if (j < i) i--;
                    continue;
                }
            }
        }
    }

    // Проверка перпендикулярного окончания одного отрезка в середине другого
    for (int i = 0; i < result_lines.count(); i++) {
        for (int j = 0; j < result_lines.count(); j++) {
            if (i == j) continue;
            line1 = result_lines[i];
            line2 = result_lines[j];

            // Проверка пересечения перпендикулярных линий
            QList<QLine> line1_replacement, line2_replacement;
            if (WireModel::mergePerpendicularTouching(line1, line2, &line1_replacement, &line2_replacement)) {
                result_lines[i] = line1_replacement[0];
                result_lines[j] = line2_replacement[0];
                if (line1_replacement.count() > 1)
                    result_lines.append(line1_replacement[1]);
                if (line2_replacement.count() > 1)
                    result_lines.append(line2_replacement[1]);
            }
        }
    }

    // Повторное вычисление QHash<QPoint, int> (для будущей отрисовки точек)
    *lines_endings = WireModel::countLineEndings(result_lines);

    return result_lines;
}

QHash<QPoint, int> WireModel::countLineEndings(const QList<QLine>& lines) {
    QHash<QPoint, int> result;
    for (const QLine& line : lines) {
        QPoint startPoint = line.p1();
        QPoint endPoint = line.p2();
        result[startPoint]++;
        result[endPoint]++;
    }
    return result;
}

bool WireModel::mergeOverlappingLines(const QHash<QPoint, int> &lines_endings, const QLine &line1, const QLine &line2,  QLine *line_result = nullptr, bool axis = 0)
{
    QLine line1_s = line1, line2_s = line2, line_swap, line_new;
    bool is_intersected = false;

    if (axis == 1) { // Проверка наложений/состыковок вдоль оси X
        line1_s = QLine(QPoint(line1.y1(), line1.x1()), QPoint(line1.y2(), line1.x2()));
        line2_s = QLine(QPoint(line2.y1(), line2.x1()), QPoint(line2.y2(), line2.x2()));
    }

    if (line1_s.x1() == line1_s.x2() && line2_s.x1() == line2_s.x2() && line1_s.x1() == line2_s.x1()) {

        if (line1_s.y2() < line1_s.y1())
            line1_s = QLine(line1_s.p2(), line1_s.p1());

        if (line2_s.y2() < line2_s.y1())
            line2_s = QLine(line2_s.p2(), line2_s.p1());

        if (line2_s.y2() < line1_s.y2()) {
            line_swap = line2_s;
            line2_s = line1_s;
            line1_s = line_swap;
        }
        // Итого: точка 2 линии 2 всегда выше точки 2 линии 1, точка 2 у каждой линии всегда выше точки 1 у той же линии
        if (line2_s.y1() < line1_s.y2()) { // Линии строго накладываются
            if (line2_s.y1() < line1_s.y1())
                line_new = QLine(line2_s.p1(), line2_s.p2());
            else
                line_new = QLine(line1_s.p1(), line2_s.p2());
            is_intersected = true;
        }
        else if (line2_s.y1() == line1_s.y2()) { // Линии строго соприкасаются
            QPoint test_point = axis == 1 ? QPoint(line2_s.y1(), line2_s.x1()) : line2_s.p1();
            if (lines_endings[test_point] == 2) {
                line_new = QLine(line1_s.p1(), line2_s.p2());
                is_intersected = true;
            }
        }

        if (is_intersected && line_result != nullptr) {
            *line_result = line_new;

            if (axis == 1) {
                *line_result = QLine(QPoint(line_new.y1(), line_new.x1()), QPoint(line_new.y2(), line_new.x2()));
            }
        }

        return is_intersected;
    }

    return false;
}

bool WireModel::mergePerpendicularTouching(const QLine &line1, const QLine &line2,
                                           QList<QLine> *line1_replacement, QList<QLine> *line2_replacement)
{
    QLine line1_s = line1, line2_s = line2, line_swap;
    QPoint intersection_point;
    bool is_intersected = false;

    line1_replacement->clear();
    line2_replacement->clear();
    *line1_replacement << line1;
    *line2_replacement << line2;

    // проверка, что линии строго паралельны осям координат и перпендикулярны друг другу
    if ((line1_s.x1() == line1_s.x2() && line2_s.y1() == line2_s.y2()) || (line1_s.y1() == line1_s.y2() && line2_s.x1() == line2_s.x2())) {
        // пусть line1_s будет горизонтальная, line2_s вертикальная
        if (line1_s.x1() == line1_s.x2()) {
            line_swap = line2_s;
            line2_s = line1_s;
            line1_s = line_swap;
        }

        // пусть точки в line1_s идут по возрастанию x, а в line2_s по возростанию y
        if (line1_s.x1() > line1_s.x2()) {
            line1_s = QLine(line1_s.p2(), line1_s.p1());
        }

        if (line2_s.y1() > line2_s.y2()) {
            line2_s = QLine(line2_s.p2(), line2_s.p1());
        }

        // проверка пересечений
        if ( ((line1_s.y1() == line2_s.y1() || line1_s.y1() == line2_s.y2()) && line1_s.x1() < line2_s.x1() && line2_s.x1() < line1_s.x2()) ||
             ((line2_s.x1() == line1_s.x1() || line2_s.x1() == line1_s.x2()) && line2_s.y1() < line1_s.y1() && line1_s.y1() < line2_s.y2())) {
            is_intersected = true;
            intersection_point = QPoint(line2_s.x1(), line1_s.y1());
        }

        // создание новых линий
        if (is_intersected) {
            if (line1.p1() == intersection_point || line1.p2() == intersection_point) {
                line2_replacement->clear();
                *line2_replacement << QLine(line2.p1(), intersection_point) << QLine(intersection_point, line2.p2());
            }
            if (line2.p1() == intersection_point || line2.p2() == intersection_point) {
                line1_replacement->clear();
                *line1_replacement << QLine(line1.p1(), intersection_point) << QLine(intersection_point, line1.p2());
            }
            return true;
        }
    }

    return false;
}

void WireModel::updateCellsRect()
{
    QRect bounding_rect;
    for (const QLine& line : this->lines_list) {
        QPoint p1 = line.p1();
        QPoint p2 = line.p2();
        QPoint topLeft(qMin(p1.x(), p2.x()), qMin(p1.y(), p2.y()));
        QPoint bottomRight(qMax(p1.x(), p2.x()), qMax(p1.y(), p2.y()));
        QRect rect(topLeft, bottomRight);
        bounding_rect = bounding_rect.united(rect);
    }

    this->cells_rect = bounding_rect;
}

