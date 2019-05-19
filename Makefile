
all: bin/Lexer.o bin/main.o
	g++ bin/main.o bin/Lexer.o -o compiler
bin/Lexer.o: src/Lexer.cpp
	g++ -c src/Lexer.cpp -o bin/Lexer.o
bin/main.o: src/main.cpp
	g++ -c src/main.cpp -o bin/main.o
