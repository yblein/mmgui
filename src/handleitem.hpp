#ifndef HANDLEITEM_H
#define HANDLEITEM_H

#include <QGraphicsEllipseItem>

class HandleItem : public QGraphicsEllipseItem
{
public:
	enum MapType {
		HeightMap,
		ColorMap,
		BinaryMap,
		AnyMap
	};
	enum IOType {
		Input,
		Output
	};
	enum { Type = UserType + 15 };

public:
	HandleItem(MapType mapType, IOType ioType, QGraphicsItem *parent);

	virtual int type() const { return Type;}

	IOType ioType() const;
	MapType mapType() const;

	bool canBeConnectedTo(const HandleItem *to);

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
	static const int HandleSize = 14;

	MapType mapType_;
	IOType ioType_;
};

#endif // HANDLEITEM_H
