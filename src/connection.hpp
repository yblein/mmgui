#ifndef CONNECTIONITEM_H
#define CONNECTIONITEM_H

#include <QGraphicsItem>

class Node;
class HandleItem;

class Connection : public QGraphicsItem
{
public:
    enum { Type = UserType + 16 };

    Connection(Node *from, Node *to, HandleItem* fromHandle, HandleItem* toHandle);

    virtual int type() const { return Type;}

    void updatePosition();

    Node *from();
    Node *to();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    virtual QPainterPath shape() const;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    Node *from_;
    Node *to_;
    HandleItem *fromHandle_;
    HandleItem *toHandle_;
    bool hovered_;
};

#endif // CONNECTIONITEM_H
