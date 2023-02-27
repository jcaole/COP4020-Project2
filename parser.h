/* File Name:	parser.h
 * Course:	COP4020
 * Project:	#1
 * Author:	Jeremy Caole
 * Description: header file for parser class
 */

#ifndef PARSER
#define PARSER

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

#define SIZE 1000		//added for project 2

int lookahead;
int lineNum;


int registers;			//added for project 2
//unsigned int varNumber		//added for project 2
//char vars[MAX][MAX];		//added for project 2
//char output[SIZE];		//added for project 2

void parser(char* fileName);
void assignmentStmt();
void expression();
void term();
void factor();
void match(int type);
void end();

char* setOperator(int);		//project 2 method

#endif
