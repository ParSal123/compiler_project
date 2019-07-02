
#include "Scope.h"

Variable *Scope::getVariable(string name)
{
    auto iter = variables.find(name);
    if (iter == variables.end())
        return nullptr;
    return iter->second;
}

int Scope::getStartAddress() const
{
    return startAddress;
}

bool Scope::isHasReturnValue() const
{
    return hasReturnValue;
}

Scope *Scope::getContainer() const
{
    return container;
}

void Scope::addParams(VariableType param)
{

}

void Scope::addVariable(string name)
{
    Variable *var = new Variable(memoryAddressAllocator * SIZEOF_VARIABLES, NON_ARRAY, currentScope);
    memoryAddressAllocator++;
    variables[name] = var;
}

Scope::Scope(int startAddress, bool hasReturnValue, ScopeType type, Scope *container) : startAddress(startAddress),
                                                                                        hasReturnValue(hasReturnValue),
                                                                                        type(type), container(container)
{}

void Scope::addArray(string name, int size)
{
    Variable *var = new Variable(memoryAddressAllocator * SIZEOF_VARIABLES, ARRAY, currentScope);
    memoryAddressAllocator += size;
    variables[name] = var;
}

