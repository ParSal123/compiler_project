
#include "SemanticAnalyser.h"

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

