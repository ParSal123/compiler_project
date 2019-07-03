
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
	if(!(currentScope->getFunction("main") != nullptr && !currentScope->getFunction("main")->isHasReturnValue() && currentScope->getFunction("main")->getParams().empty()))
		errorFile << "no main function found\n";
	pb.insert(pb.begin(), "0\t (JP, " + to_string(currentScope->getFunction("main")->getStartAddress() + 1) + ", , )");
	printProgramBlock();
    errorFile.close();
	return 0;
}
