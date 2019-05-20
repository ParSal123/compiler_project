//
// Created by Kiarash on 19/05/2019.
//

#include "Parser.h"

Parser::TokenToIndicesMap Parser::tokenIndices;

void Parser::print()
{
	/*for (int i = 0; i < diagrams.size(); i++)
	{
		TransitionDiagram &dfa = diagrams[i];
		cout <<i <<endl;
		for(auto path: dfa)
		{
			for(int j : path)
				cout << j << " ";
			cout<<endl;
		}
		cout<<"______________\n"<<endl;
	}*/
	for (auto i : tokenIndices)
		cout << i.second << " " << i.first << endl;

}

Parser::Parser(string inputProgram) : program(inputProgram), lexer(inputProgram)
{
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

void Parser::parse()
{
	TokenId currentState = tokenIndices["Program"];
	Token token = lexer.getNextToken();
	TokenStack tokenStack;
	tokenStack.push(currentState);
	while (!lexer.isLexingEnded() && !tokenStack.empty())
	{
		//TODO: to be implemented by Parsa
	}
}
