CC = gcc
CFLAGS = -g -Wall

OBJECTS: symboltable.o lexer.o parser.o

#main: $(OBJECTS) main.o
#	$(CC) $(CFLAGS) -o $@ $^

main:   symboltable.o lexer.o parser.o main.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) *.o main
