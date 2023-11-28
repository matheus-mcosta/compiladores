// Matheus de Moraes Costa 00297121

#include "lex.yy.h"
#include <stdio.h>
#include <stdlib.h>

// lex.yy.h
int yylex();
int yyparse();

extern char *yytext;
extern FILE *yyin;

int isRunning(void);
void initMe(void);

int main(int argc, char **argv) {
  fprintf(stderr, "Rodando main Matheus. \n");

  if (argc < 2) {
    printf("call: ./etapa2 input.txt \n");
    exit(1);
  }
  if (0 == (yyin = fopen(argv[1], "r"))) {
    printf("Cannot open file %s... \n", argv[1]);
    exit(1);
  }

  initMe();

  yyparse();

  printf("Fim da compilacao com sucesso\n");
  exit(0);
}
