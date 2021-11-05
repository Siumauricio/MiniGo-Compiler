%option noyywrap
%option yylineno
%option caseless
%x comment

%{
    #include <stdio.h>
     #include "main.cpp"
    enum yytokentype{
    TK_IF = 258,
    TK_ELSE = 259,
    TK_FOR = 260,
    TK_PACKAGE = 261,
    TK_IMPORT = 262,
    TK_WHILE = 263,
    TK_VOID = 264,
    TK_RETURN = 265,
    TK_FUNCTION = 266,
    TK_INT_TYPE = 267,
    TK_FLOAT_TYPE = 268,
    TK_BOOL_TYPE = 269,
    TK_VAR_TYPE = 270,
    TK_BREAK = 271,
    TK_CONTINUE =272,
    TK_PRINTF =273,
    TK_LIT_STRING=274,
    TK_LIT_INT=275,
    TK_LIT_FLOAT=276,
    TK_ID=277,
    TK_TRUE=278,
    TK_FALSE=279,
    TK_PLUS_EQUAL=280,
    TK_MINUS_EQUAL=281,
    TK_PLUS_PLUS=282,
    TK_MINUS_MINUS=283,
    TK_PERCENTAJE_EQUAL=284,
    TK_COLON_EQUAL=285,
    TK_DIVISION_EQUAL=286,
    TK_POWER_EQUAL=287,
    TK_ASTERISK_EQUAL=288,
    TK_AMPERSAND_EQUAL=289,
    TK_LINE_EQUAL=290,
    TK_OR=291,
    TK_AND=292,
    TK_EQUAL=293,
    TK_NOT_EQUAL=294,
    TK_EXCLAMATION_EQUAL=295,
    TK_GREATER_OR_EQUAL=296,
    TK_LESS_OR_EQUAL=297
    };
     int yylval;
%}

DIGIT [0-9]

%%

[\t \r \n] { /* nada */ }
"/*" {BEGIN(comment);}
")" { return ')'; }
"if" { return TK_IF; }
"else" { return TK_ELSE; }
"for" { return TK_FOR; }
"package" { return TK_PACKAGE; }
"import" { return TK_IMPORT; }
"while" { return TK_WHILE; }
"void" { return TK_VOID; }
"return" { return TK_RETURN; }
"func" { return TK_FUNCTION; }
"int" { return TK_INT_TYPE; }
"float32" { return TK_FLOAT_TYPE;  }
"bool" { return TK_BOOL_TYPE;  }
"var" { return TK_VAR_TYPE;  }
"break" { return TK_BREAK; }
"continue" { return TK_CONTINUE; }
"printf" { return TK_PRINTF; }
\".*\" { return TK_LIT_STRING; }
{DIGIT}+ { yylval = atoi(yytext); return TK_LIT_INT; }
{DIGIT}+"."{DIGIT}+ { return TK_LIT_FLOAT; }
[a-zA-Z]({DIGIT}|[a-zA-Z_0-9]|_)* {return TK_ID; }
"true" { return TK_TRUE; }
"false" { return TK_FALSE; }
"!" {return '!'; }
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
"^" { return '^'; }
"{" { return '{'; }
"}" { return '}'; }
"." { return '.'; }
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
"!=" { return TK_EXCLAMATION_EQUAL; }
"||" { return TK_OR; }
"&&" { return TK_AND; }
"==" { return TK_EQUAL; }
"!=" { return TK_NOT_EQUAL; }
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