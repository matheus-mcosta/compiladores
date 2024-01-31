#include <stdio.h>
#include <stdlib.h>

#include "asm.h"
#include "ast.h"
#include "hash.h"
#include "tacs.h"

void writeDeclarations(FILE *fout, AST_NODE *ast) {
  if (!ast)
    return;

  int i;

  switch (ast->type) {

  case AST_DECL:
    if (ast->son[1]) {
      if (ast->son[1]->symbol->datatype == DATATYPE_INT) {
        fprintf(fout,
                "\t.globl _%s\n"
                "\t.data\n"
                "\t.align 2\n"
                "_%s:\n"
                "\t.word %s\n",
                ast->symbol->text, ast->symbol->text,
                ast->son[1]->symbol->text);
      } else if (ast->son[1]->symbol->datatype == DATATYPE_CHAR) {
        fprintf(fout,
                "\t.globl _%s\n"
                "\t.data\n"
                "\t.align 2\n"
                "_%s:\n"
                "\t.byte %d\n",
                ast->symbol->text, ast->symbol->text,
                ast->son[1]->symbol->text[1]);
      }
    }

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
                "\t.globl _%s\n"
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

  fprintf(fout, "\t.cstring\n"
                "\t.align 3\n"
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
                "\t.cstring\n"
                "\t.align  3\n"
                "%s:\n"
                "\t.ascii \"%s\\0\"\n"
                "\t.text\n",
                curr_tac->op1->text, new_str);
      }
    }
  }
}

void writeTACS(FILE *fout, TAC *tacs) {
  TAC *curr_tac;

  for (curr_tac = tacs; curr_tac; curr_tac = curr_tac->next) {

    switch (curr_tac->type) {

    case TAC_BEGINFUN:
      fprintf(fout,
              "\t.text ;TAC_BEGINFUN\n"
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
              "\tldp x29, x30, [sp], 16 ; TAC_ENDFUN\n"
              "\tret\n"
              "FEND2_%s:\n",
              curr_tac->res->text);
      break;

    case TAC_RET:
      if (curr_tac->res->type == SYMBOL_LIT_INT) {
        fprintf(fout, "\t mov w0, %s ; TAC_RET\n", curr_tac->res->text);
      } else if (curr_tac->res->type == SYMBOL_SCALAR) {
        /*
         *
          adrp	x0, _a@PAGE
          add	x0, x0, _a@PAGEOFF;momd
          ldr	w0, [x0]
         *
         * */
        fprintf(fout,
                "\tadrp x0, _%s@PAGE ; TAC_RET\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tldr w0, [x0]\n",
                curr_tac->res->text, curr_tac->res->text);
      }
      break;

    case TAC_PRINT:

      if (curr_tac->res->datatype == DATATYPE_INT) {
        fprintf(fout,
                "\tadrp x0, _%s@PAGE ; TAC_PRINT INT\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tldr w0, [x0]\n"
                "\tstr w0, [sp]\n"
                "\tadrp x0, lC0@PAGE\n"
                "\tadd x0, x0, lC0@PAGEOFF\n"
                "\tbl _printf\n",
                curr_tac->res->text, curr_tac->res->text);

      } else if (curr_tac->res->type == SYMBOL_LIT_STRING) {

        fprintf(fout,
                "\tadrp x0, %s@PAGE ; TAC_PRINT STRING\n"
                "\tadd x0, x0, %s@PAGEOFF\n"
                "\tbl _printf\n",
                curr_tac->op1->text, curr_tac->op1->text);
      }

      break;

    case TAC_MOVE:

      if (curr_tac->op1->type == SYMBOL_LIT_INT) {
        fprintf(fout,
                "\tadrp x0, _%s@PAGE ; TAC_MOVE\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tmov w1, %s\n"
                "\tstr w1, [x0]\n",
                curr_tac->res->text, curr_tac->res->text, curr_tac->op1->text);
      } else {

        fprintf(fout,
                "\tadrp x0, _%s@PAGE ; TAC_MOVE\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tldr w1, [x0]\n"
                "\tadrp x0, _%s@PAGE\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tstr w1, [x0]\n",
                curr_tac->op1->text, curr_tac->op1->text, curr_tac->res->text,
                curr_tac->res->text);
        // adrp	x0, _a@PAGE
        // add	x0, x0, _a@PAGEOFF;momd
        // ldr	w1, [x0]
        // adrp	x0, _b@PAGE
        // add	x0, x0, _b@PAGEOFF;momd
        // str	w1, [x0]
      }
      // fprintf(fout,
      //     "tipo: %d, texto: %s\n", curr_tac->res->type, curr_tac->res->text);
      // fprintf(fout,
      //     "tipo: %d, texto: %s\n", curr_tac->op1->type, curr_tac->op1->text);

      break;
    case TAC_ADD:

      break;
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
