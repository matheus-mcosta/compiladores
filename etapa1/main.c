// Matheus de Moraes Costa 00297121

#include <stdio.h>
#include <stdlib.h>

// lex.yy.h
int yylex();
extern char *yytext;
extern FILE *yyin;

int isRunning(void);
void initMe(void);

int main(int argc, char **argv) {
  int token = 0;
  fprintf(stderr, "Rodando main Matheus. \n");

  if (argc < 2) {
    printf("call: ./etapa1 input.txt \n");
    exit(1);
  }
  if (0 == (yyin = fopen(argv[1], "r"))) {
    printf("Cannot open file %s... \n", argv[1]);
    exit(1);
  }
  initMe();
  while (isRunning()) {
    token = yylex();

    switch(token){
      case KW_CHAR:             printf("KW_CHAR '%d'\n", token);            break;
      case KW_INT:              printf("KW_INT '%d'\n", token);             break;
      case KW_FLOAT:              printf("KW_FLOAT '%d'\n", token);           break;
      case KW_CODE:             printf("KW_CODE '%d'\n", token);            break;
      case KW_IF:               printf("KW_IF '%d'\n", token);              break;
      case KW_ELSE:             printf("KW_ELSE '%d'\n", token);            break;
      case KW_WHILE:             printf("KW_WHILE '%d'\n", token);            break;
      case KW_INPUT:             printf("KW_INPUT '%d'\n", token);          break;
      case KW_PRINT:             printf("KW_PRINT '%d'\n", token);        break;
      case KW_RETURN:           printf("KW_RETURN '%d'\n", token);          break;
      case OPERATOR_LE:         printf("OPERATOR_LE '%d'\n", token);        break;
      case OPERATOR_GE:         printf("OPERATOR_GE '%d'\n", token);        break;
      case OPERATOR_EQ:         printf("OPERATOR_EQ '%d'\n", token);        break;
      case OPERATOR_DIF:        printf("OPERATOR_DIF '%d'\n", token);       break;
      case TK_IDENTIFIER:       printf("TK_IDENTIFIER '%d'\n", token);      break;
      case LIT_INT:             printf("LIT_INT '%d'\n", token);         break;
      case LIT_REAL:             printf("LIT_REAL '%d'\n", token);        break;
      case LIT_CHAR:            printf("LIT_CHAR '%d'\n", token);           break;
      case LIT_STRING:          printf("LIT_STRING '%d'\n", token);         break;
      case TOKEN_ERROR:         printf("TOKEN_ERROR '%d'\n", token);        break;
      default:                  printf("token '%d'\n", token);              break;

    }
    if (!isRunning())
      break;
  }
}

