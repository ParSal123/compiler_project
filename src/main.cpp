#include "Parser.h"
/*string getString(TokenType t)
{
	string ar[] = {"Number", "Id", "Keyword", "Symbol", "Invalid input", "EOF", "Whitespace"};
	return ar[t];
}*/
int main()
{
	string input;
	ifstream fin("../res/input.txt");
	stringstream buffer;
	buffer << fin.rdbuf();
	input = buffer.str();

	Parser parser(input);
//	parser.print();
	parser.parse();
	return 0;
}
