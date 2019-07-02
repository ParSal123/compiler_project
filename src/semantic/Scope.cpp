
#include "Scope.h"

Variable *Scope::getVariable(const string &name)
{
	auto iter = variables.find(name);
	if (iter != variables.end())
	{
		return iter->second;
	}
	return nullptr;
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
	params.push_back(param);
}

void Scope::addVariable(const string &name)
{
	Variable *var = new Variable(memoryAddressAllocator * SIZEOF_VARIABLES, currentToken->getLine(), NON_ARRAY,
	                             currentScope);
	memoryAddressAllocator++;
	variables[name] = var;
}

void Scope::addArray(const string &name, int size)
{
	Variable *var = new Variable(memoryAddressAllocator * SIZEOF_VARIABLES, currentToken->getLine(), ARRAY,
	                             currentScope);
	memoryAddressAllocator += size;
	variables[name] = var;
}

Scope::Scope(int definitionLine, int startAddress, int memoryStartAddress, bool hasReturnValue, ScopeType type,
             Scope *container)
		: definitionLine(definitionLine), startAddress(startAddress), memoryStartAddress(memoryStartAddress),
		  hasReturnValue(hasReturnValue),
		  type(type), container(container)
{}

Scope *Scope::getFunction(const string &name)
{
	auto iter = functions.find(name);
	if (iter == functions.end())
	{
		return nullptr;
	}
	return iter->second;
}

int Scope::getDefinitionLine() const
{
	return definitionLine;
}

Scope *Scope::addFunction(const string &name, bool hasReturnValue)
{
	Scope *func = new Scope(currentToken->getLine(), programIndex, memoryAddressAllocator, hasReturnValue, FUNCTION,
	                        currentScope);
	functions[name] = func;
	return func;
}

void Scope::setReturnAddress(int returnAddress)
{
	Scope::returnAddress = returnAddress;
}

int Scope::addTemp()
{
	return SIZEOF_VARIABLES * memoryAddressAllocator++;
}

Variable *Scope::findVariable(const string &name)
{
	Scope *current = this;
	while (current != nullptr)
	{
		auto iter = current->variables.find(name);
		if (iter != current->variables.end())
		{
			return iter->second;
		}
		current = current->container;
	}
	return nullptr;
}

