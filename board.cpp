
#include "board.h"

#include <cstdlib>
#include <thread>
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
	connect(updateTimer, &QTimer::timeout,
			this, QOverload<>::of(&Board::update));
}


void Board::mouseMoveEvent(QMouseEvent *event) {
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();
	if(qAbs(dx) >= zoom || qAbs(dy) >= zoom) {		
		dx /= static_cast<int>(zoom);
		dy /= static_cast<int>(zoom);
	
		if(viewX - dx >= 0 && viewX - dx < boardSize - boardSize/zoom)
			viewX -= dx;
		if(viewY - dy >= 0 && viewY - dy < boardSize - boardSize/zoom)
			viewY -= dy;
			
		lastPos = event->pos();
		QWidget::update();
	}
}


void Board::mousePressEvent(QMouseEvent *event) {
	lastPos = event->pos();
}


void Board::mouseReleaseEvent(QMouseEvent *event) {
	if(lastPos == event->pos()) {
		if(event->button() == Qt::LeftButton) {
			cells[active][viewY + event->y()/zoom][viewX + event->x()/zoom] = true;
		}
		if(event->button() == Qt::RightButton) {
			cells[active][viewY + event->y()/zoom][viewX + event->x()/zoom] = false;
		}
		QWidget::update();
	}
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
		-> cell with less than 2 neighbors dies
		-> cell with more than 3 neighbors dies
		-> cell with exactly 3 neighbors becomes alive
	*/
	
	unsigned int threadCount = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	for(int i=0; i<threadCount; i++) {
		threads.emplace_back([this, i, threadCount](){
			updateRegion(0, i*boardSize/threadCount, boardSize, boardSize/threadCount);
		});
	}
	for(auto &t : threads) {
		t.join();			
	}	
	
	active = active == 0 ? 1 : 0;

	QWidget::update();
}


void Board::updateRegion(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	unsigned int inactive = (active == 0) ? 1 : 0;
	for(unsigned int i=y; i<y+h; i++) {
		for(unsigned int j=x; j<x+w; j++) {
			int aliveCount = cellAt(j-1, i-1) + cellAt(j-1, i) + cellAt(j-1, i+1) + 
							 cellAt(j, i-1)   + cellAt(j, i+1) + 
							 cellAt(j+1, i-1) + cellAt(j+1, i) + cellAt(j+1, i+1);
			if(aliveCount == 3)
				cells[inactive][i][j] = true;
			else if(aliveCount < 2 || aliveCount > 3)
				cells[inactive][i][j] = false;
			else 
				cells[inactive][i][j] = cells[active][i][j];				
		}
	}
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
	viewX += boardSize/zoom/2;
	viewY += boardSize/zoom/2;
	
	QWidget::update();
}


void Board::zoomOut() {
	if(zoom == 1)
		return;
		
	// update view
	if(viewX >= boardSize/zoom/2)
		viewX -= boardSize/zoom/2;
	else
		viewX = 0;
	if(viewY >= boardSize/zoom/2)
		viewY -= boardSize/zoom/2;
	else
		viewY = 0;
		
	zoom /= 2;	
	QWidget::update();
}


void Board::setSpeed(unsigned int s) {
	speed = s;
	updateTimer->setInterval(1000 / speed);
}
