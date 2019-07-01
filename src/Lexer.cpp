
#include "Parser.h"
#include "Lexer.h"

Lexer::Lexer(string address)
{
    lexerOutFile.open(LEXER_OUT_ADDRESS);
	ifstream fin(address);
	stringstream buffer;
	buffer << fin.rdbuf();
	input = buffer.str();
}

Token* Lexer::getNextToken()
{
    char readChar;
	while (currentIndex <= input.size())
	{
		readChar = input[currentIndex++];
        line += (readChar == '\n');
//        cerr << "current state is: " << currentState;
//        cerr << " current char is: " << readChar << endl;
		switch (currentState)
		{
			case 1:
                // symbols
                if (readChar != '=' && isSymbol(readChar))
                {
                    return generateToken(-1);
                }
                else if (readChar == '=')
                {
                    currentState = 4;
                }
                // end of file
                else if (readChar == 0)
                {
                    return generateToken(Parser::tokenIndices["eof"]);
                }
                // num
                else if (isdigit(readChar))
                {
                    currentState = 2;
                }
                // comment
                else if (readChar == '/')
                {
                    currentState = 5;
                }
                // id
                else if (isalpha(readChar))
                {
                    currentState = 3;
                }
                // whitespace
                else if (isspace(readChar))
                {
                    startIndex = currentIndex;
                }
                // invalid char
                else if (!isValid(readChar))
                {
                    return generateToken(ERROR_TOKEN_ID);
                }
				break;
			case 2:
                // num
				if (isdigit(readChar))
                {
					currentState = 2;
                }
                // invalid char
                else if (!isValid(readChar))
                {
                    return generateToken(ERROR_TOKEN_ID);
                }
                else
                {
                    currentIndex--;
                    line -= (readChar == '\n');
                    return generateToken(NUM_TOKEN_ID);
                }
				break;
			case 3:
                if (!isValid(readChar))
                {
                    return generateToken(ERROR_TOKEN_ID);
                }
                else if (!isalnum(readChar))
                {
                    currentIndex--;
                    line -= (readChar == '\n');
                    return generateToken(-1);
                }
				break;
			case 4:
                // == token
                if (readChar == '=')
                {
                    return generateToken(-1);
                }
                // invalid char
                else if (!isValid(readChar))
                {
                    return generateToken(ERROR_TOKEN_ID);
                }
                // = char, need to retract
                else
                {
                    currentIndex--;
                    line -= (readChar == '\n');
                    return generateToken(-1);
                }
				break;
			case 5:
                // one line comment
				if (readChar == '/')
                {
					currentState = 6;
                }
                // multi-line comment
				else if (readChar == '*')
                {
					currentState = 7;
                }
				else
				{
                    return generateToken(ERROR_TOKEN_ID);
				}
				break;
			case 6:
                // end of file
                if (readChar == 0)
                {
                    currentIndex--;
                    line -= (readChar == '\n');
                    startIndex = currentIndex;
                    currentState = 1;
                }
                // end of line
                else if (readChar == '\n')
                {
                    startIndex = currentIndex;
                    currentState = 1;
                }
				break;
			case 7:
				if (readChar == '*')
                {
					currentState = 8;
                }
				break;
			case 8:
				if (readChar == '/')
                {
                    startIndex = currentIndex;
					currentState = 1;
                }
                else
                {
                    currentState = 7;
                }
				break;
			default:
				break;
		}
	}
    // last token ended in eof
    if (startIndex != currentIndex)
    {
        return generateToken(ERROR_TOKEN_ID);
    }
    return nullptr;
}

Token* Lexer::generateToken(int type)
{
    string buffer = input.substr(startIndex, currentIndex - startIndex);
    if (type == -1)
        type = Parser::getTokenId(buffer);
    Token *ret = new Token(type, buffer, line);
//    cerr << buffer << " " << type << endl;
    if (type == ERROR_TOKEN_ID)
    {
        errorFile << "Lexer: Line #" << line << " - Unknown Token \"" << buffer << "\"\n";
    }
    else
    {
        lexerOutFile << "Lexer: Line #" << line << " - TokenType: " << Parser::tokenNames[type] << " - Value: " << buffer << endl;
    }
    currentState = startState;
    startIndex = currentIndex;
    return ret;
}

Lexer::~Lexer()
{
    lexerOutFile.close();
}

bool Lexer::isSymbol(char c)
{
	return c == ':' || c == ';' || c == ',' || c == '[' || c == ']' || c == '(' || c == ')' || c == '{' || c == '}' ||
		   c == '+' || c == '-' || c == '*' || c == '<' || c == '=';
}

bool Lexer::isValid(char c)
{
	return isalnum(c) || isSymbol(c) || isspace(c) || c == '/' || c == '\0';
}

