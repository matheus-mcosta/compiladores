%{

#include "ast.h"

int getLineNumber();
void yyerror(const char *s);
int yylex();

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

program: list
        ;

list : global_decl list_code
     ;


global_decl: decl global_decl
           |
           ;

list_code: func_impl list_code
         |
         ;


decl: type TK_IDENTIFIER '=' value ';'
    | type TK_IDENTIFIER '[' LIT_INT ']' ';'
    | type TK_IDENTIFIER '[' LIT_INT ']'  vector_params ';'
    | func_decl
    ;

type: KW_INT
    | KW_FLOAT
    | KW_CHAR
    ;

func_decl: type TK_IDENTIFIER '(' param_list ')' ';'
         ;

func_impl: KW_CODE TK_IDENTIFIER cmd
    ;

func_call: TK_IDENTIFIER '(' arg_list ')'
         ;

arg_list: expr arg_rest
        |
        ;

arg_rest: ',' expr arg_rest
        |
        ;

param_list: param param_rest
          |
          ;

param_rest: ',' param param_rest
          |
          ;

param: type TK_IDENTIFIER
     ;
 
vector_params: value vector_params 
      | value
      ;

value: LIT_INT
     | LIT_REAL
     | LIT_CHAR
     ;


block: '{' list_cmd '}' 
     ;

list_cmd: cmd list_cmd
        |
        ;

cmd: attribute
   | if
   | while
   | print
   | block
   | return
   | ';'
   ;

attribute: TK_IDENTIFIER '=' expr ';'
         | TK_IDENTIFIER '[' expr ']' '=' expr ';'
         ;

if: KW_IF '(' expr ')' cmd
  | KW_IF '(' expr ')' cmd KW_ELSE cmd
  ;

while: KW_WHILE '(' expr ')' cmd
     ;

print: KW_PRINT expr ';'
     | KW_PRINT LIT_STRING ';'
     ;

return: KW_RETURN expr ';'
      ;

input: KW_INPUT '(' type ')'
     ;


expr: value
    | input
    | func_call
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '<' expr
    | expr '>' expr
    | expr OPERATOR_LE expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_DIF expr
    | expr '&' expr
    | expr '|' expr
    | '~' expr
    | '(' expr ')'
    | TK_IDENTIFIER
    | vector
    ;

vector: TK_IDENTIFIER '[' expr ']'
      ;

%%


void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d.", getLineNumber());
    exit(3);
}

