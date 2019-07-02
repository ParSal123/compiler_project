
#include "Variable.h"

Variable::Variable(int address, VariableType type, Scope *container) : address(address), type(type),
																	   container(container)
{}

Scope *Variable::getContainer() const
{
	return container;
}

