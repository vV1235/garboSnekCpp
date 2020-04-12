#include "Apple.h"

Apple::Apple(int x_, int y_) : 
	x{x_},
	y{y_}
{
}

Apple::Apple() :
	Apple(20, 20)
{	
}

Apple::Apple(const Apple& apple) {
	this->x = apple.x;
	this->y = apple.y;
}