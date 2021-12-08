/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "TinyGo.y"

//http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
    #include <cstdio>
    #include <iostream>
    using namespace std;
    int yylex();
    extern int yylineno;
    void yyerror(const char * s){
        fprintf(stderr, "Line: %d, error: %s\n", yylineno, s);
    }

    #define YYERROR_VERBOSE 1
    #define YYDEBUG 1
    #define EQUAL 1
    #define PLUSEQUAL 2
    #define MINUSEQUAL 3
    #define COLONEQUAL 4

#line 89 "TinyGo_parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 136 "TinyGo_parser.cpp"

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
    TK_PRINTLN = 269,
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
    TK_IMPORT = 282,
    TK_FMT = 283,
    TK_FUNCTION = 284,
    TK_LIT_TRUE = 285,
    TK_LIT_FALSE = 286,
    TK_STRING_TYPE = 287,
    TK_BOOL_TYPE = 288,
    TK_VAR_TYPE = 289,
    TK_BREAK = 290,
    TK_CONTINUE = 291,
    TK_PERCENTAJE_EQUAL = 292,
    TK_COLON_EQUAL = 293,
    TK_DIVISION_EQUAL = 294,
    TK_POWER_EQUAL = 295,
    TK_ASTERISK_EQUAL = 296,
    TK_AMPERSAND_EQUAL = 297,
    TK_LINE_EQUAL = 298,
    TK_FOR = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "TinyGo.y"

    const char * string_t;
    int int_t;
    float float_t;
    Expr * expr_t;
    ArgumentList * argument_list_t;
    Statement * statement_t;
    StatementList * statement_list_t;
    ExprList * expr_list_t;
    InitDeclaratorList * init_declarator_list_t;
    InitDeclarator * init_declarator_t;
    Declarator * declarator_t;
    Initializer * initializer_t;
    InitializerElementList * initializer_list_t;
    Declaration * declaration_t;
    DeclarationList * declaration_list_t;
    Parameter * parameter_t;
    ParameterList * parameter_list_t;
    list<string> * string_list_t;

#line 213 "TinyGo_parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TOKENS_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   538

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  208

#define YYUNDEFTOK  2
#define YYMAXUTOK   299


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    55,     2,     2,    58,     2,     2,
      45,    46,    56,    59,    49,    60,    53,    57,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    54,
      62,    50,    61,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    48,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    82,    82,    95,    96,    99,   100,   101,   102,   105,
     106,   109,   110,   113,   117,   122,   128,   135,   136,   142,
     143,   148,   149,   157,   158,   164,   165,   168,   169,   170,
     171,   176,   177,   181,   182,   183,   186,   191,   195,   196,
     199,   200,   201,   202,   203,   204,   207,   210,   211,   214,
     215,   216,   219,   220,   221,   224,   225,   226,   229,   232,
     233,   234,   237,   242,   243,   244,   251,   258,   269,   272,
     273,   274,   275,   278,   281,   282,   283,   284,   287,   288,
     289,   292,   293,   294,   295,   296,   297,   301,   302,   305,
     306,   307,   308,   312,   313,   314,   315,   318,   319,   320,
     323,   324,   325,   326,   327,   330,   331,   332,   335,   336,
     339,   340,   343,   344,   345,   346,   349,   353,   354,   355,
     356,   357
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_LIT_STRING", "TK_ID", "TK_LIT_INT",
  "TK_LIT_FLOAT", "TK_IF", "TK_ELSE", "TK_WHILE", "TK_RETURN", "TK_VOID",
  "TK_INT_TYPE", "TK_FLOAT_TYPE", "TK_PRINTLN", "TK_PLUS_EQUAL",
  "TK_MINUS_EQUAL", "TK_PLUS_PLUS", "TK_MINUS_MINUS", "TK_NOT", "TK_OR",
  "TK_AND", "TK_EQUAL", "TK_NOT_EQUAL", "TK_GREATER_OR_EQUAL",
  "TK_LESS_OR_EQUAL", "TK_PACKAGE", "TK_IMPORT", "TK_FMT", "TK_FUNCTION",
  "TK_LIT_TRUE", "TK_LIT_FALSE", "TK_STRING_TYPE", "TK_BOOL_TYPE",
  "TK_VAR_TYPE", "TK_BREAK", "TK_CONTINUE", "TK_PERCENTAJE_EQUAL",
  "TK_COLON_EQUAL", "TK_DIVISION_EQUAL", "TK_POWER_EQUAL",
  "TK_ASTERISK_EQUAL", "TK_AMPERSAND_EQUAL", "TK_LINE_EQUAL", "TK_FOR",
  "'('", "')'", "'['", "']'", "','", "'='", "'{'", "'}'", "'.'", "';'",
  "'\"'", "'*'", "'/'", "'%'", "'+'", "'-'", "'>'", "'<'", "$accept",
  "start", "input", "external_declaration", "imports", "list_libraries",
  "method_definition", "declaration_list", "declaration",
  "init_declarator_list", "ids_list", "init_declarator", "declarator",
  "parameters_type_list", "parameter_declaration", "initializer",
  "initializer_list", "statement", "print_statement", "statement_list",
  "if_statement", "expression_list", "for_statement",
  "expression_statement", "jump_statement", "block_statement", "type_init",
  "type", "Array", "primary_expression", "assignment_expression",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "multiplicative_expression", "additive_expression",
  "relational_expression", "equality_expression", "logical_or_expression",
  "logical_and_expression", "assignment_operator", "expression",
  "constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,    40,    41,    91,    93,    44,
      61,   123,   125,    46,    59,    34,    42,    47,    37,    43,
      45,    62,    60
};
# endif

