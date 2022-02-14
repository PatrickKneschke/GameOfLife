#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H


#include <QWidget>


namespace UI{
	class GameOfLife;
}


class GameOfLife : public QWidget {
public:
	GameOfLife(QWidget *parent = nullptr);
	~GameOfLife();
	
private:	
	void setupConnections();
	
	UI::GameOfLife *ui;
};


#endif
