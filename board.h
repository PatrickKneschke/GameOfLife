#ifndef BOARD_H
#define BOARD_H


#include <QFrame>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QWidget>


class Board : QFrame {
public:
	Board(QWidget *parent);
	
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event) override;
};


#endif
