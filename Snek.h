#pragma once
#include <list>

class Snek {
	friend class Game;
public:
	Snek();
private:
	struct snekSegment {
		int x;
		int y;
	};
	//bool isAlive;
	std::list<snekSegment> body;
};
