
#ifndef COMPILER_PROJECT_SEMANTIC_ANALYSER_H
#define COMPILER_PROJECT_SEMANTIC_ANALYSER_H

#include "Commons.h"
#include "Token.h"
#include "Scope.h"

constexpr int SIZEOF_VARIABLES = 4;
constexpr int MEMORY_START_ADDRESS = 1;
constexpr int RETURN_ADDRESS = 0;
constexpr int STACK_START_ADDRESS = 10000;
constexpr string ASSIGN_COMMAND = "ASSIGN";
constexpr string ADD_COMMAND = "ADD";
constexpr string SUB_COMMAND = "SUB";
constexpr string EQUAL_COMMAND = "EQ";
constexpr string JP_FALSE_COMMAND = "JPF";
constexpr string JP_COMMAND = "JP";
constexpr string LESS_THAN_COMMAND = "LT";
constexpr string MULT_COMMAND = "MULT";
constexpr string NOT_COMMAND = "NOT";
constexpr string PRINT_COMMAND = "PRINT";

class Scope;

extern int memoryAddressAllocator;
extern int programIndex;
extern vector<string> pb;
extern Token *currentToken;
extern Scope *currentScope;
extern stack<string> st;
extern bool skipDirectives;
extern bool skipNormalScope;

void addCode(string command, string arg1, string arg2, string arg3, int place = programIndex);
string getNameOfId();
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

