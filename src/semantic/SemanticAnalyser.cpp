
#include "SemanticAnalyser.h"

int memoryAddressAllocator = MEMORY_START_ADDRESS;
int programIndex = 0;
vector<string> pb;
stack<string> st;
bool skipDirectives = false;
bool skipNormalScope = false;

void push()
{
	string token = currentToken->getValue();
	if (currentToken->getType() == NUM_TOKEN_ID)
	{
		token = "#" + token;
	}
	st.push(token);
}

void addCode(const string& command, const string& arg1, const string& arg2, const string& arg3, int place)
{
	if (pb.size() <= place)
	{
		pb.resize(place + 1);
	}
	pb[place] = to_string(place + 1) + "\t(" + command + ", " + arg1 + ", " + arg2 + ", " + arg3 + ")";
}

void decl_var()
{
	string name = poll();
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
	int count = stoi(st.top().substr(1));
	st.pop();
	string name = poll();
	if (!variableDeclError(name))
	{
		currentScope->addArray(name, count);
	}
}

void negate_()
{
	string top = poll();
	top = convertToCommandFormat(top);
	if (top[0] == '#')
	{
        top = "#" + to_string(-stoi(top.substr(1)));
        st.push(top);
	}
	else
	{
		string dest = to_string(currentScope->addTemp());
		addCode(MULT_COMMAND, "#-1", top, dest);
		st.push(dest);
	}
}

void mult()
{
	string s1 = convertToCommandFormat(poll());
	string s2 = convertToCommandFormat(poll());
	string dest = to_string(currentScope->addTemp());
	addCode(MULT_COMMAND, s1, s2, dest);
	st.push(dest);
}

void sub()
{
	string s1 = convertToCommandFormat(poll());
	string s2 = convertToCommandFormat(poll());
	string dest = to_string(currentScope->addTemp());
	addCode(SUB_COMMAND, s2, s1, dest);
	st.push(dest);
}

void add()
{
	string s1 = convertToCommandFormat(poll());
	string s2 = convertToCommandFormat(poll());
	string dest = to_string(currentScope->addTemp());
	addCode(ADD_COMMAND, s2, s1, dest);
	st.push(dest);
}

void relop()
{

}

void resolve_array_index()
{

}

void assign()
{
	string source = convertToCommandFormat(poll());
    addCode(ASSIGN_COMMAND, source, convertToCommandFormat(st.top()), "");
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

string poll()
{
	string ret = st.top();
	st.pop();
	return ret;
}

void add_param()
{
	string name = poll();
	if (!variableDeclError(name))
	{
		currentScope->addVariable(name);
		currentScope->addParams((currentToken->getValue() == "[") ? ARRAY : NON_ARRAY);
	}

}

void decl_func()
{
	// todo: function overloading
	string name = poll();
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
	addCode(JP_COMMAND, to_string(programIndex + 1), "", "", stoi(st.top()));
	st.pop();
}

void jpf_if()
{
	int line = stoi(st.top());
	st.pop();
	addCode(JP_FALSE_COMMAND, st.top(), to_string(programIndex + 2), "", line);
	st.pop();
}

void printProgramBlock()
{
	ofstream outputProgram(OUTPUT_ADRESS);
	for (auto &code : pb)
	{
		outputProgram << code << endl;
	}
	outputProgram.close();
}

string convertToCommandFormat(string s)
{
	if (isalpha(s[0]))
	{
		Variable *var = currentScope->findVariable(s);
		if (var == nullptr)
		{
			errorFile << "Line #" << currentToken->getLine() << ": \"" << s << "\" is not defined.\n";
			exit(0);
		}
		else
		{
			return to_string(var->getAddress());
		}
	}
	return s;
}


