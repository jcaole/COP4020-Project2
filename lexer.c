/* File Name:
 * Course:
 * Project:
 * Author:
 * Description: source file for the lexical analyzer, analyzes the type of token, symbol table 
 * is needed for this file
 */

#include "lexer.h"

// main method, initializes lexical analyzer
void initLexer(char* fileName) {
	lineNumber = 1;
	colNumber = 1;

	//initializes symboltable
	symbolTable = initSymbolTable();

	file = fopen(fileName, "r");
}

//getter for line number
int getLineNumber() {
	return lineNumber;
}

// lexan method reads each character in file
int lexan() {
	//initializes ch, use of fgetc
	char ch = fgetc(file);
	//increment column number
	colNumber++;
	//do while loop
	do {
		//whitespaces ignored
		if (ch == ' ' || ch == '\t') {

			//initializes ch, use of fgetc
			ch = fgetc(file);
			//increment column number
			colNumber++;
		} 
		//newline ignored
		else if (ch == '\n') {
			//increments line
			lineNumber++;
			//initiliaze column number to 0 before incrememnting
			colNumber = 0;
			ch = fgetc(file);
			colNumber++;
		} 
		//comment igmored
		else if (ch == '~') {
			// checks for newline
			while (ch != '\n') {
				ch = fgetc(file);
			}
			colNumber = 0;
		}
		//use of isdigit, gets whole number returns correct type	
		else if (isdigit(ch)) {

			//initializes number of characters to 0
			int numChars = 0;
			//use of malloc
			char* numLexan = malloc(sizeof(char*));
			while (isdigit(ch)) {
				colNumber++;
				numLexan = realloc(numLexan, ++numChars * sizeof(char));
				//use of strncat
				strncat(numLexan, &ch, numChars + 1);
				ch = fgetc(file);
			}
			ch = ungetc(ch, file);
			colNumber--;
			return NUM;
		}
		//use of isalpha for alphabetical charaters
		else if (isalpha(ch)) {
			int numChars = 0;
			int capacity = 256;

			char* idLexan = malloc(sizeof(char) * capacity);
			//use of isalnum for alpha and numerical characters
			while ((isalnum(ch) || ch == '_' || ch == '.') && ch != '\n') {

				if (numChars == capacity - 1) {
					idLexan = realloc(idLexan, sizeof(char) * capacity);
				}

				if (ch == '_') {
					char nextChar = fgetc(file);
					if (nextChar == '_') {
						printf("Syntax error on line %d, col %d. Identifiers cannot contain consecutive underscores.\n", lineNumber, colNumber);
						free(idLexan);
						return DONE;
					}
					nextChar = ungetc(nextChar, file);
					colNumber--;
				}
				if (ch == '.'){
					char nextChar = fgetc(file);
					if (nextChar != '\n') {
						free(idLexan);
						return DONE;
					}
				}
				idLexan[numChars++] = ch;
				ch = fgetc(file);
				colNumber++;
			}

			if (idLexan[strlen(idLexan) - 1] == '_') {
				printf("Syntax error on line %d, col %d. Identifiers cannot end with an underscore.\nFail\n", lineNumber, colNumber);
				free(idLexan);
				return DONE;
			}
			ch = ungetc(ch, file);
			colNumber--;

			if (strcmp(idLexan, "begin") == 0){
				setTable(symbolTable, idLexan, BEGIN);
			} 
			else if (strcmp(idLexan, "end.") == 0) {
				setTable(symbolTable, idLexan, END);
			}
//			int type = lookup(idLexan);
			int type = lookup(idLexan);
			if (type == NOT_FOUND) {
				type = ID;
				setTable(symbolTable, idLexan, type);
			}
			free(idLexan);
			return type;

		} 
		else if (ch == EOF) {
			return DONE;
		} 
		else {
			return ch;
		}
	} 
	while (!feof(file));

	return DONE;
}

/*
 * getters needed
 */
int getLineNum() {
	return lineNumber;
}
int getColNum() {
	return colNumber;
}
