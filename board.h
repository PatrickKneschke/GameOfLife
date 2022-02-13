#ifndef BOARD_H
#define BOARD_H


#include <QFrame>
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>


class Board : public QFrame {
public:
	Board(QWidget *parent);
	
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event) override;
};


#endif
