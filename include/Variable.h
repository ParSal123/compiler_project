
#ifndef COMPILER_PROJECT_VARIABLE_H
#define COMPILER_PROJECT_VARIABLE_H

#include "Commons.h"
#include "Scope.h"

enum VariableType { NON_ARRAY, ARRAY };

class Variable
{
public:
    Scope* getContainer();
private:
    int address;
    VariableType type;
    Scope *container;
};

#endif

