#include "ast.h"
#include <iostream>
#include <set>
#include "asm.h"
#include <sstream>

template <typename Base, typename T>
inline bool instanceof (const T *)
{
    return is_base_of<Base, T>::value;
}
class ContextStack
{
public:
    struct ContextStack *prev;
    map<string, Type> variables;
};
class VariableInfo
{
public:
    VariableInfo(int offset, bool isArray, bool isParameter, Type type)
    {
        this->offset = offset;
        this->isArray = isArray;
        this->isParameter = isParameter;
        this->type = type;
    }
    int offset;
    bool isArray;
    bool isParameter;
    Type type;
};

class FunctionInfo
{
public:
    Type returnType;
    list<Parameter *> parameters;
};
const char *intTemps[] = {"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9"};
const char *floatTemps[] = {"$f0",
                            "$f1",
                            "$f2",
                            "$f3",
                            "$f4",
                            "$f5",
                            "$f6",
                            "$f7",
                            "$f8",
                            "$f9",
                            "$f10",
                            "$f11",
                            "$f12",
                            "$f13",
                            "$f14",
                            "$f15",
                            "$f16",
                            "$f17",
                            "$f18",
                            "$f19",
                            "$f20",
                            "$f21",
                            "$f22",
                            "$f23",
                            "$f24",
                            "$f25",
                            "$f26",
                            "$f27",
                            "$f28",
                            "$f29",
                            "$f30",
                            "$f31"};

#define INT_TEMP_COUNT 10
#define FLOAT_TEMP_COUNT 32
set<string> intTempMap;
set<string> floatTempMap;
set<string> boolTempMap;
ContextStack *context = NULL;
extern Asm assemblyFile;
int globalStackPointer = 0;
map<string, VariableInfo *> codeGenerationVars;
int labelCounter = 0;

map<string, Type> globalVariables = {};
map<string, Type> variables;
map<string, FunctionInfo *> methods;
map<string, Type> resultTypes = {
    {"INT,INT", INT},
    {"FLOAT32,FLOAT32", FLOAT32},
    {"INT,FLOAT32", FLOAT32},
    {"FLOAT32,INT", FLOAT32},
    {"STRING,STRING", STRING},
    {"BOOL,BOOL", BOOL},
};

map<string, Type> typesCompatibles = {
    {"INT_ARRAY,INT", INT},
    {"FLOAT32_ARRAY,FLOAT32", FLOAT32},
    {"STRING_ARRAY,STRING", STRING},
    {"BOOL_ARRAY,BOOL", BOOL},
};

string saveState()
{
    set<string>::iterator it = floatTempMap.begin();
    stringstream ss;
    ss << "sw $ra, " << globalStackPointer << "($sp)\n";
    globalStackPointer += 4;
    return ss.str();
}

string retrieveState(string state)
{
    std::string::size_type n = 0;
    string s = "sw";
    while ((n = state.find(s, n)) != std::string::npos)
    {
        state.replace(n, s.size(), "lw");
        n += 2;
        globalStackPointer -= 4;
    }
    return state;
}

Type functionType;
string continueLabel;
string getIntTemp()
{
    for (int i = 0; i < INT_TEMP_COUNT; i++)
    {
        if (intTempMap.find(intTemps[i]) == intTempMap.end())
        {
            intTempMap.insert(intTemps[i]);
            return string(intTemps[i]);
        }
    }
    cout << "No more int registers!" << endl;
    // exit(1);
    return "";
}
string getNewLabel(string prefix)
{
    stringstream ss;
    ss << prefix << labelCounter;
    labelCounter++;
    return ss.str();
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
    if (!context->variables.empty())
        return context->variables[id];
    return INVALID;
}

string getFloatTemp()
{
    for (int i = 0; i < FLOAT_TEMP_COUNT; i++)
    {
        if (floatTempMap.find(floatTemps[i]) == floatTempMap.end())
        {
            floatTempMap.insert(floatTemps[i]);
            return string(floatTemps[i]);
        }
    }
    cout << "No more float registers!" << endl;
    // exit(1);
    return "";
}

string getBoolTemp()
{
    for (int i = 0; i < INT_TEMP_COUNT; i++)
    {
        if (boolTempMap.find(intTemps[i]) == boolTempMap.end())
        {
            boolTempMap.insert(intTemps[i]);
            return string(intTemps[i]);
        }
    }
    cout << "No more bool registers!" << endl;
    return "";
}

void releaseIntTemp(string temp)
{
    intTempMap.erase(temp);
}

void releaseFloatTemp(string temp)
{
    floatTempMap.erase(temp);
}

void releaseRegister(string temp)
{
    releaseIntTemp(temp);
    releaseFloatTemp(temp);
}

bool isArray(Type type)
{
    if (type == INT_ARRAY || type == FLOAT32_ARRAY || type == STRING_ARRAY || type == BOOL_ARRAY)
    {
        return true;
    }
    return false;
}

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
        return "INT_ARRAY";
    case FLOAT32_ARRAY:
        return "FLOAT32_ARRAY";
    case BOOL_ARRAY:
        return "BOOL_ARRAY";
    case STRING_ARRAY:
        return "STRING_ARRAY";
    case VOID:
        return "VOID";
    }

    cout << "Unknown type" << endl;
    exit(0);
}

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
        // context->variables[id] != 0
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
        // cout<<"Tipo: "<<dec->type<<endl;
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
            // if (stmt->getKind() == RETURN_STATEMENT)
            // {
            //     //BlockStatement *block = (BlockStatement *)stmt;
            //     //block->evaluateSemantic();
            //     cout<<"RETURN STATEMENT"<<endl;

            // }
            stmt->evaluateSemantic();
        }
        its++;
    }

    return 0;
}

