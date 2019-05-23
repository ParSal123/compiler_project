//
// Created by Kiarash on 19/05/2019.
//

#include "Parser.h"

Parser::TokenToIndicesMap Parser::tokenIndices;

void Parser::print()
{
//	for(auto word: tokenIndices)
	for (auto &i : diagrams)
	{
		cout << i.first << endl;
		for (auto &path: i.second)
		{
			for (int j : path)
				cout << j << " ";
			cout << endl;
		}
		cout<<"______________\n"<<endl;
	}
	for (auto i : tokenIndices)
	{
		cout << i.second << " " << i.first << endl;
		/*for (auto j : first[i.second])
			cout << j <<" ";
		cout <<endl;
		for (auto j : follow[i.second])
			cout << j <<" ";
		cout <<endl;*/
	}
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
	isNonTerminal[ERROR_TOKEN_ID] = false;
	isNonTerminal[EPSILON_TOKEN_ID] = false;
	isNonTerminal[NUM_TOKEN_ID] = false;
	isNonTerminal[ID_TOKEN_ID] = false;
	string input;
	while (fin >> input)
	{

		if (startOfRule)
		{
			if (tokenIndices.find(input) == tokenIndices.end())
				tokenIndices[input] = numberOfTokens++;
			int id = tokenIndices[input];
			if (isupper(input[0]))
				isNonTerminal[id] = true;
			else isNonTerminal[id] = false;
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
					isNonTerminal[id] = true;
				else isNonTerminal[id] = false;
				currentPath->push_back(id);
				numberOfTokensInRule++;
			}
		}
	}
	initFirstFollow();
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

void Parser::parse(int dfa, int level)
{
	Token token = lexer.getNextToken();
	int tokenId = token.getType();
	for (auto &path : diagrams[dfa])
	{
        int cur_token = path[0];
        if ((!isNonTerminal[cur_token] && cur_token == tokenId)
                || (isNonTerminal[cur_token] && isInFirst(tokenId, cur_token))
                || (isNonTerminal[cur_token] && isInFirst(EPSILON_TOKEN_ID, cur_token) && isInFollow(tokenId, cur_token)))
        {
            for (TokenId id : path)
            {
                if (tokenId == id)
                {
                    printTree(tokenId, level);
                }
                else if (isNonTerminal[id]) // TODO: error
                {
                    printTree(tokenId, level);
                    parse(tokenId, level + 1);
                }
                token = lexer.getNextToken();
                tokenId = token.getType();
            }
            return;
        }

	}
}

void Parser::printTree(TokenId id, int level)
{
    while (level--)
        Parser::parseTree << "|\t";
    Parser::parseTree << id << endl;
}

bool Parser::isInFirst(int token, int nonTerminal)
{
	return first[nonTerminal].find(token) == first[nonTerminal].end();
}

bool Parser::isInFollow(int token, int nonTerminal)
{
	return follow[nonTerminal].find(token) == follow[nonTerminal].end();
}


ParseState::ParseState(int token, int dfaId, int index) : token(token), dfaId(dfaId), index(index)
{}
