#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H


#include <QWidget>


namespace UI{
	class GameOfLife;
}


class GameOfLife : public QWidget {
public:
	GameOfLife(QWidget *parent);
	~GameOfLife();
	
private:
	UI::GameOfLife *ui;
};


#endif
