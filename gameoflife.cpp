
#include "ui_gameoflife.h"
#include "gameoflife.h"


GameOfLife(QWidget *parent) :
	QWidget(parent),
	ui(new UI::GameOfLife)
{
	ui->setupUI(this);
}


~GameOfLife() {
	delete ui;
}
