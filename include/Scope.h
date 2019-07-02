
#ifndef COMPILER_PROJECT_SCOPE_H
#define COMPILER_PROJECT_SCOPE_H

#include "Commons.h"
#include "Variable.h"
#include "SemanticAnalyser.h"

class Variable;
enum VariableType : int;

enum ScopeType { NORMAL, IF, ELSE, WHILE, SWITCH, CASE, FUNCTION };

class Scope
{
public:
	Scope(int startAddress, bool hasReturnValue, ScopeType type, Scope *container);

	void addParams(VariableType param);
    Variable* getVariable(string name);


	int getStartAddress() const;

	bool isHasReturnValue() const;

	Scope *getContainer() const;

	void addVariable(string name);
	void addArray(string name, int size);

private:
    int startAddress, returnAddress;
    bool hasReturnValue; // there's only one type of return value and that's int
    vector<VariableType> params;
    unordered_map<string, Scope*> functions;
    unordered_map<string, Variable*> variables;
    ScopeType type;
    Scope *container;
};

#endif

