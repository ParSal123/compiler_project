//
// Created by Kiarash on 12/04/2019.
//

#ifndef COMPILER_PROJECT_TOKEN_H
#define COMPILER_PROJECT_TOKEN_H

#include "Commons.h"

class Token
{
private:
	int line;
	int type;
	string value;

public:

	Token(int type, string value, int line) : line(line), type(type), value(value)
	{}

	int getType()
	{
		return type;
	}

	string getValue()
	{
		return value;
	}

	int getLine()
	{
		return line;
	}

};

#endif //COMPILER_PROJECT_TOKEN_H

