#include <stdio.h>
#include <stdlib.h>

#include "asm.h"
#include "ast.h"
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
    fprintf(fout,
            "\t.globl _%s\n"
            "\t.data\n"
            "\t.align 2\n"
            "_%s:",
            ast->symbol->text, ast->symbol->text);
    if (ast->son[1]) {
      if (ast->son[1]->symbol->datatype == DATATYPE_INT) {
        fprintf(fout, " .word %s\n", ast->son[1]->symbol->text);
      } else if (ast->son[1]->symbol->datatype == DATATYPE_CHAR) {
        fprintf(fout, " .byte %d\n", ast->son[1]->symbol->text[1]);
      }
    }

    break;
  }

  for (i = 0; i < MAX_SONS; ++i)
    writeDeclarations(fout, ast->son[i]);
}

void asmGen(TAC *tacs, AST_NODE *ast) {

  FILE *fout = fopen("asm.s", "w");

  fprintf(fout, ".arch armv8-a\n.text\n");
  // Define a string format for printing integers
  fprintf(fout, "\t.cstring\n"
                "\t.align 3\n"
                "lC0:\n"
                "\t.ascii \"%%d\\12\\0\"\n"
                "\t.text\n");

  writeDeclarations(fout, ast);
}
