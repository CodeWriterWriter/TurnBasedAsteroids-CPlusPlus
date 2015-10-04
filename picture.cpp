#include "picture.h"
#include <string>
#include <iostream>
#include <vector>

void init(Picture &p, int width, int height)
{
	p.width = width;
	p.height = height;
	p.imgData.clear();
	std::string spaces(width, ' ');
	for( int i = 0; i != height; ++i )
		p.imgData.push_back( spaces );
}


std::ostream &write(std::ostream &os, const Picture &p)
{
	typedef std::vector<std::string>::size_type sz_type;

	for(sz_type row = 0; row != p.imgData.size(); ++row )
		os << p.imgData[row] << std::endl;

	return os;
}

// insert a character at position (x,y) in a toroidal picture
void put(Picture &p, int x, int y, char c)
{
	// wrap x coord
	if( x >= p.width) 
		x -= p.width;
	else if( x < 0 )
		x += p.width;

	// wrap y coord
	if( y >= p.height ) 
		y -= p.height;
	else if( y < 0 )
		y += p.height;

	// y gives the row and x the column
	p.imgData[y][x] = c;
}
