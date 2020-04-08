#include <iostream>
#include "Game.h"

int main() {
	Game game;
	game.constructConsole(60, 60);
	game.start();
	ScoreBoard s(5, 5);
}

