#include "ast.h"
#include <iostream>
class ContextStack
{
public:
    struct ContextStack *prev;
    map<string, Type> variables;
};

class FunctionInfo
{
public:
    Type returnType;
    list<Parameter *> parameters;
};

map<string, Type> globalVariables = {};
map<string, Type> variables;
map<string, FunctionInfo *> methods;
map<string, Type> resultTypes = {
    {"INT,INT", INT},
    {"FLOAT,FLOAT", FLOAT32},
    {"INT,FLOAT", FLOAT32},
    {"FLOAT,INT", FLOAT32},
    {"STRING,STRING", STRING},
    {"BOOL,BOOl", BOOL},
};



string getTypeName(Type type)
{
    switch (type)
    {
    case INT:
        return "INT";
    case STRING:
        return "STRING";
    case BOOL:
        return "BOOL";
    case FLOAT32:
        return "FLOAT32";
    case INT_ARRAY:
        return "INT";
    case FLOAT32_ARRAY:
        return " FLOAT32";
    case BOOL_ARRAY:
        return "BOOL";
    case STRING_ARRAY:
        return "STRING";
    }

    cout << "Unknown type" << endl;
    exit(0);
}

ContextStack *context = NULL;

void pushContext()
{
    variables.clear();
    ContextStack *c = new ContextStack();
    c->variables = variables;
    c->prev = context;
    context = c;
}

void popContext()
{
    if (context != NULL)
    {                                           //////////////if(bool){      context->previous
        ContextStack *previous = context->prev; /////////////////while(bool){    context->actual
        free(context);                          /////////////////////statement        ------------libero el actual y regreso al anterior
        context = previous;                     //////////////////}
    }                                           ///////////////}
}

Type getLocalVariableType(string id)
{
    ContextStack *currContext = context;
    while (currContext != NULL)
    {
        if (currContext->variables[id] != 0)
            return currContext->variables[id];
        currContext = currContext->prev;
    }
    if (!context->variables.empty()) ////////////validando hacia los contextos de atras  en los statements
        return context->variables[id];
   return INVALID;
}

Type getVariableType(string id)
{
    if (!globalVariables.empty())
        return globalVariables[id];
    return INVALID;
}

bool variableExists(string id)
{
    Type value;
    if (context != NULL)
    {
        value = getLocalVariableType(id);
        //context->variables[id] != 0
        if (value != 0)
            return true;
    }
    return false;
}

int BlockStatement::evaluateSemantic()
{
    cout << "BlockStatement" << endl;
    list<Declaration *>::iterator itd = this->declarations.begin();
    while (itd != this->declarations.end())
    {

       Declaration *dec = *itd;
       if (dec != NULL)
       {
           dec->evaluateSemantic();
       }

       itd++;
    }

    list<Statement *>::iterator its = this->statements.begin();
    while (its != this->statements.end())
    {
        Statement *stmt = *its;
        if (stmt != NULL)
        {
            stmt->evaluateSemantic();
        }

        its++;
    }

    return 0;
}

int Declaration::evaluateSemantic()
{
    cout<<"Declaration"<<endl;
    
    // list<string *>::iterator it = this->ids.begin();
    //  while (it != this->ids.end()){
    //      cout<<"id: "<<*it<<endl;

    //  }
   
   // cout<<this->ids.size();
    //list<string>::iterator it = this->ids.begin();
    while (it != this->ids.end())
    {   
        //cout<<this->type<<end;
       // cout<<"id: "<<(it)<<endl;
        // InitDeclarator *declaration = (*it);
        // Initializer *init = declaration->initializer;
        // cout<<init->expressions<<endl;
        // InitializerElementList Initializer = init->expressions;
        // list<Expr *>::iterator ite =  init->expressions.begin();
        //ite.

       // list<Expr *>::iterator ite = init->expressions.begin();
        
        // while(it != this->declarations.end()){

        //     init->evaluateSemantic();
        //     init = init->next;
        // }
        //cout<<"id: "<<init->expressions<<endl;
        // if (declaration->declarator->isArray)
        // {
        //     if (declaration->declarator->arrayDeclaration == NULL && declaration->initializer == NULL)
        //     {
        //         cout << "error: storage size of: " << declaration->declarator->id << " is unknown line: " << this->line << endl;
        //         exit(0);
        //     }
        // }
        // if (declaration->initializer != NULL)
        // {
        //     list<Expr *>::iterator ite = declaration->initializer->expressions.begin();
        //     while (ite != declaration->initializer->expressions.end())
        //     {
        //         Type exprType = (*ite)->getType();
        //         if (exprType != FLOAT32 && exprType != INT)
        //         {
        //             cout << "error: invalid conversion from: " << getTypeName(exprType) << " to " << getTypeName(this->type) << " line: " << this->line << endl;
        //             exit(0);
        //         }
        //         ite++;
        //     }
        // }
        // if (!variableExists(declaration->declarator->id))
        // {
        //     context->variables[declaration->declarator->id] = this->type;
        // }
        // else
        // {
        //     cout << "error: redefinition of variable: " << declaration->declarator->id << " line: " << this->line << endl;
        //     exit(0);
        // }
        it++;
    }
    return 0;
}

