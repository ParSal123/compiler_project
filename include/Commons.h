//
// Created by Kiarash on 12/04/2019.
//

#ifndef COMPILER_PROJECT_COMMONS_H
#define COMPILER_PROJECT_COMMONS_H

#include <bits/stdc++.h>

using namespace std;

typedef int TokenId;
typedef unordered_map<string, TokenId> TokenToIndicesMap;
typedef unordered_map<TokenId, string> IndicesToTokenMap;

const string LEXER_OUT_ADDRESS = "../out/lexer_output.txt";
const string PROGRAM_ADDRESS = "../in/input2.txt";
const string ERRORS_ADDRESS = "../out/errors.txt";
const string PARSE_TREE_ADDRESS = "../out/parseTree.txt";
const string GRAMMAR_ADDRESS = "../res/grammar.txt";
const string FIRST_FOLLOW_ADDRESS = "../res/firstfollow.txt";

constexpr int ERROR_TOKEN_ID = 0;
constexpr int EPSILON_TOKEN_ID = 1;
constexpr int NUM_TOKEN_ID = 2;
constexpr int ID_TOKEN_ID = 3;

extern ofstream errorFile;

#endif //COMPILER_PROJECT_COMMONS_H

