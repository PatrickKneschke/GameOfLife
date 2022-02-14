
#include "board.h"

#include <cstdlib>


Board::Board(QWidget *parent) :
	QFrame(parent),
	cells{QVector<QVector<bool>>(boardSize, QVector<bool>(boardSize, false)), QVector<QVector<bool>>(boardSize, QVector<bool>(boardSize, false))},
	active(0),
	zoom(1),
	viewX(0),
	viewY(0),
	speed(1)
{
	
	zoom = 8;
	// test cells
	srand(42);
	for(int i=0; i<boardSize; i++) {
		for(int j=0; j<boardSize; j++) {
			if(rand() % 100 == 0)
				cells[active][i][j] = true;
		}
	}
}


void Board::mousePressEvent(QMouseEvent *event) {

}


void Board::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	
	// clearckground
	painter.setPen(Qt::white);
	painter.setBrush(Qt::white);
	painter.drawRect(0, 0, boardSize, boardSize);
	
	// draw cells
	painter.setPen(Qt::black);
	painter.setBrush(Qt::black);
	for(int i=0; i<boardSize/zoom; i++) {
		for(int j=0; j<boardSize/zoom; j++) {
			if(cells[active][viewX + i][viewY + j])
				painter.drawRect(i*zoom, j*zoom, zoom, zoom);
		}
	}
}


void Board::toggleOnOff() {

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
}
