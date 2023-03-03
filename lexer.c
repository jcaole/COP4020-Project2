/* FileName:	lexer.c
 * Course:	COP4020
 * Project:	#2
 * Author:	Jeremy Caole
 * Description: lexical analyzer class, analyzes, inserts IDs into the symbol
 * table, runs lexical analyzer.
 */

#include "lexer.h"

// main method, initializes lexical analyzer
void initLexer(char *fileName) {
       	file = fopen(fileName, "r");
      	lineNumber = 1;
      	lookahead = lexan();
}

/*
 * lexical analyzer, reads each character in file.
 * store character in array to be used in symbol table.
 * return values: char, type,lexeme
 */
int lexan() {
      	memset(idLexeme, 0, MAX);
      	idLength = 0;
      	while (1) {
	    	ch = fgetc(file);
		//if params, do nothing
	    	if (ch == ' ' || ch == '\t' || ch == ',') {
		  	;
		}
		//else if, increment lineNumber
	       	else if (ch == '\n') {
		  	lineNumber++;
		}
		//else if, read comment till '\n'
	       	else if (ch == '~') {
		  	while (ch != '\n') {
				ch = fgetc(file);
		  	}
		  	ungetc(ch, file);
		}
		//else if, insert whole number, type NUM
	       	else if (isdigit(ch)) {
		  	while (isdigit(ch)) {
				//use of strncat
				strncat(idLexeme, &ch, 1);
				ch = fgetc(file);
		  	}
		  	ungetc(ch, file);
		  	return NUM;
	    	}
		//else if, insert alphabet
	       	else if (isalpha(ch)) {
		  	while (isalpha(ch) || isdigit(ch) || ch == '.' || ch == '_') {
				//use of strncat				 
				strncat(idLexeme, &ch, 1);
				idLength++;
				ch = fgetc(file);
		  	}
		  	type = getType(idLexeme, idLength);
		  	ungetc(ch, file);
		  	return type;
	    	}
	       	else if (ch == EOF) {
		  	return DONE;
	    	}
	       	else {
		  	strncat(idLexeme, &ch, 1);
		  	return ch;
	    	}
      	}
}

/*
 * helper function getType, gets type of lexeme, returns correct tyep.
 */
int getType(char *lexeme, int size) {
	//begin
      	if (strcmp(lexeme, start) == 0) {
	    	return BEGIN;
      	}
	//end
       	else if (strcmp(lexeme, end) == 0) {
	    	return END;
      	}
	//begining underscore
       	else if (lexeme[0] == '_') {
	    	return START_UNDERSCORE;
	} 
	//ending underscore
	else if (lexeme[size - 1] == '_') {
	    	return END_UNDERSCORE;
      	}
	//int
       	else if (strcmp(lexeme, "int") == 0) {
	    	return INT;
      	}
	//two underscore
       	else {
	    	for (int i = 0; i < MAX - 1; i++) {
		  	if (lexeme[i] == '_' && lexeme[i + 1] == '_') {
				return TWO_UNDERSCORE;
		  	}
	    	}
      	}
      	return ID;
}
