#include "Lexer.h"
#include "Parser.h"
using namespace std;
string getString(TokenType t)
{
	string ar[] = {"Number", "Id", "Keyword", "Symbol", "Invalid input", "EOF", "Whitespace"};
	return ar[t];
}
int main()
{
	/*string input;
	ifstream fin("./res/input.txt");
	ofstream fout("scanner.txt");
	ofstream err("lexical_errors.txt");
	stringstream buffer;
	buffer << fin.rdbuf();
	input = buffer.str();
	Lexer lexer = Lexer(input);
	int line = 1;
	fout << "1. ";
	for (Token token(Keyword, ""); (token = lexer.getNextToken()).getType() != 6;)
	{
		if(lexer.line > line+1)
		{
			line = lexer.line;
			fout <<endl << (line+1)/2 << ". ";
		}
		if (token.getType() <= 3 || token.getType() == 5)
		{
			if (token.getType() == 5)
				err << (line + 1)/2 << ". (" << token.getValue() << ", Invalid input)" << endl;
			else fout << "(" <<token.getLine()<< getString(token.getType()) << ", " << token.getValue() << ") " ;
		}

	}
	fout<<endl;*/
	Parser parser;
	parser.init();
	parser.print();
	return 0;
}