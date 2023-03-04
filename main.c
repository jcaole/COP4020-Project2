/*File name:	main.c
 * Course:	COP4020
 * Project:	1
 * Author:	Jeremy Caole
 * Description:	main class
 */

#include <stdio.h>

#include "parser.h"

int main(int argc, char *argv[]) {
	FILE* outputFile;
	memset(output, 0, 1000);
      	char file[8] = {0};
      	int i = 0;

      	if (argc == 2) {
	    	initSymbolTable();
	    	initLexer(argv[1]);
	    	printf("\nCompiling %s\n", argv[1]);

		parser();
		while (*(argv[1]) != '.' && *(argv[1]) != 0) {
		  	file[i] = *(argv[1]);
		  	i++;
		  	argv[1]++;
		}
	    	sprintf(file + strlen(file), ".out");
	    	
		outputFile = fopen(file, "w");
	    	fwrite(output, sizeof(char), strlen(output), outputFile);
	    	
		fclose(outputFile);
      	}
      	return 0;
}
