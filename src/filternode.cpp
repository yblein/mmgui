#include "filternode.hpp"

#include "connection.hpp"
#include "controlscene.hpp"
#include "filterfunctions.hpp"

FilterNode::FilterNode(const QString &name, HandleItem::MapType outputType, Filter *filter, QGraphicsItem *parent)
	: Node(name, parent), filter_(filter)
{
	//ui.setupUi(&dialog);

	addInput(HandleItem::HeightMap);
	addOutput(outputType);

	switch (outputType) {
	case HandleItem::HeightMap:
		map_ = new HeightMap();
		break;
	case HandleItem::ColorMap:
		map_ = new ColorMap();
		break;
	default:
		Q_ASSERT(0);
	}
}

FilterNode::~FilterNode()
{
	delete map_;
	delete filter_;
}

void FilterNode::updateMap()
{
	if (inputConn_.size() != 0) {
		auto prevMap = inputConn_.first()->from()->map();
		filter_->filter(prevMap, map_);
	}
}

const Map *FilterNode::rawMap()
{
	return map_;
}

void FilterNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	bool configUpdated = filter_->configure();

	if (configUpdated) {
		evictCache();
		auto cs = qobject_cast<ControlScene*>(scene());
		Q_ASSERT(cs != nullptr);
		cs->graphUpdated();
	}

	Node::mouseDoubleClickEvent(event);
}
