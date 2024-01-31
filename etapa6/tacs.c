// Matheus de Moraes Costa 00297121
// Codigo baseado na implementação do professor

#include "tacs.h"
#include "ast.h"
#include "hash.h"
#include <stdlib.h>

TAC *tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2) {
  TAC *newtac = (TAC *)calloc(1, sizeof(TAC));
  newtac->type = type;
  newtac->res = res;
  newtac->op1 = op1;
  newtac->op2 = op2;
  newtac->prev = 0;
  newtac->next = 0;
  return newtac;
}

TAC *tacJoin(TAC *l1, TAC *l2) {
  TAC *tac;
  if (!l1)
    return l2;
  if (!l2)
    return l1;

  for (tac = l2; tac->prev; tac = tac->prev)
    ;

  tac->prev = l1;
  return l2;
}

TAC *tacReverse(TAC *l) {
  TAC *tac;
  for (tac = l; tac->prev; tac = tac->prev) {
    tac->prev->next = tac;
  }
  return tac;
}

void printAllTacs(TAC *l) {
  TAC *tac;
  for (tac = l; tac; tac = tac->next) {
    printTac(tac);
  }
}

void printTac(TAC *l) {

  if (l->type == TAC_SYMBOL)
    return;

  fprintf(stderr, "TAC(");

  switch (l->type) {
  case TAC_MOVE:
    fprintf(stderr, "MOVE(");
    break;
  case TAC_ADD:
    fprintf(stderr, "ADD(");
    break;
  case TAC_SUB:
    fprintf(stderr, "SUB(");
    break;
  case TAC_MUL:
    fprintf(stderr, "MUL(");
    break;
  case TAC_DIV:
    fprintf(stderr, "DIV(");
    break;
  case TAC_GREAT:
    fprintf(stderr, "GREAT(");
    break;
  case TAC_LESS:
    fprintf(stderr, "LESS(");
    break;
  case TAC_GE:
    fprintf(stderr, "GE(");
    break;
  case TAC_LE:
    fprintf(stderr, "LE(");
    break;
  case TAC_EQ:
    fprintf(stderr, "EQ(");
    break;
  case TAC_DIF:
    fprintf(stderr, "DIF(");
    break;
  case TAC_AND:
    fprintf(stderr, "AND(");
    break;
  case TAC_OR:
    fprintf(stderr, "OR(");
    break;
  case TAC_NOT:
    fprintf(stderr, "NOT(");
    break;
  case TAC_LABEL:
    fprintf(stderr, "LABEL(");
    break;
  case TAC_BEGINFUN:
    fprintf(stderr, "BEGINFUN(");
    break;
  case TAC_ARGPUSH:
    fprintf(stderr, "ARGPUSH(");
    break;
  case TAC_ENDFUN:
    fprintf(stderr, "ENDFUN(");
    break;
  case TAC_IFZ:
    fprintf(stderr, "IFZ(");
    break;
  case TAC_JUMP:
    fprintf(stderr, "JUMP(");
    break;
  case TAC_CALL:
    fprintf(stderr, "CALL(");
    break;
  case TAC_ARG:
    fprintf(stderr, "ARG(");
    break;
  case TAC_RET:
    fprintf(stderr, "RET(");
    break;
  case TAC_PRINT:
    fprintf(stderr, "PRINT(");
    break;
  case TAC_READ:
    fprintf(stderr, "READ(");
    break;
  case TAC_VECATTR:
    fprintf(stderr, "VECATTR(");
    break;
  case TAC_VEC:
    fprintf(stderr, "VEC(");
    break;
  case TAC_PARAM:
    fprintf(stderr, "PARAM(");
    break;
  default:
    fprintf(stderr, "TAC UNKNOWN(");
    break;
  }

  if (l->res)
    fprintf(stderr, "%s, ", l->res->text);
  else
    fprintf(stderr, "0, ");
  if (l->op1)
    fprintf(stderr, "%s, ", l->op1->text);
  else
    fprintf(stderr, "0, ");
  if (l->op2)
    fprintf(stderr, "%s", l->op2->text);
  else
    fprintf(stderr, "0");

  fprintf(stderr, "))\n");
}

