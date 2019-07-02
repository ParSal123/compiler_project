
#ifndef COMPILER_PROJECT_VARIABLE_H
#define COMPILER_PROJECT_VARIABLE_H

#include "Commons.h"
#include "Scope.h"

enum VariableType { NON_ARRAY, ARRAY };

class Variable
{
public:
    Variable(int address, VariableType type, Scope *container) : address(address), type(type),
        container(container)
    Scope* getContainer();
private:
    int address;
    VariableType type;
    Scope *container;
};

#endif

