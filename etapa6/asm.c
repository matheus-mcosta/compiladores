#include <stdio.h>
#include <stdlib.h>

#include "asm.h"
#include "ast.h"
#include "hash.h"
#include "tacs.h"

TAC *getFuncionCall(TAC *tac) {
  TAC *curr_tac;
  for (curr_tac = tac; curr_tac; curr_tac = curr_tac->next) {
    if (curr_tac->type == TAC_CALL) {
      return curr_tac;
    }
  }
  return NULL;
}

void writeDeclarations(FILE *fout, AST_NODE *ast) {
  if (!ast)
    return;

  int i;

  switch (ast->type) {

  case AST_DECL:
    if (ast->son[1]) {
      if (ast->son[1]->symbol->datatype == DATATYPE_INT) {
        fprintf(fout,
                "\n\t.globl _%s\n"
                "\t.data\n"
                "\t.align 2\n"
                "_%s:\n"
                "\t.word %s\n",
                ast->symbol->text, ast->symbol->text,
                ast->son[1]->symbol->text);
      } else if (ast->son[1]->symbol->datatype == DATATYPE_CHAR) {
        fprintf(fout,
                "\n\t.globl _%s\n"
                "\t.data\n"
                "\t.align 2\n"
                "_%s:\n"
                "\t.byte %d\n",
                ast->symbol->text, ast->symbol->text,
                ast->son[1]->symbol->text[1]);
      }
    }

    break;

  case AST_VECTORD:
    fprintf(fout,
            "\n\t.globl _%s\n"
            "\t.data\n"
            "\t.align 2\n"
            "_%s:\n",
            ast->symbol->text, ast->symbol->text);

    for (i = 0; i < atoi(ast->son[1]->symbol->text); i++) {
      fprintf(fout, "\t.word 0\n");
    }

    break;
  case AST_VECTORD2:
    fprintf(fout,
            "\n\t.globl _%s\n"
            "\t.data\n"
            "\t.align 2\n"
            "_%s:\n",
            ast->symbol->text, ast->symbol->text);
    for (AST_NODE *aux = ast->son[2]; aux; aux = aux->son[1]) {
      if (aux->son[0]->symbol->datatype == DATATYPE_INT) {
        fprintf(fout, "\t.word %s\n", aux->son[0]->symbol->text);
      } else if (aux->son[0]->symbol->datatype == DATATYPE_CHAR) {
        fprintf(fout, "\t.byte %d\n", aux->son[0]->symbol->text[1]);
      }
    }
    break;

  case AST_PARAM:
    fprintf(fout,
            "\n\t.globl _%s\n"
            "\t.data\n"
            "\t.align 2\n"
            "_%s:\n"
            "\t.word 0\n",
            ast->symbol->text, ast->symbol->text);
    break;
  }

  for (i = 0; i < MAX_SONS; ++i)
    writeDeclarations(fout, ast->son[i]);
}

void writeTemps(FILE *fout) {
  HASH_NODE **Table = getTable();
  for (int i = 0; i < HASHSIZE; i++) {
    for (HASH_NODE *aux = Table[i]; aux; aux = aux->next) {
      if (strncmp(aux->text, "_TTemP", 6) == 0) {

        fprintf(fout,
                "\n\t.globl _%s\n"
                "\t.data\n"
                "\t.align 2\n"
                "_%s:\n"
                "\t.word 0\n",
                aux->text, aux->text);
      }
    }
  }
}

