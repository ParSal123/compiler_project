//
// Created by Kiarash on 12/04/2019.
//

#ifndef COMPILER_PROJECT_TOKEN_H
#define COMPILER_PROJECT_TOKEN_H

#include "Commons.h"

class Token
{
private:
	int type;
	string value;
	int line;

public:
	Token(int type, string value) : type(type), value(value)
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
	void setLine(int l)
	{
		line = l;
	}
};



#endif //COMPILER_PROJECT_TOKEN_H
