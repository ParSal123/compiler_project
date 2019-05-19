
all: bin/Lexer.o bin/Parser.o bin/main.o
	g++ bin/main.o bin/Lexer.o bin/Parser.o -o compiler
bin/Lexer.o: src/Lexer.cpp src/Lexer.h
	g++ -c src/Lexer.cpp -o bin/Lexer.o
bin/Parser.o: src/Parser.cpp src/Parser.h
	g++ -c src/Parser.cpp -o bin/Parser.o
bin/main.o: src/main.cpp
	g++ -c src/main.cpp -o bin/main.o