int GlobalDeclaration::evaluateSemantic()
{
    cout<<"GlobalDeclaration"<<endl;
    //TODO: evaluar semántica.
    return 0;
}

void addMethodDeclaration(string id, int line, Type type, ParameterList params)
{
    if (methods[id] != 0)
    {
        cout << "redefinition of function " << id << " in line: " << line << endl;
        exit(0);
    }
    methods[id] = new FunctionInfo();
    methods[id]->returnType = type;
    methods[id]->parameters = params;
}

int MethodDefinition::evaluateSemantic()
{
    if (this->params.size() > 4)
    {
        cout << "Method: " << this->id << " can't have more than 4 parameters, line: " << this->line << endl;
        exit(0);
    }

    addMethodDeclaration(this->id, this->line, this->type, this->params);
    pushContext();

    list<Parameter *>::iterator it = this->params.begin();
    while (it != this->params.end())
    {
        (*it)->evaluateSemantic();
        it++;
    }

    if (this->statement != NULL)
    {
        this->statement->evaluateSemantic();
    }
     popContext();

    return 0;
}

Type IntExpr::getType()
{
    return INT;
}

Type FloatExpr::getType()
{
    return FLOAT32;
}

Type BoolExpr::getType()
{
    return BOOL;
}

Type StringExpr::getType()
{
    return STRING;
}

#define IMPLEMENT_BINARY_GET_TYPE(name)                                                                                           \
    Type name##Expr::getType()                                                                                                    \
    {                                                                                                                             \
        return INVALID;                                                                                                            \
    }                                                                                                                               \

#define IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(name)                                                                                   \
    Type name##Expr::getType()                                                                                                    \
    {                                                                                                                             \
        return INVALID;                                                                                                          \
    }                                                                                                                            \

Type getUnaryType(Type expressionType, int unaryOperation)
{
    // switch (unaryOperation)
    // {
    // case INCREMENT:
    // case DECREMENT:
    //     if (expressionType == INT || expressionType == FLOAT32)
    //         return expressionType;
    // case NOT:
    //     if (expressionType == BOOL)
    //         return BOOL;
    // }

    // cerr << "Error: Invalid type" << endl;
    //exit(0);
    return INVALID;
} 

int Parameter::evaluateSemantic()
{
    // if (!variableExists(this->declarator->id))
    // {
    //     context->variables[declarator->id] = this->type;
    // }
    // else
    // {
    //     cout << "error: redefinition of variable: " << declarator->id << " line: " << this->line << endl;
    //     exit(0);
    // }
    return 0;
}

Type UnaryExpr::getType()
{
   Type exprType = this->expr->getType();
    return getUnaryType(exprType, this->type);
    return INVALID;
}

Type ArrayExpr::getType()
{
    //return this->id->getType();
       return INVALID;
}

Type IdExpr::getType()
{
    Type value;
    if (context != NULL)
    {
        value = getLocalVariableType(this->id);
        if (value != 0)
            return value;
    }
    value = getVariableType(this->id);
    if (value == 0)
    {
        cout << "error: '" << this->id << "' was not declared in this scope line: " << this->line << endl;
        exit(0);
    }
    return value;
    // return INVALID;
}

