#include "Parser.h"
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
