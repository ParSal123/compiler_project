
#ifndef COMPILER_PROJECT_LEXER_H
#define COMPILER_PROJECT_LEXER_H

#include "Token.h"
#include "Parser.h"

class Lexer
{
public:
	Lexer(string address);
	Token* getNextToken();
	int line = 1;

private:
	int currentState = 1;
	const int startState = 1;
	unsigned int currentIndex = 0, startIndex = 0;
	string input;
    ofstream lexerOutFile;

	bool isSymbol(char character);
	bool isValid(char c);
    Token* generateToken(int type);
    ~Lexer();

};

#endif //COMPILER_PROJECT_LEXER_H

