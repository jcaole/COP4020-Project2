/* File NAme:	parser.c
 * Course:	COP4020 Programming Languages
 * Project:	1
 * Author:	Jeremy Caole
 * Description:	functions for parsing statements for the given .in files.
 * checks for legal/illegal input in file. tracks registers.
 */

#include "parser.h"

/*
 * main method for parser class.
 */
void parser() {
      	registers = 0;
      	varNumber = 0;
      	while (lookahead != BEGIN) {
	    	match(lookahead);
	    	if (lookahead == DONE) {
		  	printf("\nSyntax Error: all programs mst start with 'begin'\n\n");
		  	freeTable();
		  	fclose(file);
		  	exit(1);
	    	}
      	}
      	match(BEGIN);
      	while (lookahead != END) {
	    	if (lookahead == DONE) {
		  	printf("\nSyntax Error: all programs must start with 'end'\n\n");
		  	freeTable();
		  	fclose(file);
		  	exit(1);
	    	}
	    	process();
      	}
     	printf("\nSuccess.\n");
      	freeTable();
      	fclose(file);
}

/*
 * match method, checks for term/operation in .in file
 */
void match(int t) {
      	if (lookahead == t) {
	    	lookahead = lexan();
      	}
       	else {
	    	printError(t);
      	}
}

/*
 * process method, variable declaration/assignment operation
 */
void process() {
      	while (lookahead == INT) {
	    	declaration();
      	}
      	while (lookahead == ID) {
	    	AssignmentStmt();
      	}
}

/*
 * declaration method, checks variable declaration
 */
void declaration() {
      	match(INT);
      	addVariable(type);
      	match(';');
}

/*
 * addVariable method, adds variables to symbol table 
 */
void addVariable(int type) {
      	while (lookahead == ID) {
	    	if (lookupVar(idLexeme)) {
		  	printf("\nError Line %d: variable '%s' already defined \n", lineNumber, idLexeme);
		  	freeTable();
		  	fclose(file);
		  	exit(1);
	    	}
	    	insertEntry(idLexeme, lineNumber, ID);
	    	match(ID);
      	}
}

/*
 * AssignmentStatement method, checks assignment operation and tracks registers
 */
void AssignmentStmt() {
	//initialize char arr Array
      	char arr[30];
      	strcpy(arr, idLexeme);
	
	//type int, clear table before closing
      	if (lookahead == INT) {
	    	match(INT);
	    	if (lookupVar(idLexeme)) {
		  	printf("\nError Line %d: Redeclaration of %s\nFail\n", lineNumber, idLexeme);
		  	freeTable();
		  	fclose(file);
		  	exit(1);
	    	}
      	}
	//type ID, clear table before closing
      	if (lookahead == ID && !lookupVar(idLexeme)) {
	    	printf("\nError Line %d: Variable %s is undefined\nFail\n", lineNumber, idLexeme);
	    	freeTable();
	    	fclose(file);
	    	exit(1);
      	}
      	match(ID);
	// checks for '='
      	if (lookahead != '=') {
	    	printf("\nError Line %d: Expected an '='\nFail\n", lineNumber);
	    	freeTable();
	    	fclose(file);
	    	exit(1);
      	}
      	match('=');
      	term();
      	match(';');

	//decrement registers
      	registers -= 1;
	//use of sprintf
      	sprintf(output + strlen(output), "%s = R%d\n", arr, registers);
      	printStatement();
}

/*
 * term method, defines terms
 */
void term() {
      	factor();
      	while (lookahead == '+' || lookahead == '-' || lookahead == '*' || lookahead == '/') {
	    	char* lookFor = setOperator(lookahead);
	    	match(lookahead);
	    	factor();

	    	sprintf(output + strlen(output), "R%d = R%d %s R%d\n", registers - 2, registers - 2, lookFor, registers - 1);
	    	registers -= 1;
	    	strcpy(varArray[varNumber], lookFor);
	    	varNumber++;
      	}
}

/*
 * setOperator method
 */ 
char* setOperator(int lookahead){
	if(lookahead == '+' ) {
		return "+";
	}
	else if(lookahead == '-') {
		return "-";
	}
	else if(lookahead == '*' ) {
		return "*";
	}
	else {
		return "/";
	}
}

/*
 * factor method, checks for parenthesis, and expressions
 */
void factor() {
	//check for '('
      	if (lookahead == '(') {
	    	match('(');
	    	if (lookahead == ')') {
		  	printf("\nError Line %d: Expected identifier got ')'\n", lineNumber);
		  	freeTable();
		  	fclose(file);
		  	exit(1);
	    	}
	    	term();
		//match closing parenthesis
	    	match(')');
      	}
	//check ID
       	else if (lookahead == ID) {
	    	if (!lookupVar(idLexeme)) {
		  	printf("\nError Line %d: variable %s not declared\n", lineNumber, idLexeme);
		  	freeTable();
		  	fclose(file);
		  	exit(1);
	    	}
		//use of sprintf
	    	sprintf(output + strlen(output), "R%d = %s\n", registers++, idLexeme);
	    	//strcpy array variable and idL
		strcpy(varArray[varNumber], idLexeme);
	    	//increment variable number
		varNumber++;
		//use of match method
	    	match(lookahead);
	}
	//check NUM
       	else if (lookahead == NUM) {
	    	sprintf(output + strlen(output), "R%d = %s\n", registers++, idLexeme);
	    	strcpy(varArray[varNumber], idLexeme);
	    	varNumber++;
	    	match(lookahead);
      	}
}

/*
 * print variables and operators that registers listed
 */
void printStatement() {
	//printf("test printStatement");
      	int i;
	//use of sprintf function in c library, sends formatted output to a string pointer, used for array
      	sprintf(output + strlen(output), "\n*****[");
      	for (i = 0; i < varNumber - 1; i++) {
	    	sprintf(output + strlen(output), "%s", varArray[i]);
	    	sprintf(output + strlen(output), ",");
      	}
      	sprintf(output + strlen(output), "%s", varArray[i]);
      	sprintf(output + strlen(output), "]*****\n\n");
      	varNumber = 0;
}

/*
 * printError method, prints error messages for identifer
 */
void printError(char c) {
	//begins with underscore
      	if (lookahead == START_UNDERSCORE) {
	    	printf("\nError Line %d: Identifier cannot start with underscore\n", lineNumber);
      	}
	//ends with underscore
	else if (lookahead == END_UNDERSCORE) {
	    	printf("\nError Line %d: Identifier cannot end with underscore\n", lineNumber);
      	}
	//has 2 underscores consecutively
	else if (lookahead == TWO_UNDERSCORE) {
	    	printf("\nError Line %d: Identifier has underscore followed by other underscore\n", lineNumber);
      	} 
	//missing '('
	else if (c == '(') {
	    	printf("\nError Line %d: syntax error expected '%c'\n", lineNumber, c);
      	} 
	//missing ')'
	else if (c == ')') {
	    	printf("\nError Line %d: syntax error expected '%c'\n", lineNumber, c);
      	}
	//missing ';'
	else if (c == ';') {
	    	printf("\nError Line %d: syntax error expected '%c'\n", lineNumber, c);
      	}
	/*
	 * free variables in symboltable and closes file before exiting
	 */
      	freeTable();
      	fclose(file);
      	exit(1);
}