void writeStrings(FILE *fout, TAC *tacs) {

  fprintf(fout, "\n\t.cstring\n"
                "\t.align 3\n"
                "lCReAD:\n"
                "\t.ascii \"%%d\\0\"\n");
  fprintf(fout, "\t.align 3\n"
                "lC0:\n"
                "\t.ascii \"%%d\\12\\0\"\n"
                "\t.text\n");
  TAC *curr_tac;

  for (curr_tac = tacs; curr_tac; curr_tac = curr_tac->next) {
    if (curr_tac->type == TAC_PRINT) {
      if (curr_tac->res->type == SYMBOL_LIT_STRING) {
        // Remove quotes
        char *new_str = curr_tac->res->text + 1;
        new_str[strlen(new_str) - 1] = '\0';

        fprintf(fout,
                "\n\t.cstring\n"
                "\t.align  3\n"
                "%s:\n"
                "\t.ascii \"%s\\0\"\n"
                "\t.text\n",
                curr_tac->op1->text, new_str);
      }
    }
  }
}

FILE *standardTwoVars(FILE *fout, TAC *tac, char *comment) {
  if (tac->op1->type == SYMBOL_LIT_INT) {
    fprintf(fout, "\n\tmov w1, %s ; %s\n", tac->op1->text, comment);
  } else if (tac->op1->type == SYMBOL_SCALAR) {
    fprintf(fout,
            "\n\tadrp x0, _%s@PAGE ; %s\n"
            "\tadd x0, x0, _%s@PAGEOFF\n"
            "\tldr w1, [x0]\n",
            tac->op1->text, comment, tac->op1->text);
  }
  if (tac->op2->type == SYMBOL_LIT_INT) {
    fprintf(fout, "\tmov w0, %s\n", tac->op2->text);
  } else if (tac->op2->type == SYMBOL_SCALAR) {
    fprintf(fout,
            "\tadrp x0, _%s@PAGE\n"
            "\tadd x0, x0, _%s@PAGEOFF\n"
            "\tldr w0, [x0]\n",
            tac->op2->text, tac->op2->text);
  }
  return fout;
}

