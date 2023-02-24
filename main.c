/*File name:	main.c
 * Course:	COP4020
 * Project:	1
 * Author:	Jeremy Caole
 * Description:	main class
 */

#include "parser.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	printf("\nCompiling %s\n", argv[1]);
	parser(argv[1]);
	end();
	return 0;
}
