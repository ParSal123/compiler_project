
#ifndef COMPILER_PROJECT_SCOPE_H
#define COMPILER_PROJECT_SCOPE_H

#include "Commons.h"
#include "Variable.h"
#include "SemanticAnalyser.h"

class Variable;

enum VariableType : int;

enum ScopeType
{
	NORMAL, IF, ELSE, WHILE, SWITCH, CASE, FUNCTION
};

class Scope
{
public:
	Scope(int definitionLine, int startAddress, int memoryStartAddress, bool hasReturnValue, ScopeType type,
	      Scope *container);

	void addParams(VariableType param);

	Variable *getVariable(const string &name);

	Variable *findVariable(const string &name);

	int getStartAddress() const;

	int getDefinitionLine() const;

	int addTemp();

	bool isHasReturnValue() const;

	Scope *getContainer() const;

	void addVariable(const string &name);

	void addArray(const string &name, int size);

	Scope *getFunction(const string &name);


	Scope *addFunction(const string &name, bool hasReturnValue);

	void setReturnAddress(int returnAddress);

	ScopeType getType() const;

	Scope *getBreak();

	int getReturnAddress() const;

	Scope *getContinue();

private:
public:
	const vector<VariableType> &getParams() const;

private:
	int definitionLine;
	int startAddress, returnAddress, memoryStartAddress;
	bool hasReturnValue; // there's only one type of return value and that's int
	vector<VariableType> params;
	unordered_map<string, Scope *> functions;
	unordered_map<string, Variable *> variables;
	ScopeType type;
	Scope *container;


};

#endif

