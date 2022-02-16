#ifndef UI_GAMEOFLIFE_H
#define UI_GAMEOFLIFE_H


#include <board.h>

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>


namespace UI {

class GameOfLife {
public:
	void setupUI(QWidget *parent) {
		mainLayout 		= new QHBoxLayout();
		
		board 			= new Board(parent);
		board->setFixedSize(1024, 1024);
		board->setFrameStyle(QFrame::Sunken | QFrame::Box);
		
		controlsFrame  	= new QFrame(parent);
		controlsLayout 	= new QVBoxLayout(controlsFrame);
		controlsLayout->setAlignment(Qt::AlignTop);
		
		startButton		= new QPushButton(QIcon("icons/play.png"), "", controlsFrame);
		startButton->setFixedSize(100, 100);
		startButton->setIconSize(QSize(80, 80));
		
		zoomInButton	= new QPushButton(QIcon("icons/zoom_in.png"), "", controlsFrame);
		zoomInButton->setFixedSize(100, 100);
		zoomInButton->setIconSize(QSize(80, 80));
		
		zoomOutButton	= new QPushButton(QIcon("icons/zoom_out.png"), "", controlsFrame);
		zoomOutButton->setFixedSize(100, 100);
		zoomOutButton->setIconSize(QSize(80, 80));
		
		speedLabel		= new QLabel("Speed", controlsFrame);
		speedLabel->setFont(QFont("Arial", 12, QFont::Bold));
		speedLabel->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
		
		speedSelect		= new QSpinBox(controlsFrame);
		speedSelect->setFixedSize(100, 100);
		speedSelect->setFont(QFont("Arial", 20, QFont::Bold));
		speedSelect->setAlignment(Qt::AlignCenter);
		speedSelect->setRange(1, Board::maxSpeed);
		
		parent->setLayout(mainLayout);
		mainLayout->addWidget(board,         0, Qt::AlignLeft);
		mainLayout->addWidget(controlsFrame, 0, Qt::AlignRight);
		
		controlsLayout->addWidget(startButton,   0, Qt::AlignCenter);
		controlsLayout->addWidget(zoomInButton,  0, Qt::AlignCenter);
		controlsLayout->addWidget(zoomOutButton, 0, Qt::AlignCenter);
		controlsLayout->addWidget(speedLabel,    0, Qt::AlignCenter);
		controlsLayout->addWidget(speedSelect,   0, Qt::AlignCenter);
		
		QObject::connect(startButton, &QPushButton::clicked, [&](){
			startButton->setIcon( board->isRunning() ? QIcon("icons/play.png") : QIcon("icons/pause.png"));
		});
	}
	
	
	QHBoxLayout *mainLayout;
	QVBoxLayout *controlsLayout;
	QFrame 		*controlsFrame;
	Board 		*board;
	QPushButton *startButton,
				*zoomInButton,
				*zoomOutButton;
	QLabel		*speedLabel;
	QSpinBox	*speedSelect;
};

} //UI


#endif
