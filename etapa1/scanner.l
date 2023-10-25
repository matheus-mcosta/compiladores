%{
#include "tokens.h"
#include "hash.c"

int Running=1;
int LineNumber=1;

%}

DIGIT [0-9]+
SPECIAL_CHAR [-=,;(){}[\]<>+*/%&|~]
ID [_a-zA-Z0-9]*[_a-zA-Z][_a-zA-Z0-9]*
WHITESPACE [\t\r\n]+
STRING \"(\\.|[^\"])*\"
CHAR \'[-=,;(){}[\]<>+*/%&|~a-zA-Z0-9]\'

%x LINE_COMMENT
%x COMMENT

%%

\n                   LineNumber++;

"//"                 { BEGIN(LINE_COMMENT); }
"///"                { BEGIN(COMMENT); }

"char"               { return KW_CHAR; }
"int"                { return KW_INT; }
"float"              { return KW_FLOAT; }
"code"               { return KW_CODE; }
"if"                 { return KW_IF; }
"else"               { return KW_ELSE; }
"while"              { return KW_WHILE; }
"input"              { return KW_INPUT; }
"print"              { return KW_PRINT; }
"return"             { return KW_RETURN; }

"<="                 { return OPERATOR_LE; }
">="                 { return OPERATOR_GE; }
"=="                 { return OPERATOR_EQ; }
"!="                 { return OPERATOR_DIF; }

{SPECIAL_CHAR}       { return yytext[0]; }


{ID}                 { hashInsert(yytext, TK_IDENTIFIER); return TK_IDENTIFIER; }
{DIGIT}              { hashInsert(yytext, LIT_INT); return LIT_INT; }
{DIGIT}\.{DIGIT}     { hashInsert(yytext, LIT_REAL); return LIT_REAL; }
{CHAR}               { hashInsert(yytext, LIT_CHAR); return LIT_CHAR; }
{STRING}             { hashInsert(yytext, LIT_STRING); return LIT_STRING; }
{WHITESPACE}         { }
" "                  { }


<LINE_COMMENT>"\n"   { LineNumber++; BEGIN(INITIAL); }
<LINE_COMMENT>.

<COMMENT>"\n"        { LineNumber++; }
<COMMENT>"\\\\\\"    { BEGIN(INITIAL); }
<COMMENT>.

.                    { return TOKEN_ERROR; }

%%

#include "main.c"

int getLineNumber(){
  return LineNumber;
}
void printLineNumber(){
  printf("\nLine: %d\n", getLineNumber());
}

int isRunning(){
  return Running;
}

void initMe(){
  hashInit();
}

int yywrap(){
	Running = 0;
  printLineNumber();
  hashPrint();
	return 1;
}
