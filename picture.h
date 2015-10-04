#ifndef PICTURE_H
#define PICTURE_H

#include <vector>
#include <iostream>

struct Picture
{
	int width;
	int height;
	std::vector<std::string> imgData;
};

typedef std::vector<Picture> PictureList;
typedef PictureList::size_type PictureID;

void init(Picture &p, int width, int height);
std::ostream &write(std::ostream &os, const Picture &p);

// insert a character at position (x,y) in a toroidal picture
void put(Picture &p, int x, int y, char c);

#endif