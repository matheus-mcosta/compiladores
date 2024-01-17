# Matheus de Moraes Costa 00297121
#
# UFRGS - Compiladores B - Marcelo Johann - 2023/2 - Etapa 5
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#


etapa5: y.tab.o lex.yy.o hash.o ast.o semantic.o main.o
	gcc -o etapa5 y.tab.o lex.yy.o hash.o ast.o semantic.o main.o

main.o: main.c
	gcc -c main.c

semantic.o: semantic.c
	gcc -c semantic.c

ast.o: ast.c
	gcc -c ast.c
	
hash.o: hash.c
	gcc -c hash.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

y.tab.c: parser.y
	yacc -d -v parser.y

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l

clean:
	rm -f *.o etapa5 lex.yy.c lex.yy.h y.tab.c y.tab.h y.output

put:
	echo put ../entregas/etapa5.tgz | sftp mmcosta@html.inf.ufrgs.br:public_html/athiwtpuescmlrhs/

