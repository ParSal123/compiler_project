#include "Parser.h"


int main()
{
	string input;
	ifstream fin(PROGRAM_ADDRESS);
	stringstream buffer;
	buffer << fin.rdbuf();
	input = buffer.str();

	Parser parser(input);
//	parser.print();
	parser.parse();
	return 0;
}
