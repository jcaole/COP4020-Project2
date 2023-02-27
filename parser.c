/* File NAme:	parser.c
 * Course:	COP4020 Programming Languages
 * Project:	1
 * Author:	Jeremy Caole
 * Description:	source code of parser class. parses tokens in order. content based on given pseudo code.
 */

#include "parser.h"

void parser(char* fileName) {
	lookahead = 0;

//	registers = 0;
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
	term();
	while (lookahead == '+' || lookahead == '-') {
		match(lookahead);
		term();
	}
}

void term() {
	factor();
	while (lookahead == '*' || lookahead == '/') {
			match(lookahead);
		factor();
	}

/*	while (lookahead == '+' || lookahead == '-' || lookahead == '*' || lookahead == '/') {
		char* firstLook = setOperator(lookahead);
		match(lookahead);
		factor();
		sprintf(output + strlen(output), "R%d = R%d %s R%d\n", registers - 2,
				registers - 2, firstLook, registers -1);
		registers -= 1;
		strcpy(vars[varNumber], firstLook);
		varsNumber++;
	}
*/
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
void match(int type) {
	
	if (lookahead == type) {
		lookahead = lexan();
	} 
	//
	else if (type == ')') {
		printf("Missing closing parenthesis on line %d, col %d.\n", getLineNum(), getColNum());
		end(1);
	}
	//	
	else if (type == ID) {
		exit(1);
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

//project 2 method setOperator
char* setOperator(int lookahead) {
	if(lookahead == '+' ){ 
		return "+";
	}
	else if(lookahead == '-') {
		return "-";
	}
	else if(lookahead == '*') {
		return "*";
	}
	else {
		return "/";
	}
}

