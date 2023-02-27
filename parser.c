/* File NAme:	parser.c
 * Course:	COP4020 Programming Languages
 * Project:	1
 * Author:	Jeremy Caole
 * Description:	source code of parser class. parses tokens in order. content based on given pseudo code.
 */

#include "parser.h"

void parser(char* fileName) {
	lookahead = 0;

	registers = 0;
//	varNumber = 0;

	initLexer(fileName);
	match(lookahead);
	match(BEGIN);
	do {
		assignmentStmt();
	} 
	while (lookahead == ID);
	
	match(END);
	end(0);
}


void assignmentStmt() {
/*	char a[30];
	strcpy(a, idLexan);

	if(lookahead == INT) {
		match(INT);
		if(lookupVar(idLexan)) {
			printf("Line: % Redeclaration of %s\n", lineNum, idLexan);
*/
	match(ID);
	if (lookahead != '=') {
		printf("Expected an '=' on line %d, col %d\nFail\n", getLineNum(), getColNum());
		exit(1);
	} 
	else {
		match(lookahead);
		expression();
		match(';');
	}
}

void expression() {
/*	term();
	while (lookahead == '+' || lookahead == '-') {
		match(lookahead);
		term();
	}
*/
	term();
	while(lookahead == '+' || lookahead == '-') {
		int operation = lookahead;
		match(operation);
		term();
		if(operation == '+') {
			printf("ADD R%d, R%d\n", registers - 2, registers - 1);
		}
		else {
			printf("SUB R%d, R%d\n", registers - 2, registers - 1);
		}
		registers--;
	}
}

void term() {
/*	factor();
	while (lookahead == '*' || lookahead == '/') {
			match(lookahead);
		factor();
	}
*/
	factor();
	while(lookahead == '*' || lookahead == '/') {
		int operation = lookahead;
		match(operation);
		factor();
		if(operation == '*') {
			printf("MUL R%d, R%d\n", registers - 2, registers - 1);
		}
		else {
			printf("DIV R%d, R%d\n", registers - 2, registers - 1);
		}
		registers--;
	}
}

void factor() {
	if (lookahead == ID) {
		match(ID);
	} 
	else if (lookahead == NUM) {
		match(NUM);
	} 
	else if (lookahead == '(') {
		match('(');
		expression();
		match(')');
	}
}

/*
 * project 2 method
 */
void setOperator(int lookahead) {
	if (lookahead == '+' || lookahead == '-' || lookahead == '*' || lookahead == '/') {
		match(lookahead);
	} 
}

void match(int type) {
	setOperator(lookahead);

	if (lookahead == type) {
		lookahead = lexan();
	} 
	//
	else if (type == ')') {
		printf("Missing closing parenthesis on line %d, col %d.\n", getLineNum(), getColNum());
		end(1);
	}
	//
	else if (type == BEGIN) {
		printf("Syntax error on line %d, col %d. All programs must start with 'begin'\n", getLineNum(), getColNum());
		end(1);
	} 
	else if (type == END) {
		printf("Syntax error on line %d, col %d. All programs must start with 'end'\n", getLineNum(), getColNum());
		end(1);
	} 
	else if (type == ';') {
		printf("Syntax error on line %d, col %d. Every assignment statement must end with a semicolon ';' 'end'\n", getLineNum(), getColNum());
		end(1);
	} 
	else {
		printf("Syntax error on line %d, col %d.\n", getLineNum(), getColNum());
		end(1);
	}
}

void end(int status) {
	if (status != 0) {
		printf("Fail\n");
		cleanTable(symbolTable);
		exit(EXIT_FAILURE);
	}
	printf("Success\n");
	printWords(symbolTable, ID);
	cleanTable(symbolTable);
	exit(EXIT_SUCCESS);
}
//added method for project 2
/*void declareVar(char* varName) {
    if (lookup(varName) == NULL) {
        insert(symbolTable, varName, 0); // add the variable to the symbol table with initial value 0
    } else {
        printf("Error: Variable %s already declared on line %d, col %d\n", varName, getLineNum(), getColNum());
        end(1);
    }
}
*/
