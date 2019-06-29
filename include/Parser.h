//
// Created by Kiarash on 19/05/2019.
//

#ifndef COMPILER_PROJECT_PARSER_H
#define COMPILER_PROJECT_PARSER_H

#include "Lexer.h"

extern Lexer *lexer;

class Parser
{
public:
	static TokenToIndicesMap tokenIndices;
	static IndicesToTokenMap tokenNames;

	Parser();
	void print();
	void parse();
	static int getTokenId(string s);

private:

	typedef vector<TokenId> DiagramPath;
	typedef vector<DiagramPath> TransitionDiagram;
	typedef unordered_map<TokenId, TransitionDiagram> DiagramList;
	typedef unordered_set<TokenId> NonTerminalSet;
	typedef unordered_set<TokenId> FirstFollowSet;
	typedef unordered_map<TokenId, FirstFollowSet> FirstFollowMap;

	int numberOfTokens = 4;
	FirstFollowMap first, follow;
	NonTerminalSet nonTerminal;
    ofstream parseTree;
	DiagramList diagrams;
	Token *currentToken;

	Token* getNextToken();
	void initFirstFollow();
	bool isInFirst(int token, int nonTerminal);
	bool isInFollow(int token, int nonTerminal);
	bool isNonTerminal(TokenId token);
	void parse(int dfa, int level, bool canParseEps);
    void printTree(TokenId id, int level, bool missed = false);
	void missingTerminal(TokenId terminalId);
	void unexpectedTerminal();
	void missingNonTerminal(TokenId nonTerminal);
	string unexpectedEndOfFile();
	string malformedInput();

};

#endif //COMPILER_PROJECT_PARSER_H

