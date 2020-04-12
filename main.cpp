#include <iostream>
#include "Game.h"

int main() {
	Game game;
	game.constructConsole(60, 60);
	game.start();
	/*ScoreBoard s;
	s.addNewPlayerToTable();
	s.popLastPlayer();*/

	return 0;
}

