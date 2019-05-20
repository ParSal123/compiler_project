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

Parser::Parser(string inputProgram) : program(inputProgram)
{
	ifstream fin("../res/grammar.txt");
	string input;
	int numberOfTokensInRule = 0;
	TransitionDiagram *currentDiagram;
	DiagramPath *currentPath;
	bool startOfRule = true;
	tokenIndices.clear();
	tokenIndices["error"] = ERROR_TOKEN_ID;
	tokenIndices["eps"] = EPSILON_TOKEN_ID;
	tokenIndices["num"] = NUM_TOKEN_ID;
	tokenIndices["id"] = ID_TOKEN_ID;

	while (fin >> input)
	{
		if (startOfRule)
		{
			if (tokenIndices.find(input) == tokenIndices.end())
				tokenIndices[input] = numberOfTokens++;
			int id = tokenIndices[input];
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
				currentPath->push_back(tokenIndices[input]);
			}
		}

	}
}

int Parser::getTokenId(string s)
{
	return tokenIndices[s];
}
