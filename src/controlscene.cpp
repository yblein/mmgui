#include "controlscene.hpp"

#include "connection.hpp"
#include "handleitem.hpp"
#include "generatornode.hpp"
#include "filternode.hpp"

#include <QGraphicsSceneMouseEvent>

ControlScene::ControlScene(QObject *parent) :
	QGraphicsScene(parent), dragFrom(nullptr)
{
	addItem(&dragLine);
	dragLine.setVisible(false);
	dragLine.setPen({Qt::black, 2});
	dragLine.setZValue(-1);
}

void ControlScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	QList<QGraphicsItem *> clickedItems = items(mouseEvent->scenePos());
	if (clickedItems.size() != 0 && clickedItems.first()->type() == Connection::Type) {
		Connection *c = qgraphicsitem_cast<Connection *>(clickedItems.first());
		c->from()->removeOutputConnection(c);
		c->to()->removeInputConnection(c);
		removeItem(c);
		delete c;

		emit graphUpdated();
	}

	QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void ControlScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (mouseEvent->button() == Qt::LeftButton) {
		QList<QGraphicsItem *> startItems = items(mouseEvent->scenePos());
		if (startItems.size() != 0 && startItems.first()->type() == HandleItem::Type) {
			if (dragFrom == nullptr) {
				dragFrom = qgraphicsitem_cast<HandleItem *>(startItems.first());
				dragLine.setLine(QLineF(dragFrom->scenePos(), mouseEvent->scenePos()));
				dragLine.setVisible(true);
				return;
			}
			mouseEvent->accept();
		}
	}

	QGraphicsScene::mousePressEvent(mouseEvent);
}

void ControlScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (dragFrom) {
		dragLine.setLine(QLineF(dragLine.line().p1(), mouseEvent->scenePos()));
	}

	QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void ControlScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (mouseEvent->button() == Qt::MidButton) {
		QList<QGraphicsItem *> clickedItems = items(mouseEvent->scenePos());
		foreach (QGraphicsItem *i, clickedItems) {
			if (i->type() != GeneratorNode::Type && i->type() != FilterNode::Type)
				continue;
			if (Node *n = dynamic_cast<Node *>(i)) {
				QList<Connection*> cs = n->disconnect();
				foreach (Connection *c, cs) {
					removeItem(c);
					delete c;
				}
				removeItem(n);
				delete n;

				emit graphUpdated();
				break;
			}
		}
	} else if (mouseEvent->button() == Qt::LeftButton && dragFrom) {
		QList<QGraphicsItem *> endItems = items(mouseEvent->scenePos());

		while (endItems.size() != 0 && endItems.first()->type() != HandleItem::Type)
			endItems.pop_front();

		if (endItems.size() != 0 && endItems.first()->type() == HandleItem::Type) {
			HandleItem *dragTo = qgraphicsitem_cast<HandleItem *>(endItems.first());

			// Swap if dragged from the input node
			if (dragFrom->ioType() == HandleItem::Input)
				std::swap(dragFrom, dragTo);

			if (dragFrom->canBeConnectedTo(dragTo)) {
				Node *p1 = dynamic_cast<Node *>(dragFrom->parentItem());
				Node *p2 = dynamic_cast<Node *>(dragTo->parentItem());

				auto newConn = new Connection(p1, p2, dragFrom, dragTo);
				newConn->setZValue(dragLine.zValue());
				addItem(newConn);
				p1->addOutputConnection(newConn);
				p2->addInputConnection(newConn);

				emit graphUpdated();
			}
		}

		dragFrom = nullptr;
		dragLine.setVisible(false);

		mouseEvent->accept();
	}

	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
