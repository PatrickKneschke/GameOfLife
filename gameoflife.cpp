
#include "ui_gameoflife.h"
#include "gameoflife.h"


GameOfLife::GameOfLife(QWidget *parent) :
	QWidget(parent),
	ui(new UI::GameOfLife)
{
	ui->setupUI(this);
}


GameOfLife::~GameOfLife() {
	delete ui;
}
