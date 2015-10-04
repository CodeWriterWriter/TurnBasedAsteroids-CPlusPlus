#ifndef COMMAND_H
#define COMMAND_H

#include <string>

struct Command
{
	std::string action;
	int  direction;
};

bool readCommand( Command& cmd );

#endif