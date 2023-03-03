/* File Name:	parser.h
 * Course:	COP4020
 * Project:	#2
 * Author:	Jeremy Caole
 * Description: header file for parser class
 */

#ifndef PARSER
#define PARSER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lexer.h"


#define SIZE 1000

/*
 * variables
 */
char varArray[MAX][MAX];
char output[SIZE];
int registers;

unsigned int varNumber;

/*
 * methods
 */
void parser();				//main method to parse words
void match(int);			//checks for term/operation
void process();				//variable declaration/assigment operator
void declaration();			//variable declaration check
void addVariable(int);			//add var to symbol table

void AssignmentStmt();			//checks assignmentStatement, track registers
void term();				
void factor();				//
char* setOperator(int);			// project 2 method, sets operators: add, sub, mul, div

void printStatement();			//
void printError(char);			//

#endif
