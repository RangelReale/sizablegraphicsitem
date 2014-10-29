#include "MainWindow.h"

#include <QMenu>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>
#include <QContextMenuEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	resize(1280, 800);
	setWindowTitle("SizableGraphicsItem Test");

	_widget = new MainView(this);
	_scene = new QGraphicsScene(this);
	_widget->setScene(_scene);

	_widget->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	_widget->setSceneRect(0, 0, 1200, 760);

	_item = new MainGraphicsItem(QRectF(100, 100, 200, 200));
	_scene->addItem(_item);

	_item2 = new MainGraphicsItem(QRectF(400, 400, 200, 200));
	//_item2->setAllowMove(false);
	//_item2->setAllowResize(false);
	_scene->addItem(_item2);

	setCentralWidget(_widget);
}

MainView::MainView(QWidget *parent) : QGraphicsView(parent)
{

}

void MainView::contextMenuEvent(QContextMenuEvent *event)
{
	//QGraphicsScene::contextMenuEvent(event);
	QGraphicsItem *item = scene()->itemAt(event->pos(), QTransform());
	if (item)
	{
		QMenu menu;
		QAction *removeAction = menu.addAction("Remove");
		QAction *selectedAction = menu.exec(event->globalPos());

		if (selectedAction == removeAction)
			delete item;
	}
	else
	{
		QGraphicsView::contextMenuEvent(event);
	}
}

MainGraphicsItem::MainGraphicsItem(QRectF pos, QGraphicsItem *parent) : SizableGraphicsItem(pos, parent)
{

}

MainGraphicsItem::~MainGraphicsItem()
{

}

void MainGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen(Qt::yellow);
	if (hasFocus())
		pen = QPen(Qt::blue);
	painter->setPen(pen);

	QBrush brush(Qt::red);
	brush.setStyle(Qt::SolidPattern);
	painter->setBrush(brush);

	painter->drawRect(boundingRect());

	QRectF r(mapRectToScene(pos()));
	r.setTopLeft(QPointF(r.left() + 10, r.top() + 10));

	painter->drawText(r, QString("%1 %2 %3 %4").arg(pos().left()).arg(pos().top()).arg(pos().width()).arg(pos().height()));
}


bool MainGraphicsItem::validatePos(QRectF newpos)
{
	return newpos.left() >= 0 && newpos.top() >= 0 && newpos.width() > 5 && newpos.height() > 5;
}
