
#include "Variable.h"

Scope *Variable::getContainer() const
{
	return container;
}

Variable::Variable(int address, int definitionLine, VariableType type, Scope *container) : address(address),
                                                                                           definitionLine(
		                                                                                           definitionLine),
                                                                                           type(type),
                                                                                           container(container)
{}

int Variable::getDefinitionLine() const
{
	return definitionLine;
}

int Variable::getAddress() const
{
	return address;
}

