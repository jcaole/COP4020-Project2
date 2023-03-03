/* FileName:	lexer.h
 * Course:	COP4020
 * Project:	#2
 * Author:	Jeremy Caole
 * Description: header file for the lexical analyzer
 */

#ifndef LEXER
#define LEXER

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "symboltable.h"

#define MAX 500

#define ID 300
#define NUM 301
#define BEGIN 400
#define END 401
#define DONE 800

//changed to match value in given chart
#define NOT_FOUND -1

/*
 * added for project 2
 */
#define INT 200
#define START_UNDERSCORE 801
#define END_UNDERSCORE 802
#define TWO_UNDERSCORE 803

FILE *file;
FILE *o_fp;

int lineNumber;
char ch;
int type;
int lookahead;
int idLength;

char idLexeme[MAX];

// functions
int lexan(void);
void initLexer(char *fileName);
int getType(char *lexema, int size);

#endif
