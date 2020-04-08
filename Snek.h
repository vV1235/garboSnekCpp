#pragma once
#include <list>

class Snek {
public:
	Snek();

	struct snekSegment {
		int x;
		int y;
	};
	//bool isAlive;
	std::list<snekSegment> body;
};
