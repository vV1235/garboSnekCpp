#include "Game.h"

Game::Game() : 
	holdKeyW{ false }, 
	holdKeyS{ false }, 
	holdKeyA{ false }, 
	holdKeyD{ false }, 
	isAlive{ true },
	sessionLifeCnt{ 1 },
	currentDirection{ Direction::TOP },
	scoreBoard(2, 2)
{
}

bool Game::setup() {
	return true;
}

void Game::logicManagment() {
	//Moving algorithm

	//0x8000 is a mask for checking if a returned value form GetAsyncState is a high bit i.e. check if the button is being held down
	//cplusplus.com/forum/general/128459/
	holdKeyW = (0x8000 & GetAsyncKeyState(0x57));
	holdKeyS = (0x8000 & GetAsyncKeyState(0x53));
	holdKeyA = (0x8000 & GetAsyncKeyState(0x41));
	holdKeyD = (0x8000 & GetAsyncKeyState(0x44));

	if(holdKeyW && currentDirection != Direction::DOWN) {
		currentDirection = Direction::TOP;
	}
	if(holdKeyS && currentDirection != Direction::TOP) {
		currentDirection = Direction::DOWN;
	}
	if(holdKeyA && currentDirection != Direction::RIGHT) {
		currentDirection = Direction::LEFT;
	}
	if(holdKeyD && currentDirection != Direction::LEFT) {
		currentDirection = Direction::RIGHT;
	}
	switch(currentDirection) {
		case Direction::TOP:
			snek.body.push_front({ snek.body.front().x, snek.body.front().y - 1 });
			break;
		case Direction::DOWN:
			snek.body.push_front({ snek.body.front().x, snek.body.front().y + 1 });
			break;
		case Direction::LEFT:
			snek.body.push_front({ snek.body.front().x - 1, snek.body.front().y });
			break;
		case Direction::RIGHT:
			snek.body.push_front({ snek.body.front().x + 1, snek.body.front().y });
			break;
	}

	//Cut off the tail so the snake wont paint on the screen
	snek.body.pop_back();
}

void Game::checkCollisions() {
	//Check collisions with body
	//should use auto but more
	for(std::list<Snek::snekSegment>::iterator i = snek.body.begin(); i != snek.body.end(); ++i) {
		//Ignore the head, check if body segment i has the same coords as the head
		if(i != snek.body.begin() && i->x == snek.body.front().x && i->y == snek.body.front().y) {
			isAlive = false;
		}
	}

	//Check collision of the snake and apple
	if(snek.body.front().x == apple.x && snek.body.front().y == apple.y) {
		snek.body.push_back({ snek.body.back().x, snek.body.back().y });
		//For now works
		int newPos = rand() % 60 + 1;
		apple.x = newPos;
		apple.y = newPos;
	}

	//Check collisions with walls
	if(snek.body.front().x < 0 || snek.body.front().x >= 60 ||
		snek.body.front().y < 0 || snek.body.front().y >= 60) {
		isAlive = false;
	}
}

void Game::display() {
	//Clear screen(should clear only needed parts, but for now, it works)
	for(int h = 0; h < 60; h++) {
		for(int w = 0; w < 60; w++) {
			screenBuf[h][w].Char.UnicodeChar = L' ';
			screenBuf[h][w].Attributes = 15;
		}
	}
	/*for(int i = 0; i < screenWidth * screenHeight; i ++) {
		screenBuf[i].Char.UnicodeChar = L' ';
		screenBuf[i].Attributes = 0x0000;
	}*/
	
	//Draw body & head
	for(auto s : snek.body) {
		draw(s.x, s.y, L'@', 0x0002);
	}
	draw(snek.body.front().x, snek.body.front().y, L'@', 0x0006);

	//Draw an apple
	draw(apple.x, apple.y, L'@', 0x0004);
	//... breaks controls a little bit so needs to change

	if(!isAlive) {
		//Show gameOverText if you failed
		for(int i = 0; i < scoreBoard.getGameOverText().size(); i++) {
			screenBuf[5][12 + i].Char.UnicodeChar = scoreBoard.getGameOverText()[i];
			screenBuf[5][12 + i].Attributes = 0x000F;
		}

		//-------------------------------------------------------------------------

		//Display score
		std::string temp;
		int x = 0;
		for(int first = 0; first < scoreBoard.getRow(); first++) {
			for(int c_ = 0; c_ < scoreBoard.getCol(); c_++) {
				temp = scoreBoard.getName(first, c_);
				for(int i = 0; i < temp.size(); i++) {
					screenBuf[10 + x][12 + i].Char.UnicodeChar = temp[i];
					screenBuf[10 + x][12 + i].Attributes = 0x000F;
				}
				x++;
			}
		}

		//-------------------------------------------------------------------------
	}
	//Still bad CHANGE THIS
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

bool Game::update(float deltaTimeCnt) {
	if(isAlive) {
		logicManagment();
		checkCollisions();
		display();
	} else {
		//Wait for space being pressed
		while(!isAlive) {
			isAlive = (0x8000 & GetAsyncKeyState(0x20)) != 0;
		}
		resetGame();
	}
	return true;
}

void Game::resetGame() {
	sessionLifeCnt++;
	snek.body = { {28, 30}, {29, 30}, {30, 30} };
	apple.x = 20;
	apple.y = 20;
	currentDirection = Direction::TOP;
}