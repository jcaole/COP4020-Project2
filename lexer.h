/* FileName:	lexer.h
 * Course:	COP4020
 * Project:	#1
 * Author:	Jeremy Caole
 * Description: header file for the lexical analyzer
 */

#ifndef LEXER
#define LEXER

#include "symboltable.h"
#include <ctype.h>

FILE* file;

//struct Hashtable
HashTable* symbolTable;

int numLexan;
char *idLexan;
int lineNumber;
int colNumber;

//initializes lexical analyzer
void initLexer(char* fileName);
int lexan();

//getters
int getLineNum();
int getColNum();

#endif
