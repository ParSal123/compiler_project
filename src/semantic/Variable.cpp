
#include "Variable.h"

Variable::Variable(int address, VariableType type, Scope *container) : address(address), type(type),
																	   container(container)l
{}

Scope *Variable::getContainer() const
{
	return container;
}

