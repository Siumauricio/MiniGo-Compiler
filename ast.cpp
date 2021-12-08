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
    {"FLOAT32,FLOAT32", FLOAT32},
    {"INT,FLOAT32", FLOAT32},
    {"FLOAT32,INT", FLOAT32},
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
bool globalVariableExists(string id)
{
    Type value;
    if (!globalVariables.empty())
    {
        value = getVariableType(id);
        if (value != 0)
            return true;
    }
    return false;
}

int BlockStatement::evaluateSemantic()
{
   // cout << "BlockStatement" << endl;
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
            cout<< "Stmt "<< stmt->getKind()<<endl;
            stmt->evaluateSemantic();
        }
        its++;
    }
    return 0;
}

int Declaration::evaluateSemantic()
{
    //cout << "\nDeclaration" << endl;
    list<string>::iterator itList = this->ids.begin();
    while(itList != this->ids.end()){
        
      if (!variableExists(*itList) && !globalVariableExists(*itList))
        {
            context->variables[*itList] = this->type;
        }else{
            cout<<"variable: "<<*itList<<" type: "<<getTypeName(this->type)<<" already exists"<<endl;
            exit(0);
        }
        cout<<"id: "<<*itList<<endl;
        itList++;
    }
    

    list<InitDeclarator * >::iterator it = this->declarations.begin();
    while(it != this->declarations.end()){
        InitDeclarator * declaration = (*it);
        if(declaration->initializer != NULL){
            list<Expr *>::iterator ite = declaration->initializer->expressions.begin();
            while(ite!= declaration->initializer->expressions.end()){
                Type exprType = (*ite)->getType();
                // cout<<"exprType: "<<getTypeName(exprType)<<endl;
                // cout<<"type: "<<getTypeName(this->type)<<endl;
                if(getTypeName(exprType) != getTypeName(this->type)){
                    cout<<"error: invalid conversion from: "<< getTypeName(exprType) <<" to " <<getTypeName(this->type)<< " line: "<<this->line <<endl;
                    exit(0);
                }
                ite++;
            }
        }
       
    it++;
  }
    return 0;
}

int GlobalDeclaration::evaluateSemantic()
{
    //cout<<"GlobalDeclaration"<<endl;
    list<string>::iterator itList = this->declaration->ids.begin();
    while(itList != this->declaration->ids.end()){
        
      if (!globalVariableExists(*itList))
        {
            globalVariables[*itList] = this->declaration->type;
        }else{
            cout<<"variable: "<<*itList<<" type: "<<getTypeName(this->declaration->type)<<" already exists"<<endl;
            exit(0);
        }
        cout<<"id: "<<*itList<<endl;
        itList++;
    }
    

    list<InitDeclarator*>::iterator it = this->declaration->declarations.begin();
    while(it != this->declaration->declarations.end()){
        InitDeclarator * declaration = (*it);
        if(declaration->initializer != NULL){
            list<Expr *>::iterator ite = declaration->initializer->expressions.begin();
            while(ite!= declaration->initializer->expressions.end()){
                Type exprType = (*ite)->getType();
                //cout<<"exprType: "<<getTypeName(exprType)<<endl;
                //cout<<"type: "<<getTypeName(this->declaration->type)<<endl;
                if(getTypeName(exprType) != getTypeName(this->declaration->type)){
                    cout<<"error: invalid conversion from: "<< getTypeName(exprType) <<" to " <<getTypeName(this->declaration->type)<< " line: "<<this->line <<endl;
                    exit(0);
                }
                ite++;
            }
        }
       
   it++;
  }
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

#define IMPLEMENT_BINARY_GET_TYPE(name)\
Type name##Expr::getType(){\
    string leftType = getTypeName(this->expr1->getType());\
    string rightType = getTypeName(this->expr2->getType());\
    Type resultType = resultTypes[leftType+","+rightType];\
    if(resultType == 0){\
        cerr<< "Error: type "<< leftType <<" can't be converted to type "<< rightType <<" line: "<<this->line<<endl;\
        exit(0);\
    }\
    return resultType; \
}\

