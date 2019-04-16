#include <bits/stdc++.h>
#include "Lexer.h"

using namespace std;
string getString(TokenType t)
{
	string ar[] = {"Number", "Id", "Keyword", "Symbol", "Invalid input", "EOF", "Whitespace"};
	return ar[t];
}
int main()
{
	string input;
	ifstream fin("C:\\Users\\Kiarash\\Desktop\\Uni\\97-98-2\\Compiler\\compiler_project\\res\\input.txt");
	ofstream fout("scanner.txt");
	ofstream err("lexical_errors.txt");
	stringstream buffer;
	buffer << fin.rdbuf();
	input = buffer.str();
	Lexer lexer = Lexer(input);
	int line = 1;
	fout << "1. ";
	for (Token token(Keyword, ""); (token = lexer.getNextToken()).type != 6;)
	{
		if(lexer.line > line+1)
		{
			line = lexer.line;
			fout <<endl << (line+1)/2 << ". ";
		}
		if (token.type <= 3 || token.type == 5)
		{
			if (token.type == 5)
				err << (line + 1)/2 << ". (" << token.value << ", Invalid input)" << endl;
			else fout << "(" << getString(token.type) << ", " << token.value << ") " ;
		}

	}
	fout<<endl;
	return 0;
}