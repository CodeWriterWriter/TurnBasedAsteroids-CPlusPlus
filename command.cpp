#include "command.h"
#include <iostream>
#include <string>

#include <cctype>

// Convert a string to lowercase
std::string &strlower(std::string &s) {
	for(std::string::size_type i = 0; i != s.length(); ++i)
	{
		s[i] = tolower(s[i]);
	}
	return s;
}

bool readCommand( Command& cmd )
{

	std::string cmdString;
	const std::string prompt = "? ";

	bool done = false;
	std::string actionStr;
	do
	{
		std::cout << prompt;
		if( std::cin >> actionStr )
		{
			strlower( actionStr );
			if( actionStr == "move" || actionStr == "shoot" )
			{
				cmd.action = actionStr;
				if( std::cin >> cmd.direction )
				{
					if( cmd.direction < 0 || cmd.direction > 8 )
						std::cout << "direction must be in range 0 - 7." << std::endl;
					else
						done = true;
				} 
				else 
				{
					std::cin.clear();
				}
			} 
			else if( actionStr == "quit" )
			{
				return false;
			}
		}
		else 
			return false;
	} while( !done );

	return true;
}

