
#include "Parser.h"

Lexer *lexer = new Lexer(PROGRAM_ADDRESS);
Parser *parser = new Parser();
ofstream errorFile(ERRORS_ADDRESS);
ofstream lexerOutFile(LEXER_OUT_ADDRESS);

int main()
{
    lexerOutFile << "salam" << endl;
//    while (lexer->getNextToken());
    errorFile.close();
    lexerOutFile.close();
//	parser->print();
//	parser->parse();
	return 0;
}
