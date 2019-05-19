//
// Created by Kiarash on 19/05/2019.
//

#include "Parser.h"

void Parser::init()
{
	ifstream fin("./res/grammar.txt");
	string input;
	int numberOfTokensInRule = 0;
	TransitionDiagram *currentDiagram;
	DiagramPath *currentPath;
	bool startOfRule = true;
	tokenIndices.clear();
	tokenIndices["eps"] = EPSILON_TOKEN_ID;
	while (fin >> input)
	{
		if (startOfRule)
		{
			diagrams.push_back(TransitionDiagram());
			currentDiagram = &diagrams[diagrams.size() - 1];
			currentDiagram->push_back(DiagramPath());
			currentPath = &((*currentDiagram)[currentDiagram->size() - 1]);
			startOfRule = false;
			if (tokenIndices.find(input) == tokenIndices.end())
				tokenIndices[input] = numberOfTokens++;
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
	for(auto i : tokenIndices)
		cout<< i.second<<" "<<i.first<<endl;

}