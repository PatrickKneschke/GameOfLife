
#include "ui_gameoflife.h"
#include "gameoflife.h"


GameOfLife::GameOfLife(QWidget *parent) :
	QWidget(parent),
	ui(new UI::GameOfLife)
{
	ui->setupUI(this);
	setupConnections();
}


GameOfLife::~GameOfLife() {
	delete ui;
}


void GameOfLife::setupConnections() {
	connect(ui->startButton, &QPushButton::clicked, 
			ui->board, &Board::toggleOnOff);
	connect(ui->zoomInButton, &QPushButton::clicked, 
			ui->board, &Board::zoomIn);
	connect(ui->zoomOutButton, &QPushButton::clicked, 
			ui->board, &Board::zoomOut);
	connect(ui->speedSelect, QOverload<int>::of(&QSpinBox::valueChanged), 
			ui->board, &Board::setSpeed);
}
