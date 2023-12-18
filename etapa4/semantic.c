// Matheus de Moraes Costa 00297121

#include "semantic.h"
#include "ast.h"
#include "hash.h"

int semanticErrors = 0;
AST_NODE *ROOT;

int checkSemantic(AST_NODE *root) {
  ROOT = root;
  setIdentifierDatatype(root);
  setNodeDatatype(root);
  checkDeclaration();
  checkUse(root);
  checkReturn(root);

  return semanticErrors;
}

void setIdentifierDatatype(AST_NODE *node) {
  if (node == NULL)
    return;

  switch (node->type) {
  case AST_SYMBOL:
    if (node->symbol->type != SYMBOL_IDENTIFIER) {
      fprintf(stderr, "Semantic error: symbol %s redeclaration at line %d\n",
              node->symbol->text, node->lineNumber);
      semanticErrors++;
    } else {
      node->symbol->type = SYMBOL_SCALAR;
      if (node->son[0]->type == AST_INT)
        node->symbol->datatype = DATATYPE_INT;
      else if (node->son[0]->type == AST_CHAR)
        node->symbol->datatype = DATATYPE_CHAR;
      else if (node->son[0]->type == AST_FLOAT)
        node->symbol->datatype = DATATYPE_REAL;
    }
    if (!isCompatible(node->symbol->datatype, node->son[1]->symbol->datatype)) {
      fprintf(stderr, "Semantic error: incompatible types at line %d\n",
              node->lineNumber);
      semanticErrors++;
    }
    break;
  case AST_VECTORD2:
    if (node->symbol->type != SYMBOL_IDENTIFIER) {
      fprintf(stderr, "Semantic error: Vector %s redeclaration at line %d\n",
              node->symbol->text, node->lineNumber);
      semanticErrors++;
    } else {
      node->symbol->type = SYMBOL_VECTOR;
      if (node->son[0]->type == AST_INT)
        node->symbol->datatype = DATATYPE_INT;
      else if (node->son[0]->type == AST_CHAR)
        node->symbol->datatype = DATATYPE_CHAR;
      else if (node->son[0]->type == AST_FLOAT)
        node->symbol->datatype = DATATYPE_REAL;
    }

    if (!checkVecElements(node->son[2], node->symbol->datatype)) {
      fprintf(stderr, "Semantic error: incompatible vector types at line %d\n",
              node->lineNumber);
      semanticErrors++;
    }
    break;
  case AST_FUNC_DECL:
    if (node->symbol->type != SYMBOL_IDENTIFIER) {
      fprintf(stderr, "Semantic error: Function %s redeclaration at line %d\n",
              node->symbol->text, node->lineNumber);
      semanticErrors++;
    } else {
      node->symbol->type = SYMBOL_FUNCTION;
      if (node->son[0]->type == AST_INT)
        node->symbol->datatype = DATATYPE_INT;
      else if (node->son[0]->type == AST_CHAR)
        node->symbol->datatype = DATATYPE_CHAR;
      else if (node->son[0]->type == AST_FLOAT)
        node->symbol->datatype = DATATYPE_REAL;
    }
    break;
  case AST_PARAM:
    if (node->symbol->type != SYMBOL_IDENTIFIER) {
      fprintf(stderr, "Semantic error: Parameter %s redeclaration at line %d\n",
              node->symbol->text, node->lineNumber);
      semanticErrors++;
    } else {
      node->symbol->type = SYMBOL_PARAM;
      if (node->son[0]->type == AST_INT)
        node->symbol->datatype = DATATYPE_INT;
      else if (node->son[0]->type == AST_CHAR)
        node->symbol->datatype = DATATYPE_CHAR;
      else if (node->son[0]->type == AST_FLOAT)
        node->symbol->datatype = DATATYPE_REAL;
    }
    break;
  default:
    break;
  }

  for (int i = 0; i < MAX_SONS; i++) {
    setIdentifierDatatype(node->son[i]);
  }
}

