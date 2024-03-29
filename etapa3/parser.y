%{

#include "ast.h"

int getLineNumber();
void yyerror(const char *s);
int yylex();


AST_NODE *root;

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

program: list           {root=$$; astPrint(0,root);}
        ;

list : global_decl list_code {$$ = astCreate(AST_LIST, 0, $1, $2, 0, 0);}
     ;


global_decl: decl global_decl {$$ = astCreate(AST_GLOBAL_DECL, 0, $1, $2, 0, 0);}
           |           {$$ = 0;}
           ;

list_code: func_impl list_code {$$ = astCreate(AST_LIST_CODE, 0, $1, $2, 0, 0);}
         |           {$$ = 0;}
         ;


decl: type TK_IDENTIFIER '=' value ';' {$$ = astCreate(AST_DECL, $2, $1, $4, 0, 0);}
    | type TK_IDENTIFIER '[' LIT_INT ']' ';' {$$ = astCreate(AST_VECTORD, $2, $1, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), 0, 0);}
    | type TK_IDENTIFIER '[' LIT_INT ']'  vector_params ';' {$$ = astCreate(AST_VECTORD2, $2, $1, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), $6, 0);}
    | type TK_IDENTIFIER '(' param_list ')' ';'  {$$ = astCreate(AST_FUNC_DECL, $2, $1, $4, 0, 0);}
    ;

type: KW_INT { $$ = astCreate(AST_INT, 0, 0, 0, 0, 0);}
    | KW_FLOAT { $$ = astCreate(AST_FLOAT, 0, 0, 0, 0, 0);}
    | KW_CHAR { $$ = astCreate(AST_CHAR, 0, 0, 0, 0, 0);}
    ;

func_impl: KW_CODE TK_IDENTIFIER cmd { $$ = astCreate(AST_FUNC_IMPL, $2, $3, 0, 0, 0);}
    ;

func_call: TK_IDENTIFIER '(' arg_list ')' {$$ = astCreate(AST_FUNC_CALL, $1, $3, 0, 0, 0);}
         ;

arg_list: expr arg_rest {$$ = astCreate(AST_ARG_LIST, 0, $1, $2, 0, 0);}
        |           {$$ = 0;}
        ;

arg_rest: ',' expr arg_rest {$$ = astCreate(AST_ARG_REST, 0, $2, $3, 0, 0);}
        |           {$$ = 0;}
        ;

param_list: param param_rest {$$ = astCreate(AST_PARAM_LIST, 0, $1, $2, 0, 0);}
          |           {$$ = 0;}
          ;

param_rest: ',' param param_rest {$$ = astCreate(AST_PARAM_REST, 0, $2, $3, 0, 0);}
          |           {$$ = 0;}
          ;

param: type TK_IDENTIFIER {$$ = astCreate(AST_PARAM, $2, $1, 0, 0, 0);}
     ;
 
vector_params: value vector_params  { $$ = astCreate(AST_VECTOR_PARAMS, 0, $1, $2, 0, 0);}
    | value { $$ = astCreate(AST_VECTOR_PARAMS, 0, $1, 0, 0, 0);}
      ;

value: LIT_INT {$$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
     | LIT_REAL {$$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
     | LIT_CHAR {$$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
     ;


block: '{' list_cmd '}' {$$ = astCreate(AST_BLOCK, 0, $2, 0, 0, 0);}
     ;

list_cmd: cmd list_cmd {$$ = astCreate(AST_LIST_CMD, 0, $1, $2, 0, 0);}
        |               {$$ = 0;}
        ;

cmd: attribute {$$ = $1;}
   | if{$$ = $1;}
   | while{$$ = $1;}
   | print{$$ = $1;}
   | block{$$ = $1;}
   | return{$$ = $1;}
   | ';' {$$ = astCreate(AST_SEMI, 0,0,0,0,0);}
   ;

attribute: TK_IDENTIFIER '=' expr ';' {$$ = astCreate(AST_ATTRIBUTE, $1, $3, 0, 0, 0);}
        | TK_IDENTIFIER '[' expr ']' '=' expr ';' {$$ = astCreate(AST_ATTRIB_VEC, $1, $3, $6, 0, 0);}
         ;

if: KW_IF '(' expr ')' cmd {$$ = astCreate(AST_IF, 0, $3, $5, 0, 0);}
  | KW_IF '(' expr ')' cmd KW_ELSE cmd {$$ = astCreate(AST_IF_ELSE, 0, $3, $5, $7, 0);}
  ;

while: KW_WHILE '(' expr ')' cmd {$$ = astCreate(AST_WHILE, 0, $3, $5, 0, 0);}
     ;

print: KW_PRINT expr ';' {$$ = astCreate(AST_PRINT, 0, $2, 0, 0, 0);}
     
    | KW_PRINT LIT_STRING ';' {$$ = astCreate(AST_PRINT, 0, astCreate(AST_SYMBOL, $2, 0, 0, 0, 0), 0, 0, 0);}
     ;

return: KW_RETURN expr ';' {$$ = astCreate(AST_RETURN, 0, $2, 0, 0, 0);}
      ;

input: KW_INPUT '(' type ')' {$$ = astCreate(AST_INPUT, 0, $3, 0, 0, 0);}
     ;


expr: value {$$ = $1;}
    | input {$$ = $1;}
    | func_call{$$ = $1;}
    | expr '+' expr {$$ = astCreate(AST_ADD, 0, $1, $3, 0, 0);}
    | expr '-' expr {$$ = astCreate(AST_SUB, 0, $1, $3, 0, 0);}
    | expr '*' expr {$$ = astCreate(AST_MUL, 0, $1, $3, 0, 0);}
    | expr '/' expr {$$ = astCreate(AST_DIV, 0, $1, $3, 0, 0);}
    | expr '<' expr {$$ = astCreate(AST_LESS, 0, $1, $3, 0, 0);}
    | expr '>' expr {$$ = astCreate(AST_GREATER, 0, $1, $3, 0, 0);}
    | expr OPERATOR_LE expr {$$ = astCreate(AST_LE, 0, $1, $3, 0, 0);}
    | expr OPERATOR_GE expr {$$ = astCreate(AST_GE, 0, $1, $3, 0, 0);}
    | expr OPERATOR_EQ expr {$$ = astCreate(AST_EQ, 0, $1, $3, 0, 0);}
    | expr OPERATOR_DIF expr {$$ = astCreate(AST_DIF, 0, $1, $3, 0, 0);}
    | expr '&' expr {$$ = astCreate(AST_AND, 0, $1, $3, 0, 0);}
    | expr '|' expr {$$ = astCreate(AST_OR, 0, $1, $3, 0, 0);}
    | '~' expr {$$ = astCreate(AST_NOT, 0, $2, 0, 0, 0);}
    | '(' expr ')' {$$ = astCreate(AST_PAREN, 0, $2, 0, 0, 0);}
    | TK_IDENTIFIER {$$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
    | vector{$$ = $1;}
    ;

vector: TK_IDENTIFIER '[' expr ']' {$$ = astCreate(AST_VECTOR, $1, $3, 0, 0, 0);}
      ;

%%


void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d.", getLineNumber());
    exit(3);

}

AST_NODE *getAST() {
    return root;
}

