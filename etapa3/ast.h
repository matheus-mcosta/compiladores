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
#define AST_FUNC_DECL 21
#define AST_FUNC_IMPL 22
#define AST_FUNC_CALL 23
#define AST_ARG_LIST 24
#define AST_ARG_REST 25
#define AST_PARAM_LIST 26
#define AST_PARAM_REST 27
#define AST_PARAM 28
#define AST_VECTOR_PARAMS 29
#define AST_BLOCK 30
#define AST_LIST_CMD 31
#define AST_ATTRIBUTE 32
#define AST_ATTRIB_VEC 33
#define AST_IF 34
#define AST_IF_ELSE 35
#define AST_WHILE 36
#define AST_PRINT 37
#define AST_RETURN 38
#define AST_INPUT 39
#define AST_PAREN 40
#define AST_INT 41
#define AST_FLOAT 42
#define AST_CHAR 43
#define AST_VECTOR 44
#define AST_SEMI 45

typedef struct ast_node {
  int type;
  HASH_NODE *symbol;
  struct ast_node *son[MAX_SONS];
} AST_NODE;

AST_NODE *astCreate(int type, HASH_NODE *symbol, AST_NODE *s0, AST_NODE *s1,
                    AST_NODE *s2, AST_NODE *s3);
void astPrint(int level, AST_NODE *node);

void astDecompile(AST_NODE *node, FILE *out);

#endif
