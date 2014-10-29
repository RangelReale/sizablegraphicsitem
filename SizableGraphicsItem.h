//
// SizableGraphicsItem.h
//

#ifndef __SIZABLEGRAPHICSITEM__H
#define __SIZABLEGRAPHICSITEM__H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>

class SizableGraphicsItem : public QGraphicsItem
{
public:
	typedef enum
	{
		None = 0,
		Move = 1,
		Left = 2,
		Top = 4,
		Right = 8,
		Bottom = 16,
	} operationmode_t;

	typedef int operation_t;

	SizableGraphicsItem(QRectF pos, QGraphicsItem *parent = 0);

	const QRectF &pos() const { return _pos; }
	void setPos(const QRectF &pos);

	bool allowMove() const { return _allowmove; }
	void setAllowMove(bool value) { _allowmove = value; }

	bool allowResize() const { return _allowresize; }
	void setAllowResize(bool value) { _allowresize = value; }

	QRectF boundingRect() const;

	void raise();
protected:
	virtual bool validatePos(QRectF newpos);
	virtual void positionChanged() {}

	void mousePressEvent(QGraphicsSceneMouseEvent* e);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* e);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* e);
	void hoverMoveEvent(QGraphicsSceneHoverEvent *e);
private:
	void positionChange(QRectF newpos);

	operation_t operationPosition(QPointF pos);
	QCursor operationCursor(operation_t resize);

	QRectF _pos;
	operation_t _operation;
	bool _allowmove;
	bool _allowresize;
};

#endif // __SIZABLEGRAPHICSITEM__H
