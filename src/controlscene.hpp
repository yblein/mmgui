#ifndef CONTROLSCENE_H
#define CONTROLSCENE_H

#include "handleitem.hpp"

#include <QGraphicsScene>

class ControlScene : public QGraphicsScene
{
	Q_OBJECT
public:
	explicit ControlScene(QObject *parent = 0);

signals:
	void graphUpdated();

public slots:

protected:
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);

private:
	HandleItem *dragFrom;
	QGraphicsLineItem dragLine;
};

#endif // CONTROLSCENE_H
