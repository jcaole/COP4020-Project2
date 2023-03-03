/* File Name:	symboltable.h
 * Course: 	COP4020
 * Project:	#2
 * Author:	Jeremy Caole
 * Description: header file for class symbol table
 */

#ifndef SYMBOLTABLE
#define SYMBOLTABLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>

#include "lexer.h"


/*
 * moved defined variables to lexical analyzer class.
 */
#define MAX 500

/*
 * initilized start and end array variables
 */
char start[MAX];
char end[MAX];

/*
 * removed Hashtable struct, struct Entry creates symbol table
 * utilizes linkedlist 
 */
struct Entry {
      	char word[MAX];
      	int value;
      	struct Entry *next;
      	int line;
};

struct Entry *head;
struct Entry *newEntry;

/*
 *modified for project 2
 */
void initSymbolTable(void);
bool lookupVar(char *word);

void insertEntry(char *id, int line, int size);

/*
 * modified cleanTable method from project 1
 */
void freeTable();

#endif
