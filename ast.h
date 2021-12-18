#include <string>
#include <list>
#include <map>
#include "code.h"


using namespace std;

class Expr;
class InitDeclarator;
class Declaration;
class Parameter;
class Statement;
typedef list<Expr *> InitializerElementList;
typedef list<InitDeclarator *> InitDeclaratorList;
typedef list<Declaration *> DeclarationList;
typedef list<Parameter *> ParameterList;
typedef list<Statement *> StatementList;
typedef list<Expr *> ArgumentList;
typedef list<Expr *> ExprList;
typedef list<string *> IdList;


enum StatementKind{
    WHILE_STATEMENT,
    FOR_STATEMENT,
    IF_STATEMENT,
    EXPRESSION_STATEMENT,
    RETURN_STATEMENT,
    CONTINUE_STATEMENT,
    BREAK_STATEMENT,
    BLOCK_STATEMENT,
    PRINT_STATEMENT,
    FUNCTION_DEFINITION_STATEMENT,
    GLOBAL_DECLARATION_STATEMENT,
    ELSE_STATEMENT,
    IMPORT_STATEMENT,
    PACKAGE_STATEMENT
};


enum UnaryType{
    INCREMENT,
    DECREMENT,
    NOT
};

class Statement{
    public:
        int line;
        virtual int evaluateSemantic() = 0;
        virtual StatementKind getKind() = 0;
        virtual string genCode()=0;

};

class Expr{
    public:
        int line;
        virtual Type getType() = 0;
        virtual void genCode(Code &code)=0;

};

class Initializer{
    public:
        Initializer(InitializerElementList expressions, int line){
            this->expressions = expressions;
            this->line = line;
        }
        InitializerElementList expressions;
        int line;
};

class Declarator{
    public:
        Declarator(string id, Expr* arrayDeclaration, bool isArray, int line){
            this->id = id;
            this->isArray = isArray;
            this->line = line;
            this->arrayDeclaration = arrayDeclaration;
        }
        string id;
        bool isArray;
        int line;
        Expr * arrayDeclaration;
};

class InitDeclarator{
    public:
        InitDeclarator(Type type,Initializer * initializer, int line){
             this->type = type;
            this->initializer = initializer;
            this->line = line;
        }
        Initializer * initializer;
        int line;
        Type type;

};

class Declaration{
    public:
        Declaration(Type type, list<string> ids, InitDeclaratorList declarations, int line){
            this->ids = ids;
            this->type = type;
            this->declarations = declarations;
            this->line = line;
        }
        list<string> ids;
        Type type;
        InitDeclaratorList declarations;
        int line;
        int evaluateSemantic();
        string genCode();

};

class Parameter{
    public:
        Parameter(Type type, Declarator * declarator, bool isArray, int line){
            this->type = type;
            this->declarator = declarator;
            this->line = line;
        }
        Type type;
        Declarator* declarator;
        bool isArray;
        int line;
        int evaluateSemantic();
};

class BlockStatement : public Statement{
    public:
        BlockStatement(StatementList statements, DeclarationList declarations, int line){
            this->statements = statements;
            this->declarations = declarations;
            this->line = line;
        }
        StatementList statements;
        DeclarationList declarations;
        int line;
        int evaluateSemantic();
        string genCode();
        StatementKind getKind(){
            return BLOCK_STATEMENT;
        }
};

class GlobalDeclaration : public Statement {
    public:
        GlobalDeclaration(Declaration * declaration){
            this->declaration = declaration;
        }
        Declaration * declaration;
        int evaluateSemantic();
        string genCode();
        StatementKind getKind(){
            return GLOBAL_DECLARATION_STATEMENT;
        }
};


class ImportDeclaration : public Statement {
    public:
        ImportDeclaration(){
           
        }
        int evaluateSemantic();
        string genCode();
        StatementKind getKind(){
            return IMPORT_STATEMENT;
        }
};

