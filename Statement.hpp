#ifndef __AST__STATEMENT__
#define __AST__STATEMENT__

#include <vector>
#include <string>

#include "SymbolTable.hpp"
#include "CompilerContext.hpp"
#include "Node.hpp"
#include "llvm/IR/Function.h"

class AbstractStatement {
public:
    virtual void evaluate(SymbolTable &) = 0;
    virtual ~AbstractStatement() = default;

    virtual void codegen(CompilerContext *) = 0;

    virtual void dumpAST(std::string, CompilerContext *) = 0;

};


class GroupedStatements: public AbstractStatement {
    
public:
    GroupedStatements() = default;
    ~GroupedStatements() = default;

    virtual void evaluate(SymbolTable &);
    void addStatement(std::unique_ptr<AbstractStatement> stmt);
    virtual void codegen(CompilerContext *);

    virtual void dumpAST(std::string, CompilerContext *);


private:
    std::vector<std::unique_ptr<AbstractStatement>> _statements;
};

class PrintStatement: public AbstractStatement {

public:
    PrintStatement(std::string identifier): _identifier{identifier} {}
    ~PrintStatement() = default;

    virtual void evaluate(SymbolTable &);
    virtual void codegen(CompilerContext *);

    virtual void dumpAST(std::string, CompilerContext *);


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

    virtual void dumpAST(std::string, CompilerContext *);


private:
    std::string _val;
    std::unique_ptr<AbstractNode> _assign;
};

// class Function {

// public:
//     ~Function() = default;

//     virtual void evaluate(
//         SymbolTable &,
//         std::vector<std::unique_ptr<AbstractNode>>
//     ) = 0;


// }


class FunctionCall: public AbstractStatement {
public:

    FunctionCall(
        std::string functionName,
        std::unique_ptr<std::vector<std::unique_ptr<AbstractNode>>> funcArgs
    ): _functionName{functionName}, _functionArgs{std::move(funcArgs)}
    {}

    ~FunctionCall() = default;

    //virtual llvm::Function codegen(CompilerContext *);
    virtual void codegen(CompilerContext *);
    virtual void evaluate(SymbolTable &);
    virtual void dumpAST(std::string, CompilerContext *);

private:
    std::string _functionName;
    std::unique_ptr<std::vector<std::unique_ptr<AbstractNode>>> _functionArgs;
    // std::unique_ptr<GroupedStatements> _funcBody;
};


#endif