Type MethodInvocationExpr::getType()
{
    // FunctionInfo *func = methods[this->id->id];
    // if (func == NULL)
    // {
    //     cout << "error: function " << this->id->id << " not found, line: " << this->line << endl;
    //     exit(0);
    // }
    // Type funcType = func->returnType;
    // if (func->parameters.size() > this->args.size())
    // {
    //     cout << "error: to few arguments to function" << this->id->id << " line: " << this->line << endl;
    //     exit(0);
    // }
    // if (func->parameters.size() < this->args.size())
    // {
    //     cout << "error: to many arguments to function " << this->id->id << " line: " << this->line << endl;
    //     exit(0);
    // }

    // list<Parameter *>::iterator paramIt = func->parameters.begin();
    // list<Expr *>::iterator argsIt = this->args.begin();
    // while (paramIt != func->parameters.end() && argsIt != this->args.end())
    // {
    //     string paramType = getTypeName((*paramIt)->type);
    //     string argType = getTypeName((*argsIt)->getType());
    //     if (paramType != argType)
    //     {
    //         cout << "error: invalid conversion from: " << argType << " to " << paramType << " line: " << this->line << endl;
    //         exit(0);
    //     }
    //     paramIt++;
    //     argsIt++;
    // }

    // return funcType;
    return INVALID;
}

Type PostIncrementExpr::getType()
{
    //return this->expr->getType();
    return INVALID;
}

Type PostDecrementExpr::getType()
{
    //return this->expr->getType();
    return INVALID;
}



int ElseStatement::evaluateSemantic()
{
    list<Expr *>::iterator itr = this->expressions->begin();
    while (itr != this->expressions->end())
    {
        string expressionType = getTypeName((*itr)->getType());
        if (expressionType != "BOOL")
        {
            cout << "Expression for if must be boolean";
            exit(0);
        }
        pushContext();
        this->trueStatement->evaluateSemantic();
        popContext();
        pushContext();
        if (this->falseStatement != NULL)
            this->falseStatement->evaluateSemantic();
        popContext();
        itr++;
    }

    return 0;
}

/*
while(true){
    if(true){
        int a = 5;
    }
}
*/

int IfStatement::evaluateSemantic()
{
    list<Expr *>::iterator itr = this->expressions->begin();
    cout << "If" << endl;
    while (itr != this->expressions->end())
    {
        string expressionType = getTypeName((*itr)->getType());
        cout << expressionType << endl;
        if (expressionType != "BOOL")
        {
            cout << "Expression for if must be boolean";
            exit(0);
        }
        pushContext();
        this->trueStatement->evaluateSemantic();
        popContext();
        itr++;
    }
    return 0;
}

int ExprStatement::evaluateSemantic()
{
     return this->expr->getType();
}

int ReturnStatement::evaluateSemantic()
{
   return this->expr->getType();
}

int BreakStatement::evaluateSemantic()
{
    return 0;
}

int ContinueStatement::evaluateSemantic()
{
    return 0;
}

int PrintStatement::evaluateSemantic()
{
    return 0;
}
int ImportDeclaration::evaluateSemantic()
{
    return 0;
}
int PackageDeclaration::evaluateSemantic()
{
    return 0;
}

int ForStatement::evaluateSemantic()
{
    // if (this->declarator != NULL)
    // {
    //     if (!variableExists(this->declarator->id))
    //     {
    //         context->variables[declarator->id] = VAR;
    //     }
    // }
    // if (this->expressionLeft != NULL)
    // {
    //     if (this->expressionLeft->getType() != BOOL)
    //     {
    //         cout << "Expression in declaration 'for' must be boolean";
    //         exit(0);
    //     }
    //     pushContext();
    //     if (this->statement != NULL)
    //     {
    //         this->statement->evaluateSemantic();
    //     }
    //     popContext();
    // }

    return 0;
}

IMPLEMENT_BINARY_GET_TYPE(Add);
IMPLEMENT_BINARY_GET_TYPE(Sub);
IMPLEMENT_BINARY_GET_TYPE(Mul);
IMPLEMENT_BINARY_GET_TYPE(Div);
IMPLEMENT_BINARY_GET_TYPE(Assign);
IMPLEMENT_BINARY_GET_TYPE(PlusAssign);
IMPLEMENT_BINARY_GET_TYPE(MinusAssign);
IMPLEMENT_BINARY_GET_TYPE(Percentage);

IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Eq);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Neq);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Gte);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Lte);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Gt);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Lt);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(LogicalAnd);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(LogicalOr);
