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
  case AST_SYMBOL:
    fprintf(stderr, "AST_SYMBOL, ");
    break;
  case AST_ADD:
    fprintf(stderr, "AST_ADD, ");
    break;
  case AST_SUB:
    fprintf(stderr, "AST_SUB, ");
    break;
  case AST_MUL:
    fprintf(stderr, "AST_MUL, ");
    break;
  case AST_DIV:
    fprintf(stderr, "AST_DIV, ");
    break;
  case AST_LESS:
    fprintf(stderr, "AST_LESS, ");
    break;
  case AST_GREATER:
    fprintf(stderr, "AST_GREATER, ");
    break;
  case AST_LE:
    fprintf(stderr, "AST_LE, ");
    break;
  case AST_GE:
    fprintf(stderr, "AST_GE, ");
    break;
  case AST_EQ:
    fprintf(stderr, "AST_EQ, ");
    break;
  case AST_DIF:
    fprintf(stderr, "AST_DIF, ");
    break;
  case AST_AND:
    fprintf(stderr, "AST_AND, ");
    break;
  case AST_OR:
    fprintf(stderr, "AST_OR, ");
    break;
  case AST_NOT:
    fprintf(stderr, "AST_NOT, ");
    break;
case AST_VECTORD:
    fprintf(stderr, "AST_VECTORD, ");
    break;
case AST_VECTORD2:
    fprintf(stderr, "AST_VECTORD2, ");
    break;
  case AST_LIST:
    fprintf(stderr, "AST_LIST, ");
    break;
  case AST_GLOBAL_DECL:
    fprintf(stderr, "AST_GLOBAL_DECL, ");
    break;
  case AST_LIST_CODE:
    fprintf(stderr, "AST_LIST_CODE, ");
    break;
  case AST_DECL:
    fprintf(stderr, "AST_DECL, ");
    break;
  case AST_TYPE:
    fprintf(stderr, "AST_TYPE, ");
    break;
  case AST_FUNC_DECL:
    fprintf(stderr, "AST_FUNC_DECL, ");
    break;
  case AST_FUNC_IMPL:
    fprintf(stderr, "AST_FUNC_IMPL, ");
    break;
  case AST_FUNC_CALL:
    fprintf(stderr, "AST_FUNC_CALL, ");
    break;
  case AST_ARG_LIST:
    fprintf(stderr, "AST_ARG_LIST, ");
    break;
  case AST_ARG_REST:
    fprintf(stderr, "AST_ARG_REST, ");
    break;
  case AST_PARAM_LIST:
    fprintf(stderr, "AST_PARAM_LIST, ");
    break;
  case AST_PARAM_REST:
    fprintf(stderr, "AST_PARAM_REST, ");
    break;
  case AST_PARAM:
    fprintf(stderr, "AST_PARAM, ");
    break;
  case AST_VECTOR_PARAMS:
    fprintf(stderr, "AST_VECTOR_PARAMS, ");
    break;
  case AST_VALUE:
    fprintf(stderr, "AST_VALUE, ");
    break;
  case AST_BLOCK:
    fprintf(stderr, "AST_BLOCK, ");
    break;
  case AST_LIST_CMD:
    fprintf(stderr, "AST_LIST_CMD, ");
    break;
  case AST_CMD:
    fprintf(stderr, "AST_CMD, ");
    break;
  case AST_ATTRIBUTE:

    fprintf(stderr, "AST_ATTRIBUTE, ");
    break;
  case AST_IF:
    fprintf(stderr, "AST_IF, ");
    break;
  case AST_WHILE:
    fprintf(stderr, "AST_WHILE, ");
    break;
  case AST_PRINT:
    fprintf(stderr, "AST_PRINT, ");
    break;
  case AST_RETURN:
    fprintf(stderr, "AST_RETURN, ");
    break;
  case AST_INPUT:
    fprintf(stderr, "AST_INPUT, ");
    break;

  // default:
  //   fprintf(stderr, "AST_ERROR,");
  //   break;
  }

  if (node->symbol)
    fprintf(stderr, ", %s)\n", node->symbol->text);
  else
    fprintf(stderr, "\n");

  for (i = 0; i < MAX_SONS; ++i)
    astPrint(level + 1, node->son[i]);
}
