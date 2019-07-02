
#include "SemanticAnalyser.h"

int memoryAddressAllocator = MEMORY_START_ADDRESS;
int programIndex = 0;
vector<string> pb;
stack<string> st;
bool skipDirectives = false;
bool skipNormalScope = false;

void push()
{
	st.push(currentToken->getValue());
}

void addCode(string command, string arg1, string arg2, string arg3, int place = programIndex)
{
	if (pb.capacity() <= place)
	{
		pb.resize(place);
	}
	pb[place] = to_string(place + 1) + "\t(" + command + ", " + arg1 + ", " + arg2 + ", " + arg3 + ")";
}

void decl_var()
{
	string name = getNameOfId();
	if (!variableDeclError(name))
	{
		currentScope->addVariable(name);
	}
}

bool variableDeclError(const string &name)
{
	bool flag = false;
	if (st.top() == "void")
	{
		errorFile << "Line #" << currentToken->getLine() << ": Illegal type of void.\n";
		flag = true;
	}
	st.pop();
	if (currentScope->getVariable(name) != nullptr)
	{
		errorFile << "Line #" << currentToken->getLine() << ": Variable \"" << name
		          << "\" is already defined in this scope at Line #"
		          << currentScope->getVariable(name)->getDefinitionLine() << ".\n";
		flag = true;
	}
	return flag;
}

void decl_arr()
{
	// TODO: arrays and variables with same name
	int count = stoi(st.top());
	st.pop();
	string name = getNameOfId();
	if (!variableDeclError(name))
	{
		currentScope->addArray(name, count);
	}
}

void negate_()
{

}

void mult()
{

}

void sub()
{

}

void add()
{

}

void relop()
{

}

void resolve_array_index()
{

}

void assign()
{

}

void func_call()
{

}

void pop()
{
	st.pop();
}

void break_()
{

}

void continue_()
{

}

void decl_switch_scope()
{

}

void return_assignment()
{

}

void return_type_check()
{

}

void decl_while_scope()
{

}

void label()
{
	st.push(to_string(programIndex));
}

void decl_else_scope()
{
	currentScope = new Scope(currentToken->getLine(), programIndex, memoryAddressAllocator, false, ELSE, currentScope);
	if (currentToken->getValue() == "{")
	{
        skipNormalScope = true;
	}
}

void decl_if_scope()
{
	currentScope = new Scope(currentToken->getLine(), programIndex, memoryAddressAllocator, false, IF, currentScope);
	if (currentToken->getValue() == "{")
	{
        skipNormalScope = true;
	}
}

void decl_normal_scope()
{
	if (!skipNormalScope)
	{
		currentScope = new Scope(currentToken->getLine(), programIndex, memoryAddressAllocator, false, NORMAL,
		                         currentScope);
	}
}

string getNameOfId()
{
	string ret = st.top();
	st.pop();
	return ret;
}

void add_param()
{
	string name = getNameOfId();
	if (!variableDeclError(name))
	{
		currentScope->addVariable(name);
		currentScope->addParams((currentToken->getValue() == "[") ? ARRAY : NON_ARRAY);
	}

}

void decl_func()
{
	// todo: function overloading
	string name = getNameOfId();
	if (currentScope->getFunction(name) != nullptr)
	{
		errorFile << "Line #" << currentToken->getLine() << ": Function name \"" << name
		          << "\" already exists in Line #"
		          << currentScope->getFunction(name)->getDefinitionLine() << endl;
		skipDirectives = true;
		st.pop();
		return;
	}
	bool hasReturnValue = st.top() == "int";
	st.pop();
	currentScope = currentScope->addFunction(name, hasReturnValue);

}

void end_skip_directives()
{
	skipDirectives = false;
}

void end_scope()
{
	currentScope->setReturnAddress(programIndex);
	currentScope = currentScope->getContainer();
}

void save()
{
	st.push(to_string(programIndex));
	programIndex++;
}

void jp_if()
{
	addCode(JP_COMMAND, to_string(programIndex), "", "", stoi(st.top()));
	st.pop();
}

void jpf_if()
{
	int line = stoi(st.top());
	st.pop();
	addCode(JP_FALSE_COMMAND, st.top(), to_string(programIndex + 1), "", line);
	st.pop();
}


