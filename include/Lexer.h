//
// Created by Kiarash on 12/04/2019.
//
#ifndef COMPILER_PROJECT_LEXER_H
#define COMPILER_PROJECT_LEXER_H

#include "Token.h"

class Lexer
{
public:

	Lexer(string input);

	Token getNextToken();
	int line = 1,tokenLine = 1;
private:
	int currentState = 1;
	const int startState = 1;
	int currentIndex = 0;
	string input, buffer = "";
	TokenType accept[13] = {None, None, Num, Id, Symbol, Symbol, Symbol, Whitespace, None, None, None, None,
							Comment};
	bool issymbol(char character);

	bool valid(char c);

	bool isequal(char c);

	void reset();

	bool isKeyword(string buffer);

	bool isEOF(char c);

	bool isWhitespace(char c);

	bool isEndline(char c);

	bool isSlash(char c);

	bool isStar(char c);
};

#endif //COMPILER_PROJECT_LEXER_H
