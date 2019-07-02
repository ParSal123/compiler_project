
#include "SemanticAnalyser.h"

int memoryAddressAllocator = MEMORY_START_ADDRESS;
stack<string> st;

void push()
{
	st.push(currentToken->getValue());
}

void decl_var()
{
	bool flag = true;
	string name = st.top();
	st.pop();
	if (st.top() == "void")
	{
		errorFile << "Line #" << currentToken->getLine() << ": Illegal type of void.\n";
		flag = false;
	}
	if (currentScope->getVariable(name) != nullptr)
	{
		errorFile << "Line #" << currentToken->getLine() << ": Variable " << name
				  << " is already defined in this scope.\n";
		flag = false;
	}
	if (flag)
	{
		currentScope->addVariable(name);
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

void end_while_scope()
{

}

void decl_while_scope()
{

}

void label()
{

}

void end_else_scope()
{

}

void decl_else_scope()
{

}

void decl_if_scope()
{

}

void decl_normal_scope()
{

}

void add_param_arr()
{

}

void add_param_int()
{

}

void error_void_param()
{
	errorFile << "Line #" << currentToken->getLine() << ": Illegal type of void.\n";
}

void decl_func()
{

}

void decl_arr()
{

}