void setNodeDatatype(AST_NODE *node) {
  if (node == NULL)
    return;

  for (int i = 0; i < MAX_SONS; i++) {
    setNodeDatatype(node->son[i]);
  }

  if (node->type == AST_SYMBOL) {
    if (node->symbol->type == SYMBOL_VECTOR ||
        node->symbol->type == SYMBOL_FUNCTION) {
      fprintf(stderr, "Semantic error: symbol %s is not a scalar at line %d\n",
              node->symbol->text, node->lineNumber);
      semanticErrors++;
    }
    node->datatype = node->son[1]->symbol->datatype;
  } else if (node->type == AST_FUNC_CALL || node->type == AST_VECTOR) {
    node->datatype = node->symbol->datatype;
  } else if (node->type == AST_PAREN) {
    node->datatype = node->son[0]->datatype;
  } else if (isArithmetic(node->type)) {
    AST_NODE *left = node->son[0];
    AST_NODE *right = node->son[1];
    if (!isCompatible(left->datatype, right->datatype) ||
        left->datatype == DATATYPE_BOOL || right->datatype == DATATYPE_BOOL) {
      fprintf(stderr,
              "Semantic error: Arithmetic with incompatible types at line %d\n",
              node->lineNumber);
      semanticErrors++;
    }
    node->datatype = convertDatatypes(left->datatype, right->datatype);
  } else if (isComparison(node->type)) {
    if (!isNumeric(node->son[0]->datatype) ||
        !isNumeric(node->son[1]->datatype)) {
      fprintf(stderr,
              "Semantic error: Comparison operation with incompatible types at "
              "line %d\n",
              node->lineNumber);
      semanticErrors++;
    }
    node->datatype = DATATYPE_BOOL;
  } else if (isLogical(node->type)) {
    if (node->type == AST_NOT) {
      if (node->son[0]->datatype != DATATYPE_BOOL) {
        fprintf(
            stderr,
            "Semantic error: Logical operation incompatible types at line %d\n",
            node->lineNumber);
        semanticErrors++;
      }
    } else if (node->son[0]->datatype != DATATYPE_BOOL ||
               node->son[1]->datatype != DATATYPE_BOOL) {
      fprintf(
          stderr,
          "Semantic error: Logical operation incompatible types at line %d\n",
          node->lineNumber);
      semanticErrors++;
    }
    node->datatype = DATATYPE_BOOL;
  }
}

void checkDeclaration() {
  int numUndeclared = hashCheckUndeclared();
  semanticErrors += numUndeclared;
}

void checkUse(AST_NODE *node) {}

int checkVecElements(AST_NODE *node, int type) {}

int isCompatible(int type1, int type2) {
  return (type1 == type2) || (isInt(type1) && isInt(type2));
}

int isInt(int type) { return (type == DATATYPE_INT || type == DATATYPE_CHAR); }

int isNumeric(int type) {
  return (type == DATATYPE_INT || type == DATATYPE_CHAR ||
          type == DATATYPE_REAL);
}

int isComparison(int type) {
  return (type == AST_LESS || type == AST_GREATER || type == AST_LE ||
          type == AST_GE || type == AST_EQ || type == AST_DIF);
}

int isArithmetic(int type) {
  return (type == AST_ADD || type == AST_SUB || type == AST_MUL ||
          type == AST_DIV);
}

int isLogical(int type) {
  return (type == AST_AND || type == AST_OR || type == AST_NOT);
}

int convertDatatypes(int type1, int type2) {
  return type1 > type2 ? type1 : type2;
}

void checkFunctionCall(AST_NODE *node) {}

AST_NODE *getFunctionDecl(AST_NODE *node) { return NULL; }

void checkPrint(AST_NODE *node) {}

int checkArgs(AST_NODE *node, AST_NODE *decl) { return 0; }

int getArgsCount(AST_NODE *node) { return 0; }

void compareArgs(AST_NODE *node, AST_NODE *decl) {}

void checkReturnTypes(AST_NODE *node, int type) {
  if (node == NULL)
    return;

  if (node->type == AST_RETURN) {
    if (!isCompatible(node->son[0]->datatype, type)) {
      fprintf(stderr, "Semantic error: return type at line %d\n",
              node->lineNumber);
      semanticErrors++;
    }
  }
  for (int i = 0; i < MAX_SONS; i++) {
    if (node->son[i] == NULL) {
      break;
    }
    checkReturnTypes(node->son[i], type);
  }
}

void checkReturn(AST_NODE *node) {
  if (node != NULL && node->type == AST_FUNC_DECL) {
    checkReturnTypes(node, node->symbol->datatype);
  }
  for (int i = 0; i < MAX_SONS; i++) {
    if (node->son[i] == NULL) {
      break;
    }
    checkReturn(node->son[i]);
  }
}
