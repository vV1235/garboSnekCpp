#pragma once
#include "GameEngine.h"
#include "Snek.h"
#include "Apple.h"
#include "ScoreBoard.h"

class Game : public GameEngine {
public:
	Game();
	virtual bool setup();
	virtual bool update(float deltaTimeCnt);
private:
	void checkCollisions();
	void logicManagment();
	void display();
	void resetGame();

	Snek snek;
	Apple apple;
	ScoreBoard scoreBoard;
	bool isAlive;

	enum class Direction {
		TOP,
		DOWN,
		LEFT,
		RIGHT
	};

	Direction currentDirection;
	bool holdKeyW;
	bool holdKeyS;
	bool holdKeyA;
	bool holdKeyD;
	short sessionLifeCnt;
};