//
// Created by Kiarash on 19/05/2019.
//

#ifndef COMPILER_PROJECT_PARSER_H
#define COMPILER_PROJECT_PARSER_H


#include "Token.h"

class Parser {
public:


	Parser(string inputProgram);

	void print();
	static int getTokenId(string s);
private:
	string program;
	int numberOfTokens = 4;

	typedef int TokenId;
	typedef vector <TokenId> DiagramPath;
	typedef vector <DiagramPath> TransitionDiagram;
	typedef unordered_map <int, TransitionDiagram> DiagramList;
	typedef unordered_map<string, int> TokenToIndicesMap;
	static TokenToIndicesMap tokenIndices;
	DiagramList diagrams;

};


#endif //COMPILER_PROJECT_PARSER_H
