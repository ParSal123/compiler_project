
#include "SemanticAnalyser.h"

int memoryAddressAllocator = MEMORY_START_ADDRESS;
stack<string> st;

bool variableDeclError(const string &name);

void push()
{
	st.push(currentToken->getValue());
}


void decl_var()
{
	string name = st.top();
	st.pop();
    if (!variableDeclError(name))
	{
		currentScope->addVariable(name);
	}
}

bool variableDeclError(const string &name) {
    bool flag = false;
    if (st.top() == "void") {
        errorFile << "Line #" << currentToken->getLine() << ": Illegal type of void.\n";
        flag = true;
    }
    st.pop();
    if (currentScope->getVariable(name) != nullptr) {
        errorFile << "Line #" << currentToken->getLine() << ": Variable " << name
                  << " is already defined in this scope.\n";
        flag = true;
    }
    return flag;
}

void decl_arr()
{
    // TODO: arrays and variables with same name
    int count = stoi(st.top());
    st.pop();
    string name = st.top();
    st.pop();
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


