#ifndef BOARD_H
#define BOARD_H


#include <QFrame>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QWidget>


class Board : public QFrame {
public:
	Board(QWidget *parent);
	
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event) override;
	
	
	static constexpr unsigned int boardSize = 1024;
	static constexpr unsigned int minViewSize = 32;
	
	
public slots:
	void toggleOnOff();
	void zoomIn();
	void zoomOut();
	void setSpeed(int s);
	
private:
	QVector<QVector<bool>> cells[2];
	unsigned int active;
	unsigned int zoom;
	unsigned int viewX;
	unsigned int viewY;
	unsigned int speed;
};


#endif
