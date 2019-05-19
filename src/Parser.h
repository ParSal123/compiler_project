//
// Created by Kiarash on 19/05/2019.
//

#ifndef COMPILER_PROJECT_PARSER_H
#define COMPILER_PROJECT_PARSER_H


#include "Token.h"

class Parser {
public:
	void init();
	void print();
private:
	int numberOfTokens = 2;
	const int EPSILON_TOKEN_ID = 1;
	typedef int TokenId;
	typedef vector <TokenId> DiagramPath;
	typedef vector <DiagramPath> TransitionDiagram;
	typedef vector <TransitionDiagram> DiagramList;
	typedef vector<string> tokenNames;
	typedef unordered_map<string, int> TokenToIndicesMap;
	TokenToIndicesMap tokenIndices;
	DiagramList diagrams;
};


#endif //COMPILER_PROJECT_PARSER_H
