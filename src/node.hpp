#ifndef NODE_H
#define NODE_H

#include "handleitem.hpp"
#include "map.hpp"

#include <QGraphicsRectItem>

class Connection;

class Node : public QGraphicsRectItem
{
public:
	Node(QString name, QGraphicsItem *parent = 0);
	virtual ~Node() {}

	enum { Type = UserType + 1 };

	virtual int type() const { return Type; }

	//! Return a pointer to the calculated map with cache handling
	virtual const Map* map();

	void addInput(HandleItem::MapType mapType);
	void addOutput(HandleItem::MapType mapType);

	void addInputConnection(Connection *conn);
	void addOutputConnection(Connection *conn);

	void removeInputConnection(Connection *conn);
	void removeOutputConnection(Connection *conn);

	QList<Connection *> disconnect();

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

	virtual void updateMap() = 0;
	virtual const Map* rawMap() = 0;

	void evictCache();

	QString name_;
	QList<HandleItem*> inputs_;
	QList<HandleItem*> outputs_;
	QList<Connection*> inputConn_;
	QList<Connection*> outputConn_;
	bool cached_;
};

#endif // NODE_H
