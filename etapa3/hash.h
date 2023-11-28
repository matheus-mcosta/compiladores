// Matheus de Moraes Costa 00297121
// Codigo baseado na implementação do professor

#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 997

extern char *yytext;

typedef struct hash_node {
  int type;
  char *text;
  struct hash_node *next;
} HASH_NODE;

void initMe(void);

int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);
#endif