#define YYPACT_NINF (-88)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-75)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      95,    26,     9,    28,    35,    61,    95,   -88,   -88,   -88,
     -88,   -88,   -88,    73,    75,    69,   -88,    30,   -88,   -88,
       3,   -88,    12,   -88,   -88,   -88,   -88,    32,   116,    76,
     -88,   -10,     8,    80,    24,   -88,    53,   -88,   379,    81,
     -88,   440,   387,    83,   129,   -88,    89,   -88,    53,   105,
     -88,     8,   150,    76,   -88,   -88,   -88,   -88,   440,   440,
     440,   -88,   -88,   440,   107,   440,   155,   -88,   -88,   -88,
      27,    -2,    87,   -42,   -15,    46,   141,   145,   -88,    76,
     -88,   -88,   114,   -88,   463,   440,   115,   -88,   -88,   301,
     -88,   172,   -88,   -88,   -88,   215,   -88,   -88,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,    53,   -88,    89,   -88,    81,
     -88,   -88,   -88,   121,    53,    66,   -88,   141,   117,   -88,
     -88,   410,   440,   -88,   -88,   -88,   -88,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   -88,   -88,   440,   344,   -88,   -88,   156,    37,   131,
     -88,   344,   -88,   -88,   258,   -88,    19,   -88,   -88,   -88,
     -88,   433,   440,   -88,   -88,   -88,   -88,    92,   123,   132,
     -88,   -88,   -88,    87,    87,   -42,   -42,   -42,   -42,   -15,
     -15,   145,    46,   137,   161,    -1,   142,   440,   -88,   -88,
     -88,   -88,   141,   -88,   440,   -88,   -88,   476,   344,   440,
     134,   -88,   -88,   146,   440,   -88,   344,   -88
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     2,     4,     7,     5,
       6,     8,    12,     0,     9,     0,    24,     0,     1,     3,
       0,    11,     0,    70,    71,    72,    69,     0,     0,     0,
      10,    27,     0,    35,     0,    32,     0,    23,     0,    19,
      22,     0,     0,     0,     0,    15,     0,    68,     0,     0,
      33,     0,     0,     0,   121,    75,   117,   118,     0,     0,
       0,   119,   120,     0,     0,     0,     0,    25,    81,    36,
      92,    96,    99,   104,   107,   111,    80,   109,    76,     0,
      30,    29,     0,    73,     0,     0,     0,    60,    61,     0,
      65,     0,    18,    48,    45,     0,    41,    44,    40,    43,
      42,   116,    58,    14,    67,     0,    16,     0,    31,    20,
      89,    90,    91,     0,     0,     0,    96,    39,     0,    85,
      86,     0,     0,   114,   115,   113,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,    28,     0,     0,    53,    59,     0,    75,     0,
      57,    58,    66,    17,     0,    62,     0,    47,    34,    13,
      74,     0,     0,    37,    77,    83,    88,     0,     0,    79,
      93,    94,    95,    97,    98,   102,   103,   100,   101,   105,
     106,   108,   110,     0,    49,    52,     0,     0,    55,    63,
      64,    26,    38,    84,     0,    82,    78,    54,    51,     0,
       0,    87,    50,     0,     0,    46,     0,    56
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -88,   -88,   -88,   187,   -88,   181,   -88,   100,   -39,   143,
     -88,   118,   109,   -88,   147,    40,   -88,   -87,   -88,   113,
     -88,   -88,   -88,   -88,   -88,   -17,   154,     2,   -88,   -88,
     -38,   -88,   -88,   -34,   -44,    16,   -28,    70,   -54,    72,
     -88,   -62,   -88
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    14,     9,    91,    10,    39,
      17,    40,    33,    34,    35,    67,   115,    93,    94,    95,
      96,   144,    97,    98,    99,   100,    46,    47,    48,    68,
     101,    70,   167,    71,    72,    73,    74,    75,    76,    77,
     127,   102,    78
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      69,   113,   150,    80,    82,    92,    21,   -58,   157,   133,
     134,   117,    12,   123,   124,    45,    31,   131,   132,    29,
      23,    24,   145,   146,   110,   111,   112,   151,    41,   103,
      11,   116,    15,   -58,   106,    50,   125,    42,    53,    16,
      25,    26,    23,    24,   119,   120,   135,   136,   126,    30,
     104,   -58,   153,     4,    13,    43,    92,   184,    32,    44,
     168,    18,    25,    26,   188,    23,    24,   157,   137,   138,
      51,   190,   121,    52,   122,    41,    12,    27,    21,    28,
      36,   183,   185,   166,    42,    25,    26,   173,   174,   169,
     159,   -27,    23,    24,   170,   171,   172,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   158,   192,   179,
     180,   202,    25,    26,    22,   162,   161,   153,   163,   207,
      37,     1,     2,    69,     3,   200,    38,    49,   116,     4,
      79,    83,    54,    55,    56,    57,    84,   203,   193,    85,
      44,   194,   206,   128,   129,   130,    58,    59,    60,   175,
     176,   177,   178,   105,    31,   114,   201,    86,   118,    61,
      62,   139,   142,     4,    87,    88,   140,   160,   147,   198,
     186,   195,   164,    89,    63,    54,    55,    56,    57,    84,
      44,    90,    85,   197,    66,   187,   196,   199,   204,    58,
      59,    60,   205,    19,    20,   156,   109,   141,   149,   108,
      86,   191,    61,    62,   154,   107,     4,    87,    88,     0,
     182,   181,     0,     0,     0,     0,    89,    63,    54,    55,
      56,    57,    84,    44,   152,    85,     0,    66,     0,     0,
       0,     0,    58,    59,    60,     0,     0,     0,     0,     0,
       0,     0,     0,    86,     0,    61,    62,     0,     0,     4,
      87,    88,     0,     0,     0,     0,     0,     0,     0,    89,
      63,    54,    55,    56,    57,    84,    44,   155,    85,     0,
      66,     0,     0,     0,     0,    58,    59,    60,     0,     0,
       0,     0,     0,     0,     0,     0,    86,     0,    61,    62,
       0,     0,     0,    87,    88,     0,     0,     0,     0,     0,
       0,     0,    89,    63,    54,   148,    56,    57,    84,    44,
     189,    85,     0,    66,     0,     0,     0,     0,    58,    59,
      60,     0,     0,     0,     0,     0,     0,     0,     0,    86,
       0,    61,    62,     0,     0,     0,    87,    88,     0,     0,
       0,     0,     0,     0,     0,    89,    63,    54,    55,    56,
      57,    84,    44,     0,    85,     0,    66,     0,     0,     0,
       0,    58,    59,    60,     0,     0,     0,     0,     0,     0,
       0,     0,    86,     0,    61,    62,     0,     0,     0,    87,
      88,     0,    54,    55,    56,    57,     0,     0,    89,    63,
      54,    55,    56,    57,     0,    44,    58,    59,    60,    66,
       0,     0,     0,     0,    58,    59,    60,     0,     0,    61,
      62,     0,     0,    54,    55,    56,    57,    61,    62,     0,
       0,     0,     0,     0,    63,     0,    64,    58,    59,    60,
      65,     0,    63,     0,    66,    81,    54,    55,    56,    57,
      61,    62,    66,    54,    55,    56,    57,     0,     0,     0,
      58,    59,    60,     0,     0,    63,   165,    58,    59,    60,
       0,     0,     0,    61,    62,    66,    54,    55,    56,    57,
      61,    62,     0,     0,     0,     0,     0,     0,    63,     0,
      58,    59,    60,     0,    65,    63,     0,     0,    66,     0,
       0,   -74,   -74,    61,    62,    66,   -74,   -74,   -74,   -74,
     -74,   -74,     0,     0,     0,     0,     0,     0,   143,     0,
       0,     0,     0,     0,   -74,     0,     0,     0,    66,     0,
       0,     0,     0,   -74,     0,     0,   -74,     0,     0,     0,
       0,     0,   -74,   -74,   -74,   -74,   -74,   -74,   -74
};

