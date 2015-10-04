//+
// Console Asteroids by Karl Sandison, 2012
//-
#include "command.h"
#include "world.h"

#include <vector>
#include <iostream>
#include <string>

void clearScreen()
{
#ifdef WIN32
	system( "CLS" );
#endif
}

// Display instructions screen
void welcome()
{
	std::cout << 
		"\t\tC O N S O L E   A S T E R O I D S\n"
		"\tInstructions:\n"
		"\t=============\n"
		"\n"
		"\tConsole Asteroids is a turn-based remake of the arcade classic.\n"
		"\tOn each turn you may issue one command. The available commands are:\n"
		"\n"
		"\t\tshoot d\t\tfire a bullet in direction d\n"
		"\n"
		"\t\tmove  d\t\tmove in direction d\n"
		"\n"
		"\t\tThe directions are:\n"
		"\t\t\t0 = North; 1 = North West; 2 = East\n"
		"\t\t\t3 = South East; 4 = South; 5 = South West\n"
		"\t\t\t6 = West; 7 = North West\n"
		"\n"
		"\t\t\t\t7 0 1\n"
		"\t\t\t\t6   2\n"
		"\t\t\t\t5 4 3\n"
		"\n"
		"\t\tquit   \t\tquit the game <ctrl>-z has the same effect\n"
		"\n\n\n"
		"\nPress Enter"
		;
	std::string garbage;
	getline(std::cin, garbage);
}

// transform the coordinates held in x and y
// such that their new values correspond to a
// a movement in the given direction at the
// given speed.
/*void move(int &x, int &y, int speed, int direction)
{
	                     // 0   1   2   3   4   5   6   7
	static int deltaX[] = { 0, +1, +1, +1,  0, -1, -1, -1};
	static int deltaY[] = {-1, -1,  0, +1, +1, +1,  0, -1};

	x += deltaX[direction] * speed;
	y += deltaY[direction] * speed;
}*/


void move(int &x, int&y, int &speed, int direction)
{
	int direct;
	if (direction == 5)
	{
		direct = direction;
	}
	else
	{
		direct = (direction / 2) -1;
	}
	static int deltaX[] = {0, -1, +1, +0, 0 };
	static int deltaY[] = {+1, 0, 0, -1, 0};

	if (direct == 5)
	{
		speed = 0;
		/*x += deltaX[direct] *speed;
		y += deltaX[direct] * speed;
		*/
	}
	else
	{
		if (speed == 0)
		{
			speed = 2;
		}
		x += deltaX[direct] * speed;
		y += deltaY[direct] * speed;
	}
}
// If the coordinates (x,y) are outside the boundaries
// of given given width and height, they are wrapped
// around the corresponding horizontal and/or vertical
// boundaries.
void wrap(int width, int height, int &x, int &y)
{
	if( x >= width) 
		x -= width;
	else if( x < 0 )
		x += width;

	if( y >= height ) 
		y -= height;
	else if( y < 0 )
		y += height;
}

void shoot(World &w, int dir)
{
	if( w.ship.numBullets > 0 )
	{
		--w.ship.numBullets;
		// Re-animate a dead bullet
		for(BulletList::size_type i = 0; i != w.bullets.size(); ++i)
		{
			Bullet &b = w.bullets[i];
			if( b.dead )
			{
				b.direction = dir;
				b.x = w.ship.x;
				b.y = w.ship.y;
				b.dead = false;
				return;
			}
		}
	}
}


void applyCommand(const Command &cmd, World &w)
{
	if( cmd.action == "move")
	{
		w.ship.direction = cmd.direction;
	}
	else if( cmd.action == "shoot")
	{
		shoot(w, cmd.direction);
	}
}


void display(const World& w)
{
	clearScreen();
	std::string score = std::to_string(w.score);
	std::cout << "\tC O N S O L E   A S T E R O I D S\n \t Score = " << score << " \t Speed = " << w.ship.speed << "\n";
	draw( w );
}

void moveShip(World &w)
{
	move(w.ship.x, w.ship.y, w.ship.speed,  w.ship.direction );
	wrap(w.width, w.height, w.ship.x, w.ship.y);
}

void moveAsteroids(World &w)
{
	for( AsteroidList::size_type i = 0; i != w.asteroids.size(); ++i)
	{
		Asteroid &a = w.asteroids[i];
		move( a.x, a.y, a.speed, a.direction ); 
		wrap( w.width, w.height, a.x, a.y);
	}
}

void moveBullets(World &w)
{
	for(BulletList::size_type i = 0; i != w.bullets.size(); ++i)
	{
		Bullet &b = w.bullets[i];
		if( !b.dead )
		{
			move( b.x, b.y, w.bulletSpeed, b.direction );
			if( b.x < 0 || b.x >= w.width || b.y < 0 || b.y >= w.height )
			{
				b.dead = true;
				++w.ship.numBullets;
			}
		}
	}
}

void moveGameObjects(World &w)
{
	moveShip( w );
	moveAsteroids( w );
	moveBullets( w );
}

void processBulletAsteroidCollisions(World &w)
{
	// check for collisions between bullets and asteroids
	for(BulletList::size_type i = 0; i != w.bullets.size(); ++i)
	{
		Bullet &b = w.bullets[i];
		if( !b.dead ) 
		{
			for( AsteroidList::size_type i = 0; i != w.asteroids.size(); )
			{
				Asteroid &a = w.asteroids[i];
				if( isColliding( b.x, b.y, a ) )
				{
					if (a.category == 0)
					{
						b.dead = true;
						++w.ship.numBullets;
						w.score += 200;
						w.asteroids.push_back(mkSmallAsteroid(a.x, a.y, a.direction));
						w.asteroids.erase(w.asteroids.begin() + i);
					}
					else
					{
						b.dead = true;
						++w.ship.numBullets;
						w.score += 100;
						w.asteroids.erase(w.asteroids.begin() + i);
					}
				}
				else
					++i;
			}
		}
	}
}

void processShipAsteroidCollisions(World &w)
{
	Ship &s = w.ship;
	for( AsteroidList::size_type i = 0; i != w.asteroids.size(); ++i)
	{
		Asteroid &a = w.asteroids[i];
		if( isColliding( s.x, s.y, a ) )
		{
			s.dead = true;
			return; // only need to be killed once
		}
	}
}

void processCollisions(World &w)
{
	processBulletAsteroidCollisions( w );
	processShipAsteroidCollisions( w );
}

void update(World &w)
{
	moveGameObjects( w );
	processCollisions( w );
}

void displayYouWon(World &w)
{
	std::cout << "You won! Amazing shooting Hotshot!" << std::endl;
}

void displayYouLose(World &w)
{
	std::cout << "Game Over!" << std::endl;
}

int main(int argc, char* argv[])
{
	World world;
	setup( world );

	welcome();

	Command toDo;
	display( world );
	while( readCommand( toDo ) )
	{
		applyCommand( toDo, world );
		update( world );

		display( world );
		if( isGameOver( world ) )
			break;
	}

	if( world.ship.dead || !world.asteroids.empty() )
		displayYouLose( world );
	else
		displayYouWon( world );

	return 0;
}