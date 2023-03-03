/* File Name: 	symboltable.h
 * Course:	COP4020
 * Project:	1
 * Author:	Jeremy Caole
 * Description:	symbol table class, uses a hashtable struct, inserts, seaches, writes the tokens(words) into and
 * from table.
 */

#include "symboltable.h"

HashTable* initSymbolTable() {
	ht = createTable();
	return ht;
}

int hash(const char* word) {
	int index = 0;
	int c;
	while ((c = *word++))
		index = ((MAX << 5) + MAX) + c;

	return index % MAX;
}

//method creates table to be used in lexical analyzer
HashTable* createTable() {
	// use of malloc, allocates memory for table
	HashTable* table = malloc(sizeof(HashTable));

	// use of malloc, allocates memory for words(tokens) for table
	table->entries = malloc(sizeof(Entry*) * MAX);
	
	//initializes number of entries to 0
	table->numEntries = 0;
	for (int i = 0; i < MAX; ++i)
		table->entries[i] = NULL;

	return table;
}

// Creates a single word value pair
Entry* setEntries(const char *word, const int value) {
	Entry* entries = malloc(sizeof(Entry) * 1);
	entries->word = malloc(strlen(word) + 1);
	strcpy(entries->word, word);
	entries->value = value;

	// next starts out null but may be set later on
	entries->next = NULL;

	return entries;
}

// insert a word and value into the table
void setTable(HashTable* table, const char *word, int value) {
	int slot = hash(word);

	// try to look up an entries set
	Entry* entries = table->entries[slot];

	//added for project 2
	if (strcmp(word, "INT") == 0) {
		value = INT;
	}
//	int slot = hash(word);
	// no entries means slot empty, insert immediately
	if (entries == NULL) {
		table->entries[slot] = setEntries(word, value);
		return;
	}

	Entry* prev;

	// walk through each entries until either the end is
	// reached or a matching word is found
	while (entries != NULL) {
		// check word
		if (strcmp(entries->word, word) == 0) {
			// match found, replace value
			entries->value = value;
			return;
		}

		// walk to next
		prev = entries;
		entries = prev->next;
	}

	// end of chain reached without a match, add new
	prev->next = setEntries(word, value);
}

// search for a specific value by its word
int getTable(HashTable* table, const char *word) {
	int slot = hash(word);

	// try to find a valid slot
	Entry* entries = table->entries[slot];
	// printf("The entries at slot %d is %d\n", slot, entries->value);

	while (entries != NULL) {
		if(strcmp(word, "INT") == 0) {
			return INT;
		}
		// return value if found
		if (strcmp(entries->word, word) == 0) {
			return entries->value;
		}

		entries = entries->next;
	}
	return NOT_FOUND;
}

// cleans hashtable, free allocated mem
void cleanTable(HashTable* table) {
	if (!table)
		return;
	size_t i = 0;
	if (table->entries) {

		// frees allocated entries
		Entry* current;
		while (i < MAX) {
			Entry* entries = table->entries[i];
			while (1) {
				if (entries == NULL) {
					break;
				}
				if (entries->word) {
					free(entries->word);
					entries->value = 0;
				}
				current = entries;
				entries = entries->next;
				free(current);
			}
			i++;
		}

		// frees entry pointers
		free(table->entries);
		table->entries = NULL;
	}

	// Free table's pointers
	free(table);
	table = NULL;
	return;
}

// print table
void printTable(HashTable* table) {
	//
	printf("slot[    ] word = value\n");
	for (int i = 0; i < MAX; ++i) {
		Entry* entries = table->entries[i];
		//
		if (entries == NULL) {
			continue;
		}
		//endless loop
		while (1) {
			printf("slot[%4d]: ", i);
			printf("%s=%d\n", entries->word, entries->value);
			
			//ends loop after no entries are left
			if (entries->next == NULL) {
				break;
			}
			entries = entries->next;
		}
	}
}

// print all the words, used after completed checks.
void printWords(HashTable* table, int type) {

	printf("slot[    ] key = value\n");

	for (int i = 0; i < MAX; ++i) {
		Entry* entries = table->entries[i];
		//
		if (entries == NULL) {
			continue;
		}
		//endless loop
		while (1) {
			if (entries->value == type) {
				printf("%s, ", entries->word);
				
				if (entries->next == NULL) {
					break;
				}
				entries = entries->next;
			}
			if (entries->next == NULL) {
				break;
			}
		}
	}
	printf("]\n");
}

int lookup(char *word) {
	return getTable(ht, word);
}



//lookupEntry method for project 2
Entry* lookupEntry(HashTable* table, const char *word) {
    int slot = hash(word);

    // try to find a valid slot
    Entry* entries = table->entries[slot];
    while (entries != NULL) {
        // return entry if found
        if (strcmp(entries->word, word) == 0) {
            return entries;
        }
        entries = entries->next;
    }

    // entry not found
    return NULL;
}

//lookupVar method for project 2
int lookupVar(char *id) {
	Entry* entry = lookupEntry(ht, id);
	if(entry == NULL) {
		return 0;
	}
	return 1;
}
