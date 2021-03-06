//
// Created by Kiarash on 19/05/2019.
//

#include "Parser.h"

TokenToIndicesMap Parser::tokenIndices;
IndicesToTokenMap Parser::tokenNames;

void Parser::print()
{
	for (auto &i : diagrams)
	{
		cout << i.first << " " << tokenNames[i.first] << endl;
		for (auto &path: i.second)
		{
			for (int j : path)
				cout << tokenNames[j] << " ";
			cout << endl;
		}
		cout << "First: " << endl;
		for (auto j : first[i.first])
			cout << tokenNames[j] << " ";
		cout << endl << "Follow: " << endl;
		for (auto j : follow[i.first])
			cout << tokenNames[j] << " ";
		cout << endl;
		cout << "______________\n" << endl;
	}
	for (auto &i : tokenIndices)
		cout << i.second << " " << i.first << endl;
}

Parser::Parser()
{
	parseTree.open(PARSE_TREE_ADDRESS);
	ifstream fin(GRAMMAR_ADDRESS);
	int numberOfTokensInRule = 0;
	TransitionDiagram *currentDiagram = nullptr;
	DiagramPath *currentPath = nullptr;
	bool startOfRule = true;
	tokenIndices.clear();
	tokenIndices["error"] = ERROR_TOKEN_ID;
	tokenIndices["eps"] = EPSILON_TOKEN_ID;
	tokenIndices["num"] = NUM_TOKEN_ID;
	tokenIndices["id"] = ID_TOKEN_ID;
	string input;
	while (fin >> input)
	{

		if (startOfRule)
		{
			if (tokenIndices.find(input) == tokenIndices.end())
				tokenIndices[input] = numberOfTokens++;
			int id = tokenIndices[input];
			if (isupper(input[0]))
				nonTerminal.insert(id);
			diagrams[id] = TransitionDiagram();
			currentDiagram = &diagrams[id];
			currentDiagram->push_back(DiagramPath());
			currentPath = &((*currentDiagram)[currentDiagram->size() - 1]);
			startOfRule = false;
		}
		else
		{
			if (input == "->") continue;
			else if (input == ".")
			{
				startOfRule = true;
				if (numberOfTokensInRule == 0)
					currentPath->push_back(EPSILON_TOKEN_ID);
				numberOfTokensInRule = 0;
			}
			else if (input == "|")
			{
				if (numberOfTokensInRule == 0)
					currentPath->push_back(EPSILON_TOKEN_ID);
				numberOfTokensInRule = 0;
				currentDiagram->push_back(DiagramPath());
				currentPath = &((*currentDiagram)[currentDiagram->size() - 1]);
			}
			else
			{
				if (tokenIndices.find(input) == tokenIndices.end())
					tokenIndices[input] = numberOfTokens++;
				int id = tokenIndices[input];
				if (isupper(input[0]))
					nonTerminal.insert(id);
				currentPath->push_back(id);
				numberOfTokensInRule++;
			}
		}
	}
	for (auto &token : tokenIndices)
	{
		tokenNames[token.second] = token.first;
	}
	initFirstFollow();
}

void Parser::initFirstFollow()
{
	ifstream fin(FIRST_FOLLOW_ADDRESS);
	string input;
	while (getline(fin, input))
	{
		string firstSet, followSet, nullable, endable, alaki;
		getline(fin, firstSet);
		getline(fin, followSet);
		getline(fin, nullable);
		getline(fin, endable);
		getline(fin, alaki);
		int id = tokenIndices[input];
		stringstream firstSS(firstSet), followSS(followSet);
		string in;
		while (firstSS >> in)
			first[id].insert(tokenIndices[in]);
		while (followSS >> in)
			follow[id].insert(tokenIndices[in]);
		if (nullable == "yes")
			first[id].insert(EPSILON_TOKEN_ID);
	}
}

int Parser::getTokenId(string s)
{
    if (tokenIndices.find(s) != tokenIndices.end())
    {
        return tokenIndices[s];
    }
    return ID_TOKEN_ID;
}

