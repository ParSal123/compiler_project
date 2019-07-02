
#ifndef COMPILER_PROJECT_SCOPE_H
#define COMPILER_PROJECT_SCOPE_H

#include "Commons.h"

enum ScopeType { NORMAL, IF, ELSE, WHILE, SWITCH, CASE, FUNCTION };

class Scope
{
public:
    Scope(int startAddress, bool hasReturnValue, ScopeType type, Scope *container):
        startAddress(startAddress), hasReturnValue(hasReturnValue),
        container(container), type(type)
    {}
    int getStartAddress();
    int getReturnAddress();
    void setReturnAddress(int returnAddress);
    bool hasReturnValue();
    Scope* getContainer();
    void addParams(VariableType param);
    Variable* getVariable(string name);
    void addVariable(string name);

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

