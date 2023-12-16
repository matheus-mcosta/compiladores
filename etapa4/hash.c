// Matheus de Moraes Costa 00297121
// Codigo baseado na implementação do professor

#include "hash.h"

HASH_NODE *Table[HASHSIZE];

void hashInit(void) {
  int i = 0;
  for (i = 0; i < HASHSIZE; i++) {
    Table[i] = 0;
  }
}

int hashAddress(char *text) {
  int address = 1;
  int i = 0;
  for (i = 0; i < strlen(text); i++) {
    address = (address * text[i]) % HASHSIZE + 1;
  }
  return address - 1;
}

HASH_NODE *hashFind(char *text) {
  HASH_NODE *node;
  int address = hashAddress(text);
  for (node = Table[address]; node; node = node->next) {
    if (strcmp(node->text, text) == 0) {
      return node;
    }
  }
  return 0;
}

HASH_NODE *hashInsert(char *text, int type) {
  HASH_NODE *newnode;
  int address = hashAddress(text);
  if ((newnode = hashFind(text)) != 0) {
    return newnode;
  }
  newnode = (HASH_NODE *)calloc(1, sizeof(HASH_NODE));
  newnode->type = type;
  newnode->text = (char *)calloc(strlen(text) + 1, sizeof(char));

  switch (type) {
  case SYMBOL_LIT_INT:
    newnode->datatype = DATATYPE_INT;
    break;
  case SYMBOL_LIT_REAL:
    newnode->datatype = DATATYPE_REAL;
    break;
  case SYMBOL_LIT_CHAR:
    newnode->datatype = DATATYPE_CHAR;
    break;
  }

  strcpy(newnode->text, text);
  newnode->next = Table[address];
  Table[address] = newnode;
  return newnode;
}

void hashPrint(void) {
  HASH_NODE *node;
  int i = 0;
  for (i = 0; i < HASHSIZE; i++) {
    for (node = Table[i]; node; node = node->next) {
      printf("Table[%d] has %s\n", i, node->text);
    }
  }
}

int hashCheckUndeclared(void) {
  HASH_NODE *node;
  int num_undeclared = 0;
  for (int i = 0; i < HASHSIZE; i++) {
    for (node = Table[i]; node; node = node->next) {
      if (node->type == SYMBOL_IDENTIFIER) {
        fprintf(stderr, "Undeclared identifier %s\n", node->text);
        num_undeclared++;
      }
    }
  }
  return num_undeclared;
}
