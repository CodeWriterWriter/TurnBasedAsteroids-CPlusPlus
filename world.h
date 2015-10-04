#ifndef WORLD_H
#define WORLD_H

#include "asteroid.h"
#include "picture.h"

struct Ship
{
	int speed;
	int direction;
	int numBullets;
	int maxBullets;
	int x;
	int y;
	char imgChar;
	bool dead;
};

struct Bullet
{
	int speed;
	int direction;
	int x;
	int y;
	bool dead;
};
typedef std::vector<Bullet> BulletList;

struct World
{
	int width;
	int height;
	AsteroidList asteroids;
	Ship ship;
	Picture screen;
	PictureList asteroidPictures;
	int  bulletSpeed;
	char bulletChar;
	BulletList bullets;
	int score;
};


void setup(World& w);

void draw(const World& w);

bool isGameOver(const World& w);


#endif