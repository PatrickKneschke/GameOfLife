#ifndef BOARD_H
#define BOARD_H


#include <QFrame>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <QWidget>


class Board : public QFrame {
public:
	Board(QWidget *parent);
	
	void mousePressEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;
	void update();
	bool isRunning();
	
	
	static constexpr unsigned int boardSize = 1024;
	static constexpr unsigned int maxZoom 	= 32;
	static constexpr unsigned int maxSpeed	= 10;
	
	
public slots:
	void toggleOnOff();
	void zoomIn();
	void zoomOut();
	void setSpeed(unsigned int s);
	
private:
	int cellAt(unsigned int x, unsigned int y);
	

	QVector<QVector<bool>> cells[2];
	unsigned int active;
	unsigned int zoom;
	unsigned int viewX;
	unsigned int viewY;
	unsigned int speed;
	bool running;
	QTimer *updateTimer;
};


#endif
