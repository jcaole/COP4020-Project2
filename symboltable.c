/* File Name:	symboltable.c
 * Course: 	COP4020
 * Project:	#2
 * Author:	Jeremy Caole
 * Description: class symbol table, holds symbol table needed for lexicalanalyzer and parser class.
 * adds and searches for words in table.
 */

#include "symboltable.h"

// this functuons iniztialize the table.
void initSymbolTable() {
	strcpy(start, "begin");
	strcpy(end, "end.");
}

/*
 * lookupVar method, looks for variable in table
 */
bool lookupVar(char *lexeme) {
      	struct Entry *current = head;
      	if (current == NULL) {
	    	return false;
      	}
      	while (strcmp(current->word, lexeme) != 0) {
	    	if (current->next == NULL) {
		  	return false;
	    	} 
		else {
		  	current = current->next;
	    	}
      	}
      	return true;
}

/*
 * isertEntry method, adds entries to table
 */
void insertEntry(char *id, int line, int t) {
      	newEntry = (struct Entry *)malloc(sizeof(struct Entry));
      	strncpy(newEntry->word, id, sizeof(newEntry->word) - 1);
      	newEntry->value = t;
      	newEntry->next = NULL;
      	newEntry->line = line;

      	if (head == NULL) {
	    	head = newEntry;
      	} 
	else {
	    	struct Entry *lastEntry = head;
	    	while (lastEntry->next != NULL) {
		  	lastEntry = lastEntry->next;
	    	}
	    	lastEntry->next = newEntry;
      	}
}

/*
 * freeTable method, modified cleanTable, delete content in table
 */
void freeTable() {
      	struct Entry *pNode = head, *pNext;
      	while (NULL != pNode) {
	    	pNext = pNode->next;
	    	free(pNode);
	    	pNode = pNext;
      	}
}
