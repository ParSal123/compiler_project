//
// Created by Kiarash on 12/04/2019.
//
#ifndef COMPILER_PROJECT_LEXER_H
#define COMPILER_PROJECT_LEXER_H

#include "Token.h"
#include "Parser.h"

class Lexer
{
public:

	Lexer(string input);
	Token getNextToken();
	int line = 1;
private:
	int currentState = 1;
	const int startState = 1;
	unsigned int currentIndex = 0;
	string input, buffer = "";
	int tokenTypeOfState[13] = {-1, -1, NUM_TOKEN_ID, ID_TOKEN_ID, 0, 0, 0, -2, -1, -1, -1, -1,
							-3};
	bool isSymbol(char character);

	bool valid(char c);

	bool isEqual(char c);

	bool isSymbol(string s);

	void reset();

	bool isKeyword(string buffer);

	bool isEOF(char c);

	bool isWhitespace(char c);

	bool isEndline(char c);

	bool isSlash(char c);

	bool isStar(char c);

};

#endif //COMPILER_PROJECT_LEXER_H
