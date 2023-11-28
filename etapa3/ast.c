// Matheus de Moraes Costa 00297121
// Codigo baseado na implementação do professor

#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

AST_NODE *astCreate(int type, HASH_NODE *symbol, AST_NODE *son0, AST_NODE *son1,
                    AST_NODE *son2, AST_NODE *son3) {
  AST_NODE *newNode;
  newNode = (AST_NODE *)calloc(1, sizeof(AST_NODE));
  newNode->type = type;
  newNode->symbol = symbol;
  newNode->son[0] = son0;
  newNode->son[1] = son1;
  newNode->son[2] = son2;
  newNode->son[3] = son3;
  return newNode;
}

void astPrint(int level, AST_NODE *node) {
  int i;
  if (!node)
    return;

  for (i = 0; i < level; i++)
    fprintf(stderr, "  ");

  fprintf(stderr, "AST( ");

  switch (node->type) {
  default:
    fprintf(stderr, "AST_UNKNOWN,");
    break;
  }

  if (node->symbol)
    fprintf(stderr, ", %s)\n", node->symbol->text);
  else
    fprintf(stderr, "NULL )\n");

  for (i = 0; i < MAX_SONS; ++i)
    astPrint(level + 1, node->son[i]);
}