class PackageDeclaration : public Statement {
    public:
        PackageDeclaration(){
           
        }
        int evaluateSemantic();
        string genCode();
        StatementKind getKind(){
            return PACKAGE_STATEMENT;
        }
};


class MethodDefinition : public Statement{
    public:
        MethodDefinition(Type type, string id, ParameterList params, Statement * statement, int line){
            this->type = type;
            this->id = id;
            this->params = params;
            this->statement = statement;
            this->line = line;
        }

        Type type;
        string id;
        ParameterList params;
        Statement * statement;
        int line;
        int evaluateSemantic();
        string genCode();
        StatementKind getKind(){
            return FUNCTION_DEFINITION_STATEMENT;
        }
};

class IntExpr : public Expr{
    public:
        IntExpr(int value, int line){
            this->value = value;
            this->line = line;
        }
        int value;
        Type getType();
        void genCode(Code &code);
       int evaluateSemantic();

};

class FloatExpr : public Expr{
    public:
        FloatExpr(float value, int line){
            this->value = value;
            this->line = line;
        }
        float value;
        Type getType();
        void genCode(Code &code);
};

class BoolExpr : public Expr{
    public:
        BoolExpr(bool value, int line){
            this->value = value;
            this->line = line;
        }
        bool value;
        Type getType();
        void genCode(Code &code);
};


class BinaryExpr : public Expr{
    public:
        BinaryExpr(Expr * expr1, Expr *expr2, int line){
            this->expr1 = expr1;
            this->expr2 = expr2;
            this->line = line;
        }
        Expr * expr1;
        Expr *expr2;
        int line;
};

#define IMPLEMENT_BINARY_EXPR(name) \
class name##Expr : public BinaryExpr{\
    public: \
        name##Expr(Expr * expr1, Expr *expr2, int line) : BinaryExpr(expr1, expr2, line){}\
        Type getType(); \
        void genCode(Code &code); \
};

class UnaryExpr : public Expr{
    public:
        UnaryExpr(int type, Expr* expr, int line){
            this->type = type;
            this->expr = expr;
            this->line = line;
        }
        int type;
        Expr* expr;
        int line;
        Type getType();
        void genCode(Code &code);
};

class PostIncrementExpr: public Expr{
    public:
        PostIncrementExpr(Expr * expr, int line){
            this->expr = expr;
            this->line = line;
        }
        Expr * expr;
        int line;
        Type getType();
        void genCode(Code &code);
};

class PostDecrementExpr: public Expr{
    public:
        PostDecrementExpr(Expr * expr, int line){
            this->expr = expr;
            this->line = line;
        }
        Expr * expr;
        int line;
        Type getType();
        void genCode(Code &code);
};

class IdExpr : public Expr{
    public:
        IdExpr(string id, int line){
            this->id = id;
            this->line = line;
        }
        string id;
        int line;
        Type getType();
        void genCode(Code &code);
};

class ArrayExpr : public Expr{
    public:
        ArrayExpr(IdExpr * id, Expr * expr, int line){
            this->id = id;
            this->expr = expr;
            this->line = line;
        }
        IdExpr * id;
        Expr * expr;
        int line;
        Type getType();
        void genCode(Code &code);

};

class MethodInvocationExpr : public Expr{
    public:
        MethodInvocationExpr(IdExpr * id, ArgumentList args, int line){
            this->id = id;
            this->args = args;
            this->line = line;
        }
        IdExpr * id;
        ArgumentList args;
        int line;
        Type getType();
        void genCode(Code &code);
};

class StringExpr : public Expr{
    public:
        StringExpr(string value, int line){
            this->value = value;
            this->line = line;
        }
        string value;
        int line;
        Type getType();
        void genCode(Code &code);

};

// class WhileStatement: public Statement{
//     public:
//         WhileStatement(Expr * expr, Statement * stmt, int line){
//             this->expr = expr;
//             this->stmt = stmt;
//             this->line = line;
//         }
//         Expr* expr;
//         Statement * stmt;
//         int line;
//         int evaluateSemantic();
//         StatementKind getKind(){
//             return WHILE_STATEMENT;
//         }
// };

