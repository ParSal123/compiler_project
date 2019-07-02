
#ifndef COMPILER_PROJECT_SEMANTIC_ANALYSER_H
#define COMPILER_PROJECT_SEMANTIC_ANALYSER_H

#include "Commons.h"
#include "Token.h"
#include "Scope.h"

constexpr int SIZEOF_VARIABLES = 4;
constexpr int MEMORY_START_ADDRESS = 1;
constexpr int RETURN_ADDRESS = 0;
constexpr int STACK_START_ADDRESS = 10000;
const string ASSIGN_COMMAND = "ASSIGN";
const string ADD_COMMAND = "ADD";
const string SUB_COMMAND = "SUB";
const string EQUAL_COMMAND = "EQ";
const string JP_FALSE_COMMAND = "JPF";
const string JP_COMMAND = "JP";
const string LESS_THAN_COMMAND = "LT";
const string MULT_COMMAND = "MULT";
const string NOT_COMMAND = "NOT";
const string PRINT_COMMAND = "PRINT";

class Scope;

extern int memoryAddressAllocator;
extern int programIndex;
extern vector<string> pb;
extern Token *currentToken;
extern Scope *currentScope;
extern stack<string> st;
extern bool skipDirectives;
extern bool skipNormalScope;

void printProgramBlock();
void addCode(const string& command, const string& arg1, const string& arg2, const string& arg3, int place = programIndex++);
string poll();
string convertToCommandFormat(string s);
bool variableDeclError(const string& name);
void end_skip_directives();
void push();
void decl_var();
void end_scope();
void decl_arr();
void decl_func();
void add_param();
void decl_normal_scope();
void decl_if_scope();
void decl_else_scope();
void label();
void decl_while_scope();
void return_type_check();
void return_assignment();
void decl_switch_scope();
void continue_();
void break_();
void pop();
void func_call();
void assign();
void resolve_array_index();
void relop();
void add();
void sub();
void mult();
void negate_();
void save();
void jpf_if();
void jp_if();


#endif

