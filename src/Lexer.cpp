//
// Created by Kiarash on 12/04/2019.
//

#include "Lexer.h"

Lexer::Lexer(string input) : input(input)
{}

Token Lexer::getNextToken()
{
	while (true)
	{
		char readChar = input[currentIndex++];
		if(readChar == '\n')
			line++;
		bool validChar = true, halt = false;
		switch (currentState)
		{
			case 1:
				if (isdigit(readChar))
					currentState = 2;
				else if (isalpha(readChar))
					currentState = 3;
				else if (issymbol(readChar))
					currentState = 4;
				else if (isequal(readChar))
					currentState = 5;
				else if (isWhitespace(readChar))
				{
					currentState = 7;
				}
				else if (isSlash(readChar))
					currentState = 8;
				else if (isEOF(readChar))
				{
					reset();
					return Token(Eof, "");
				} else halt = true;
				break;
			case 2:
				if (isdigit(readChar))
					currentState = 2;
				else halt = true;
				break;
			case 3:
				if (isalnum(readChar))
					currentState = 3;
				else halt = true;
				break;
			case 4:
				halt = true;
				break;
			case 5:
				if (isequal(readChar))
					currentState = 6;
				else halt = true;
				break;
			case 6:
				halt = true;
				break;
			case 7:
				halt = true;
				break;
			case 8:
				if (isSlash(readChar))
					currentState = 9;
				else if (isStar(readChar))
					currentState = 10;
				else
				{
					validChar = false;
					halt = true;
				}
				break;
			case 9:
				if(!isEndline(readChar))
					currentState = 9;
				else currentState = 12;
				break;
			case 10:
				if (isStar(readChar))
					currentState = 11;
				else currentState = 10;
				break;
			case 11:
				if (isSlash(readChar))
					currentState = 12;
				else currentState = 10;
				break;
			case 12:
				halt = true;
				break;
			default:
				break;
		}
		if (halt)
		{
			if (!valid(readChar) || !validChar)
			{
				Token ret = Token(Error, buffer + readChar);
				reset();
				return ret;
			} else
			{
				if (accept[currentState] != None)
				{
					currentIndex--;
					Token ret = Token(
							isKeyword(buffer) ? Keyword : accept[currentState],
							buffer);
					reset();
					return ret;
				}
			}
			currentIndex--;
			reset();
		} else buffer += readChar;
	}
}

void Lexer::reset()
{
	currentState = startState;
	buffer.clear();
}

bool Lexer::issymbol(char c)
{
	return c == ':' || c == ';' || c == ',' || c == '[' || c == ']' || c == '(' || c == ')' || c == '{' || c == '}' || c == '+'
		   || c == '-' || c == '*' || c == '<';
}

bool Lexer::valid(char c)
{
	return isalnum(c) || issymbol(c) || isWhitespace(c) || c == '=' || c == '/' || c == '\0';
}

bool Lexer::isWhitespace(char c)
{
	return c == 32 || isEndline(c) || c == 13 || c == 9 || c == 11 || c == 12;
}

bool Lexer::isequal(char c)
{
	return c == '=';
}

bool Lexer::isEndline(char c)
{
	return c == '\n';
}

bool Lexer::isSlash(char c)
{
	return c == '/';
}

bool Lexer::isStar(char c)
{
	return c == '*';
}


bool Lexer::isKeyword(string buffer)
{
	return buffer == "if" || buffer == "else" || buffer == "void" || buffer == "int" || buffer == "while"
		   || buffer == "break" || buffer == "continue" || buffer == "switch" || buffer == "default"
		   || buffer == "case" || buffer == "return";
}

bool Lexer::isEOF(char c)
{
	return c == '\0' || currentIndex >= input.length();
}
