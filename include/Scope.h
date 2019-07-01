
#ifndef COMPILER_PROJECT_SCOPE_H
#define COMPILER_PROJECT_SCOPE_H

#include "Commons.h"

enum ScopeType { NORMAL, IF, ELSE, WHILE, SWITCH, CASE, FUNCTION };

class Scope
{
public:
    Scope(int startAddress, int returnAddress, bool hasReturnValue, ScopeType type, Scope *container):
        startAddress(startAddress), returnAddress(returnAddress), hasReturnValue(hasReturnValue),
        container(container), type(type)
    {}
    int getStartAddress();
    int getReturnAddress();
    bool hasReturnValue();
    Scope* getContainer();
    void addArguments(VariableType argument);

private:
    int startAddress, returnAddress;
    bool hasReturnValue; // there's only one type of return value and that's int
    vector<VariableType> arguments;
    unordered_map<string, Scope*> functions;
    unordered_map<string, Variable*> variables;
    ScopeType type;
    Scope *container;
};

#endif

