#ifndef BOARD_H
#define BOARD_H


#include <QFrame>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <QWidget>


class Board : public QFrame {
	Q_OBJECT
public:
	Board(QWidget *parent);
	
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;
	bool isRunning();
	
	
	static constexpr unsigned int boardSize = 1024;
	static constexpr unsigned int maxZoom 	= 32;
	static constexpr unsigned int maxSpeed	= 10;
	
	
public slots:
	void toggleOnOff();
	void zoomIn();
	void zoomOut();
	void setSpeed(unsigned int s);
	void update();
	
private:
	int cellAt(unsigned int x, unsigned int y);
	void updateRegion(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

	QVector<QVector<bool>> cells[2];
	unsigned int active;
	unsigned int zoom;
	unsigned int viewX;
	unsigned int viewY;
	unsigned int speed;
	bool running;
	QTimer *updateTimer;
	
	QPoint lastPos;
};


#endif
