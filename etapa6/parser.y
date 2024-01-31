%{

#include "ast.h"
#include "semantic.h"
#include "tacs.h"

extern int getLineNumber();
void yyerror(const char *s);
int yylex();


extern int semanticErrors;
AST_NODE *root;
TAC *TACs;

%}

%token KW_CHAR
%token KW_INT
%token KW_FLOAT

%token KW_CODE

%token KW_IF
%token KW_ELSE
%token KW_WHILE
%token KW_INPUT
%token KW_PRINT
%token KW_RETURN

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF

%token <symbol> TK_IDENTIFIER

%token <symbol> LIT_INT
%token <symbol> LIT_REAL
%token <symbol> LIT_CHAR
%token <symbol> LIT_STRING

%token TOKEN_ERROR


%type <ast> program
%type <ast> list
%type <ast> global_decl
%type <ast> list_code
%type <ast> decl
%type <ast> type
%type <ast> func_impl
%type <ast> func_call
%type <ast> arg_list
%type <ast> arg_rest
%type <ast> param_list
%type <ast> param_rest
%type <ast> param
%type <ast> vector_params
%type <ast> value
%type <ast> block
%type <ast> list_cmd
%type <ast> cmd
%type <ast> attribute
%type <ast> if
%type <ast> while
%type <ast> print
%type <ast> return
%type <ast> input
%type <ast> vector
%type <ast> expr




%left '&' '|'
%left '<' '>' '='
%left OPERATOR_DIF OPERATOR_EQ
%left OPERATOR_GE OPERATOR_LE
%left '+' '-'
%left '*' '/'

%right '~'

%union {
  HASH_NODE *symbol;
  AST_NODE *ast;
}

%%

program: list           {root=$$; astPrint(0,root); semanticErrors = checkSemantic(root);
                         TACs=tacReverse(generateCode(root, 0));}
        ;

list : global_decl list_code {$$ = astCreate(AST_LIST, 0, $1, $2, 0, 0, getLineNumber());}
     ;


global_decl: decl global_decl {$$ = astCreate(AST_GLOBAL_DECL, 0, $1, $2, 0, 0, getLineNumber());}
           |           {$$ = 0;}
           ;

list_code: func_impl list_code {$$ = astCreate(AST_LIST_CODE, 0, $1, $2, 0, 0, getLineNumber());}
         |           {$$ = 0;}
         ;


decl: type TK_IDENTIFIER '=' value ';' {$$ = astCreate(AST_DECL, $2, $1, $4, 0, 0, getLineNumber());}
    | type TK_IDENTIFIER '[' LIT_INT ']' ';' {$$ = astCreate(AST_VECTORD, $2, $1, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0, getLineNumber()), 0, 0, getLineNumber());}
    | type TK_IDENTIFIER '[' LIT_INT ']'  vector_params ';' {$$ = astCreate(AST_VECTORD2, $2, $1, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0, getLineNumber()), $6, 0, getLineNumber());}
    | type TK_IDENTIFIER '(' param_list ')' ';'  {$$ = astCreate(AST_FUNC_DECL, $2, $1, $4, 0, 0, getLineNumber());}
    ;

type: KW_INT { $$ = astCreate(AST_INT, 0, 0, 0, 0, 0, getLineNumber());}
    | KW_FLOAT { $$ = astCreate(AST_FLOAT, 0, 0, 0, 0, 0, getLineNumber());}
    | KW_CHAR { $$ = astCreate(AST_CHAR, 0, 0, 0, 0, 0, getLineNumber());}
    ;

func_impl: KW_CODE TK_IDENTIFIER cmd { $$ = astCreate(AST_FUNC_IMPL, $2, $3, 0, 0, 0, getLineNumber());}
    ;

func_call: TK_IDENTIFIER '(' arg_list ')' {$$ = astCreate(AST_FUNC_CALL, $1, $3, 0, 0, 0, getLineNumber());}
         ;

arg_list: expr arg_rest {$$ = astCreate(AST_ARG_LIST, 0, $1, $2, 0, 0, getLineNumber());}
        |           {$$ = 0;}
        ;

arg_rest: ',' expr arg_rest {$$ = astCreate(AST_ARG_REST, 0, $2, $3, 0, 0, getLineNumber());}
        |           {$$ = 0;}
        ;

param_list: param param_rest {$$ = astCreate(AST_PARAM_LIST, 0, $1, $2, 0, 0, getLineNumber());}
          |           {$$ = 0;}
          ;

param_rest: ',' param param_rest {$$ = astCreate(AST_PARAM_REST, 0, $2, $3, 0, 0, getLineNumber());}
          |           {$$ = 0;}
          ;

param: type TK_IDENTIFIER {$$ = astCreate(AST_PARAM, $2, $1, 0, 0, 0, getLineNumber());}
     ;
 
vector_params: value vector_params  { $$ = astCreate(AST_VECTOR_PARAMS, 0, $1, $2, 0, 0, getLineNumber());}
    | value { $$ = astCreate(AST_VECTOR_PARAMS, 0, $1, 0, 0, 0, getLineNumber());}
      ;

