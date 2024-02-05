// Matheus de Moraes Costa 00297121
// Codigo baseado na implementação do professor
#ifndef TACS_HEADER
#define TACS_HEADER

#include "ast.h"

#define TAC_SYMBOL 1
#define TAC_MOVE 2
#define TAC_ADD 3	 
#define TAC_SUB 4	
#define TAC_MUL 5	
#define TAC_DIV 6
#define TAC_GREAT 7
#define TAC_LESS 8
#define TAC_GE 9
#define TAC_LE 10
#define TAC_EQ 11
#define TAC_DIF 12
#define TAC_AND 13
#define TAC_OR 14
#define TAC_NOT 15
#define TAC_LABEL 16
#define TAC_BEGINFUN 17
#define TAC_ENDFUN 18
#define TAC_IFZ 19
#define TAC_JUMP 20
#define TAC_CALL 21
#define TAC_ARG 22
#define TAC_ARGPUSH 23
#define TAC_RET 24
#define TAC_PRINT 25
#define TAC_READ 26
#define TAC_VECATTR 27
#define TAC_VEC 28
#define TAC_PARAM 29
#define TAC_FUNDEC 30



typedef struct tac_struct{
    int type;
    HASH_NODE *res;
    HASH_NODE *op1;
    HASH_NODE *op2;
    struct tac_struct *prev;
    struct tac_struct *next;
} TAC;

TAC *tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2);
TAC *tacJoin(TAC *l1, TAC *l2);
TAC *tacReverse(TAC *l);
void printTac(TAC *l);
void printAllTacs(TAC *l);
TAC *generateCode(AST_NODE *node, HASH_NODE *currentLabel);


TAC *createBinOp(int type, TAC *son[], int datatype);
TAC *createIf(TAC *son[]);
TAC *createWhile(TAC *son[], HASH_NODE *label);
TAC *createFunc(TAC *symbol, TAC *params, TAC *code);





#endif
