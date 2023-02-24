/* File Name:	parser.h
 * Course:	COP4020
 * Project:	#1
 * Author:	Jeremy Caole
 * Description: header file for parser class
 */

#ifndef PARSER
#define PARSER

#include <stdio.h>

#include "lexer.h"

int lookahead;
int lineNum;

void parser(char* fileName);
void assignmentStmt();
void expression();
void term();
void factor();
void match(int type);
void end();
#endif
