#pragma once

class Apple {
	friend class Game;
public:
	Apple();
	Apple(int x_, int y_);
	Apple(const Apple& apple);
	Apple(const Apple&& apple) = delete;
private:
	int x;
	int y;
};