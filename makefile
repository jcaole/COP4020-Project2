CC = gcc
CFLAGS  = -g -Wall

OBJECTS: symboltable.o lexer.o parser.o main.o

symboltable.o: symboltable.h
	$(CC) $(CFLAGS) -c symboltable.c

lexer.o: lexer.h 
	$(CC) $(CFLAGS) -c lexer.c

parser.o: parser.h
	$(CC) $(CFLAGS) -c parser.c

main.o: lexer.h parser.h
	$(CC) $(CFLAGS) -c main.c

main: symboltable.o lexer.o parser.o main.o 
	$(CC) $(CFLAGS) lexer.o parser.o symboltable.o main.o -o main

clean: 
	$(RM) *.o *.out main
