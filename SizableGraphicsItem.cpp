#include "SizableGraphicsItem.h"

#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>

SizableGraphicsItem::SizableGraphicsItem(QRectF pos, QGraphicsItem *parent) :
	QGraphicsItem(parent), _pos(pos), _operation(0), _allowmove(true), _allowresize(true)
{
	setFlag(QGraphicsItem::ItemIsSelectable);
	setFlag(QGraphicsItem::ItemIsFocusable);
	setAcceptHoverEvents(true);
}

void SizableGraphicsItem::raise()
{
	static int zvaluect = 1;
	setZValue(zvaluect++);
}

QRectF SizableGraphicsItem::boundingRect() const
{
	return _pos;
}

void SizableGraphicsItem::setPos(const QRectF &pos)
{
	prepareGeometryChange();
	_pos = pos;
}


bool SizableGraphicsItem::validatePos(QRectF newpos)
{
	return true;
}

void SizableGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
	if (e->buttons() == Qt::LeftButton)
	{
		//qDebug() << "mousePressEvent: " << e->pos();
		raise();
		_operation = operationPosition(e->pos());
	}
	QGraphicsItem::mousePressEvent(e);
}

void SizableGraphicsItem::positionChange(QRectF newpos)
{
	if (validatePos(newpos))
	{
		_pos = newpos;
		positionChanged();
	}
}

void SizableGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* e)
{
	if (e->buttons() == Qt::LeftButton)
	{
		//qDebug() << "mouseMoveEvent: " << e->pos() << " => DOWN: " << e->buttonDownPos(Qt::LeftButton);
		prepareGeometryChange();
		QRectF newpos(_pos);
		if ((_operation & Move))
			newpos.moveTo(newpos.left() + e->pos().x() - e->lastPos().x(), newpos.top() + e->pos().y() - e->lastPos().y());
		if ((_operation & Left))
			newpos.setLeft(newpos.left() + e->pos().x() - e->lastPos().x());
		if ((_operation & Right))
			newpos.setRight(newpos.right() + e->pos().x() - e->lastPos().x());
		if ((_operation & Top))
			newpos.setTop(newpos.top() + e->pos().y() - e->lastPos().y());
		if ((_operation & Bottom))
			newpos.setBottom(newpos.bottom() + e->pos().y() - e->lastPos().y());
		positionChange(newpos);
	}
	QGraphicsItem::mouseMoveEvent(e);
}

void SizableGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* e)
{
	if (e->buttons() == Qt::LeftButton)
	{
		//qDebug() << "mouseReleaseEvent: " << e->pos() << " => DOWN: " << e->buttonDownPos(Qt::LeftButton);
		_operation = 0;
	}
	QGraphicsItem::mouseReleaseEvent(e);
}

void SizableGraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent *e)
{
	//qDebug() << "hoverMoveEvent: " << e->pos();
	setCursor(operationCursor(operationPosition(e->pos())));

	QGraphicsItem::hoverMoveEvent(e);
}

SizableGraphicsItem::operation_t SizableGraphicsItem::operationPosition(QPointF pos)
{
	const int ADJUST = 10;

	operation_t ret = None;

	if (_allowresize)
	{
		if (pos.x() - _pos.x() < ADJUST)
			ret |= Left;
		if (pos.y() - _pos.y() < ADJUST)
			ret |= Top;

		if (_pos.right() - pos.x() < ADJUST)
			ret |= Right;
		if (_pos.bottom() - pos.y() < ADJUST)
			ret |= Bottom;
	}

	if (_allowmove)
	{
		if (ret == None && _pos.contains(pos))
			ret |= Move;
	}

	return ret;
}

QCursor SizableGraphicsItem::operationCursor(SizableGraphicsItem::operation_t operation)
{
	QCursor ret;
	if (operation > 0)
	{
		if ((operation & Move))
			ret = Qt::SizeAllCursor;
		else if (operation & (operation - 1)) // check if more than 1 bit is set
		{
			if (((operation & Left) && (operation & Top)) || ((operation & Right) && (operation & Bottom)))
				ret = Qt::SizeFDiagCursor;
			else
				ret = Qt::SizeBDiagCursor;
		}
		else if ((operation & Left) || (operation & Right))
			ret = Qt::SizeHorCursor;
		else
			ret = Qt::SizeVerCursor;
	}
	return ret;
}

