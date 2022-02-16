
#include "board.h"

#include <cstdlib>
#include <time.h>

#include <QDebug>


Board::Board(QWidget *parent) :
	QFrame(parent),
	cells{QVector<QVector<bool>>(boardSize, QVector<bool>(boardSize, false)), QVector<QVector<bool>>(boardSize, QVector<bool>(boardSize, false))},
	active(0),
	zoom(1),
	viewX(0),
	viewY(0),
	speed(1),
	running(false),
	updateTimer(new QTimer(this))
{
	zoom = 32;	
	// test cells
	/*
	// "Glider"
	cells[active][1][2] = true;
	cells[active][2][3] = true;
	cells[active][3][1] = true;
	cells[active][3][2] = true;
	cells[active][3][3] = true;
	*/

	// random cells
	srand(time(nullptr));
	for(unsigned int y=0; y<boardSize; y++) {
		for(unsigned int x=0; x<boardSize; x++) {
			if(rand() % 10 == 0)
				cells[active][y][x] = true;
		}
	}
	
			
	connect(updateTimer, &QTimer::timeout,
			this, QOverload<>::of(&Board::update));
}


void Board::mousePressEvent(QMouseEvent *event) {
	if(event->button() == Qt::LeftButton) {
		cells[active][viewY + event->y()/zoom][viewX + event->x()/zoom] = true;
	}
	if(event->button() == Qt::RightButton) {
		cells[active][viewY + event->y()/zoom][viewX + event->x()/zoom] = false;
	}
	
	QWidget::update();
}


void Board::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	
	// clear background
	painter.setPen(Qt::white);
	painter.setBrush(Qt::white);
	painter.drawRect(0, 0, boardSize, boardSize);
	
	// draw cells
	painter.setPen(Qt::black);
	painter.setBrush(Qt::black);
	for(unsigned int y=0; y<boardSize/zoom; y++) {
		for(unsigned int x=0; x<boardSize/zoom; x++) {
			if(cells[active][viewY + y][viewX + x])
				painter.drawRect(x*zoom, y*zoom, zoom, zoom);
		}
	}
}


void Board::update() {
	/* simulation update :
		-> cells with less than 2 neighbors dies
		-> cells with more than 3 neighbors dies
		-> cells with exactly 3 neighbors becomes alive
	*/
	unsigned int inactive = (active == 0) ? 1 : 0;
	for(unsigned int y=0; y<boardSize; y++) {
		for(unsigned int x=0; x<boardSize; x++) {
			int aliveCount = cellAt(x-1, y-1) + cellAt(x-1, y) + cellAt(x-1, y+1) + 
							 cellAt(x, y-1)   + cellAt(x, y+1) + 
							 cellAt(x+1, y-1) + cellAt(x+1, y) + cellAt(x+1, y+1);
			if(aliveCount == 3)
				cells[inactive][y][x] = true;
			else if(aliveCount < 2 || aliveCount > 3)
				cells[inactive][y][x] = false;
			else 
				cells[inactive][y][x] = cells[active][y][x];				
		}
	}
	active = inactive;

	QWidget::update();
}


bool Board::isRunning() {
	return running;
}


int Board::cellAt(unsigned int x, unsigned int y) {
	if(x<0 || x>=boardSize || y<0 || y>=boardSize || !cells[active][y][x])
		return 0;
	
	return 1;
}


void Board::toggleOnOff() {
	if(running) {
		updateTimer->stop();
		running = false;
	}
	else {
		updateTimer->start(1000 / speed);
		running = true;	
	}
}


void Board::zoomIn() {
	if(zoom == maxZoom)
		return;
	zoom *= 2;
	update();
}


void Board::zoomOut() {
	if(zoom == 1)
		return;
	zoom /= 2;
	update();
}


void Board::setSpeed(unsigned int s) {
	speed = s;
	updateTimer->setInterval(1000 / speed);
}