void writeTACS(FILE *fout, TAC *tacs) {

  int arg_count = 0;
  TAC *curr_tac;

  for (curr_tac = tacs; curr_tac; curr_tac = curr_tac->next) {

    switch (curr_tac->type) {

    case TAC_BEGINFUN:
      fprintf(fout,
              "\n\t.text ;TAC_BEGINFUN\n"
              "\t.align 2\n"
              "\t.globl _%s\n"
              "_%s:\n"
              "FBEGIN_%s:\n"
              "\tstp\tx29, x30, [sp, -16]!\n"
              "\tmov\tx29, sp\n",
              curr_tac->res->text, curr_tac->res->text, curr_tac->res->text);
      break;

    case TAC_ENDFUN:
      fprintf(fout,
              "\n\tldp x29, x30, [sp], 16 ; TAC_ENDFUN\n"
              "\tret\n"
              "FEND2_%s:\n",
              curr_tac->res->text);
      break;

    case TAC_RET:
      if (curr_tac->res->type == SYMBOL_LIT_INT) {
        fprintf(fout,
                "\n\t mov w0, %s ; TAC_RET\n"
                "\tldp x29, x30, [sp], 16 \n"
                "\tret\n",
                curr_tac->res->text);
      } else if (curr_tac->res->type == SYMBOL_SCALAR) {
        /*
         *
          adrp	x0, _a@PAGE
          add	x0, x0, _a@PAGEOFF;momd
          ldr	w0, [x0]
         *
         * */
        fprintf(fout,
                "\n\tadrp x0, _%s@PAGE ; TAC_RET\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tldr w0, [x0]\n"
                "\tldp x29, x30, [sp], 16\n"
                "\tret\n",
                curr_tac->res->text, curr_tac->res->text);
      }
      break;

    case TAC_LABEL:
      fprintf(fout, "\n%s:\n", curr_tac->res->text);
      break;

    case TAC_JUMP:
      fprintf(fout, "\n\tb %s ; TAC_JUMP\n", curr_tac->res->text);
      break;

    case TAC_PRINT:

      if (curr_tac->res->datatype == DATATYPE_INT ||
          curr_tac->res->datatype == DATATYPE_CHAR) {
        fprintf(fout,
                "\n\tadrp x0, _%s@PAGE ; TAC_PRINT INT\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tldr w0, [x0]\n"
                "\tstr w0, [sp]\n"
                "\tadrp x0, lC0@PAGE\n"
                "\tadd x0, x0, lC0@PAGEOFF\n"
                "\tbl _printf\n",
                curr_tac->res->text, curr_tac->res->text);

      } else if (curr_tac->res->type == SYMBOL_LIT_STRING) {

        fprintf(fout,
                "\n\tadrp x0, %s@PAGE ; TAC_PRINT STRING\n"
                "\tadd x0, x0, %s@PAGEOFF\n"
                "\tbl _printf\n",
                curr_tac->op1->text, curr_tac->op1->text);
      }

      break;
    case TAC_READ:

      fprintf(fout,
              "\n \tadrp x0, _%s@PAGE ; TAC_READ\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr x0, [sp]\n"
              "\tadrp x0, lCReAD@PAGE\n"
              "\tadd x0, x0, lCReAD@PAGEOFF\n"
              "\tbl _scanf\n",
              curr_tac->res->text, curr_tac->res->text);
      break;

    case TAC_MOVE:

      if (curr_tac->op1->type == SYMBOL_LIT_INT) {
        fprintf(fout,
                "\n\tadrp x0, _%s@PAGE ; TAC_MOVE\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tmov w1, %s\n"
                "\tstr w1, [x0]\n",
                curr_tac->res->text, curr_tac->res->text, curr_tac->op1->text);
      } else if (curr_tac->op1->type == SYMBOL_SCALAR) {

        fprintf(fout,
                "\n\tadrp x0, _%s@PAGE ; TAC_MOVE\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tldr w1, [x0]\n"
                "\tadrp x0, _%s@PAGE\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tstr w1, [x0]\n",
                curr_tac->op1->text, curr_tac->op1->text, curr_tac->res->text,
                curr_tac->res->text);
      }
      break;

      // TODO: Add support for vector index expr

    case TAC_VEC: {

      if (curr_tac->op2->type == SYMBOL_LIT_INT) {
        int offset = atoi(curr_tac->op2->text) * 4;
        fprintf(fout,
                "\n\tadrp x0, _%s@PAGE ; TAC_MOVE\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tldr w1, [x0, %d]\n"
                "\tadrp x0, _%s@PAGE\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tstr w1, [x0]\n",
                curr_tac->op1->text, curr_tac->op1->text, offset,
                curr_tac->res->text, curr_tac->res->text);
      } else if (curr_tac->op2->type == SYMBOL_SCALAR) {
        // adrp	x0, _b@PAGE
        // add	x0, x0, _b@PAGEOFF;momd
        // ldr	w1, [x0]
        // adrp	x0, _v@PAGE
        // add	x0, x0, _v@PAGEOFF;momd
        // sxtw	x1, w1
        // ldr	w1, [x0, x1, lsl 2]
        // adrp	x0, _a@PAGE
        // add	x0, x0, _a@PAGEOFF;momd
        // str	w1, [x0]
        fprintf(fout,
                "\n\tadrp x0, _%s@PAGE ; TAC_MOVE\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tldr w1, [x0]\n"
                "\tadrp x0, _%s@PAGE\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tsxtw x1, w1\n"
                "\tldr w1, [x0, x1, lsl 2]\n"
                "\tadrp x0, _%s@PAGE\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tstr w1, [x0]\n",
                curr_tac->op2->text, curr_tac->op2->text, curr_tac->op1->text,
                curr_tac->op1->text, curr_tac->res->text, curr_tac->res->text);
      }
    }

    break;
    case TAC_VECATTR:

    {
      if (curr_tac->op2->type == SYMBOL_LIT_INT) {
        int offset = atoi(curr_tac->op2->text) * 4;

        if (curr_tac->op1->type == SYMBOL_LIT_INT) {
          fprintf(fout,
                  "\n\tadrp x0, _%s@PAGE ; TAC_VECATTR\n"
                  "\tadd x0, x0, _%s@PAGEOFF\n"
                  "\tmov w1, %s\n"
                  "\tstr w1, [x0, %d]\n",
                  curr_tac->res->text, curr_tac->res->text, curr_tac->op1->text,
                  offset);
        } else if (curr_tac->op1->type == SYMBOL_SCALAR) {

          fprintf(fout,
                  "\n\tadrp x0, _%s@PAGE ; TAC_VECATTR\n"
                  "\tadd x0, x0, _%s@PAGEOFF\n"
                  "\tldr w1, [x0]\n"
                  "\tadrp x0, _%s@PAGE\n"
                  "\tadd x0, x0, _%s@PAGEOFF\n"
                  "\tstr w1, [x0, %d]\n",
                  curr_tac->op1->text, curr_tac->op1->text, curr_tac->res->text,
                  curr_tac->res->text, offset);
        }
      } else if (curr_tac->op2->type == SYMBOL_SCALAR) {
        if (curr_tac->op1->type == SYMBOL_LIT_INT) {
          fprintf(fout,
                  "\n\tadrp x0, _%s@PAGE ; TAC_VECATTR\n"
                  "\tadd x0, x0, _%s@PAGEOFF\n"
                  "\tldr w1, [x0]\n"
                  "\tadrp x0, _%s@PAGE\n"
                  "\tadd x0, x0, _%s@PAGEOFF\n"
                  "\tsxtw x1, w1\n"
                  "\tmov w2, %s\n"
                  "\tstr w2, [x0, x1, lsl 2]\n",
                  curr_tac->op2->text, curr_tac->op2->text, curr_tac->res->text,
                  curr_tac->res->text, curr_tac->op1->text);
        } else if (curr_tac->op1->type == SYMBOL_SCALAR) {

          fprintf(fout,
                  "\n\tadrp x0, _%s@PAGE ; TAC_VECATTR\n"
                  "\tadd x0, x0, _%s@PAGEOFF\n"
                  "\tldr w1, [x0]\n"
                  "\tadrp x0, _%s@PAGE\n"
                  "\tadd x0, x0, _%s@PAGEOFF\n"
                  "\tldr w2, [x0]\n"
                  "\tadrp x0, _%s@PAGE\n"
                  "\tadd x0, x0, _%s@PAGEOFF\n"
                  "\tsxtw x1, w1\n"
                  "\tstr w2, [x0, x1, lsl 2]\n",
                  curr_tac->op2->text, curr_tac->op2->text, curr_tac->op1->text,
                  curr_tac->op1->text, curr_tac->res->text,
                  curr_tac->res->text);
        }
      }
    } break;
    case TAC_ADD:

      standardTwoVars(fout, curr_tac, "TAC_ADD");

      fprintf(fout,
              "\n\tadd w1, w1, w0\n"
              "\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr w1, [x0]\n",
              curr_tac->res->text, curr_tac->res->text);

      break;
    case TAC_SUB:
      standardTwoVars(fout, curr_tac, "TAC_SUB");
      fprintf(fout,
              "\n\tsub w1, w1, w0\n"
              "\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr w1, [x0]\n",
              curr_tac->res->text, curr_tac->res->text);

      break;

    case TAC_MUL:
      standardTwoVars(fout, curr_tac, "TAC_MUL");

      fprintf(fout,
              "\n\tmul w1, w1, w0\n"
              "\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr w1, [x0]\n",
              curr_tac->res->text, curr_tac->res->text);

      break;

    case TAC_DIV:
      standardTwoVars(fout, curr_tac, "TAC_DIV");
      fprintf(fout,
              "\n\tsdiv w1, w1, w0\n"
              "\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr w1, [x0]\n",
              curr_tac->res->text, curr_tac->res->text);
      break;

    case TAC_GREAT:
      standardTwoVars(fout, curr_tac, "TAC_GREAT");
      fprintf(fout,
              "\n\tcmp w1, w0\n"
              "\tcset w1, gt\n"
              "\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr w1, [x0]\n",
              curr_tac->res->text, curr_tac->res->text);
      break;

    case TAC_LESS:
      standardTwoVars(fout, curr_tac, "TAC_LESS");
      fprintf(fout,
              "\n\tcmp w1, w0\n"
              "\tcset w1, lt\n"
              "\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr w1, [x0]\n",
              curr_tac->res->text, curr_tac->res->text);
      break;

    case TAC_GE:
      standardTwoVars(fout, curr_tac, "TAC_GE");
      fprintf(fout,
              "\n\tcmp w1, w0\n"
              "\tcset w1, ge\n"
              "\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr w1, [x0]\n",
              curr_tac->res->text, curr_tac->res->text);
      break;

    case TAC_LE:
      standardTwoVars(fout, curr_tac, "TAC_LE");
      fprintf(fout,
              "\n\tcmp w1, w0\n"
              "\tcset w1, le\n"
              "\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr w1, [x0]\n",
              curr_tac->res->text, curr_tac->res->text);
      break;

    case TAC_EQ:
      standardTwoVars(fout, curr_tac, "TAC_EQ");
      fprintf(fout,
              "\n\tcmp w1, w0\n"
              "\tcset w1, eq\n"
              "\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr w1, [x0]\n",
              curr_tac->res->text, curr_tac->res->text);

      break;

    case TAC_DIF:
      standardTwoVars(fout, curr_tac, "TAC_DIF");
      fprintf(fout,
              "\n\tcmp w1, w0\n"
              "\tcset w1, ne\n"
              "\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr w1, [x0]\n",
              curr_tac->res->text, curr_tac->res->text);
      break;

    case TAC_AND:
      standardTwoVars(fout, curr_tac, "TAC_AND");
      fprintf(fout,
              "\n\tand w1, w1, w0\n"
              "\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr w1, [x0]\n",
              curr_tac->res->text, curr_tac->res->text);
      break;

    case TAC_OR:
      standardTwoVars(fout, curr_tac, "TAC_OR");
      fprintf(fout,
              "\n\torr w1, w1, w0\n"
              "\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr w1, [x0]\n",
              curr_tac->res->text, curr_tac->res->text);
      break;
    case TAC_NOT:
      fprintf(fout,
              "\n\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tldr w1, [x0]\n"
              "\teor w1, w1, 1\n"
              "\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr w1, [x0]\n",
              curr_tac->op1->text, curr_tac->op1->text, curr_tac->res->text,
              curr_tac->res->text);
      break;

    case TAC_IFZ:
      fprintf(fout,
              "\n\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tldr w1, [x0]\n"
              "\tcmp w1, 0\n"
              "\tbeq %s\n",
              curr_tac->op1->text, curr_tac->op1->text, curr_tac->res->text);
      break;

    case TAC_CALL:
      arg_count = 0;

      fprintf(fout,
              "\tbl _%s ; TAC_CALL\n"
              "\tmov w1, w0\n"
              "\tadrp x0, _%s@PAGE\n"
              "\tadd x0, x0, _%s@PAGEOFF\n"
              "\tstr w1, [x0]\n",
              curr_tac->op1->text, curr_tac->res->text, curr_tac->res->text);
      break;

    case TAC_ARG: {
      if (curr_tac->res->type == SYMBOL_LIT_INT) {
        fprintf(fout, "\tmov w%d, %s\n", arg_count, curr_tac->res->text);
      }
      arg_count++;

    } break;
    }
  }
}

void asmGen(TAC *tacs, AST_NODE *ast) {

  FILE *fout = fopen("asm.s", "w");

  fprintf(fout, ".arch armv8-a\n.text\n");
  writeStrings(fout, tacs);
  writeDeclarations(fout, ast);
  writeTemps(fout);
  writeTACS(fout, tacs);
}
