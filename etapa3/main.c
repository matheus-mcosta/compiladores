// Matheus de Moraes Costa 00297121

#include "ast.h"
#include "lex.yy.h"
#include <stdio.h>
#include <stdlib.h>

// lex.yy.h
extern int yylex();
extern int yyparse();
extern void astPrint(int level, AST_NODE *node);
extern AST_NODE *getAST();

extern char *yytext;
extern FILE *yyin;

int isRunning(void);
void initMe(void);

int main(int argc, char **argv) {
  FILE *out;
  fprintf(stderr, "Rodando main Matheus. \n");

  if (argc < 3) {
    printf("call: ./etapa3 input.txt output.txt\n");
    exit(1);
  }
  if (0 == (yyin = fopen(argv[1], "r"))) {
    printf("Cannot open file %s... \n", argv[1]);
    exit(1);
  }
if (0 == (out = fopen(argv[2], "w+"))) {
    printf("Cannot open file %s... \n", argv[2]);
    exit(1);
}

  initMe();

  yyparse();
  astPrint(0, getAST());

  astDecompile(getAST(), out);
  fclose(out);

  printf("Fim da compilacao com sucesso\n");
  exit(0);
}
