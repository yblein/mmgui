#include "handleitem.hpp"

#include <QPen>
#include <QBrush>

HandleItem::HandleItem(MapType mapType, IOType ioType, QGraphicsItem *parent)
    : QGraphicsEllipseItem(QRectF(-HandleSize/2, -HandleSize/2, HandleSize, HandleSize), parent),
      mapType_(mapType), ioType_(ioType)
{
    setPen(QPen(Qt::black, 2));
    setAcceptHoverEvents(true);

    QBrush brush;
    switch (mapType_) {
    case HeightMap:
        brush = QColor(200, 100, 100);
        break;
    case ColorMap:
        brush = Qt::cyan;
        break;
    case BinaryMap:
        brush = Qt::black;
        break;
    case AnyMap:
        brush = Qt::white;
    }
    setBrush(brush);
}

HandleItem::MapType HandleItem::mapType() const
{
    return mapType_;
}

bool HandleItem::canBeConnectedTo(const HandleItem *to)
{
    return (to != this
            && parentItem() != to->parentItem()
            && to->ioType_ != ioType_
            && (to->mapType_ == mapType_ || to->mapType_ == HandleItem::AnyMap));
}

HandleItem::IOType HandleItem::ioType() const
{
    return ioType_;
}

void HandleItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //TODO: handle proper highlighting at scene level when dragging
    setPen({Qt::gray, (qreal)(pen().width())});
    QGraphicsItem::hoverEnterEvent(event);
}

void HandleItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setPen({Qt::black, (qreal)(pen().width())});
    QGraphicsItem::hoverLeaveEvent(event);
}
