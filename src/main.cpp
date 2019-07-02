
#include "Parser.h"

Lexer *lexer = new Lexer(PROGRAM_ADDRESS);
Parser *parser = new Parser();
ofstream errorFile(ERRORS_ADDRESS);

int main()
{
	// todo: forward definition
	//parser->print();
	cerr << "salam\n";
	parser->parse();
    errorFile.close();
	return 0;
}
