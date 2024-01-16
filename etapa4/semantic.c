// Matheus de Moraes Costa 00297121

#include "semantic.h"
#include "ast.h"
#include "hash.h"
#include <stdio.h>

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
  case AST_DECL:
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
  case AST_VECTORD:
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
    checkVecSize(node);

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
    node->datatype = node->symbol->datatype;
  } else if (node->type == AST_FUNC_CALL) {
    node->datatype = node->symbol->datatype;
  } else if (node->type == AST_VECTOR) {

    if (!isInt(node->son[0]->datatype)) {
      fprintf(stderr, "Semantic error: Index must be integer at line %d\n",
              node->lineNumber);
      semanticErrors++;
    }
    node->datatype = node->symbol->datatype;

  } else if (node->type == AST_INPUT) {
    switch (node->son[0]->type) {
    case AST_INT:
      node->datatype = DATATYPE_INT;
      break;
    case AST_CHAR:
      node->datatype = DATATYPE_CHAR;
      break;
    case AST_FLOAT:
      node->datatype = DATATYPE_REAL;
    default:
      break;
    }

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
    if (!isCompatible(node->son[0]->datatype, node->son[1]->datatype)) {
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

void checkUse(AST_NODE *node) {
  if (node == NULL)
    return;

  switch (node->type) {
  case AST_ATTRIBUTE:
    if (node->symbol->type != SYMBOL_SCALAR &&
        node->symbol->type != SYMBOL_PARAM) { // verificar
      fprintf(stderr, "Semantic error: symbol %s is not a scalar at line %d\n",
              node->symbol->text, node->lineNumber);
      semanticErrors++;
    }

    if (node->son[0]->type == AST_VECTOR) {
      if (node->son[0]->symbol->type != SYMBOL_VECTOR) {
        fprintf(stderr,
                "Semantic error: symbol %s is not a vector for indexing at "
                "line %d\n",
                node->son[0]->symbol->text, node->lineNumber);
        semanticErrors++;
      }
      if (!isCompatible(node->symbol->datatype, node->son[0]->datatype)) {
        fprintf(stderr,
                "Semantic error: incompatible vector types at line %d\n",
                node->lineNumber);
        semanticErrors++;
      }
      if (!isInt(node->son[0]->son[0]->datatype)) {
        fprintf(stderr, "Semantic error: Index must be integer at line %d\n",
                node->lineNumber);
        semanticErrors++;
      }
    }

    if (!isCompatible(node->symbol->datatype, node->son[0]->datatype)) {
      fprintf(stderr,
              "Semantic error: incompatible attribute types at line %d\n",
              node->lineNumber);
      semanticErrors++;
    }
    break;
  case AST_ATTRIB_VEC:
    if (node->symbol->type != SYMBOL_VECTOR) {
      fprintf(
          stderr,
          "Semantic error: symbol %s is not a vector for indexing at line %d\n",
          node->symbol->text, node->lineNumber);
      semanticErrors++;
    }
    if (!isCompatible(node->symbol->datatype, node->son[1]->datatype)) {
      fprintf(stderr, "Semantic error: incompatible vector types at line %d\n",
              node->lineNumber);
      semanticErrors++;
    }
    if (!isInt(node->son[0]->datatype)) {
      fprintf(stderr, "Semantic error: Index must be integer at line %d\n",
              node->lineNumber);
      semanticErrors++;
    }
    break;
  case AST_FUNC_CALL:
    checkFunctionCall(node);
    break;
    break;
  case AST_IF:
  case AST_IF_ELSE:
  case AST_WHILE:
    if (node->son[0]->datatype != DATATYPE_BOOL) {
      fprintf(stderr, "Semantic error: expression must be boolean at line %d\n",
              node->lineNumber);
      semanticErrors++;
    }
    break;

  case AST_PRINT:
    if (node->son[0]->type == AST_VECTOR) {
      if (!isInt(node->son[0]->son[0]->datatype)) {
        fprintf(stderr, "Semantic error: Index must be integer at line %d\n",
                node->lineNumber);
        semanticErrors++;
      }
    }

  default:
    break;
  }
  for (int i = 0; i < MAX_SONS; i++) {
    checkUse(node->son[i]);
  }
}

int checkVecElements(AST_NODE *node, int type) {
  if (node != NULL) {
    if (!isCompatible(node->son[0]->symbol->datatype, type))
      return 0;
    if (node->son[1] != NULL)
      return checkVecElements(node->son[1], type);
  }
  return 1;
}

int countVecElements(AST_NODE *node) {
  if (node != NULL) {
    int elements = 0;
    if (node->son[1] != NULL)
      elements = countVecElements(node->son[1]);
    return elements + 1;
  }
  return 0;
}

int checkVecSize(AST_NODE *node) {
  if (node != NULL) {
    int size = atoi(node->son[1]->symbol->text);
    int elements = countVecElements(node->son[2]);
    if (size != elements) {
      fprintf(stderr,
              "Semantic error: vector %s declared with size %d, but has %d "
              "elements at line %d\n",
              node->symbol->text, size, elements, node->lineNumber);
      semanticErrors++;
      return 0;
    }
  }

  return 1;
}

int isCompatible(int type1, int type2) {
  return (type1 == type2) || (isInt(type1) && isInt(type2));
}

int isInt(int type) { return (type == DATATYPE_INT || type == DATATYPE_CHAR); }

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

void checkFunctionCall(AST_NODE *node) {
  AST_NODE *decl = getFunctionDeclaration(node->symbol->text, ROOT);
  if (decl == NULL) {
    fprintf(stderr, "Semantic error: function %s undeclared at line %d\n",
            node->symbol->text, node->lineNumber);
    semanticErrors++;
    return;
  } else if (checkNumArgs(node, decl)) {
    compareArgs(node->son[0], decl->son[1]);
  }
}

AST_NODE *getFunctionDeclaration(char *name, AST_NODE *node) {
  if (node->symbol != NULL && node->type == AST_FUNC_DECL &&
      strcmp(node->symbol->text, name) == 0) {
    return node;
  }

  for (int i = 0; i < MAX_SONS; i++) {
    if (node->son[i] == NULL) {
      return NULL;
    }
    AST_NODE *res = getFunctionDeclaration(name, node->son[i]);
    if (res != NULL)
      return res;
  }
  return NULL;
}

int checkNumArgs(AST_NODE *node, AST_NODE *decl) {
  int called = getArgsCount(node->son[0]);
  int declared = getArgsCount(decl->son[1]);
  if (called != declared) {
    fprintf(stderr,
            "Semantic error: function %s called with %d arguments, but "
            "declared with %d at line %d\n",
            node->symbol->text, called, declared, node->lineNumber);
    semanticErrors++;
    return 0;
  }
  return 1;
}

int getArgsCount(AST_NODE *node) {

  if (node == NULL)
    return 0;
  if (node->son[1] != NULL)
    return 1 + getArgsCount(node->son[1]);
  else
    return 1;
}

void compareArgs(AST_NODE *node, AST_NODE *decl) {
  if (node == NULL)
    return;
  if (node->son[0] != NULL) {
    if (!isCompatible(node->son[0]->datatype, decl->son[0]->symbol->datatype)) {
      fprintf(stderr,
              "Semantic error: incompatible argument types at line %d\n",
              node->lineNumber);
      semanticErrors++;
    }
    if (node->son[0]->type == AST_SYMBOL) {
      if (node->son[0]->symbol->type == SYMBOL_VECTOR) {
        fprintf(stderr,
                "Semantic error: vector %s cannot be passed as argument at "
                "line %d\n",
                node->son[0]->symbol->text, node->lineNumber);
        semanticErrors++;
      } else if (node->son[0]->symbol->type == SYMBOL_FUNCTION) {
        fprintf(stderr,
                "Semantic error: function %s cannot be passed as argument at "
                "line %d\n",
                node->son[0]->symbol->text, node->lineNumber);
        semanticErrors++;
      }
    }

    if (node->son[1] != NULL)
      compareArgs(node->son[1], decl->son[1]);
  }
}

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
  if (node != NULL && node->type == AST_FUNC_IMPL) {
    checkReturnTypes(node, node->symbol->datatype);
  }
  for (int i = 0; i < MAX_SONS; i++) {
    if (node->son[i] == NULL) {
      break;
    }
    checkReturn(node->son[i]);
  }
}