void Parser::parse(int dfa, int level, bool canParseEps)
{
	int tokenId = currentToken->getType();
	for (auto &path : diagrams[dfa])
	{
		int firstToken = path[0];
        cerr << "first token of the path is: " << tokenNames[firstToken] << endl;
		if ((!isNonTerminal(firstToken) && firstToken == tokenId)
			|| (firstToken == EPSILON_TOKEN_ID && canParseEps)
			|| (isNonTerminal(firstToken) && isInFirst(tokenId, firstToken))
			|| (isNonTerminal(firstToken) && isInFirst(EPSILON_TOKEN_ID, firstToken) && isInFollow(tokenId, firstToken)))
		{
            cerr << "entering the path\n";
			for (TokenId id : path)
			{
                cerr << "level: " << level << " and expected token is: " << tokenNames[id] << endl;
				if (!isNonTerminal(id))
				{
					if (id == tokenId)
					{
						printTree(tokenId, level);
						currentToken = getNextToken();
                        if (currentToken == nullptr)
                        {
                            return;
                        }
                        cerr << "current token is: " << tokenNames[currentToken->getType()] << endl;
					}
					else if (id == EPSILON_TOKEN_ID && canParseEps)
                    {
						printTree(id, level);
                    }
					else if (id == tokenIndices["eof"])
                    {
						throw malformedInput();
                    }
					else
					{
						printError(missingTerminal(id));
						printTree(id, level, true);
					}
				}
				else
				{
					while (!isInFirst(tokenId, id) && !isInFollow(tokenId, id))
					{
                        cerr << "token " << tokenNames[tokenId] << " is not in first or follow set of " << tokenNames[id] << endl;
						if (tokenId == tokenIndices["eof"])
							throw unexpectedEndOfFile();
						printError(unexpectedTerminal());
						currentToken = getNextToken();
                        if (currentToken == nullptr)
                        {
                            return;
                        }
                        cerr << "current token is: " << tokenNames[currentToken->getType()] << endl;
						tokenId = currentToken->getType();
					}

					if (isInFirst(tokenId, id) ||
						(isInFirst(EPSILON_TOKEN_ID, id) && isInFollow(tokenId, id)))
                    {
					    printTree(id, level);
						parse(id, level + 1, isInFollow(tokenId, id));
                    }
					else
                    {
					    printTree(id, level, true);
						printError(missingNonTerminal(id));
                    }
				}
                if (currentToken == nullptr)
                {
                    return;
                }
				tokenId = currentToken->getType();
			}
			return;
		}
	}
}

Token* Parser::getNextToken()
{
	auto ret = lexer->getNextToken();
	if (ret != nullptr && ret->getType() == ERROR_TOKEN_ID)
	{
		return getNextToken();
	}
	return ret;
}

void Parser::printTree(TokenId id, int level, bool missed)
{
	while (level--)
		parseTree << "|\t";
	parseTree << tokenNames[id];
    if (!missed && (id == ID_TOKEN_ID || id == NUM_TOKEN_ID))
    {
        parseTree << " --- " << currentToken->getValue();
    }
	if (missed) parseTree << " (missed)";
	parseTree << endl;
}

bool Parser::isInFirst(int token, int nonTerminal)
{
	return first[nonTerminal].find(token) != first[nonTerminal].end();
}

bool Parser::isInFollow(int token, int nonTerminal)
{
	return follow[nonTerminal].find(token) != follow[nonTerminal].end();
}

bool Parser::isNonTerminal(int token)
{
	return nonTerminal.find(token) != nonTerminal.end();
}

void Parser::parse()
{
	parseTree << "Program" << endl;
	try
	{
	    currentToken = lexer->getNextToken();
        cerr << "current token is: " << tokenNames[currentToken->getType()] << endl;
		parse(getTokenId("Program"), 1, false);
	}
	catch (string msg)
	{
        printError(msg);
	}
}

void Parser::printError(string msg)
{
    errorFile << "Parser: Line #" << msg << endl;
}

string Parser::missingTerminal(TokenId terminalId)
{
    return to_string(currentToken->getLine()) + " - Syntax Error! Missing Terminal " + tokenNames[terminalId];
}

string Parser::unexpectedTerminal()
{
    return to_string(currentToken->getLine()) + " - Syntax Error! Unexpected Terminal "
        + tokenNames[currentToken->getType()] + " \"" + currentToken->getValue() + "\"";
}

string Parser::missingNonTerminal(TokenId nonTerminal)
{
    return to_string(currentToken->getLine()) + " - Syntax Error! Missing Nonterminal "
        + tokenNames[nonTerminal];
}

string Parser::unexpectedEndOfFile()
{
	return to_string(currentToken->getLine()) + " - Syntax Error! Unexpected eof";
}

string Parser::malformedInput()
{
	return to_string(currentToken->getLine()) + " - Syntax Error! Malformed Input";
}
