//
// Created by Kiarash on 19/05/2019.
//

#ifndef COMPILER_PROJECT_PARSER_H
#define COMPILER_PROJECT_PARSER_H


#include "Lexer.h"

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
	typedef unordered_map <TokenId, TransitionDiagram> DiagramList;
	typedef unordered_map<string, TokenId> TokenToIndicesMap;
	typedef unordered_map<TokenId, string> IndicesToTokenMap;
	typedef unordered_set<TokenId> NonTerminalSet;
	typedef unordered_set<TokenId> FirstFollowSet;
	typedef unordered_map<TokenId, FirstFollowSet> FirstFollowMap;

	string program;
	int numberOfTokens = 4;
	FirstFollowMap first, follow;
	NonTerminalSet nonTerminal;
	static TokenToIndicesMap tokenIndices;
	static IndicesToTokenMap tokenNames;
    ofstream parseTree, errors;
	DiagramList diagrams;
	Lexer lexer;
	Token currentToken;

	void initFirstFollow();
	bool isInFirst(int token, int nonTerminal);
	bool isInFollow(int token, int nonTerminal);
	bool isNonTerminal(TokenId token);

	void parse(int dfa, int level, bool canParseEps);
    void printTree(TokenId id, int level);

	Token getNextToken();

	void lexingError(Token token);

	void missingTerminal(TokenId terminalId);

	void unexpectedTerminal();

	void missingNonTerminal(TokenId nonTerminal);

	string unexpectedEndOfFile();

	string malformedInput();
};


#endif //COMPILER_PROJECT_PARSER_H
