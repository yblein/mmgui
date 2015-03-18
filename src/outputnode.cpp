#include "outputnode.hpp"

#include "connection.hpp"

#include <mm/normalize.h>

OutputNode::OutputNode(QGraphicsItem *parent) :
	Node("Output", parent)
{
	addInput(HandleItem::AnyMap);
}

void OutputNode::updateMap()
{
}

const Map *OutputNode::rawMap()
{
	if (inputConn_.size() == 0) {
		return nullptr;
	}

	return inputConn_.first()->from()->map();
}
