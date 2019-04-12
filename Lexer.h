//
// Created by Kiarash on 12/04/2019.
//

#ifndef COMPILER_PROJECT_LEXER_H
#define COMPILER_PROJECT_LEXER_H

#include "Token.h"

class Lexer
{
public:
	string input;

	Lexer(string input);

	Token getNextToken();

};

#endif //COMPILER_PROJECT_LEXER_H
