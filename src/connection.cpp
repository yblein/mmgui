#include "connection.hpp"

#include "node.hpp"
#include "handleitem.hpp"

#include <QPen>
#include <QPainter>

static QPainterPath qt_graphicsItem_shapeFromPath(const QPainterPath &path, const QPen &pen)
{
    // We unfortunately need this hack as QPainterPathStroker will set a width of 1.0
    // if we pass a value of 0.0 to QPainterPathStroker::setWidth()
    const qreal penWidthZero = qreal(0.00000001);

    if (path == QPainterPath())
        return path;
    QPainterPathStroker ps;
    ps.setCapStyle(pen.capStyle());
    if (pen.widthF() <= 0.0)
        ps.setWidth(penWidthZero);
    else
        ps.setWidth(pen.widthF());
    ps.setJoinStyle(pen.joinStyle());
    ps.setMiterLimit(pen.miterLimit());
    QPainterPath p = ps.createStroke(path);
    p.addPath(path);
    return p;
}

Connection::Connection(Node *from, Node *to, HandleItem *fromHandle, HandleItem *toHandle)
    : QGraphicsItem(),
      from_(from), to_(to), fromHandle_(fromHandle), toHandle_(toHandle), hovered_(false)
{
    setAcceptHoverEvents(true);
    updatePosition();
//    setPen({Qt::black, 4});
}

void Connection::updatePosition()
{
    prepareGeometryChange();
//    setLine({fromHandle_->scenePos(), toHandle_->scenePos()});
    //d->line = line;
    update();
}

Node *Connection::from()
{
    return from_;
}

Node *Connection::to()
{
    return to_;
}

QRectF Connection::boundingRect() const
{
    return shape().controlPointRect();
    QPointF p1 = fromHandle_->scenePos();
    QPointF p2 = toHandle_->scenePos();
    const qreal x1 = p1.x();
    const qreal x2 = p2.x();
    const qreal y1 = p1.y();
    const qreal y2 = p2.y();
    qreal lx = qMin(x1, x2);
    qreal rx = qMax(x1, x2);
    qreal ty = qMin(y1, y2);
    qreal by = qMax(y1, y2);
    return QRectF(lx, ty, rx - lx, by - ty);
}

void Connection::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPointF p1 = fromHandle_->scenePos();
    QPointF p2 = toHandle_->scenePos();
    QPointF c1 = fromHandle_->scenePos();
    QPointF c2 = toHandle_->scenePos();
    double d = 0.5 * qAbs(p2.x() - p1.x());
    c1.rx() += d;
    c2.rx() -= d;

    QPainterPath path;
    path.moveTo(p1);
    path.cubicTo(c1, c2, p2);

    painter->setPen({(hovered_ ? Qt::gray : fromHandle_->brush().color()), 2});
    painter->drawPath(path);
}

QPainterPath Connection::shape() const
{
    QPointF p1 = fromHandle_->scenePos();
    QPointF p2 = toHandle_->scenePos();
    QPointF c1 = fromHandle_->scenePos();
    QPointF c2 = toHandle_->scenePos();
    double d = 0.5 * qAbs(p2.x() - p1.x());
    c1.rx() += d;
    c2.rx() -= d;

    QPainterPath path;
    path.moveTo(p1);
    path.cubicTo(c1, c2, p2);
    return qt_graphicsItem_shapeFromPath(path, {Qt::black, 8});
}

void Connection::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //TODO: handle proper highlighting at scene level when dragging
//    setPen({Qt::gray, pen().widthF()});
    hovered_ = true;
    QGraphicsItem::hoverEnterEvent(event);
}

void Connection::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
//    setPen({Qt::black, pen().widthF()});
    hovered_ = false;
    QGraphicsItem::hoverLeaveEvent(event);
}
