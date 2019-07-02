//
// Created by Kiarash on 19/05/2019.
//

#ifndef COMPILER_PROJECT_PARSER_H
#define COMPILER_PROJECT_PARSER_H

#include "Lexer.h"

extern Lexer *lexer;
Token *currentToken;
Scope *currentScope;

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
	typedef unordered_set<TokenId> NonTerminalSet, DirectiveSet;
	typedef unordered_set<TokenId> FirstFollowSet;
	typedef unordered_map<TokenId, FirstFollowSet> FirstFollowMap;
	typedef unordered_map<TokenId, void(*)()> TokenToFunctionMap;

	int numberOfTokens = 4;
	FirstFollowMap first, follow;
	NonTerminalSet nonTerminal;
	DirectiveSet directiveSet;
	TokenToFunctionMap directiveFunctions;
    ofstream parseTree;
	DiagramList diagrams;

    ~Parser();
	Token* getNextToken();
	void initFirstFollow();
	bool isInFirst(int token, int nonTerminal);
	bool isInFollow(int token, int nonTerminal);
	bool isNonTerminal(TokenId token);
	void parse(int dfa, int level, bool canParseEps);
    void printTree(TokenId id, int level, bool missed = false);
    void printError(string msg);
	string missingTerminal(TokenId terminalId);
	string unexpectedTerminal();
	string missingNonTerminal(TokenId nonTerminal);
	string unexpectedEndOfFile();
	string malformedInput();

	bool isDirective(TokenId token) const;

	void initDirectiveFunctions();
};

#endif //COMPILER_PROJECT_PARSER_H

