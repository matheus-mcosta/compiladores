#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

// Matheus de Moraes Costa 00297121

#include "ast.h"

int checkSemantic(AST_NODE *node);
void setIdentifierDatatype(AST_NODE *node);
void setNodeDatatype(AST_NODE *node);
void checkDeclaration();
void checkUse(AST_NODE *node);
int checkVecElements(AST_NODE *node, int datatype);
int countVecElements(AST_NODE *node);
int checkVecSize(AST_NODE *node);
int isCompatible(int type1, int type2);
int isInt(int type);
int isComparison(int type);
int isArithmetic(int type);
int isLogical(int type);
int convertDatatypes(int type1, int type2);
void checkFunctionCall(AST_NODE *node);
AST_NODE *getFunctionDeclaration(char *name, AST_NODE *node);
int checkNumArgs(AST_NODE *node, AST_NODE *decl);
int getArgsCount(AST_NODE *node);
void compareArgs(AST_NODE *node, AST_NODE *decl);
void checkReturn(AST_NODE *node);
void checkReturnTypes(AST_NODE *node, int datatype);

#endif
