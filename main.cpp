#include <iostream>
#include "Game.h"
#include "Testing.h"
#define DEBUG

int main() {
#ifdef DEBUG
	Testing* t = t->getInstance();
	Testing* t2 = t2->getInstance();
	Testing::Tetromino* tetr;
	Testing::L l;
	tetr = &l;
	tetr->displayShape();
#else
	Game game;
	game.constructConsole(60, 60);
	game.start();
	return 0;
#endif // DEBUG
}