static const yytype_int16 yycheck[] =
{
      38,    63,    89,    41,    42,    44,     3,     8,    95,    24,
      25,    65,     3,    15,    16,    32,     4,    59,    60,    17,
      12,    13,    84,    85,    58,    59,    60,    89,    38,    46,
       4,    65,     4,    34,    51,    33,    38,    47,    36,     4,
      32,    33,    12,    13,    17,    18,    61,    62,    50,    46,
      48,    52,    91,    34,    45,    47,    95,   144,    46,    51,
     122,     0,    32,    33,   151,    12,    13,   154,    22,    23,
      46,    52,    45,    49,    47,    38,     3,    47,     3,    49,
      48,   143,   144,   121,    47,    32,    33,   131,   132,   127,
     107,    54,    12,    13,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   105,   162,   137,
     138,   198,    32,    33,    45,    49,   114,   156,    52,   206,
       4,    26,    27,   161,    29,   187,    50,    47,   162,    34,
      49,    48,     3,     4,     5,     6,     7,   199,    46,    10,
      51,    49,   204,    56,    57,    58,    17,    18,    19,   133,
     134,   135,   136,    48,     4,    48,   194,    28,     3,    30,
      31,    20,    48,    34,    35,    36,    21,    46,    53,     8,
      14,    48,    55,    44,    45,     3,     4,     5,     6,     7,
      51,    52,    10,    46,    55,    54,    54,    45,    54,    17,
      18,    19,    46,     6,    13,    95,    53,    79,    89,    52,
      28,   161,    30,    31,    91,    51,    34,    35,    36,    -1,
     140,   139,    -1,    -1,    -1,    -1,    44,    45,     3,     4,
       5,     6,     7,    51,    52,    10,    -1,    55,    -1,    -1,
      -1,    -1,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    30,    31,    -1,    -1,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      45,     3,     4,     5,     6,     7,    51,    52,    10,    -1,
      55,    -1,    -1,    -1,    -1,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,
      -1,    -1,    -1,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    45,     3,     4,     5,     6,     7,    51,
      52,    10,    -1,    55,    -1,    -1,    -1,    -1,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,
      -1,    30,    31,    -1,    -1,    -1,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,     3,     4,     5,
       6,     7,    51,    -1,    10,    -1,    55,    -1,    -1,    -1,
      -1,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    30,    31,    -1,    -1,    -1,    35,
      36,    -1,     3,     4,     5,     6,    -1,    -1,    44,    45,
       3,     4,     5,     6,    -1,    51,    17,    18,    19,    55,
      -1,    -1,    -1,    -1,    17,    18,    19,    -1,    -1,    30,
      31,    -1,    -1,     3,     4,     5,     6,    30,    31,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    47,    17,    18,    19,
      51,    -1,    45,    -1,    55,    48,     3,     4,     5,     6,
      30,    31,    55,     3,     4,     5,     6,    -1,    -1,    -1,
      17,    18,    19,    -1,    -1,    45,    46,    17,    18,    19,
      -1,    -1,    -1,    30,    31,    55,     3,     4,     5,     6,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      17,    18,    19,    -1,    51,    45,    -1,    -1,    55,    -1,
      -1,    15,    16,    30,    31,    55,    20,    21,    22,    23,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    26,    27,    29,    34,    64,    65,    66,    67,    69,
      71,     4,     3,    45,    68,     4,     4,    73,     0,    66,
      68,     3,    45,    12,    13,    32,    33,    47,    49,    90,
      46,     4,    46,    75,    76,    77,    48,     4,    50,    72,
      74,    38,    47,    47,    51,    88,    89,    90,    91,    47,
      90,    46,    49,    90,     3,     4,     5,     6,    17,    18,
      19,    30,    31,    45,    47,    51,    55,    78,    92,    93,
      94,    96,    97,    98,    99,   100,   101,   102,   105,    49,
      93,    48,    93,    48,     7,    10,    28,    35,    36,    44,
      52,    70,    71,    80,    81,    82,    83,    85,    86,    87,
      88,    93,   104,    88,    90,    48,    88,    89,    77,    72,
      96,    96,    96,   104,    48,    79,    96,   101,     3,    17,
      18,    45,    47,    15,    16,    38,    50,   103,    56,    57,
      58,    59,    60,    24,    25,    61,    62,    22,    23,    20,
      21,    74,    48,    45,    84,   104,   104,    53,     4,    75,
      80,   104,    52,    71,    82,    52,    70,    80,    90,    88,
      46,    90,    49,    52,    55,    46,    93,    95,   104,    93,
      96,    96,    96,    97,    97,    98,    98,    98,    98,    99,
      99,   102,   100,   104,    80,   104,    14,    54,    80,    52,
      52,    78,   101,    46,    49,    48,    54,    46,     8,    45,
     104,    93,    80,   104,    54,    46,   104,    80
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    65,    65,    66,    66,    66,    66,    67,
      67,    68,    68,    69,    69,    69,    69,    70,    70,    71,
      71,    72,    72,    73,    73,    74,    74,    75,    75,    75,
      75,    76,    76,    77,    77,    77,    78,    78,    79,    79,
      80,    80,    80,    80,    80,    80,    81,    82,    82,    83,
      83,    83,    84,    84,    84,    85,    85,    85,    86,    87,
      87,    87,    88,    88,    88,    88,    88,    89,    89,    90,
      90,    90,    90,    91,    92,    92,    92,    92,    93,    93,
      93,    94,    94,    94,    94,    94,    94,    95,    95,    96,
      96,    96,    96,    97,    97,    97,    97,    98,    98,    98,
      99,    99,    99,    99,    99,   100,   100,   100,   101,   101,
     102,   102,   103,   103,   103,   103,   104,   105,   105,   105,
     105,   105
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     2,     2,
       4,     2,     1,     7,     6,     5,     6,     2,     1,     4,
       6,     3,     1,     3,     1,     2,     5,     1,     4,     3,
       3,     3,     1,     2,     4,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     6,     2,     1,     3,
       5,     4,     2,     1,     3,     3,     7,     2,     1,     2,
       1,     1,     3,     4,     4,     2,     3,     2,     1,     1,
       1,     1,     1,     2,     3,     1,     1,     3,     4,     3,
       1,     1,     4,     3,     4,     2,     2,     3,     1,     2,
       2,     2,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 82 "TinyGo.y"
             {
       list<Statement *>::iterator it = (yyvsp[0].statement_list_t)->begin();
     while(it != (yyvsp[0].statement_list_t)->end()){
         if((*it)->getKind() !=PACKAGE_STATEMENT  && (*it)->getKind() !=IMPORT_STATEMENT){
            //cout << "Error: package and import statements are not allowed in the main function" << endl;
           // exit(1);
           printf("semantic result: %d \n",(*it)->evaluateSemantic());
         }
        it++;
     }
}
#line 1628 "TinyGo_parser.cpp"
    break;

  case 3:
#line 95 "TinyGo.y"
                                  {(yyval.statement_list_t) = (yyvsp[-1].statement_list_t); (yyval.statement_list_t)->push_back((yyvsp[0].statement_t));}
#line 1634 "TinyGo_parser.cpp"
    break;

  case 4:
#line 96 "TinyGo.y"
                           {(yyval.statement_list_t) = new StatementList; (yyval.statement_list_t)->push_back((yyvsp[0].statement_t));}
#line 1640 "TinyGo_parser.cpp"
    break;

  case 5:
#line 99 "TinyGo.y"
                                        {(yyval.statement_t) = (yyvsp[0].statement_t);}
#line 1646 "TinyGo_parser.cpp"
    break;

  case 6:
#line 100 "TinyGo.y"
                          {(yyval.statement_t) = new GlobalDeclaration((yyvsp[0].declaration_t));}
#line 1652 "TinyGo_parser.cpp"
    break;

  case 7:
#line 101 "TinyGo.y"
                      {  (yyval.statement_t)=new ImportDeclaration(); }
#line 1658 "TinyGo_parser.cpp"
    break;

  case 8:
#line 102 "TinyGo.y"
                               { (yyval.statement_t)=new PackageDeclaration();}
#line 1664 "TinyGo_parser.cpp"
    break;

  case 13:
#line 113 "TinyGo.y"
                                                                                              { //void hola(int x){}
                    (yyval.statement_t) = new MethodDefinition((Type)(yyvsp[-1].int_t), (yyvsp[-5].string_t), *(yyvsp[-3].parameter_list_t), (yyvsp[0].statement_t), yylineno );
                    delete (yyvsp[-3].parameter_list_t);
                 }
#line 1673 "TinyGo_parser.cpp"
    break;

  case 14:
#line 117 "TinyGo.y"
                                                                        { // void hola(){}
                     ParameterList * pm = new ParameterList;
                      (yyval.statement_t) = new MethodDefinition((Type)(yyvsp[-1].int_t), (yyvsp[-4].string_t), *pm, (yyvsp[0].statement_t), yylineno );
                      delete pm;
                 }
#line 1683 "TinyGo_parser.cpp"
    break;

  case 15:
#line 122 "TinyGo.y"
                                                             {
                      ParameterList * pm = new ParameterList;
                      (yyval.statement_t) = new MethodDefinition((Type)0, (yyvsp[-3].string_t), *pm, (yyvsp[0].statement_t), yylineno );
                      delete pm;
                      }
#line 1693 "TinyGo_parser.cpp"
    break;

  case 16:
#line 128 "TinyGo.y"
                                                                                { //void hola(int x){}
                    (yyval.statement_t) = new MethodDefinition((Type)0, (yyvsp[-4].string_t), *(yyvsp[-2].parameter_list_t), (yyvsp[0].statement_t), yylineno );
                    delete (yyvsp[-2].parameter_list_t);
                 }
#line 1702 "TinyGo_parser.cpp"
    break;

  case 17:
#line 135 "TinyGo.y"
                                               { (yyval.declaration_list_t) = (yyvsp[-1].declaration_list_t); (yyval.declaration_list_t)->push_back((yyvsp[0].declaration_t));  }
#line 1708 "TinyGo_parser.cpp"
    break;

  case 18:
#line 136 "TinyGo.y"
                              {(yyval.declaration_list_t) = new DeclarationList; (yyval.declaration_list_t)->push_back((yyvsp[0].declaration_t));}
#line 1714 "TinyGo_parser.cpp"
    break;

  case 19:
#line 142 "TinyGo.y"
                                                            { (yyval.declaration_t) = new Declaration((Type)(yyvsp[-1].int_t),*(yyvsp[-2].string_list_t),*(yyvsp[0].init_declarator_list_t), yylineno); delete (yyvsp[-2].string_list_t);  }
#line 1720 "TinyGo_parser.cpp"
    break;

  case 20:
#line 143 "TinyGo.y"
                                                                      { (yyval.declaration_t) = new Declaration((Type)(yyvsp[-1].int_t),*(yyvsp[-4].string_list_t),*(yyvsp[0].init_declarator_list_t), yylineno); delete (yyvsp[-4].string_list_t); }
#line 1726 "TinyGo_parser.cpp"
    break;

  case 21:
#line 148 "TinyGo.y"
                                                               { (yyval.init_declarator_list_t) = (yyvsp[-2].init_declarator_list_t); (yyval.init_declarator_list_t)->push_back((yyvsp[0].init_declarator_t)); }
#line 1732 "TinyGo_parser.cpp"
    break;

  case 22:
#line 149 "TinyGo.y"
                                  { (yyval.init_declarator_list_t) = new InitDeclaratorList; (yyval.init_declarator_list_t)->push_back((yyvsp[0].init_declarator_t)); }
#line 1738 "TinyGo_parser.cpp"
    break;

  case 23:
#line 157 "TinyGo.y"
                              { (yyval.string_list_t) = (yyvsp[-2].string_list_t); (yyval.string_list_t)->push_back((yyvsp[0].string_t));   }
#line 1744 "TinyGo_parser.cpp"
    break;

  case 24:
#line 158 "TinyGo.y"
                 { (yyval.string_list_t) = new list<string>; (yyval.string_list_t)->push_back((yyvsp[0].string_t));   }
#line 1750 "TinyGo_parser.cpp"
    break;

  case 25:
#line 164 "TinyGo.y"
                                 { (yyval.init_declarator_t) = new InitDeclarator( (yyvsp[0].initializer_t), yylineno); }
#line 1756 "TinyGo_parser.cpp"
    break;

  case 26:
#line 165 "TinyGo.y"
                                               { (yyval.init_declarator_t) = new InitDeclarator( (yyvsp[0].initializer_t), yylineno); }
#line 1762 "TinyGo_parser.cpp"
    break;

  case 27:
#line 168 "TinyGo.y"
                  {(yyval.declarator_t) = new Declarator((yyvsp[0].string_t), NULL, false, yylineno);}
#line 1768 "TinyGo_parser.cpp"
    break;

  case 28:
#line 169 "TinyGo.y"
                                                { (yyval.declarator_t) = new Declarator((yyvsp[-3].string_t), (yyvsp[-1].expr_t), true, yylineno);}
#line 1774 "TinyGo_parser.cpp"
    break;

  case 29:
#line 170 "TinyGo.y"
                          {(yyval.declarator_t) = new Declarator((yyvsp[-2].string_t), NULL, true, yylineno);}
#line 1780 "TinyGo_parser.cpp"
    break;

  case 30:
#line 171 "TinyGo.y"
                                                       { (yyval.declarator_t) = new Declarator((yyvsp[-2].string_t), (yyvsp[0].expr_t), false, yylineno);}
#line 1786 "TinyGo_parser.cpp"
    break;

  case 31:
#line 176 "TinyGo.y"
                                                                     {(yyval.parameter_list_t) = (yyvsp[-2].parameter_list_t); (yyval.parameter_list_t)->push_back((yyvsp[0].parameter_t));}
#line 1792 "TinyGo_parser.cpp"
    break;

  case 32:
#line 177 "TinyGo.y"
                                           { (yyval.parameter_list_t) = new ParameterList; (yyval.parameter_list_t)->push_back((yyvsp[0].parameter_t)); }
#line 1798 "TinyGo_parser.cpp"
    break;

  case 33:
#line 181 "TinyGo.y"
                                       { (yyval.parameter_t) = new Parameter((Type)(yyvsp[0].int_t), (yyvsp[-1].declarator_t), false, yylineno); }
#line 1804 "TinyGo_parser.cpp"
    break;

  case 34:
#line 182 "TinyGo.y"
                                                { (yyval.parameter_t) = new Parameter((Type)(yyvsp[0].int_t), (yyvsp[-3].declarator_t), true, yylineno); }
#line 1810 "TinyGo_parser.cpp"
    break;

  case 35:
#line 183 "TinyGo.y"
                                  { (yyval.parameter_t) = new Parameter((Type)0, (yyvsp[0].declarator_t), false, yylineno); }
#line 1816 "TinyGo_parser.cpp"
    break;

  case 36:
#line 186 "TinyGo.y"
                                   {
    InitializerElementList * list = new InitializerElementList;
    list->push_back((yyvsp[0].expr_t));
    (yyval.initializer_t) = new Initializer(*list, yylineno);
}
#line 1826 "TinyGo_parser.cpp"
    break;

  case 37:
#line 191 "TinyGo.y"
                                      { (yyval.initializer_t) = new Initializer(*(yyvsp[-1].initializer_list_t), yylineno); delete (yyvsp[-1].initializer_list_t);  }
#line 1832 "TinyGo_parser.cpp"
    break;

  case 38:
#line 195 "TinyGo.y"
                                                             { (yyval.initializer_list_t) = (yyvsp[-2].initializer_list_t); (yyval.initializer_list_t)->push_back((yyvsp[0].expr_t)); }
#line 1838 "TinyGo_parser.cpp"
    break;

  case 39:
#line 196 "TinyGo.y"
                                        {(yyval.initializer_list_t) = new InitializerElementList; (yyval.initializer_list_t)->push_back((yyvsp[0].expr_t));}
#line 1844 "TinyGo_parser.cpp"
    break;

  case 40:
#line 199 "TinyGo.y"
                                {(yyval.statement_t) = (yyvsp[0].statement_t);}
#line 1850 "TinyGo_parser.cpp"
    break;

  case 41:
#line 200 "TinyGo.y"
                        {(yyval.statement_t) = (yyvsp[0].statement_t); }
#line 1856 "TinyGo_parser.cpp"
    break;

  case 42:
#line 201 "TinyGo.y"
                          {(yyval.statement_t) = (yyvsp[0].statement_t);}
#line 1862 "TinyGo_parser.cpp"
    break;

  case 43:
#line 202 "TinyGo.y"
                         {(yyval.statement_t) = (yyvsp[0].statement_t);}
#line 1868 "TinyGo_parser.cpp"
    break;

  case 44:
#line 203 "TinyGo.y"
                           {(yyval.statement_t) = (yyvsp[0].statement_t);}
#line 1874 "TinyGo_parser.cpp"
    break;

  case 45:
#line 204 "TinyGo.y"
                          {(yyval.statement_t) = (yyvsp[0].statement_t);}
#line 1880 "TinyGo_parser.cpp"
    break;

  case 46:
#line 207 "TinyGo.y"
                                                            {(yyval.statement_t) = new PrintStatement((yyvsp[-1].expr_t), yylineno); }
#line 1886 "TinyGo_parser.cpp"
    break;

  case 47:
#line 210 "TinyGo.y"
                                         { (yyval.statement_list_t) = (yyvsp[-1].statement_list_t); (yyval.statement_list_t)->push_back((yyvsp[0].statement_t)); }
#line 1892 "TinyGo_parser.cpp"
    break;

  case 48:
#line 211 "TinyGo.y"
                          { (yyval.statement_list_t) = new StatementList; (yyval.statement_list_t)->push_back((yyvsp[0].statement_t)); }
#line 1898 "TinyGo_parser.cpp"
    break;

  case 49:
#line 214 "TinyGo.y"
                                              { (yyval.statement_t) = new IfStatement((yyvsp[-1].expr_list_t), (yyvsp[0].statement_t), yylineno); }
#line 1904 "TinyGo_parser.cpp"
    break;

  case 50:
#line 215 "TinyGo.y"
                                                                  {(yyval.statement_t) = new ElseStatement((yyvsp[-3].expr_list_t), (yyvsp[-2].statement_t), (yyvsp[0].statement_t), yylineno);}
#line 1910 "TinyGo_parser.cpp"
    break;

  case 51:
#line 216 "TinyGo.y"
                                                        {(yyval.statement_t) = new ElseStatement((yyvsp[-2].expr_list_t), (yyvsp[-1].statement_t), NULL, yylineno);}
#line 1916 "TinyGo_parser.cpp"
    break;

  case 52:
#line 219 "TinyGo.y"
                                            { (yyval.expr_list_t)=(yyvsp[-1].expr_list_t); (yyval.expr_list_t)->push_back((yyvsp[0].expr_t)); }
#line 1922 "TinyGo_parser.cpp"
    break;

  case 53:
#line 220 "TinyGo.y"
                             { (yyval.expr_list_t) = new ExprList; (yyval.expr_list_t)->push_back((yyvsp[0].expr_t)); }
#line 1928 "TinyGo_parser.cpp"
    break;

  case 54:
#line 221 "TinyGo.y"
                                     { (yyval.expr_list_t) = new ExprList; (yyval.expr_list_t)->push_back((yyvsp[-1].expr_t)); }
#line 1934 "TinyGo_parser.cpp"
    break;

  case 55:
#line 224 "TinyGo.y"
                                           { (yyval.statement_t) =new ForStatement(NULL, NULL,(yyvsp[-1].expr_t), (yyvsp[0].statement_t), yylineno); }
#line 1940 "TinyGo_parser.cpp"
    break;

  case 56:
#line 225 "TinyGo.y"
                                                                          { (yyval.statement_t) = new ForStatement((yyvsp[-5].declarator_t), (yyvsp[-3].expr_t), (yyvsp[-1].expr_t), (yyvsp[0].statement_t), yylineno); }
#line 1946 "TinyGo_parser.cpp"
    break;

  case 57:
#line 226 "TinyGo.y"
                                { (yyval.statement_t) =new ForStatement(NULL, NULL, NULL, (yyvsp[0].statement_t), yylineno); }
#line 1952 "TinyGo_parser.cpp"
    break;

  case 58:
#line 229 "TinyGo.y"
                                  {(yyval.statement_t) = new ExprStatement((yyvsp[0].expr_t), yylineno);}
#line 1958 "TinyGo_parser.cpp"
    break;

  case 59:
#line 232 "TinyGo.y"
                                      { (yyval.statement_t) = new ReturnStatement((yyvsp[0].expr_t), yylineno); }
#line 1964 "TinyGo_parser.cpp"
    break;

  case 60:
#line 233 "TinyGo.y"
                            { (yyval.statement_t) = new BreakStatement( yylineno); }
#line 1970 "TinyGo_parser.cpp"
    break;

  case 61:
#line 234 "TinyGo.y"
                            { (yyval.statement_t) = new ContinueStatement( yylineno); }
#line 1976 "TinyGo_parser.cpp"
    break;

  case 62:
#line 237 "TinyGo.y"
                                        { 
                    DeclarationList * list = new DeclarationList();
                    (yyval.statement_t) = new BlockStatement(*(yyvsp[-1].statement_list_t), *list, yylineno);
                    delete list;
               }
#line 1986 "TinyGo_parser.cpp"
    break;

  case 63:
#line 242 "TinyGo.y"
                                                           {(yyval.statement_t) = new BlockStatement(*(yyvsp[-1].statement_list_t), *(yyvsp[-2].declaration_list_t), yylineno); delete (yyvsp[-2].declaration_list_t); delete (yyvsp[-1].statement_list_t); }
#line 1992 "TinyGo_parser.cpp"
    break;

  case 64:
#line 243 "TinyGo.y"
                                                          {(yyval.statement_t) = new BlockStatement(*(yyvsp[-2].statement_list_t), *(yyvsp[-1].declaration_list_t), yylineno); delete (yyvsp[-2].statement_list_t); delete (yyvsp[-1].declaration_list_t); }
#line 1998 "TinyGo_parser.cpp"
    break;

  case 65:
#line 244 "TinyGo.y"
                         { 
                   StatementList * stmts = new StatementList();
                   DeclarationList * decls = new DeclarationList();
                   (yyval.statement_t) = new BlockStatement(*stmts, *decls, yylineno);
                   delete stmts;
                   delete decls;
               }
#line 2010 "TinyGo_parser.cpp"
    break;

  case 66:
#line 251 "TinyGo.y"
                                          {
                   StatementList * stmt = new StatementList();
                   (yyval.statement_t) = new BlockStatement( *stmt,*(yyvsp[-1].declaration_list_t), yylineno);
                   delete stmt;
               }
#line 2020 "TinyGo_parser.cpp"
    break;

  case 67:
#line 258 "TinyGo.y"
                      { 
        if((yyvsp[0].int_t) == INT){
            (yyval.int_t) = INT_ARRAY;
        }else if((yyvsp[0].int_t) == FLOAT32){
            (yyval.int_t) = FLOAT32_ARRAY;
        }else if((yyvsp[0].int_t) == BOOL){
            (yyval.int_t) = BOOL_ARRAY;
        }else if((yyvsp[0].int_t) == STRING){
            (yyval.int_t) = STRING_ARRAY;
        }
    }
#line 2036 "TinyGo_parser.cpp"
    break;

  case 68:
#line 269 "TinyGo.y"
            {(yyval.int_t) = (yyvsp[0].int_t);}
#line 2042 "TinyGo_parser.cpp"
    break;

  case 69:
#line 272 "TinyGo.y"
                    {(yyval.int_t) = BOOL;}
#line 2048 "TinyGo_parser.cpp"
    break;

  case 70:
#line 273 "TinyGo.y"
                   {(yyval.int_t) = INT;}
#line 2054 "TinyGo_parser.cpp"
    break;

  case 71:
#line 274 "TinyGo.y"
                     {(yyval.int_t) = FLOAT32;}
#line 2060 "TinyGo_parser.cpp"
    break;

  case 72:
#line 275 "TinyGo.y"
                      {(yyval.int_t) = STRING;}
#line 2066 "TinyGo_parser.cpp"
    break;

  case 74:
#line 281 "TinyGo.y"
                                       {(yyval.expr_t) = (yyvsp[-1].expr_t);}
#line 2072 "TinyGo_parser.cpp"
    break;

  case 75:
#line 282 "TinyGo.y"
            {(yyval.expr_t) = new IdExpr((yyvsp[0].string_t), yylineno); }
#line 2078 "TinyGo_parser.cpp"
    break;

  case 76:
#line 283 "TinyGo.y"
               {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 2084 "TinyGo_parser.cpp"
    break;

  case 77:
#line 284 "TinyGo.y"
                           { (yyval.expr_t) = new StringExpr((yyvsp[-1].string_t), yylineno); }
#line 2090 "TinyGo_parser.cpp"
    break;

  case 80:
#line 289 "TinyGo.y"
                                             { (yyval.expr_t) = (yyvsp[0].expr_t); }
#line 2096 "TinyGo_parser.cpp"
    break;

  case 81:
#line 292 "TinyGo.y"
                                       {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 2102 "TinyGo_parser.cpp"
    break;

  case 82:
#line 293 "TinyGo.y"
                                                            { (yyval.expr_t) = new ArrayExpr((IdExpr*)(yyvsp[-3].expr_t), (yyvsp[-1].expr_t), yylineno); }
#line 2108 "TinyGo_parser.cpp"
    break;

  case 83:
#line 294 "TinyGo.y"
                                                 { (yyval.expr_t) = new MethodInvocationExpr((IdExpr*)(yyvsp[-2].expr_t), *(new ArgumentList), yylineno); }
#line 2114 "TinyGo_parser.cpp"
    break;

  case 84:
#line 295 "TinyGo.y"
                                                                          { (yyval.expr_t) = new MethodInvocationExpr((IdExpr*)(yyvsp[-3].expr_t), *(yyvsp[-1].argument_list_t), yylineno); }
#line 2120 "TinyGo_parser.cpp"
    break;

  case 85:
#line 296 "TinyGo.y"
                                                      { (yyval.expr_t) = new PostIncrementExpr((IdExpr*)(yyvsp[-1].expr_t), yylineno); }
#line 2126 "TinyGo_parser.cpp"
    break;

  case 86:
#line 297 "TinyGo.y"
                                                        { (yyval.expr_t) = new PostDecrementExpr((IdExpr*)(yyvsp[-1].expr_t), yylineno); }
#line 2132 "TinyGo_parser.cpp"
    break;

  case 87:
#line 301 "TinyGo.y"
                                                                             {(yyval.argument_list_t) = (yyvsp[-2].argument_list_t);  (yyval.argument_list_t)->push_back((yyvsp[0].expr_t));}
#line 2138 "TinyGo_parser.cpp"
    break;

  case 88:
#line 302 "TinyGo.y"
                                                { (yyval.argument_list_t) = new ArgumentList; (yyval.argument_list_t)->push_back((yyvsp[0].expr_t));}
#line 2144 "TinyGo_parser.cpp"
    break;

  case 89:
#line 305 "TinyGo.y"
                                                {(yyval.expr_t) = new UnaryExpr(INCREMENT, (yyvsp[0].expr_t), yylineno);}
#line 2150 "TinyGo_parser.cpp"
    break;

  case 90:
#line 306 "TinyGo.y"
                                                  {(yyval.expr_t) = new UnaryExpr(DECREMENT, (yyvsp[0].expr_t), yylineno);}
#line 2156 "TinyGo_parser.cpp"
    break;

  case 91:
#line 307 "TinyGo.y"
                                           {(yyval.expr_t) = new UnaryExpr(NOT, (yyvsp[0].expr_t), yylineno);}
#line 2162 "TinyGo_parser.cpp"
    break;

  case 92:
#line 308 "TinyGo.y"
                                     { (yyval.expr_t) = (yyvsp[0].expr_t);}
#line 2168 "TinyGo_parser.cpp"
    break;

  case 93:
#line 312 "TinyGo.y"
                                                                          { (yyval.expr_t) = new MulExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 2174 "TinyGo_parser.cpp"
    break;

  case 94:
#line 313 "TinyGo.y"
                                                       { (yyval.expr_t) = new DivExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 2180 "TinyGo_parser.cpp"
    break;

  case 95:
#line 314 "TinyGo.y"
                                                       { (yyval.expr_t) = new PercentageExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 2186 "TinyGo_parser.cpp"
    break;

  case 96:
#line 315 "TinyGo.y"
                         {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 2192 "TinyGo_parser.cpp"
    break;

  case 97:
#line 318 "TinyGo.y"
                                                                        { (yyval.expr_t) = new AddExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 2198 "TinyGo_parser.cpp"
    break;

  case 98:
#line 319 "TinyGo.y"
                                                                        { (yyval.expr_t) = new SubExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 2204 "TinyGo_parser.cpp"
    break;

  case 99:
#line 320 "TinyGo.y"
                                                {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 2210 "TinyGo_parser.cpp"
    break;

  case 100:
#line 323 "TinyGo.y"
                                                                     { (yyval.expr_t) = new GtExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 2216 "TinyGo_parser.cpp"
    break;

  case 101:
#line 324 "TinyGo.y"
                                                                      { (yyval.expr_t) = new LtExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 2222 "TinyGo_parser.cpp"
    break;

  case 102:
#line 325 "TinyGo.y"
                                                                                     { (yyval.expr_t) = new GteExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 2228 "TinyGo_parser.cpp"
    break;

  case 103:
#line 326 "TinyGo.y"
                                                                                 { (yyval.expr_t) = new LteExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 2234 "TinyGo_parser.cpp"
    break;

  case 104:
#line 327 "TinyGo.y"
                                           {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 2240 "TinyGo_parser.cpp"
    break;

  case 105:
#line 330 "TinyGo.y"
                                                                         { (yyval.expr_t) = new EqExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 2246 "TinyGo_parser.cpp"
    break;

  case 106:
#line 331 "TinyGo.y"
                                                                            { (yyval.expr_t) = new NeqExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 2252 "TinyGo_parser.cpp"
    break;

  case 107:
#line 332 "TinyGo.y"
                                           {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 2258 "TinyGo_parser.cpp"
    break;

  case 108:
#line 335 "TinyGo.y"
                                                                          { (yyval.expr_t) = new LogicalOrExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 2264 "TinyGo_parser.cpp"
    break;

  case 109:
#line 336 "TinyGo.y"
                                             {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 2270 "TinyGo_parser.cpp"
    break;

  case 110:
#line 339 "TinyGo.y"
                                                                          { (yyval.expr_t) = new LogicalAndExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno); }
#line 2276 "TinyGo_parser.cpp"
    break;

  case 111:
#line 340 "TinyGo.y"
                                            {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 2282 "TinyGo_parser.cpp"
    break;

  case 112:
#line 343 "TinyGo.y"
                         { (yyval.int_t) = EQUAL; }
#line 2288 "TinyGo_parser.cpp"
    break;

  case 113:
#line 344 "TinyGo.y"
                                      {(yyval.int_t) = COLONEQUAL; }
#line 2294 "TinyGo_parser.cpp"
    break;

  case 114:
#line 345 "TinyGo.y"
                                   {(yyval.int_t) = PLUSEQUAL; }
#line 2300 "TinyGo_parser.cpp"
    break;

  case 115:
#line 346 "TinyGo.y"
                                    { (yyval.int_t) = MINUSEQUAL; }
#line 2306 "TinyGo_parser.cpp"
    break;

  case 116:
#line 349 "TinyGo.y"
                                  {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 2312 "TinyGo_parser.cpp"
    break;

  case 117:
#line 353 "TinyGo.y"
                     { (yyval.expr_t) = new IntExpr((yyvsp[0].int_t) , yylineno); }
#line 2318 "TinyGo_parser.cpp"
    break;

  case 118:
#line 354 "TinyGo.y"
                       { (yyval.expr_t) = new FloatExpr((yyvsp[0].float_t) , yylineno);}
#line 2324 "TinyGo_parser.cpp"
    break;

  case 119:
#line 355 "TinyGo.y"
                       { (yyval.expr_t) = new BoolExpr(true , yylineno);}
#line 2330 "TinyGo_parser.cpp"
    break;

  case 120:
#line 356 "TinyGo.y"
                       { (yyval.expr_t) = new BoolExpr(false , yylineno); }
#line 2336 "TinyGo_parser.cpp"
    break;

  case 121:
#line 357 "TinyGo.y"
                        { (yyval.expr_t) = new StringExpr((yyvsp[0].string_t) , yylineno);}
#line 2342 "TinyGo_parser.cpp"
    break;


#line 2346 "TinyGo_parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 359 "TinyGo.y"
