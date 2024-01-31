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

    // 	.globl _a
    // 	.data
    // 	.align	2
    // _a:

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
              "\t.text\n"
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
              "\tldp x29, x30, [sp], 16\n"
              "\tret\n"
              "FEND2_%s:\n",
              curr_tac->res->text);
      break;

    case TAC_RET:
      if (curr_tac->res->type == SYMBOL_LIT_INT) {
        fprintf(fout, "\t mov w0, %s\n", curr_tac->res->text);
      } else if (curr_tac->res->type == SYMBOL_SCALAR) {
        /*
         *
          adrp	x0, _a@PAGE
          add	x0, x0, _a@PAGEOFF;momd
          ldr	w0, [x0]
         *
         * */
        fprintf(fout,
                "\tadrp x0, _%s@PAGE\n"
                "\tadd x0, x0, _%s@PAGEOFF\n"
                "\tldr w0, [x0]\n",
                curr_tac->res->text, curr_tac->res->text);
      }

    case TAC_PRINT:

      if (curr_tac->res->datatype == DATATYPE_INT) {

      } else if (curr_tac->res->type == SYMBOL_LIT_STRING) {

        fprintf(fout,
                "\tadrp x0, %s@PAGE\n"
                "\tadd x0, x0, %s@PAGEOFF\n"
                "\tbl _printf\n",
                curr_tac->op1->text, curr_tac->op1->text);
      }
      /*
       *
       String print
        adrp	x0, lC01PAGE
        add	x0, x0, lC01PAGEOFF;momd
        bl	_printf


    Number print
        adrp	x0, _a@PAGE
        add	x0, x0, _a@PAGEOFF;momd
        ldr	w0, [x0]
        str	w0, [sp]
        adrp	x0, lC0@PAGE
        add	x0, x0, lC0@PAGEOFF;momd
        bl	_printf


       * */
      break;

      break;
    }
  }
}

void asmGen(TAC *tacs, AST_NODE *ast) {

  FILE *fout = fopen("asm.s", "w");

  fprintf(fout, ".arch armv8-a\n.text\n");
  // Define a string format for printing integers

  writeStrings(fout, tacs);
  writeDeclarations(fout, ast);
  writeTACS(fout, tacs);
}
