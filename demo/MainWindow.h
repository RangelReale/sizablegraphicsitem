//
// MainWindow.h
//

#ifndef __MAINWINDOW__H
#define __MAINWINDOW__H

#define POCO_NO_UNWINDOWS
#define NOMINMAX

#include "SizableGraphicsItem.h"

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

class MainGraphicsItem;

class MainScene;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = 0);

protected Q_SLOTS:
private:
    QGraphicsView *_widget;
	QGraphicsScene *_scene;
	MainGraphicsItem *_item, *_item2;
};

class MainView : public QGraphicsView
{
public:
	MainView(QWidget *parent = 0);
protected:
	void contextMenuEvent(QContextMenuEvent *event);
};


class MainGraphicsItem : public SizableGraphicsItem
{
public:
	MainGraphicsItem(QRectF pos, QGraphicsItem *parent = 0);
	~MainGraphicsItem();

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
	bool validatePos(QRectF newpos);
};

#endif // __MAINWINDOW__H
