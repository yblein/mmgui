#include "generatornode.hpp"

#include "controlscene.hpp"

GeneratorNode::GeneratorNode(const QString &name, HandleItem::MapType outputType, Generator *generator, QGraphicsItem *parent) :
    Node(name, parent), generator_(generator)
{
    addOutput(outputType);

    switch (outputType) {
    case HandleItem::HeightMap:
        map_ = new HeightMap();
        break;
    default:
        Q_ASSERT(0);
    }
}

GeneratorNode::~GeneratorNode()
{
    delete generator_;
}

void GeneratorNode::updateMap()
{
    generator_->generate(map_);
}

const Map *GeneratorNode::rawMap()
{
    return map_;
}

void GeneratorNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    bool changed = generator_->configure();
    if (changed) {
        evictCache();
        auto cs = qobject_cast<ControlScene*>(scene());
        Q_ASSERT(cs != nullptr);
        cs->graphUpdated();
    }
    Node::mouseDoubleClickEvent(event);
}