#define IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(name)\
Type name##Expr::getType(){\
    string leftType = getTypeName(this->expr1->getType());\
    string rightType = getTypeName(this->expr2->getType());\
    Type resultType = resultTypes[leftType+","+rightType];\
    if(resultType == 0){\
        cerr<< "Error: type "<< leftType <<" can't be converted to type "<< rightType <<" line: "<<this->line<<endl;\
        exit(0);\
    }\
    return BOOL; \
}\

Type getUnaryType(Type expressionType, int unaryOperation)
{
    switch (unaryOperation)
    {
    case INCREMENT:
    case DECREMENT:
        if (expressionType == INT || expressionType == FLOAT32)
            return expressionType;
    case NOT:
        if (expressionType == BOOL)
            return BOOL;
    }

    cerr << "Error: Invalid type" << endl;
    exit(0);
    return INVALID;
} 

int Parameter::evaluateSemantic()
{
    if (!variableExists(this->declarator->id))
    {
        context->variables[declarator->id] = this->type;
    }
    else
    {
        cout << "error: redefinition of variable: " << declarator->id << " line: " << this->line << endl;
        exit(0);
    }
    return 0;
}

Type UnaryExpr::getType()
{

   Type exprType = this->expr->getType();
    return getUnaryType(exprType, this->type);
 //   return INVALID;
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
    FunctionInfo *func = methods[this->id->id];
    if (func == NULL)
    {
        cout << "error: function " << this->id->id << " not found, line: " << this->line << endl;
        exit(0);
    }
    Type funcType = func->returnType;
    if (func->parameters.size() > this->args.size())
    {
        cout << "error: to few arguments to function" << this->id->id << " line: " << this->line << endl;
        exit(0);
    }
    if (func->parameters.size() < this->args.size())
    {
        cout << "error: to many arguments to function " << this->id->id << " line: " << this->line << endl;
        exit(0);
    }

    list<Parameter *>::iterator paramIt = func->parameters.begin();
    list<Expr *>::iterator argsIt = this->args.begin();
    while (paramIt != func->parameters.end() && argsIt != this->args.end())
    {
        string paramType = getTypeName((*paramIt)->type);
        string argType = getTypeName((*argsIt)->getType());
        if (paramType != argType)
        {
            cout << "error: invalid conversion from: " << argType << " to " << paramType << " line: " << this->line << endl;
            exit(0);
        }
        paramIt++;
        argsIt++;
    }

    return funcType;
   // return INVALID;
}

Type PostIncrementExpr::getType()
{
    Type idType= this->expr->getType();
    switch(idType){
        case INT:
        case FLOAT32:
              return this->expr->getType();
    }
        cout<<"Cannot increment a variable type: "<<getTypeName(idType)<<endl;
        exit(0);
}

Type PostDecrementExpr::getType()
{
    Type idType= this->expr->getType();
    switch(idType){
        case INT:
        case FLOAT32:
              return this->expr->getType();
    }
        cout<<"Cannot decrement a variable type: "<<getTypeName(idType)<<endl;
        exit(0);
}

int ElseStatement::evaluateSemantic()
{
    //cout << "\nelse statement" << endl;
    list<Expr *>::iterator itr = this->expressions->begin();
    while (itr != this->expressions->end())
    {
        string expressionType = getTypeName((*itr)->getType());
        if (expressionType != "BOOL")
        {
            cout << "Error Expression for if must be boolean\n";
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


int IfStatement::evaluateSemantic()
{
   // cout << "\nIf" << endl;

    list<Expr *>::iterator itr = this->expressions->begin();
    while (itr != this->expressions->end())
    {
        string expressionType = getTypeName((*itr)->getType());
       
        if (expressionType != "BOOL")
        {
            cout << "Error Expression for if must be boolean 1\n";
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
    //18 te encontre
    

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
   return this->expr->getType();
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
   
    if (this->declarator != NULL)
    {
        if (!variableExists(this->declarator->id))
        {
            context->variables[declarator->id] = this->declarator->arrayDeclaration->getType();
        }
    }
    if (this->expressionLeft != NULL)
    {
        
        if (this->expressionLeft->getType() != BOOL)
        {
            cout << "Expression in declaration 'for' must be boolean";
            exit(0);
        }
        pushContext();
        if (this->statement != NULL)
        {
            this->statement->evaluateSemantic();
        }
        popContext();
    }

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
