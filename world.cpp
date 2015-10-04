#include "world.h"
#include <iostream>
#include <ctime>

void setup(World& w)
{
	w.width=40;
	w.height=20;
	w.asteroids.clear();

	w.ship.imgChar = 'o';
	w.ship.numBullets = w.ship.maxBullets = 5;
	w.ship.speed = 2;
	w.ship.direction = 0;
	w.ship.x = w.width / 2;
	w.ship.y = w.height / 2;
	w.ship.dead = false;

	w.score = 0;

	w.bulletSpeed = 3;
	w.bulletChar = '+';
	w.bullets.clear();
	for(BulletList::size_type i = 0; i != w.ship.maxBullets; ++i)
	{
		Bullet b;
		b.dead = true;
		w.bullets.push_back(b);
	}

	Picture pic; 
	
	// picture for large asteroids
	pic.imgData.push_back("/---\\");
	pic.imgData.push_back("|   |");
	pic.imgData.push_back("|   |");
	pic.imgData.push_back("|   |");
	pic.imgData.push_back("\\---/");
	pic.height = pic.imgData.size();
	pic.width = pic.imgData[0].length();
	w.asteroidPictures.push_back( pic );

	// picture for small asteroids
	pic.imgData.clear();
	pic.imgData.push_back("/-\\");
	pic.imgData.push_back("|  |");
	pic.imgData.push_back("\\-/");
	pic.height = pic.imgData.size();
	pic.width = pic.imgData[0].length();
	w.asteroidPictures.push_back( pic );

	// Spawn some asteroids
	
	srand(time(0));
	for (int i = 0; i < 3; i++)
	{
		int x = rand() % 40;
		int y = rand() % 20;
		int dir = rand() % 5 + 1;
		while ((18 < x) && (x < 23) && (8 < y) && (y < 13))
		{
			x = rand() % 40;
			y = rand() % 20;

		}
		w.asteroids.push_back(mkLargeAsteroid(x, y, dir));

	}

	/*
	w.asteroids.push_back( mkLargeAsteroid( 0,  0, 3) );
	w.asteroids.push_back( mkLargeAsteroid(29, 10, 6) );
	w.asteroids.push_back( mkLargeAsteroid( 4, 17, 3) );
	*/

}


bool isGameOver(const World& w)
{
	return w.asteroids.size() == 0 || w.ship.dead ;
}


void draw(const World &w, Picture &screen, const Asteroid &a)
{
	const int left  = a.x - a.radius;
	const int top = a.y - a.radius;

	int x = left; int y = top;

	const Picture &ap = w.asteroidPictures[a.category];
	for( std::vector<std::string>::size_type row = 0; row != ap.imgData.size(); ++row)
	{
		x = left;
		for(std::string::size_type col = 0; col != ap.imgData[row].length(); ++col)
		{
			put(screen, x, y, ap.imgData[row][col]);
			++x;
		}
		++y;
	}
}

void draw(const World& w)
{
	Picture screen;
	init( screen, w.width, w.height );

	// Draw asteroids
	for( AsteroidList::size_type i = 0; i != w.asteroids.size(); ++i )
	{
		draw( w, screen, w.asteroids[i] );
	}

	// Draw bullets
	for(BulletList::size_type i = 0; i != w.bullets.size(); ++i)
	{
		const Bullet &b = w.bullets[i];
		if( !b.dead )
		{
			put(screen, b.x, b.y, w.bulletChar);
		}
	}

	// Draw ship
	put(screen, w.ship.x, w.ship.y, w.ship.imgChar);

	// output to screen
	write(std::cout, screen);
}

