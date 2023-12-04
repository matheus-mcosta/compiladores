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
#define AST_LE 8
#define AST_GE 9
#define AST_EQ 10
#define AST_DIF 11
#define AST_AND 12
#define AST_OR 13
#define AST_NOT 14
#define AST_VECTORD 15
#define AST_VECTORD2 16
#define AST_LIST 17
#define AST_GLOBAL_DECL 18
#define AST_LIST_CODE 19
#define AST_DECL 20
#define AST_TYPE 21
#define AST_FUNC_DECL 22
#define AST_FUNC_IMPL 23
#define AST_FUNC_CALL 24
#define AST_ARG_LIST 25
#define AST_ARG_REST 26
#define AST_PARAM_LIST 27
#define AST_PARAM_REST 28
#define AST_PARAM 29
#define AST_VECTOR_PARAMS 30
#define AST_VALUE 31
#define AST_BLOCK 32
#define AST_LIST_CMD 33
#define AST_CMD 34
#define AST_ATTRIBUTE 35
#define AST_ATTRIB_VEC 36
#define AST_IF 37
#define AST_IF_ELSE 38
#define AST_WHILE 38
#define AST_PRINT 39
#define AST_RETURN 40
#define AST_INPUT 41
#define AST_PAREN 42
#define AST_INT 43
#define AST_FLOAT 44
#define AST_CHAR 45
#define AST_VECTOR 46

typedef struct ast_node {
  int type;
  HASH_NODE *symbol;
  struct ast_node *son[MAX_SONS];
} AST_NODE;

AST_NODE *astCreate(int type, HASH_NODE *symbol, AST_NODE *s0, AST_NODE *s1,
                    AST_NODE *s2, AST_NODE *s3);
void astPrint(int level, AST_NODE *node);

#endif
