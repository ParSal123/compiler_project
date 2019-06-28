//
// Created by Kiarash on 12/04/2019.
//

#ifndef COMPILER_PROJECT_COMMONS_H
#define COMPILER_PROJECT_COMMONS_H

#include <bits/stdc++.h>

using namespace std;

const string PROGRAM_ADDRESS = "../in/input.txt";
const string ERRORS_ADDRESS = "../out/errors.txt";
const string PARSE_TREE_ADDRESS = "../out/parseTree.txt";
const string GRAMMAR_ADDRESS = "../res/grammar.txt";
const string FIRST_FOLLOW_ADDRESS = "../res/firstfollow.txt";


constexpr int ERROR_TOKEN_ID = 0;
constexpr int EPSILON_TOKEN_ID = 1;
constexpr int NUM_TOKEN_ID = 2;
constexpr int ID_TOKEN_ID = 3;

#endif //COMPILER_PROJECT_COMMONS_H
