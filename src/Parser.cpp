//
// Created by Kiarash on 19/05/2019.
//

#include "Parser.h"

Parser::TokenToIndicesMap Parser::tokenIndices;
Parser::IndicesToTokenMap Parser::tokenNames;
void Parser::print()
{
//	for(auto word: tokenIndices)
	for (auto &i : diagrams)
	{
		cout << i.first <<" "<<tokenNames[i.first] << endl;
		for (auto &path: i.second)
		{
			for (int j : path)
				cout << tokenNames[j] << " ";
			cout << endl;
		}
		cout<<"First: "<<endl;
		for (auto j : first[i.first])
			cout << tokenNames[j] <<" ";
		cout <<endl << "Follow: " << endl;
		for (auto j : follow[i.first])
			cout << tokenNames[j] <<" ";
		cout <<endl;
		cout<<"______________\n"<<endl;
	}
	for(auto &i : tokenIndices)
		cout << i.second << " "<<i.first<<endl;
}

Parser::Parser(string inputProgram) : program(inputProgram), lexer(inputProgram)
{
    parseTree.open("../parseTree.txt");
	ifstream fin("../res/grammar.txt");
	int numberOfTokensInRule = 0;
	TransitionDiagram *currentDiagram = nullptr;
	DiagramPath *currentPath = nullptr;
	bool startOfRule = true;
	tokenIndices.clear();
	tokenIndices["error"] = ERROR_TOKEN_ID;
	tokenIndices["eps"] = EPSILON_TOKEN_ID;
	tokenIndices["num"] = NUM_TOKEN_ID;
	tokenIndices["id"] = ID_TOKEN_ID;
//	isNonTerminal[ERROR_TOKEN_ID] = false;
//	isNonTerminal[EPSILON_TOKEN_ID] = false;
//	isNonTerminal[NUM_TOKEN_ID] = false;
//	isNonTerminal[ID_TOKEN_ID] = false;
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
	currentToken = lexer.getNextToken();

}

void Parser::initFirstFollow()
{
	ifstream fin("../res/firstfollow.txt");
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
	return tokenIndices[s];
}

void Parser::parse(int dfa, int level, bool canParseEps)
{
//	Token token = lexer.getNextToken();
	int tokenId = currentToken.getType();
	for (auto &path : diagrams[dfa])
	{
        int firstToken = path[0];
		if ((!isNonTerminal(firstToken) && firstToken == tokenId)
				|| (firstToken == EPSILON_TOKEN_ID && canParseEps)
                || (isNonTerminal(firstToken) && isInFirst(tokenId, firstToken))
                || (isNonTerminal(firstToken) && isInFirst(EPSILON_TOKEN_ID, firstToken) && isInFollow(tokenId, firstToken)))
        {

            for (TokenId id : path)
            {
                if (!isNonTerminal(id))
				{
					if (id == tokenId)
					{
						printTree(tokenId, level);
						currentToken = lexer.getNextToken();
					}
					else if (id == EPSILON_TOKEN_ID && canParseEps)
						printTree(id, level);
				}
                else// TODO: error
                {
                    printTree(id, level);
                    parse(id, level + 1, isInFollow(tokenId, dfa));
                }
				tokenId = currentToken.getType();
			}
            return;
        }

	}
}

void Parser::printTree(TokenId id, int level)
{
    while (level--)
        Parser::parseTree << "|\t";
    Parser::parseTree << tokenNames[id] << endl;
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
	parseTree << "Program" <<endl;

	parse(getTokenId("Program"), 1, false);
}