TAC *generateCode(AST_NODE *node, HASH_NODE *currentLabel) {
  if (!node) {
    return 0;
  }

  TAC *code[MAX_SONS];
  if (node->type == AST_WHILE) {
    currentLabel = makeLabel();
  }

  for (int i = 0; i < MAX_SONS; i++) {
    code[i] = generateCode(node->son[i], currentLabel);
  }

  switch (node->type) {
  // OPS
  case AST_SYMBOL:
    return tacCreate(TAC_SYMBOL, node->symbol, 0, 0);
  case AST_ADD:
    return createBinOp(TAC_ADD, code, node->datatype);
  case AST_SUB:
    return createBinOp(TAC_SUB, code, node->datatype);
  case AST_MUL:
    return createBinOp(TAC_MUL, code, node->datatype);
  case AST_DIV:
    return createBinOp(TAC_DIV, code, node->datatype);
  case AST_GREATER:
    return createBinOp(TAC_GREAT, code, node->datatype);
  case AST_LESS:
    return createBinOp(TAC_LESS, code, node->datatype);
  case AST_EQ:
    return createBinOp(TAC_EQ, code, node->datatype);
  case AST_GE:
    return createBinOp(TAC_GE, code, node->datatype);
  case AST_LE:
    return createBinOp(TAC_LE, code, node->datatype);
  case AST_DIF:
    return createBinOp(TAC_DIF, code, node->datatype);
  case AST_AND:
    return createBinOp(TAC_AND, code, node->datatype);
  case AST_OR:
    return createBinOp(TAC_OR, code, node->datatype);
  case AST_NOT:
    return createBinOp(TAC_NOT, code, node->datatype);
  // CMDS
  // case AST_DECL:
  //   return tacJoin(code[0], tacCreate(TAC_MOVE, node->symbol,
  //                                     code[1] ? code[1]->res : 0, 0));
  case AST_ATTRIBUTE:
    return tacJoin(code[0], tacCreate(TAC_MOVE, node->symbol,
                                      code[0] ? code[0]->res : 0, 0));
  // case AST_VECTORD2:
  //   return tacJoin(tacJoin(code[0], code[1]),
  //                  tacCreate(TAC_VECATTR, node->symbol,
  //                            code[2] ? code[2]->res : 0,
  //                            code[1] ? code[1]->res : 0));
  case AST_ATTRIB_VEC:
    return tacJoin(tacJoin(code[0], code[1]),
                   tacCreate(TAC_VECATTR, node->symbol,
                             code[1] ? code[1]->res : 0,
                             code[0] ? code[0]->res : 0));
  case AST_INPUT:
    return tacCreate(TAC_READ, makeTemp(node->datatype), node->symbol, 0);
  case AST_PRINT:
    return tacJoin(code[0],
                   tacCreate(TAC_PRINT, code[0] ? code[0]->res : 0, makeString(), 0));
  case AST_RETURN:
    return tacJoin(code[0],
                   tacCreate(TAC_RET, code[0] ? code[0]->res : 0, 0, 0));
  case AST_IF_ELSE:
  case AST_IF:
    return createIf(code);
  case AST_WHILE:
    return createWhile(code, currentLabel);

  case AST_FUNC_CALL:
    return tacJoin(code[0], tacCreate(TAC_CALL, makeTemp(node->datatype),
                                      node->symbol, 0));
  case AST_ARG_LIST:
  case AST_ARG_REST:
    return tacJoin(
        code[1],
        tacJoin(code[0], tacCreate(TAC_ARG, code[0] ? code[0]->res : 0, 0, 0)));
  case AST_VECTOR:
    return tacJoin(code[0],
                   tacCreate(TAC_VEC, makeTemp(node->datatype), node->symbol,
                             code[0] ? code[0]->res : 0));

  case AST_FUNC_IMPL:
    return createFunc(tacCreate(TAC_SYMBOL, node->symbol, 0, 0), code[0],
                      code[1]);
    // case AST_PARAM:
    //   return tacJoin(tacCreate(TAC_PARAM, node->symbol, 0, 0), code[1]);

  default:
    return tacJoin(tacJoin(tacJoin(code[0], code[1]), code[2]), code[3]);
  }
}

TAC *createBinOp(int type, TAC *son[], int datatype) {
  HASH_NODE *op1;
  HASH_NODE *op2;

  if (son[0]) {
    op1 = son[0]->res;
  } else {
    op1 = 0;
  }

  if (son[1]) {
    op2 = son[1]->res;
  } else {
    op2 = 0;
  }

  return tacJoin(
      son[0], tacJoin(son[1], tacCreate(type, makeTemp(datatype), op1, op2)));
}

TAC *createIf(TAC *son[]) {

  HASH_NODE *ifLabel = makeLabel();
  TAC *tacIf =
      tacJoin(son[0], tacCreate(TAC_IFZ, ifLabel, son[0] ? son[0]->res : 0, 0));
  TAC *tacIfLabel = tacCreate(TAC_LABEL, ifLabel, 0, 0);

  if (son[2]) {
    HASH_NODE *elseLabel = makeLabel();
    TAC *tacElseLabel = tacCreate(TAC_LABEL, elseLabel, 0, 0);
    TAC *tacJumpElse = tacCreate(TAC_JUMP, elseLabel, 0, 0);

    return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacIf, son[1]), tacJumpElse),
                                   tacIfLabel),
                           son[2]),
                   tacElseLabel);

  } else {
    return tacJoin(tacJoin(tacIf, son[1]), tacIfLabel);
  }
}

TAC *createWhile(TAC *son[], HASH_NODE *label) {

  HASH_NODE *jumpLabel = makeLabel();

  TAC *tacWhile = tacCreate(TAC_IFZ, jumpLabel, son[0] ? son[0]->res : 0, 0);
  TAC *tacWhileLabel = tacCreate(TAC_LABEL, label, 0, 0);
  TAC *tacJump = tacCreate(TAC_JUMP, label, 0, 0);
  TAC *tacJumpLabel = tacCreate(TAC_LABEL, jumpLabel, 0, 0);

  return tacJoin(
      tacJoin(
          tacJoin(tacJoin(tacJoin(tacWhileLabel, son[0]), tacWhile), son[1]),
          tacJump),
      tacJumpLabel);
}

TAC *createFunc(TAC *symbol, TAC *params, TAC *code) {
  return tacJoin(
      tacJoin(tacJoin(tacCreate(TAC_BEGINFUN, symbol->res, 0, 0), params),
              code),
      tacCreate(TAC_ENDFUN, symbol->res, 0, 0));
}
