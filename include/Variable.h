
#ifndef COMPILER_PROJECT_VARIABLE_H
#define COMPILER_PROJECT_VARIABLE_H

#include "Commons.h"
#include "Scope.h"


enum VariableType : int {
    NON_ARRAY, ARRAY
};

class Scope;

class Variable {
public:
    Variable(int address, VariableType type, Scope *container);
    Scope *getContainer() const;

private:
    int address;
    VariableType type;
    Scope *container;

};

#endif

