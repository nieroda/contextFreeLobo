#ifndef __AST__STATEMENT__
#define __AST__STATEMENT__

class SymbolTable;
//#include "SymbolTable.hpp"
#include "CompilerContext.hpp"
#include "Node.hpp"

#include <vector>

class AbstractStatement {
public:
    virtual void evaluate(SymbolTable &) = 0;
    virtual ~AbstractStatement() = default;

    virtual void codegen(CompilerContext *) = 0;

    virtual void dumpAST(std::string) = 0;

};


class GroupedStatements: public AbstractStatement {
    
public:
    GroupedStatements() = default;
    ~GroupedStatements() = default;

    virtual void evaluate(SymbolTable &);
    void addStatement(std::unique_ptr<AbstractStatement> stmt);
    virtual void codegen(CompilerContext *);

    virtual void dumpAST(std::string);


private:
    std::vector<std::unique_ptr<AbstractStatement>> _statements;
};

class PrintStatement: public AbstractStatement {

public:
    PrintStatement(std::string identifier): _identifier{identifier} {}
    ~PrintStatement() = default;

    virtual void evaluate(SymbolTable &);
    virtual void codegen(CompilerContext *);

    virtual void dumpAST(std::string);


private:
    std::string _identifier;
};

class AssignmentStatement: public AbstractStatement {

public:
    AssignmentStatement(std::string val, std::unique_ptr<AbstractNode> toAssign):
        _val{val}, _assign{std::move(toAssign)}
    {}
    ~AssignmentStatement() = default;

    virtual void evaluate(SymbolTable &);
    virtual void codegen(CompilerContext *);

    virtual void dumpAST(std::string);


private:
    std::string _val;
    std::unique_ptr<AbstractNode> _assign;
};

class FunctionCall: public AbstractStatement {
public:

    FunctionCall(
        std::string functionName,
        std::unique_ptr<std::vector<std::unique_ptr<AbstractNode>>> funcArgs
    ): _functionName{functionName}, _functionArgs{std::move(funcArgs)}
    {}

    ~FunctionCall() = default;

    virtual void codegen(CompilerContext *);
    virtual void evaluate(SymbolTable &);
    virtual void dumpAST(std::string);

// private:
    std::string _functionName;
    std::unique_ptr<std::vector<std::unique_ptr<AbstractNode>>> _functionArgs;
};

class FunctionDefinition {

public:
    FunctionDefinition(
        std::string functionName,
        std::vector<std::string> functionArgNames,
        std::unique_ptr<GroupedStatements> functionBody
    ): _functionName{functionName},
       _functionArgNames{functionArgNames},
       _functionBody{std::move(functionBody)}
    {}

    void dumpAST(std::string);
    void evaluate(SymbolTable &);


// private:
    std::string _functionName;
    std::vector<std::string> _functionArgNames;
    std::unique_ptr<GroupedStatements> _functionBody;
};



#endif