#include "node.hpp"

#include "handleitem.hpp"
#include "connection.hpp"

#include <QTextBlockFormat>
#include <QTextCursor>
#include <QGraphicsScene>

Node::Node(QString name, QGraphicsItem *parent)
	: QGraphicsRectItem(-40, -20, 80, 40, parent),
	  name_(name), cached_(false)
{
	setBrush(Qt::white);
	setPen(QPen(Qt::black, 2));
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);

	auto text = new QGraphicsTextItem(name, this);

	QTextBlockFormat format;
	format.setAlignment(Qt::AlignCenter);
	QTextCursor cursor = text->textCursor();
	cursor.select(QTextCursor::Document);
	cursor.mergeBlockFormat(format);
	cursor.clearSelection();
	text->setTextCursor(cursor);

	text->setTextWidth(boundingRect().width());
	text->setPos(boundingRect().topLeft());
}

const Map *Node::map()
{
	if (!cached_) {
		cached_ = true;
		updateMap();
	}
	return rawMap();
}

void Node::addInput(HandleItem::MapType mapType)
{
	inputs_ << new HandleItem(mapType, HandleItem::Input, this);
	inputs_.last()->setPos(boundingRect().left(), 0);
}

void Node::addOutput(HandleItem::MapType mapType)
{
	outputs_ << new HandleItem(mapType, HandleItem::Output, this);
	outputs_.last()->setPos(boundingRect().right(), 0);
}

void Node::addInputConnection(Connection *conn)
{
	if (inputConn_.size() != 0) {
		Connection *c = inputConn_.first();
		c->from()->outputConn_.removeOne(c);
		inputConn_.clear();
		scene()->removeItem(c);
		delete c;
	}

	inputConn_ << conn;
	evictCache();
}

void Node::addOutputConnection(Connection *conn)
{
	outputConn_ << conn;
}

void Node::removeInputConnection(Connection *conn)
{
	inputConn_.removeOne(conn);
	evictCache();
}

void Node::removeOutputConnection(Connection *conn)
{
	outputConn_.removeOne(conn);
}

QList<Connection*> Node::disconnect()
{
	foreach (Connection *c, inputConn_) {
		c->from()->removeOutputConnection(c);
	}
	foreach (Connection *c, outputConn_) {
		c->to()->removeInputConnection(c);
	}
	inputConn_.append(outputConn_);
	return inputConn_;
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == QGraphicsItem::ItemPositionChange) {
		foreach (Connection *c, inputConn_) {
			c->updatePosition();
		}
		foreach (Connection *c, outputConn_) {
			c->updatePosition();
		}
	}

	return value;
}

void Node::evictCache()
{
	cached_ = false;
	foreach (Connection *c, outputConn_) {
		c->to()->evictCache();
	}
}
