/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_TOKENS_H_INCLUDED
# define YY_YY_TOKENS_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "TinyGo.y"

    #include "ast.h"

#line 52 "tokens.h"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_LIT_STRING = 258,
    TK_ID = 259,
    TK_LIT_INT = 260,
    TK_LIT_FLOAT = 261,
    TK_IF = 262,
    TK_ELSE = 263,
    TK_WHILE = 264,
    TK_RETURN = 265,
    TK_VOID = 266,
    TK_INT_TYPE = 267,
    TK_FLOAT_TYPE = 268,
    TK_PRINTF = 269,
    TK_PLUS_EQUAL = 270,
    TK_MINUS_EQUAL = 271,
    TK_PLUS_PLUS = 272,
    TK_MINUS_MINUS = 273,
    TK_NOT = 274,
    TK_OR = 275,
    TK_AND = 276,
    TK_EQUAL = 277,
    TK_NOT_EQUAL = 278,
    TK_GREATER_OR_EQUAL = 279,
    TK_LESS_OR_EQUAL = 280,
    TK_PACKAGE = 281,
    TK_MAIN = 282,
    TK_IMPORT = 283,
    TK_FMT = 284,
    TK_FUNCTION = 285,
    TK_LIT_TRUE = 286,
    TK_LIT_FALSE = 287,
    TK_STRING_TYPE = 288,
    TK_BOOL_TYPE = 289,
    TK_VAR_TYPE = 290,
    TK_BREAK = 291,
    TK_CONTINUE = 292,
    TK_PERCENTAJE_EQUAL = 293,
    TK_COLON_EQUAL = 294,
    TK_DIVISION_EQUAL = 295,
    TK_POWER_EQUAL = 296,
    TK_ASTERISK_EQUAL = 297,
    TK_AMPERSAND_EQUAL = 298,
    TK_LINE_EQUAL = 299,
    TK_FOR = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 22 "TinyGo.y"

    const char * string_t;
    int int_t;
    float float_t;
    Expr * expr_t;
    ArgumentList * argument_list_t;
    Statement * statement_t;
    StatementList * statement_list_t;
    InitDeclaratorList * init_declarator_list_t;
    InitDeclarator * init_declarator_t;
    Declarator * declarator_t;
    Initializer * initializer_t;
    InitializerElementList * initializer_list_t;
    Declaration * declaration_t;
    DeclarationList * declaration_list_t;
    Parameter * parameter_t;
    ParameterList * parameter_list_t;

#line 128 "tokens.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TOKENS_H_INCLUDED  */
