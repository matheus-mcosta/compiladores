// Matheus de Moraes Costa 00297121
// Codigo baseado na implementação do professor

#ifndef AST_HEADER
#define AST_HEADER

#include "hash.h"

#define MAX_SONS 4

#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_SUB 3
#define AST_MUL 4
#define AST_DIV 5
#define AST_LESS 6
#define AST_GREATER 7

typedef struct ast_node {
  int type;
  HASH_NODE *symbol;
  struct ast_node *son[MAX_SONS];
} AST_NODE;

AST_NODE *astCreate(int type, HASH_NODE *symbol, AST_NODE *s0, AST_NODE *s1,
                    AST_NODE *s2, AST_NODE *s3);
void astPrint(int level, AST_NODE *node);

#endif