value: LIT_INT {$$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0, getLineNumber());}
     | LIT_REAL {$$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0, getLineNumber());}
     | LIT_CHAR {$$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0, getLineNumber());}
     ;


block: '{' list_cmd '}' {$$ = astCreate(AST_BLOCK, 0, $2, 0, 0, 0, getLineNumber());}
     ;

list_cmd: cmd list_cmd {$$ = astCreate(AST_LIST_CMD, 0, $1, $2, 0, 0, getLineNumber());}
        |               {$$ = 0;}
        ;

cmd: attribute {$$ = $1;}
   | if{$$ = $1;}
   | while{$$ = $1;}
   | print{$$ = $1;}
   | block{$$ = $1;}
   | return{$$ = $1;}
   | ';' {$$ = astCreate(AST_SEMI, 0,0,0,0,0, getLineNumber());}
   ;

attribute: TK_IDENTIFIER '=' expr ';' {$$ = astCreate(AST_ATTRIBUTE, $1, $3, 0, 0, 0, getLineNumber());}
        | TK_IDENTIFIER '[' expr ']' '=' expr ';' {$$ = astCreate(AST_ATTRIB_VEC, $1, $3, $6, 0, 0, getLineNumber());}
         ;

if: KW_IF '(' expr ')' cmd {$$ = astCreate(AST_IF, 0, $3, $5, 0, 0, getLineNumber());}
  | KW_IF '(' expr ')' cmd KW_ELSE cmd {$$ = astCreate(AST_IF_ELSE, 0, $3, $5, $7, 0, getLineNumber());}
  ;

while: KW_WHILE '(' expr ')' cmd {$$ = astCreate(AST_WHILE, 0, $3, $5, 0, 0, getLineNumber());}
     ;

print: KW_PRINT expr ';' {$$ = astCreate(AST_PRINT, 0, $2, 0, 0, 0, getLineNumber());}
     
    | KW_PRINT LIT_STRING ';' {$$ = astCreate(AST_PRINT, 0, astCreate(AST_SYMBOL, $2, 0, 0, 0, 0, getLineNumber()), 0, 0, 0, getLineNumber());}
     ;

return: KW_RETURN expr ';' {$$ = astCreate(AST_RETURN, 0, $2, 0, 0, 0, getLineNumber());}
      ;

input: KW_INPUT '(' type ')' {$$ = astCreate(AST_INPUT, 0, $3, 0, 0, 0, getLineNumber());}
     ;


expr: value {$$ = $1;}
    | input {$$ = $1;}
    | func_call{$$ = $1;}
    | expr '+' expr {$$ = astCreate(AST_ADD, 0, $1, $3, 0, 0, getLineNumber());}
    | expr '-' expr {$$ = astCreate(AST_SUB, 0, $1, $3, 0, 0, getLineNumber());}
    | expr '*' expr {$$ = astCreate(AST_MUL, 0, $1, $3, 0, 0, getLineNumber());}
    | expr '/' expr {$$ = astCreate(AST_DIV, 0, $1, $3, 0, 0, getLineNumber());}
    | expr '<' expr {$$ = astCreate(AST_LESS, 0, $1, $3, 0, 0, getLineNumber());}
    | expr '>' expr {$$ = astCreate(AST_GREATER, 0, $1, $3, 0, 0, getLineNumber());}
    | expr OPERATOR_LE expr {$$ = astCreate(AST_LE, 0, $1, $3, 0, 0, getLineNumber());}
    | expr OPERATOR_GE expr {$$ = astCreate(AST_GE, 0, $1, $3, 0, 0, getLineNumber());}
    | expr OPERATOR_EQ expr {$$ = astCreate(AST_EQ, 0, $1, $3, 0, 0, getLineNumber());}
    | expr OPERATOR_DIF expr {$$ = astCreate(AST_DIF, 0, $1, $3, 0, 0, getLineNumber());}
    | expr '&' expr {$$ = astCreate(AST_AND, 0, $1, $3, 0, 0, getLineNumber());}
    | expr '|' expr {$$ = astCreate(AST_OR, 0, $1, $3, 0, 0, getLineNumber());}
    | '~' expr {$$ = astCreate(AST_NOT, 0, $2, 0, 0, 0, getLineNumber());}
    | '(' expr ')' {$$ = astCreate(AST_PAREN, 0, $2, 0, 0, 0, getLineNumber());}
    | TK_IDENTIFIER {$$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0, getLineNumber());}
    | vector{$$ = $1;}
    ;

vector: TK_IDENTIFIER '[' expr ']' {$$ = astCreate(AST_VECTOR, $1, $3, 0, 0, 0, getLineNumber());}
      ;

%%

void getSemanticErrors(){
    if (semanticErrors > 0){
        fprintf(stderr, "Semantic errors found: %d\n", semanticErrors);
        exit(4);
    }
}

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d.", getLineNumber());
    exit(3);

}

AST_NODE *getAST() {
    return root;
}

TAC *getTACs() {
    return TACs;
}
