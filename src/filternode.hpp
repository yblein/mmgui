#ifndef NOTEITEM_H
#define NOTEITEM_H

#include "node.hpp"

#include <QDialog>

class FilterNode : public Node
{
public:
    typedef std::function<void(const Map*, Map*)> Filter;

    FilterNode(const QString &name, HandleItem::MapType outputType,
               Filter filter, QGraphicsItem *parent = 0);

    ~FilterNode();

protected:
    void updateMap();

    const Map *rawMap();

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    //FilterController controller_;
    //QDialog dialog;
    //Ui ui;
    Filter filter_;
    Map *map_;
};

#endif // NOTEITEM_H
