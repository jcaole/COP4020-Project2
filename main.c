//#include "lexer.h"
#include "parser.h"
//#include "table.h"
#include <stdio.h>

int main(int argc, char *argvc[]) {
  memset(output, 0, 1000);
  char f_name[8] = {0};
  int i = 0;

  if (argc == 2) {
    initSymbolTable();
    initLexer(argvc[1]);
    printf("\nCompiling %s\n", argvc[1]);
    parse();

    while (*(argvc[1]) != '.' && *(argvc[1]) != 0) {
      f_name[i] = *(argvc[1]);
      i++;
      argvc[1]++;
    }
    sprintf(f_name + strlen(f_name), ".out");
    o_fp = fopen(f_name, "w");
    fwrite(output, sizeof(char), strlen(output), o_fp);
    fclose(o_fp);
  }
  return 0;
}
