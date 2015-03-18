#ifndef OUTPUTNODE_H
#define OUTPUTNODE_H

#include "node.hpp"
#include <mm/heightmap.h>

class OutputNode : public Node
{
public:
	explicit OutputNode(QGraphicsItem *parent = 0);

	enum { Type = UserType + 3 };

	virtual int type() const { return Type; }

protected:
	virtual void updateMap();
	virtual const Map* rawMap();
};

#endif // OUTPUTNODE_H
