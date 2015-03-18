#ifndef NOTEITEM_H
#define NOTEITEM_H

#include "node.hpp"

#include <QDialog>

class Filter;

class FilterNode : public Node
{
public:
	FilterNode(const QString &name, HandleItem::MapType outputType,
			   Filter *filter, QGraphicsItem *parent = 0);

	~FilterNode();

	enum { Type = UserType + 2 };

	virtual int type() const { return Type; }

protected:
	void updateMap();

	const Map *rawMap();

	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
	Filter *filter_;
	Map *map_;
};

#endif // NOTEITEM_H