class ElseStatement : public Statement{
    public:
        ElseStatement(ExprList * expressions, Statement * trueStatement, Statement * falseStatement, int line){
            this->expressions = expressions;
            this->trueStatement = trueStatement;
            this->line = line;
            this->falseStatement = falseStatement;
        }
        ExprList * expressions;
        Statement * trueStatement;
        Statement * falseStatement;
        int line;
        int evaluateSemantic();
        string genCode();
        StatementKind getKind(){return ELSE_STATEMENT;}
};

class IfStatement : public Statement{
    public:
        IfStatement(ExprList * expressions, Statement * trueStatement, int line){
            this->expressions = expressions;
            this->trueStatement = trueStatement;
            this->line = line;
        }
        ExprList * expressions;
        Statement * trueStatement;
        int line;
        int evaluateSemantic();
        string genCode();
        StatementKind getKind(){return IF_STATEMENT;}
};

class ForStatement : public Statement{
    public:
        ForStatement(Declarator* declarator,Expr * expressionLeft, Expr * expressionRight, Statement * statement, int line){
            this->declarator=declarator;
            this->expressionLeft=expressionLeft;
            this->expressionRight=expressionRight;
            this->statement = statement;
            this->line = line;
        }
        Declarator* declarator;
        Expr * expressionLeft;
        Expr * expressionRight;
        Statement * statement;
        int line;
        int evaluateSemantic();
        string genCode();
        StatementKind getKind(){return FOR_STATEMENT;}
};



class ExprStatement : public Statement{
    public:
        ExprStatement(Expr * expr, int line){
            this->expr = expr;
            this->line = line;
        }
        Expr * expr;
        int line;

        int evaluateSemantic();
        string genCode();
        StatementKind getKind(){return EXPRESSION_STATEMENT;}
};

class BreakStatement : public Statement{
    public:
        BreakStatement( int line){
            this->line = line;
        }
                int line;

        int evaluateSemantic();
        string genCode();

        StatementKind getKind(){return BREAK_STATEMENT;}
};

class ContinueStatement : public Statement{
    public:
        ContinueStatement( int line){
            this->line = line;
        }
        int line;

        int evaluateSemantic();
        string genCode();
        StatementKind getKind(){return BREAK_STATEMENT;}
};


class ReturnStatement : public Statement{
    public:
        ReturnStatement(Expr * expr, int line){
            this->expr = expr;
            this->line = line;
        }
        Expr * expr;
        int line;
        int evaluateSemantic();
        string genCode();
        StatementKind getKind(){return RETURN_STATEMENT;}
};


class PrintStatement : public Statement{
    public:
        PrintStatement(Expr * expr, int line){
            this->expr = expr;
            this->line = line;
        }
       int line;
        Expr * expr;
        int evaluateSemantic();
        string genCode();
        StatementKind getKind(){return PRINT_STATEMENT;}
};


IMPLEMENT_BINARY_EXPR(Add);
IMPLEMENT_BINARY_EXPR(Sub);
IMPLEMENT_BINARY_EXPR(Mul);
IMPLEMENT_BINARY_EXPR(Div);
IMPLEMENT_BINARY_EXPR(Eq);
IMPLEMENT_BINARY_EXPR(Neq);
IMPLEMENT_BINARY_EXPR(Gte);
IMPLEMENT_BINARY_EXPR(Lte);
IMPLEMENT_BINARY_EXPR(Gt);
IMPLEMENT_BINARY_EXPR(Lt);
IMPLEMENT_BINARY_EXPR(LogicalAnd);
IMPLEMENT_BINARY_EXPR(LogicalOr);
IMPLEMENT_BINARY_EXPR(Assign);
IMPLEMENT_BINARY_EXPR(PlusAssign);
IMPLEMENT_BINARY_EXPR(MinusAssign);
///agregado
IMPLEMENT_BINARY_EXPR(Percentage);