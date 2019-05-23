//
// Created by Kiarash on 19/05/2019.
//

#ifndef COMPILER_PROJECT_PARSER_H
#define COMPILER_PROJECT_PARSER_H


#include "Lexer.h"

struct ParseState
{
	int token, dfaId, index;

	ParseState(int token, int dfaId, int index);
};
class Parser {
public:


	Parser(string inputProgram);

	void print();
	void parse();
	static int getTokenId(string s);
private:
	typedef int TokenId;
	typedef vector <TokenId> DiagramPath;
	typedef vector <DiagramPath> TransitionDiagram;
	typedef unordered_map <int, TransitionDiagram> DiagramList;
	typedef unordered_map<string, int> TokenToIndicesMap;
	typedef unordered_map<int, bool> TokenIdToBoolMap;
	typedef unordered_set<int> FirstFollowSet;
	typedef unordered_map<int, FirstFollowSet> FirstFollowMap;
	typedef stack<ParseState> TokenStack;

	string program;
	int numberOfTokens = 4;
	FirstFollowMap first, follow;
	TokenIdToBoolMap isNonTerminal;
	static TokenToIndicesMap tokenIndices;
    ofstream parseTree;
	DiagramList diagrams;
	Lexer lexer;

	void initFirstFollow();
	bool isInFirst(int token, int nonTerminal);
	bool isInFollow(int token, int nonTerminal);

	void parse(int dfa, int level);
    void printTree(TokenId id, int level);
};


#endif //COMPILER_PROJECT_PARSER_H
