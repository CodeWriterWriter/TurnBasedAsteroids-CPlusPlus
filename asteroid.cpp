#include "asteroid.h"

Asteroid mkSmallAsteroid(int x, int y, int dir)
{
	Asteroid a;
	a.category = 1;
	a.x = x; a.y = y;
	a.radius = 1;

	a.speed = 3;
	a.direction = dir;

	return a;
}

Asteroid mkLargeAsteroid(int x, int y, int dir)
{
	Asteroid a;
	a.category = 0;
	a.x = x; a.y = y;
	a.radius = 2;

	a.speed = 1;
	a.direction = dir;

	return a;
}

bool isColliding(int x, int y, const Asteroid &a)
{
	int r = a.radius+1;
	return (a.x - x)*(a.x - x) + (a.y - y)*(a.y - y) < r * r; 
}
