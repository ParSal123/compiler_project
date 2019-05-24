//
// Created by Kiarash on 12/04/2019.
//

#include "Parser.h"
#include "Lexer.h"

Lexer::Lexer(string input) : input(input)
{}


Token Lexer::getNextToken()
{
	while (true)
	{
		char readChar = input[currentIndex++];
		bool validChar = true, halt = false;
		switch (currentState)
		{
			case 1:
				if (isdigit(readChar))
					currentState = 2;
				else if (isalpha(readChar))
					currentState = 3;
				else if (isSymbol(readChar))
					currentState = 4;
				else if (isEqual(readChar))
					currentState = 5;
				else if (isWhitespace(readChar))
				{
					if (isEndline(readChar))
						line++;
					currentState = 7;
				}
				else if (isSlash(readChar))
					currentState = 8;
				else if (isEOF(readChar))
				{
					reset();
					return Token(Parser::getTokenId("eof"), "eof", line);
				}
				else halt = true;
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
				if (isEqual(readChar))
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
				if (!isEndline(readChar))
					currentState = 9;
				else currentState = 12;
				break;
			case 10:
				if (isEndline(readChar)) line++;
				if (isStar(readChar))
					currentState = 11;
				else currentState = 10;
				break;
			case 11:
				if (isEndline(readChar)) line++;
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
				Token ret = Token(ERROR_TOKEN_ID, buffer + readChar, line);
				reset();
				return ret;
			}
			else
			{
				if (tokenTypeOfState[currentState] != -1)
				{
					currentIndex--;
					Token ret = Token(
							isKeyword(buffer) || isSymbol(buffer) ? Parser::getTokenId(buffer)
																  : tokenTypeOfState[currentState],
							buffer, line);
					reset();
					if (ret.getType() < 0) return getNextToken();
					return ret;
				}
			}
			currentIndex--;
			reset();
		}
		else buffer += readChar;
	}
}

void Lexer::reset()
{
	currentState = startState;
	buffer.clear();
}

bool Lexer::isSymbol(char c)
{
	return c == ':' || c == ';' || c == ',' || c == '[' || c == ']' || c == '(' || c == ')' || c == '{' || c == '}' ||
		   c == '+' || c == '-' || c == '*' || c == '<';
}

bool Lexer::isSymbol(string s)
{
	return s == ":" || s == ";" || s == "," || s == "[" || s == "]" || s == "(" || s == ")" || s == "{" || s == "}" ||
		   s == "+" || s == "-" || s == "*" || s == "<" || s == "=" || s == "==";
}

bool Lexer::valid(char c)
{
	return isalnum(c) || isSymbol(c) || isWhitespace(c) || c == '=' || c == '/' || c == '\0';
}

bool Lexer::isWhitespace(char c)
{
	return c == 32 || isEndline(c) || c == 13 || c == 9 || c == 11 || c == 12;
}

bool Lexer::isEqual(char c)
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