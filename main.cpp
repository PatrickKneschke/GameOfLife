
#include <QApplication>
#include "gameoflife.h"

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	
	GameOfLife game;
	game.show();
	
	return app.exec();
}
