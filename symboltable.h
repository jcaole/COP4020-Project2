#ifndef SYMBOLTABLE
#define SYMBOLTABLE


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"


// required values for the table
#define MAX 250

char end[MAX];
char start[MAX];

// This is the struc used to create
// the symble table, linkedList
struct Entry {
      	char value[MAX];
      	int typ;
      	struct Entry *next;
      	int line;
};

struct Entry *head;
struct Entry *newEntry;

// function
bool lookupVar(char *lexema);
void initSymbolTable(void);
void insertEntry(char *lexema, int line, int size);
void free_table();

#endif
