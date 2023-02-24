/* File Name:	symboltable.h
 * Course: 	COP4020
 * Project:	#1
 * Author:	Jeremy Caole
 * Description: header file for class symbol table
 */

#ifndef SYMBOLTABLE
#define SYMBOLTABLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//defined variables
#define ID 300
#define NUM 301
#define BEGIN 400
#define END 401
#define DONE -1
#define NOT_FOUND 404
#define MAX 500

//NOTE: typedef is needed to create a new name for existing datatype
//entry struct
typedef struct Entry {
	char *word;
	int value;
	struct Entry* next;
}Entry;

//hashtable struct
typedef struct HashTable {
	Entry** entries;
	int numEntries;
	int size;
} HashTable;

//set content for table
void setTable(HashTable* table, const char *word, const int value);

//get content in table
int getTable(HashTable* table, const char *word);

//returns the hashed indexed word
int hash(const char *word);

//method creates symbol table to be used in lexical analyzer
HashTable* createTable();

//set entries
Entry* setEntries(const char *word, const int value);

//methods to print content of table
void printTable(HashTable* table);
void printWords(HashTable* table, int type);

//delete content in table
void cleanTable(HashTable* table);

//initialize hashtable
HashTable* ht;

//main method 
HashTable* initSymbolTable();

//method to check word in symbol table
int lookup(char *word);

#endif
