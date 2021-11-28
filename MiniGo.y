%{
//http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
    #include <cstdio>
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
%}

%union{
    const char * string_t;
    int int_t;
    float float_t;
    bool bool_t;
    // Expr * expr_t;
    // ArgumentList * argument_list_t;
    // Statement * statement_t;
    // StatementList * statement_list_t;
    // InitDeclaratorList * init_declarator_list_t;
    // InitDeclarator * init_declarator_t;
    // Declarator * declarator_t;
    // Initializer * initializer_t;
    // InitializerElementList * initializer_list_t;
    // Declaration * declaration_t;
    // DeclarationList * declaration_list_t;
    // Parameter * parameter_t;
    // ParameterList * parameter_list_t;
}

%token TK_LIT_STRING TK_ID
%token TK_LIT_INT 
%token TK_LIT_FLOAT
%token TK_IF TK_ELSE
%token TK_FOR TK_WHILE TK_BREAK TK_CONTINUE TK_RETURN
%token TK_VOID TK_INT_TYPE TK_FLOAT_TYPE  TK_STRING_TYPE
%token TK_PRINTF
%token TK_PLUS_EQUAL TK_MINUS_EQUAL TK_PLUS_PLUS TK_MINUS_MINUS
%token TK_OR TK_AND
%token TK_EQUAL TK_NOT_EQUAL TK_GREATER_OR_EQUAL TK_LESS_OR_EQUAL
%token TK_PACKAGE TK_IMPORT TK_FUNCTION
%token TK_BOOL_TYPE TK_VAR_TYPE TK_TRUE TK_FALSE 
%token TK_PERCENTAJE_EQUAL TK_COLON_EQUAL TK_DIVISION_EQUAL TK_POWER_EQUAL TK_ASTERISK_EQUAL TK_AMPERSAND_EQUAL
%token TK_LINE_EQUAL TK_EXCLAMATION_EQUAL


/* %type<expr_t> assignment_expression logical_or_expression */
//%type<statement_list_t> /*statement_list*/ input
/* %type<statement_t> external_declaration method_definition //block_statement statement */
/* %type<declaration_t> declaration
%type<declaration_list_t> declaration_list
%type<initializer_t> initializer
%type<initializer_list_t> initializer_list */
/* %type<declarator_t> declarator */
/* %type<init_declarator_t> init_declarator
%type<init_declarator_list_t> init_declarator_list */
/* %type<parameter_t> parameter_declaration
%type<parameter_list_t> parameters_type_list */
/* %type<int_t> type assignment_operator
%type<expr_t> constant expression logical_and_expression additive_expression multiplicative_expression equality_expression relational_expression
%type<expr_t> unary_expression postfix_expression primary_expression
%type<argument_list_t> argument_expression_list
%type <statement_t> if_statement while_statement expression_statement jump_statement */

%%
start: input {printf("Codigo Valido\n");}

input: input external_declaration 
    | external_declaration 
    ;

external_declaration: method_definition
            ;

method_definition: TK_FUNCTION TK_ID '(' parameters_type_list ')' function_array type block_statement
            | TK_FUNCTION TK_ID '(' ')' function_array type block_statement
            ;

parameters_type_list: parameter_declaration 
            | parameters_type_list ',' parameter_declaration
            ;
            
parameter_declaration : declarator data_type
            | TK_ID
            ;

function_array : '[' ']'
            |
            ;

declarator : TK_ID 
        | TK_ID '[' ']' 
        | TK_ID '[' TK_LIT_INT ']'
        ;

data_type: TK_INT_TYPE
        | TK_FLOAT_TYPE
        | TK_BOOL_TYPE
        | TK_STRING_TYPE
        ;

block_statement: '{'  '}'
            ;

type: TK_INT_TYPE
    | TK_FLOAT_TYPE
    | TK_BOOL_TYPE
    | TK_STRING_TYPE
    |
    ;
%%