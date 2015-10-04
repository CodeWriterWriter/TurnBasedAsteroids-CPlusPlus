#ifndef ASTEROID_H
#define ASTEROID_H

#include <vector>

struct Asteroid
{
	int category;
	int x;
	int y;
	int radius;
	int speed;
	int direction; 
};


typedef std::vector<Asteroid> AsteroidList;

bool isColliding(int x, int y, const Asteroid &a);

Asteroid mkSmallAsteroid(int x, int y, int dir);
Asteroid mkLargeAsteroid(int x, int y, int dir);

#endif