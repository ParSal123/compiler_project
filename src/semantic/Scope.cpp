
#include "Scope.h"

Variable* Scope::getVariable(string name)
{
    auto iter = variables.find(name);
    if (iter == variables.end())
        return nullptr;
    return iter->second;
}

void Scope::addVariable(string name)
{
    Variable* var = new Variable(

