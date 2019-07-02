
#ifndef COMPILER_PROJECT_SEMANTIC_ANALYSER_H
#define COMPILER_PROJECT_SEMANTIC_ANALYSER_H

#include "Commons.h"
#include "Token.h"
#include "Scope.h"

constexpr int SIZEOF_VARIABLES = 4;
constexpr int MEMORY_START_ADDRESS = 1;
constexpr int RETURN_ADDRESS = 0;
constexpr int STACK_START_ADDRESS = 10000;


int memoryAddressAllocator = MEMORY_START_ADDRESS;
extern Token *currentToken;
extern Scope *currentScope;
stack<string> st;

void push();
void decl_var();
void decl_arr();
void decl_func();
void error_void_param();
void add_param_int();
void add_param_arr();
void decl_normal_scope();
void decl_if_scope();
void decl_else_scope();
void end_else_scope();
void label();
void decl_while_scope();
void end_while_scope();
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

#endif