int Declaration::evaluateSemantic()
{

    if (!variableExists(this->id) && !globalVariableExists(this->id))
    {
        cout << "Variable " << this->id << " declared with type: " << this->type << endl;
        context->variables[this->id] = this->type;
    }
    else
    {
        cout << "variable: " << this->id << " type: " << getTypeName(this->type) << " already exists" << endl;
        exit(0);
    }

    list<InitDeclarator *>::iterator it = this->declarations.begin();
    while (it != this->declarations.end())
    {
        InitDeclarator *declaration = (*it);

        if (declaration->initializer != NULL)
        {
            list<Expr *>::iterator ite = declaration->initializer->expressions.begin();

            while (ite != declaration->initializer->expressions.end())
            {
                Type exprType = (*ite)->getType();
                if (Expr *v = dynamic_cast<MethodInvocationExpr *>((*ite)))
                {
                    if (this->type != exprType)
                    {
                        cout << "Assignation error: " << getTypeName(this->type) << " != " << getTypeName(exprType) << endl;
                        exit(0);
                    }
                }
                else
                {
                    if (isArray(this->type))
                    {
                        // cout<<declaration->type <<" "<<exprType<<endl;
                        if (declaration->type == exprType)
                        {
                            Type resultType = typesCompatibles[getTypeName(this->type) + "," + getTypeName(exprType)];
                            if (resultType == 0)
                            {
                                cout << "Type1: " << getTypeName(this->type) << " and " << getTypeName(exprType) << " are not compatible" << endl;
                                exit(0);
                            }
                        }
                        else
                        {
                            cout << "Type2: " << getTypeName(exprType) << " and " << getTypeName(declaration->type) << " are not compatible" << endl;
                            exit(0);
                        }
                    }
                    else
                    {
                        // cout<<
                        if (getTypeName(exprType) != getTypeName(this->type))
                        {
                            cout << "error: invalid conversion from: " << getTypeName(exprType) << " to " << getTypeName(this->type) << " line: " << this->line << endl;
                            exit(0);
                        }
                    }
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
    // cout<<"GlobalDeclaration"<<endl;

    if (!globalVariableExists(this->declaration->id))
    {
        globalVariables[this->declaration->id] = this->declaration->type;
    }
    else
    {
        cout << "variable: " << this->declaration->id << " type: " << getTypeName(this->declaration->type) << " already exists" << endl;
        exit(0);
    }
    // cout<<"id: "<<*itList<<endl;

    list<InitDeclarator *>::iterator it = this->declaration->declarations.begin();
    while (it != this->declaration->declarations.end())
    {
        InitDeclarator *declaration = (*it);
        if (declaration->initializer != NULL)
        {
            list<Expr *>::iterator ite = declaration->initializer->expressions.begin();
            while (ite != declaration->initializer->expressions.end())
            {
                Type exprType = (*ite)->getType();
                if (isArray(this->declaration->type))
                {
                    if (declaration->type == exprType)
                    {
                        Type resultType = typesCompatibles[getTypeName(this->declaration->type) + "," + getTypeName(exprType)];
                        if (resultType == 0)
                        {
                            cout << "Type: " << getTypeName(this->declaration->type) << " and " << getTypeName(exprType) << " are not compatible" << endl;
                            exit(0);
                        }
                    }
                    else
                    {
                        cout << "Type: " << getTypeName(exprType) << " and " << getTypeName(declaration->type) << " are not compatible" << endl;
                        exit(0);
                    }
                }
                else
                {
                    if (getTypeName(exprType) != getTypeName(this->declaration->type))
                    {
                        cout << "error: invalid conversion from: " << getTypeName(exprType) << " to " << getTypeName(this->declaration->type) << " line: " << this->line << endl;
                        exit(0);
                    }
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
    // cout<<this->type<<endl;
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

        functionType = this->type;
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

#define IMPLEMENT_BINARY_GET_TYPE(name)                                                                                            \
    Type name##Expr::getType()                                                                                                     \
    {                                                                                                                              \
        string leftType = getTypeName(this->expr1->getType());                                                                     \
        string rightType = getTypeName(this->expr2->getType());                                                                    \
        Type resultType = resultTypes[leftType + "," + rightType];                                                                 \
        if (resultType == 0)                                                                                                       \
        {                                                                                                                          \
            cerr << "Error: type1 " << leftType << " can't be converted to type " << rightType << " line: " << this->line << endl; \
            exit(0);                                                                                                               \
        }                                                                                                                          \
        return resultType;                                                                                                         \
    }

#define IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(name)                                                                                    \
    Type name##Expr::getType()                                                                                                     \
    {                                                                                                                              \
        string leftType = getTypeName(this->expr1->getType());                                                                     \
        string rightType = getTypeName(this->expr2->getType());                                                                    \
        Type resultType = resultTypes[leftType + "," + rightType];                                                                 \
        if (resultType == 0)                                                                                                       \
        {                                                                                                                          \
            cerr << "Error: type2 " << leftType << " can't be converted to type " << rightType << " line: " << this->line << endl; \
            exit(0);                                                                                                               \
        }                                                                                                                          \
        return BOOL;                                                                                                               \
    }

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
    Type resultType = typesCompatibles[getTypeName(this->id->getType()) + "," + getTypeName(this->expr->getType())];
    return resultType;
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
        // cout<< "Parametro "<<paramType<<endl;
        // cout<< "Argumento "<<argType<<endl;
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
    Type idType = this->expr->getType();
    switch (idType)
    {
    case INT:
    case FLOAT32:
        return this->expr->getType();
    }
    cout << "Cannot increment a variable type: " << getTypeName(idType) << endl;
    exit(0);
}

Type PostDecrementExpr::getType()
{
    Type idType = this->expr->getType();
    switch (idType)
    {
    case INT:
    case FLOAT32:
        return this->expr->getType();
    }
    cout << "Cannot decrement a variable type: " << getTypeName(idType) << endl;
    exit(0);
}

int ElseStatement::evaluateSemantic()
{
    if (this->conditionalExpr->getType() != BOOL)
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
    return 0;
}

int IfStatement::evaluateSemantic()
{
    if (this->conditionalExpr->getType() != BOOL)
    {
        cout << "Expression for if must be boolean";
        exit(0);
    }
    pushContext();
    this->trueStatement->evaluateSemantic();
    popContext();
    return 0;
}

int ExprStatement::evaluateSemantic()
{

    return this->expr->getType();
}

int ReturnStatement::evaluateSemantic()
{
    if (this->expr->getType() != functionType)
    {
        cout << "error: function type: " << getTypeName(functionType) << " cannot return a variable type: " << getTypeName(this->expr->getType()) << " line: " << this->expr->line << endl;
        exit(0);
    }
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
    if (this->expr->getType() == INVALID)
    {
        cout << "Error: Print statement must be have a TYPE\n";
        exit(0);
    }

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
            cout << "Error: expression in declaration 'for' must be boolean in line: " << this->line << endl;
            exit(0);
        }
    }

    if (this->expressionRight != NULL)
    {
        if (this->expressionRight->getType() != INT && this->expressionRight->getType() != FLOAT32)
        {
            cout << "Error: expression in declaration 'for' must be int or float32 in line: " << this->line << endl;
            exit(0);
        }
    }

    pushContext();
    if (this->statement != NULL)
    {
        this->statement->evaluateSemantic();
    }
    popContext();

    return 0;
}

/////////////////////

string intArithmetic(Code &leftCode, Code &rightCode, Code &code, char op)
{
    stringstream ss;
    code.place = getIntTemp();
    switch (op)
    {
    case '+':
        ss << "add " << code.place << ", " << leftCode.place << ", " << rightCode.place;
        break;
    case '-':
        ss << "sub " << code.place << ", " << leftCode.place << ", " << rightCode.place;
        break;
    case '*':
        ss << "mult " << leftCode.place << ", " << rightCode.place << endl
           << "mflo " << code.place;
        break;
    case '/':
        ss << "div " << leftCode.place << ", " << rightCode.place
           << "mflo " << code.place;
        break;
    default:
        break;
    }
    return ss.str();
}

string floatArithmetic(Code &leftCode, Code &rightCode, Code &code, char op)
{
    stringstream ss;
    code.place = getFloatTemp();
    switch (op)
    {
    case '+':
        ss << "add.s " << code.place << ", " << leftCode.place << ", " << rightCode.place;
        break;
    case '-':
        ss << "sub.s " << code.place << ", " << leftCode.place << ", " << rightCode.place;
        break;
    case '*':
        ss << "mul.s " << code.place << ", " << leftCode.place << ", " << rightCode.place;
        break;
    case '/':
        ss << "div.s " << code.place << ", " << leftCode.place << ", " << rightCode.place;
        break;
    default:
        break;
    }
    return ss.str();
}

string MethodDefinition::genCode()
{ /// done
    if (this->statement == NULL)
        return "";

    int stackPointer = 4;
    globalStackPointer = 0;
    stringstream code;
    code << this->id << ": " << endl;
    string state = saveState();
    code << state << endl;
    if (this->params.size() > 0)
    {
        list<Parameter *>::iterator it = this->params.begin();
        for (int i = 0; i < this->params.size(); i++)
        {
            code << "sw $a" << i << ", " << stackPointer << "($sp)" << endl;
            codeGenerationVars[(*it)->declarator->id] = new VariableInfo(stackPointer, false, true, (*it)->type);
            if(isArray((*it)->type)){
                codeGenerationVars[(*it)->declarator->id] = new VariableInfo(stackPointer, true, true, (*it)->type);
            }else{
                codeGenerationVars[(*it)->declarator->id] = new VariableInfo(stackPointer, false, true, (*it)->type);
            }
            stackPointer += 4;
            globalStackPointer += 4;
            it++;
        }
    }
    code << this->statement->genCode() << endl;
    stringstream sp;
    int currentStackPointer = globalStackPointer;
    sp << endl
       << "addiu $sp, $sp, -" << currentStackPointer << endl;
    code << retrieveState(state);
    code << "addiu $sp, $sp, " << currentStackPointer << endl;
    code << "jr $ra" << endl;
    codeGenerationVars.clear();
    string result = code.str();
    result.insert(id.size() + 2, sp.str());
    return result;
}

void IntExpr::genCode(Code &code)
{ // done
    string temp = getIntTemp();
    code.place = temp;
    stringstream ss;
    ss << "li " << temp << ", " << this->value << endl;
    code.code = ss.str();
    code.type = INT;
}

void FloatExpr::genCode(Code &code)
{ // done
    string floatTemp = getFloatTemp();
    code.place = floatTemp;
    stringstream ss;
    ss << "li.s " << floatTemp << ", " << this->value << endl;
    code.code = ss.str();
    code.type = FLOAT32;
}

void StringExpr::genCode(Code &code)
{ // done
    string strLabel = getNewLabel("string");
    stringstream ss;
    ss << strLabel << ": .asciiz" << this->value << "" << endl;
    assemblyFile.data += ss.str();
    code.code = "";
    code.place = strLabel;
    code.type = STRING;
}

void IdExpr::genCode(Code &code)
{ // done
    if (codeGenerationVars.find(this->id) == codeGenerationVars.end())
    {
        code.type = globalVariables[this->id];
        if (globalVariables[this->id] == INT_ARRAY || globalVariables[this->id] == FLOAT32_ARRAY)
        {
            
            string intTemp = getIntTemp();
            code.code = "la " + intTemp + ", " + this->id + "\n";
            code.place = intTemp;
        }
        if (globalVariables[this->id] == FLOAT32)
        {
            string floatTemp = getFloatTemp();
            code.place = floatTemp;
            code.code = "l.s " + floatTemp + ", " + this->id + "\n";
        }
        else
        {
            string intTemp = getIntTemp();
            code.place = intTemp;
            code.code = "lw " + intTemp + ", " + this->id + "\n";
        }
    }
    else
    {
        code.type = codeGenerationVars[this->id]->type;
        if (codeGenerationVars[this->id]->type == FLOAT32 && !codeGenerationVars[this->id]->isArray)
        {
            string floatTemp = getFloatTemp();
            code.place = floatTemp;
            code.code = "l.s " + floatTemp + ", " + to_string(codeGenerationVars[this->id]->offset) + "($sp)\n";
        }
        else if (codeGenerationVars[this->id]->type == INT && !codeGenerationVars[this->id]->isArray ||
                 codeGenerationVars[this->id]->type == BOOL && !codeGenerationVars[this->id]->isArray)
        {
            string intTemp = getIntTemp();
            code.place = intTemp;
            code.code = "lw " + intTemp + ", " + to_string(codeGenerationVars[this->id]->offset) + "($sp)\n";
        }
        else if (codeGenerationVars[this->id]->isArray)
        {
            string intTemp = getIntTemp();
            code.code = "la " + intTemp + ", " + to_string(codeGenerationVars[this->id]->offset) + "($sp)\n";
            code.place = intTemp;
        }
    }
    
}

void ArrayExpr::genCode(Code &code)
{ // done
    Code arrayCode;
    string name = this->id->id;
    stringstream ss;
    this->expr->genCode(arrayCode);
    releaseRegister(arrayCode.place);
    if (codeGenerationVars.find(name) == codeGenerationVars.end())
    {
        string temp = getIntTemp();
        string labelAddress = getIntTemp();
        ss << arrayCode.code << endl
           << "li $a0, 4" << endl
           << "mult $a0, " << arrayCode.place << endl
           << "mflo " << temp << endl
           << "la " << labelAddress << ", " << name << endl
           << "add " << temp << ", " << labelAddress << ", " << temp << endl;
        releaseRegister(labelAddress);
        if (globalVariables[name] == INT)
        {
            ss << "lw " << temp << ", 0(" << temp << ")" << endl;
            code.place = temp;
        }
        else if (globalVariables[name] == FLOAT32)
        {
            string floatTemp = getFloatTemp();
            ss << "l.s " << floatTemp << ", 0(" << temp << ")" << endl;
            code.place = floatTemp;
        }
        else if (globalVariables[name] == BOOL)
        {
            string boolTemp = getBoolTemp();
            ss << "lb " << boolTemp << ", 0(" << temp << ")" << endl;
            code.place = boolTemp;
        }
    }
    else
    {
        string temp = getIntTemp();
        string address = getIntTemp();
        ss << arrayCode.code << endl
           << "li $a0, 4" << endl
           << "mult $a0, " << arrayCode.place << endl
           << "mflo " << temp << endl;
        if (!codeGenerationVars[name]->isParameter)
            ss << "la " + address + ", " << codeGenerationVars[name]->offset << "($sp)\n";
        else
            ss << "lw " << address << ", " << codeGenerationVars[name]->offset << "($sp)" << endl;
        ss << "add " << temp << ", " << address << ", " << temp << endl;
        releaseRegister(address);
        if (codeGenerationVars[name]->type == INT)
        {
            ss << "lw " << temp << ", 0(" << temp << ")" << endl;
            code.place = temp;
            code.type = INT;
        }
        else if (codeGenerationVars[name]->type == FLOAT32)
        {
            string floatTemp = getFloatTemp();
            ss << "l.s " << floatTemp << ", 0(" << temp << ")" << endl;
            code.place = floatTemp;
            code.type = FLOAT32;
        }
        else if (codeGenerationVars[name]->type == BOOL)
        {
            string boolTemp = getBoolTemp();
            ss << "lb " << boolTemp << ", 0(" << temp << ")" << endl;
            code.place = boolTemp;
            code.type = BOOL;
        }
    }
    code.code = ss.str();
}

void toFloat(Code &code)
{
    if (code.type == INT)
    {
        string floatTemp = getFloatTemp();
        stringstream ss;
        ss << code.code
           << "mtc1 " << code.place << ", " << floatTemp << endl
           << "cvt.s.w " << floatTemp << ", " << floatTemp << endl;
        releaseRegister(code.place);
        code.place = floatTemp;
        code.type = FLOAT32;
        code.code = ss.str();
    }
    else
    {
        /* nothing */
    }
}

#define IMPLEMENT_BINARY_ARIT_GEN_CODE(name, op)                          \
    void name##Expr::genCode(Code &code)                                  \
    {                                                                     \
        Code leftCode, rightCode;                                         \
        stringstream ss;                                                  \
        this->expr1->genCode(leftCode);                                   \
        this->expr2->genCode(rightCode);                                  \
        if (leftCode.type == INT && rightCode.type == INT)                \
        {                                                                 \
            code.type = INT;                                              \
            releaseRegister(leftCode.place);                              \
            releaseRegister(rightCode.place);                             \
            ss << leftCode.code << endl                                   \
               << rightCode.code << endl                                  \
               << intArithmetic(leftCode, rightCode, code, op) << endl;   \
        }                                                                 \
        else                                                              \
        {                                                                 \
            code.type = FLOAT32;                                          \
            toFloat(leftCode);                                            \
            toFloat(rightCode);                                           \
            releaseRegister(leftCode.place);                              \
            releaseRegister(rightCode.place);                             \
            ss << leftCode.code << endl                                   \
               << rightCode.code << endl                                  \
               << floatArithmetic(leftCode, rightCode, code, op) << endl; \
        }                                                                 \
        code.code = ss.str();                                             \
    }

void UnaryExpr::genCode(Code &code)
{
    this->expr->genCode(code);
}

void PostIncrementExpr::genCode(Code &code)
{ // done
    Code exprCode;
    this->expr->genCode(exprCode);
    stringstream ss;
    ss << exprCode.code;
    if (exprCode.type == INT)
    {
        string temp = getIntTemp();
        ss << "addi " << temp << ", " << exprCode.place << ", 1" << endl;
        releaseRegister(exprCode.place);
        code.place = temp;
    }
    else if (exprCode.type == FLOAT32)
    {
        string temp = getFloatTemp();
        ss << "add.s " << temp << ", " << exprCode.place << ", 1.0" << endl;
        releaseRegister(exprCode.place);
        code.place = temp;
    }
    code.code = ss.str();
}

void PostDecrementExpr::genCode(Code &code)
{ // done
    Code exprCode;
    this->expr->genCode(exprCode);
    stringstream ss;
    ss << exprCode.code;
    if (exprCode.type == INT)
    {
        string temp = getIntTemp();
        ss << "addi " << temp << ", " << exprCode.place << ", -1" << endl;
        releaseRegister(exprCode.place);
        code.place = temp;
    }
    else if (exprCode.type == FLOAT32)
    {
        string temp = getFloatTemp();
        ss << "add.s " << temp << ", " << exprCode.place << ", -1.0" << endl;
        releaseRegister(exprCode.place);
        code.place = temp;
    }
    code.code = ss.str();
}

void MethodInvocationExpr::genCode(Code &code)
{ // remaining array parameters
    list<Expr *>::iterator it = this->args.begin();
    list<Code> codes;
    stringstream ss;
    Code argCode;
    while (it != this->args.end())
    {
        (*it)->genCode(argCode);
        cout<<argCode.code<<endl;
        ss << argCode.code << endl;
        codes.push_back(argCode);
        it++;
    }

    int i = 0;
    list<Code>::iterator placesIt = codes.begin();
    while (placesIt != codes.end())
    {
        releaseRegister((*placesIt).place);
        if ((*placesIt).type == INT || (*placesIt).type == BOOL)
            ss << "move $a" << i << ", " << (*placesIt).place << endl;
        else if ((*placesIt).type == FLOAT32)
            ss << "mfc1 $a" << i << ", " << (*placesIt).place << endl;
        i++;
        placesIt++;
    }

    ss << "jal " << this->id->id << endl;
    string reg;
    if (methods[this->id->id]->returnType == INT || methods[this->id->id]->returnType == BOOL)
    {
        reg = getIntTemp();
        ss << "move " << reg << ", $v0";
    }
    else if (methods[this->id->id]->returnType == FLOAT32)
    {
        reg = getFloatTemp();
        ss << "mfc1 $v0, " << reg << endl;
    }
    code.code = ss.str();
    code.place = reg;
}

string ElseStatement::genCode()
{
    string elseLabel = getNewLabel("else");
    string endIfLabel = getNewLabel("endif");
    Code exprCode;
    this->conditionalExpr->genCode(exprCode);
    stringstream code;
    code << exprCode.code << endl;
    if (exprCode.type == INT)
    {
        code << "beqz " << exprCode.place << ", " << elseLabel << endl;
    }
    else if (exprCode.type == FLOAT32)
    {
        code << "bc1f " << elseLabel << endl;
    }
    else if (exprCode.type == BOOL)
    {
        code << "beq " << exprCode.place << ", $zero, " << elseLabel << endl;
    }
    code << this->trueStatement->genCode() << endl
         << "j " << endIfLabel << endl
         << elseLabel << ": " << endl
         << this->falseStatement->genCode() << endl
         << endIfLabel << " :" << endl;
    releaseRegister(exprCode.place);
    return code.str();
}

string IfStatement::genCode()
{
    string endIfLabel = getNewLabel("endif");
    Code exprCode;
    this->conditionalExpr->genCode(exprCode);
    stringstream code;
    code << exprCode.code << endl;
    if (exprCode.type == INT)
    {
        code << "beqz " << exprCode.place << ", " << endIfLabel << endl;
    }
    else if (exprCode.type == FLOAT32)
    {
        code << "bc1f " << endIfLabel << endl;
    }
    else if (exprCode.type == BOOL)
    {
        code << "beq " << exprCode.place << ", $zero, " << endIfLabel << endl;
    }
    code << this->trueStatement->genCode() << endl
         << endIfLabel << " :" << endl;
    releaseRegister(exprCode.place);

    return code.str();
}

string ExprStatement::genCode()
{ // done
    Code exprCode;
    this->expr->genCode(exprCode);
    return exprCode.code;
}

string ReturnStatement::genCode()
{ // done
    Code exprCode;
    this->expr->genCode(exprCode);
    releaseRegister(exprCode.place);
    stringstream ss;
    ss << exprCode.code << endl;
    if (exprCode.type == INT || exprCode.type == BOOL)
        ss << "move $v0, " << exprCode.place << endl;
    else
        ss << "mfc1 $v0, " << exprCode.place << endl;
    return ss.str();
}

string PrintStatement::genCode()
{ // done
    Code exprCode;
    this->expr->genCode(exprCode);
    releaseRegister(exprCode.place);
    stringstream code;
    code << exprCode.code << endl;
    if (exprCode.type == INT || exprCode.type == BOOL)
    {
        code << "move $a0, " << exprCode.place << endl
             << "li $v0, 1" << endl
             << "syscall" << endl;
    }
    else if (exprCode.type == FLOAT32)
    {
        code << "mov.s $f12, " << exprCode.place << endl
             << "li $v0, 2" << endl
             << "syscall" << endl;
    }
    else if (exprCode.type == STRING)
    {
        code << "la $a0, " << exprCode.place << endl
             << "li $v0, 4" << endl
             << "syscall" << endl;
    }
    return code.str();
}

void EqExpr::genCode(Code &code)
{
    Code leftSideCode;
    Code rightSideCode;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    stringstream ss;
    if (leftSideCode.type == INT && rightSideCode.type == INT)
    {
        code.type = INT;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        ss << leftSideCode.code << endl
           << rightSideCode.code << endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        string temp = getIntTemp();
        string label = getNewLabel("label");
        string finalLabel = getNewLabel("finalLabel");
        ss << "beq " << leftSideCode.place << ", " << rightSideCode.place << ", " << label + "\n";
        ss << "addi " << temp << ", $zero, 0" << endl
           << " j " << finalLabel << endl;
        ss << label << ":" << endl
           << "addi " << temp << ", $zero, 1" << endl
           << finalLabel << ":" << endl;
        code.place = temp;
    }
    else if (leftSideCode.type == BOOL && rightSideCode.type == BOOL)
    {
        code.type = BOOL;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        ss << leftSideCode.code << endl
           << rightSideCode.code << endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        string temp = getIntTemp();
        string label = getNewLabel("label");
        string finalLabel = getNewLabel("finalLabel");
        ss << "beq " << leftSideCode.place << ", " << rightSideCode.place << ", " << label + "\n";
        ss << "addi " << temp << ", $zero, 0" << endl
           << " j " << finalLabel << endl;
        ss << label << ":" << endl
           << "addi " << temp << ", $zero, 1" << endl
           << finalLabel << ":" << endl;
        code.place = temp;
    }
    else
    {
        code.type = FLOAT32;
        toFloat(leftSideCode);
        toFloat(rightSideCode);
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        ss << leftSideCode.code << endl
           << rightSideCode.code << endl;
    }
    code.code = ss.str();
}

void NeqExpr::genCode(Code &code)
{
    Code leftSideCode;
    Code rightSideCode;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    stringstream ss;
    if (leftSideCode.type == INT && rightSideCode.type == INT)
    {
        code.type = INT;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        ss << leftSideCode.code << endl
           << rightSideCode.code << endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        string temp = getIntTemp();
        string label = getNewLabel("label");
        string finalLabel = getNewLabel("finalLabel");
        ss << "bne " << leftSideCode.place << ", " << rightSideCode.place << ", " << label + "\n";
        ss << "addi " << temp << ", $zero, 0" << endl
           << " j " << finalLabel << endl;
        ss << label << ":" << endl
           << "addi " << temp << ", $zero, 1" << endl
           << finalLabel << ":" << endl;
        code.place = temp;
    }
    else
    {
        code.type = FLOAT32;
        toFloat(leftSideCode);
        toFloat(rightSideCode);
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        ss << leftSideCode.code << endl
           << rightSideCode.code << endl;
    }
    code.code = ss.str();
}

void GteExpr::genCode(Code &code)
{
    Code leftSideCode;
    Code rightSideCode;
    stringstream ss;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    if (leftSideCode.type == INT && rightSideCode.type == INT)
    {
        code.type = INT;
        ss << leftSideCode.code << endl
           << rightSideCode.code << endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        string temp = getIntTemp();
        ss << "sge " << temp << ", " << leftSideCode.place << ", " << rightSideCode.place << endl;
        code.place = temp;
    }
    else
    {
        code.type = FLOAT32;
        toFloat(leftSideCode);
        toFloat(rightSideCode);
        ss << leftSideCode.code << endl
           << rightSideCode.code << endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        ss << "c.le.s " << rightSideCode.place << ", " << leftSideCode.place << endl;
    }
    code.code = ss.str();
}

void LteExpr::genCode(Code &code)
{
    Code leftSideCode;
    Code rightSideCode;
    stringstream ss;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    if (leftSideCode.type == INT && rightSideCode.type == INT)
    {
        code.type = INT;
        ss << leftSideCode.code << endl
           << rightSideCode.code << endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        string temp = getIntTemp();
        ss << "sle " << temp << ", " << leftSideCode.place << ", " << rightSideCode.place << endl;
        code.place = temp;
    }
    else
    {
        code.type = FLOAT32;
        toFloat(leftSideCode);
        toFloat(rightSideCode);
        ss << leftSideCode.code << endl
           << rightSideCode.code << endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        ss << "c.le.s " << leftSideCode.place << ", " << rightSideCode.place << endl;
    }
    code.code = ss.str();
}

void GtExpr::genCode(Code &code)
{
    Code leftSideCode;
    Code rightSideCode;
    stringstream ss;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    //cout<<this->expr1->getType()<<endl;
    if (leftSideCode.type == INT && rightSideCode.type == INT)
    {
        cout<<"int"<<endl;
        code.type = INT;
        ss << leftSideCode.code << endl
           << rightSideCode.code << endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        string temp = getIntTemp();
        ss << "sgt " << temp << ", " << leftSideCode.place << ", " << rightSideCode.place << endl;
        code.place = temp;
    }
    else
    {
        cout<<"float"<<endl;
        code.type = FLOAT32;
        toFloat(leftSideCode);
        toFloat(rightSideCode);
        ss << leftSideCode.code << endl
           << rightSideCode.code << endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        ss << "c.lt.s " << rightSideCode.place << ", " << leftSideCode.place << endl;
    }
    code.code = ss.str();
}

void LtExpr::genCode(Code &code)
{
    Code leftSideCode;
    Code rightSideCode;
    stringstream ss;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    if (leftSideCode.type == INT && rightSideCode.type == INT)
    {
        code.type = INT;
        ss << leftSideCode.code << endl
           << rightSideCode.code << endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        string temp = getIntTemp();
        ss << "slt " << temp << ", " << leftSideCode.place << ", " << rightSideCode.place << endl;
        code.place = temp;
    }
    else
    {
        code.type = FLOAT32;
        toFloat(leftSideCode);
        toFloat(rightSideCode);
        ss << leftSideCode.code << endl
           << rightSideCode.code << endl;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        ss << "c.lt.s " << leftSideCode.place << ", " << rightSideCode.place << endl;
    }
    code.code = ss.str();
}

void LogicalAndExpr::genCode(Code &code)
{
    Code leftSideCode;
    Code rightSideCode;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    stringstream ss;
    ss << leftSideCode.code << endl
       << rightSideCode.code << endl;
    releaseRegister(leftSideCode.place);
    releaseRegister(rightSideCode.place);
    string temp = getIntTemp();
    string label = getNewLabel("label");
    string finalLabel = getNewLabel("finalLabel");
    ss << "addi " << temp << ", $zero, 0" << endl;
    ss << "beq " << leftSideCode.place << ", " << temp << ", " << finalLabel << endl;
    ss << "beq " << rightSideCode.place << ", " << temp << ", " << finalLabel << endl;
    ss << label << ":" << endl
       << "addi " << temp << ", $zero, 1" << endl
       << finalLabel << ":" << endl;
    code.place = temp;
    code.code = ss.str();
}

void LogicalOrExpr::genCode(Code &code)
{
    Code leftSideCode;
    Code rightSideCode;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    stringstream ss;
    ss << leftSideCode.code << endl
       << rightSideCode.code << endl;
    releaseRegister(leftSideCode.place);
    releaseRegister(rightSideCode.place);
    string temp = getIntTemp();
    string label = getNewLabel("label");
    string finalLabel = getNewLabel("finalLabel");
    ss << "addi " << temp << ", $zero, 1" << endl;
    ss << "beq " << leftSideCode.place << ", " << temp << ", " << finalLabel << endl;
    ss << "beq " << rightSideCode.place << ", " << temp << ", " << finalLabel << endl;
    ss << label << ":" << endl
       << "addi " << temp << ", $zero, 0" << finalLabel << ":";
    code.place = temp;
    code.code = ss.str();
}

void AssignExpr::genCode(Code &code)
{
    Code rightSideCode;
    stringstream ss;
    this->expr2->genCode(rightSideCode);
    ss << rightSideCode.code << endl;
    string name = ((IdExpr *)this->expr1)->id;
    if (name != "")
    {
        if (codeGenerationVars.find(name) == codeGenerationVars.end())
        {
            if (rightSideCode.type == INT)
                ss << "sw " << rightSideCode.place << ", " << name << endl;
            else if (rightSideCode.type == FLOAT32)
                ss << "s.s " << rightSideCode.place << ", " << name << endl;
        }
        else
        {
            if (rightSideCode.type == INT)
                ss << "sw " << rightSideCode.place << ", " << codeGenerationVars[name]->offset << "($sp)" << endl;
            else if (rightSideCode.type == FLOAT32)
                ss << "s.s " << rightSideCode.place << ", " << codeGenerationVars[name]->offset << "($sp)" << endl;
        }
        releaseRegister(rightSideCode.place);
    }
    else
    {
        Code arrayExpr;
        string name = ((ArrayExpr *)this->expr1)->id->id;
        ((ArrayExpr *)this->expr1)->expr->genCode(arrayExpr);
        releaseRegister(arrayExpr.place);
        ss << arrayExpr.code << endl;
        string temp = getIntTemp();
        string address = getIntTemp();
        if (codeGenerationVars.find(name) == codeGenerationVars.end())
        {
            ss << "li $a0, 4" << endl
               << "mult $a0, " << arrayExpr.place << endl
               << "mflo " << temp << endl
               << "la " << address << ", " << name << endl
               << "add " << temp << ", " << temp << ", " << address << endl;
            Code rightSideCode;
            this->expr2->genCode(rightSideCode);
            ss << rightSideCode.code << endl
               << "sw " << rightSideCode.place << ", 0(" << temp << ")" << endl;
        }
        else
        {
            ss << "li $a0, 4" << endl
               << "mult $a0, " << arrayExpr.place << endl
               << "mflo " << temp << endl;
            if (!codeGenerationVars[name]->isParameter)
                ss << "la " + address + ", " << codeGenerationVars[name]->offset << "($sp)" << endl;
            else
                ss << "lw " << address << ", " << codeGenerationVars[name]->offset << "($sp)" << endl;
            ss << "add " << temp << ", " << temp << ", " << address << endl;
            Code rightSideCode;
            this->expr2->genCode(rightSideCode);
            ss << rightSideCode.code << endl;
            ss << "sw " << rightSideCode.place << ", 0(" << temp << ")" << endl;
        }
        releaseRegister(temp);
        releaseRegister(address);
        releaseRegister(rightSideCode.place);
        releaseRegister(arrayExpr.place);
    }
    code.code = ss.str();
}

void PlusAssignExpr::genCode(Code &code)
{
    Code leftSideCode;
    Code rightSideCode;
    stringstream ss;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    ss << leftSideCode.code << endl;
    ss << rightSideCode.code << endl;
    if (leftSideCode.type == INT)
        ss << "add " << leftSideCode.place << ", " << leftSideCode.place << ", " << rightSideCode.place;
    else if (leftSideCode.type == FLOAT32)
        ss << "add.s " << leftSideCode.place << ", " << leftSideCode.place << ", " << rightSideCode.place;
    string name = ((IdExpr *)this->expr1)->id;
    if (codeGenerationVars.find(name) == codeGenerationVars.end())
    {
        if (leftSideCode.type == INT)
            ss << "sw " << leftSideCode.place << ", " << name << endl;
        else if (leftSideCode.type == FLOAT32)
            ss << "s.s " << leftSideCode.place << ", " << name << endl;
    }
    else
    {
        if (leftSideCode.type == INT)
            ss << "sw " << leftSideCode.place << ", " << codeGenerationVars[name]->offset << "($sp)" << endl;
        else if (leftSideCode.type == FLOAT32)
            ss << "s.s " << leftSideCode.place << ", " << codeGenerationVars[name]->offset << "($sp)" << endl;
    }
    releaseRegister(leftSideCode.place);
    code.code = ss.str();
}

void MinusAssignExpr::genCode(Code &code)
{
    Code leftSideCode;
    Code rightSideCode;
    stringstream ss;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    ss << leftSideCode.code << endl;
    ss << rightSideCode.code << endl;
    if (leftSideCode.type == INT)
        ss << "sub " << leftSideCode.place << ", " << leftSideCode.place << ", " << rightSideCode.place;
    else if (leftSideCode.type == FLOAT32)
        ss << "div.s " << leftSideCode.place << ", " << leftSideCode.place << ", " << rightSideCode.place;
    string name = ((IdExpr *)this->expr1)->id;
    if (codeGenerationVars.find(name) == codeGenerationVars.end())
    {
        if (leftSideCode.type == INT)
            ss << "sw " << leftSideCode.place << ", " << name << endl;
        else if (leftSideCode.type == FLOAT32)
            ss << "s.s " << leftSideCode.place << ", " << name << endl;
    }
    else
    {
        if (leftSideCode.type == INT)
            ss << "sw " << leftSideCode.place << ", " << codeGenerationVars[name]->offset << "($sp)" << endl;
        else if (leftSideCode.type == FLOAT32)
            ss << "s.s " << leftSideCode.place << ", " << codeGenerationVars[name]->offset << "($sp)" << endl;
    }
    releaseRegister(leftSideCode.place);
    code.code = ss.str();
}

string BlockStatement::genCode()
{
    stringstream ss;

    list<Declaration *>::iterator itd = this->declarations.begin();
    while (itd != this->declarations.end())
    {
        Declaration *dec = *itd;
        if (dec != NULL)
        {
            ss << dec->genCode() << endl;
        }
        itd++;
    }

    list<Statement *>::iterator its = this->statements.begin();
    while (its != this->statements.end())
    {
        Statement *stmt = *its;
        if (stmt != NULL)
        {
            ss << stmt->genCode() << endl;
        }

        its++;
    }
    return ss.str();
}

string GlobalDeclaration::genCode()
{
    list<InitDeclarator *>::iterator it = this->declaration->declarations.begin();
    stringstream data;
    stringstream code;
    while (it != this->declaration->declarations.end())
    {
        InitDeclarator *declaration = (*it);
        data << this->declaration->id << ": .word 0";
        if (declaration->initializer != NULL)
        {
            list<Expr *>::iterator itExpr = declaration->initializer->expressions.begin();
            for (int i = 0; i < declaration->initializer->expressions.size(); i++)
            {
                Code exprCode;
                (*itExpr)->genCode(exprCode);
                code << exprCode.code;
                if (!isArray(this->declaration->type))
                {
                    if (exprCode.type == INT)
                        code << "sw " << exprCode.place << ", " << this->declaration->id << endl;
                    else if (exprCode.type == FLOAT32)
                        code << "s.s " << exprCode.place << ", " << this->declaration->id << endl;
                }
                else
                {
                    string temp = getIntTemp();
                    code << "la " << temp << ", " << this->declaration->id << endl;
                    if (exprCode.type == INT)
                    {
                        code << "sw " << exprCode.place << ", " << i * 4 << "(" << temp << ")" << endl;
                    }
                    else if (exprCode.type == FLOAT32)
                    {
                        code << "s.s " << exprCode.place << ", " << i * 4 << "(" << temp << ")" << endl;
                    }
                }
                releaseRegister(exprCode.place);
                itExpr++;
            }
        }
        data << endl;
        it++;
    }

    assemblyFile.data += data.str();
    return code.str();
}

string PackageDeclaration::genCode()
{
    return "";
}

string ImportDeclaration::genCode()
{
    return "";
}

string ContinueStatement::genCode()
{
    stringstream ss;
    string label = getNewLabel("update");
    ss << "j " << label << endl;
    ss << label << ":" << endl;
    return ss.str();
    
}

string BreakStatement::genCode()
{
    stringstream ss;
    string label = getNewLabel("Exit");
    ss << "j " << label << endl;
    ss << label << ":" << endl;
    return ss.str();
}

void BoolExpr::genCode(Code &code)
{
    string temp = getIntTemp();
    code.place = temp;
    stringstream ss;
    ss << "li " << temp << ", " << (int)this->value << endl;
    code.code = ss.str();
    code.type = BOOL;
}

void PercentageExpr::genCode(Code &code)
{
    Code leftSideCode;
    Code rightSideCode;
    stringstream ss;
    this->expr1->genCode(leftSideCode);
    this->expr2->genCode(rightSideCode);
    ss << leftSideCode.code << endl;
    ss << rightSideCode.code << endl;
    if (leftSideCode.type == INT)
    {
        ss << "div " << leftSideCode.place << ", " << rightSideCode.place << endl;
        ss << "mfhi " << leftSideCode.place << endl;
    }
    else if (leftSideCode.type == FLOAT32)
        ss << "div.s " << leftSideCode.place << ", " << leftSideCode.place << ", " << rightSideCode.place << endl;

    releaseRegister(leftSideCode.place);
    code.code = ss.str();
}

string ForStatement::genCode()
{
    stringstream ss;
    string forLabel = getNewLabel("for");
    string endForLabel = getNewLabel("endFor");
    Code declaratorCode;
    Code leftCode;
    Code rightCode;
    string name;
    if (this->declarator != NULL && this->expressionLeft != NULL && this->expressionRight != NULL)
    {
        if (!this->declarator->isArray)
        {
            this->declarator->arrayDeclaration->genCode(declaratorCode);
            name = this->declarator->id;
            codeGenerationVars[name] = new VariableInfo(globalStackPointer, false, false, this->declarator->arrayDeclaration->getType());
            globalStackPointer += 4;
        }
        releaseRegister(declaratorCode.place);
        this->expressionLeft->genCode(leftCode);
        this->expressionRight->genCode(rightCode);
        ss << forLabel << ": " << endl;
        ss << leftCode.code << endl;
        ss << "beqz " << leftCode.place << ", " << endForLabel << endl;
        ss << "addi " << declaratorCode.place << ", " << declaratorCode.place << ", 1" << endl;
        ss << "sw " << declaratorCode.place << ", " << codeGenerationVars[name]->offset << "($sp)" << endl;
        ss << this->statement->genCode() << endl;
        ss << "j " << forLabel << endl;
        ss << endForLabel << ": " << endl;
    }
    else if (this->declarator == NULL && this->expressionLeft != NULL && this->expressionRight == NULL)
    {
        this->expressionLeft->genCode(leftCode);
        ss << forLabel << ": " << endl;
        ss << leftCode.code << endl;
        ss << "beqz " << leftCode.place << ", " << endForLabel << endl;
        ss << this->statement->genCode() << endl;
        ss << "j " << forLabel << endl;
        ss << endForLabel << ": " << endl;
    }
    else
    {
        ss << forLabel << ": " << endl;
        ss << this->statement->genCode() << endl;
        ss << "j " << forLabel << endl;
        ss << endForLabel << ": " << endl;
    }
    return ss.str();
}

string Declaration::genCode()
{
    stringstream code;
    list<InitDeclarator *>::iterator it = this->declarations.begin();
    while (it != this->declarations.end())
    {
        InitDeclarator *declaration = (*it);
        cout << getTypeName(this->type) << endl;
        if (!isArray(this->type))
        {
            codeGenerationVars[this->id] = new VariableInfo(globalStackPointer, false, false, this->type);
            globalStackPointer += 4;
        }
        else
        {
            codeGenerationVars[this->id] = new VariableInfo(globalStackPointer, true, false, this->type);
        }

        if (declaration->initializer != NULL)
        {
            list<Expr *>::iterator itExpr = declaration->initializer->expressions.begin();
            int offset = codeGenerationVars[this->id]->offset;
            for (int i = 0; i < declaration->initializer->expressions.size(); i++)
            {
                Code exprCode;
                (*itExpr)->genCode(exprCode);
                code << exprCode.code << endl;
                if (exprCode.type == INT)
                    code << "sw " << exprCode.place << ", " << offset << "($sp)" << endl;
                else if (exprCode.type == FLOAT32)
                    code << "s.s " << exprCode.place << ", " << offset << "($sp)" << endl;
                releaseRegister(exprCode.place);
                itExpr++;
                if (isArray(this->type))
                {
                    globalStackPointer += 4;
                    offset += 4;
                }
            }
        }
        it++;
    }
    return code.str();
}

IMPLEMENT_BINARY_GET_TYPE(Add);
IMPLEMENT_BINARY_GET_TYPE(Sub);
IMPLEMENT_BINARY_GET_TYPE(Mul);
IMPLEMENT_BINARY_GET_TYPE(Div);
IMPLEMENT_BINARY_GET_TYPE(Assign);
IMPLEMENT_BINARY_GET_TYPE(PlusAssign);
IMPLEMENT_BINARY_GET_TYPE(MinusAssign);
IMPLEMENT_BINARY_GET_TYPE(Percentage);

IMPLEMENT_BINARY_ARIT_GEN_CODE(Add, '+');
IMPLEMENT_BINARY_ARIT_GEN_CODE(Sub, '-');
IMPLEMENT_BINARY_ARIT_GEN_CODE(Mul, '*');
IMPLEMENT_BINARY_ARIT_GEN_CODE(Div, '/');

IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Eq);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Neq);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Gte);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Lte);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Gt);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(Lt);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(LogicalAnd);
IMPLEMENT_BINARY_BOOLEAN_GET_TYPE(LogicalOr);

// string forLabel = getNewLabel("loop");
// string exitForLabel = getNewLabel("exit");
// Code exprCode;
// Code exprLeftCode;
// Code exprRightCode;
// this->declarator->arrayDeclaration->genCode(exprCode);
// this->expressionLeft->genCode(exprLeftCode);
// this->expressionRight->genCode(exprRightCode);
// stringstream code;
// code << exprCode.code << endl;
// if (exprCode.type == INT)
// {
//     code << "beqz " << exprCode.place << ", " << exitForLabel << endl;
// }
// else
// {
//     code << "bc1f " << exitForLabel << endl;
// }
// code << this->statement->genCode() << endl
//      << exitForLabel << " :" << endl;
// releaseRegister(exprCode.place);

// return code.str();