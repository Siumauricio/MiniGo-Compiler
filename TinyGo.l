%option noyywrap
%option yylineno
%option caseless
%x comment

%{
    #include <stdio.h>
    #include "tokens.h"
%}

DIGIT [0-9]

%%

[\t \r \n] { /* nada */ }
"/*" {BEGIN(comment);}
"package" { return TK_PACKAGE; }
"import" { return TK_IMPORT; }
"fmt" {return TK_FMT;}
"func" { return TK_FUNCTION; }
")" { return ')'; }
"if" { return TK_IF; }
"else" { return TK_ELSE; }
"for" { return TK_FOR; }
"while" { return TK_WHILE; }
"return" { return TK_RETURN; }
"string" { return TK_STRING_TYPE; }
"int" { return TK_INT_TYPE; }
"float32" { return TK_FLOAT_TYPE;  }
"bool" { return TK_BOOL_TYPE;  }
"var" { return TK_VAR_TYPE;  }
"break" { return TK_BREAK; }
"continue" { return TK_CONTINUE; }
"Println" { return TK_PRINTLN; }
"true" { return TK_LIT_TRUE; }
"false" { return TK_LIT_FALSE; }
\".*\" { yylval.string_t = strdup(yytext); return TK_LIT_STRING; }
{DIGIT}+ { yylval.int_t = atoi(yytext); return TK_LIT_INT; }
{DIGIT}+"."{DIGIT}+ { yylval.float_t = atof(yytext); return TK_LIT_FLOAT; }
[a-zA-Z]({DIGIT}|[a-zA-Z_0-9]|_)* { yylval.string_t = strdup(yytext); return TK_ID; }
"!" {return TK_NOT; }
";" {return ';'; }
"," {return ','; }
"+" {return '+'; }
"-" {return '-'; }
"/" {return '/'; }
"*" {return '*'; }
"%" {return '%'; }
"=" {return '='; }
"[" { return '['; }
"]" { return ']'; }
"." { return '.'; }
"^" { return '^'; }
"{" { return '{'; }
"}" { return '}'; }
"+=" { return TK_PLUS_EQUAL; }
"-=" { return TK_MINUS_EQUAL; }
"++" { return TK_PLUS_PLUS; }
"--" { return TK_MINUS_MINUS; }
"%=" { return TK_PERCENTAJE_EQUAL; }
":=" { return TK_COLON_EQUAL; }
"/=" { return TK_DIVISION_EQUAL; }
"^=" { return TK_POWER_EQUAL; }
"*=" { return TK_ASTERISK_EQUAL; }
"&=" { return TK_AMPERSAND_EQUAL; }
"|=" { return TK_LINE_EQUAL; }
"!=" { return TK_NOT_EQUAL; }
"||" { return TK_OR; }
"&&" { return TK_AND; }
"==" { return TK_EQUAL; }
">" { return '>'; }
"<" { return '<'; }
">=" { return TK_GREATER_OR_EQUAL; }
"<=" { return TK_LESS_OR_EQUAL; }
"(" { return '('; }
"//"[^\n]* {/* nada */}
. {printf("caracter '%c' invalido en la linea %d\n", yytext[0], yylineno);}

<comment>"*/" {BEGIN(INITIAL);}
<comment>.|\n {/*nada*/}
<comment><<EOF>> {printf("comentario incompleto en la linea %d\n", yylineno); return 0;}
%%