// Matheus de Moraes Costa 00297121
// Codigo baseado na implementação do professor

#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 997

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_REAL 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_IDENTIFIER 5

#define SYMBOL_SCALAR 6
#define SYMBOL_VECTOR 7
#define SYMBOL_FUNCTION 8
#define SYMBOL_PARAM 9

#define DATATYPE_CHAR 10
#define DATATYPE_INT 11
#define DATATYPE_REAL 12
#define DATATYPE_BOOL 13

extern char *yytext;

typedef struct hash_node {
  int type;
  int datatype;
  char *text;
  struct hash_node *next;
} HASH_NODE;

void initMe(void);

int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);
int hashCheckUndeclared(void);
#endif
