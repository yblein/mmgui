#include "filternode.hpp"

#include "connection.hpp"

FilterNode::FilterNode(const QString &name, HandleItem::MapType outputType, FilterNode::Filter filter, QGraphicsItem *parent)
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
}

void FilterNode::updateMap()
{
	if (inputConn_.size() != 0) {
		auto prevMap = inputConn_.first()->from()->map();
		filter_(prevMap, map_);
	}
}

const Map *FilterNode::rawMap()
{
	return map_;
}

void FilterNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	/*
	bool configUpdated;// = controller_.configure();

	configUpdated = dialog.exec();

	if (configUpdated) {
		evictCache();
		auto cs = qobject_cast<ControlScene*>(scene());
		Q_ASSERT(cs != nullptr);
		cs->graphUpdated();
	}*/

	Node::mouseDoubleClickEvent(event);
}
