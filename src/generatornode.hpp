#ifndef INPUTNODE_H
#define INPUTNODE_H

#include "fractalgenerator.hpp"
#include "generator.hpp"
#include "node.hpp"

#include <mm/heightmap.h>

class GeneratorNode : public Node
{
public:
    explicit GeneratorNode(const QString &name, HandleItem::MapType outputType, Generator *generator, QGraphicsItem *parent = 0);

    ~GeneratorNode();

protected:
    virtual void updateMap();
    virtual const Map* rawMap();

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    Generator *generator_;
    Map *map_;
};

#endif // INPUTNODE_H
