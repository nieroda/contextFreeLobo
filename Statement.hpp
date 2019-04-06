#ifndef __AST__STATEMENT__
#define __AST__STATEMENT__

#include <vector>
#include <string>

#include "SymbolTable.hpp"
#include "CompilerContext.hpp"
#include "llvm/IR/LLVMContext.h"
#include "Node.hpp"

class AbstractStatement {
public:
    virtual void evaluate(SymbolTable &) = 0;
    virtual ~AbstractStatement() = default;
    virtual void printInstrs(llvm::LLVMContext *) = 0;
    virtual void codegen(CompilerContext *) = 0;

};

class GroupedStatements: public AbstractStatement {
    
public:
    GroupedStatements() = default;
    ~GroupedStatements() = default;

    virtual void evaluate(SymbolTable &);
    void addStatement(std::unique_ptr<AbstractStatement> stmt);
    void printInstrs(llvm::LLVMContext *) ;
    virtual void codegen(CompilerContext *);


private:
    std::vector<std::unique_ptr<AbstractStatement>> _statements;
};

class PrintStatement: public AbstractStatement {

public:
    PrintStatement(std::string identifier): _identifier{identifier} {}
    ~PrintStatement() = default;
    void printInstrs(llvm::LLVMContext *); 

    virtual void evaluate(SymbolTable &);
    virtual void codegen(CompilerContext *);


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
    void printInstrs(llvm::LLVMContext *); 


private:
    std::string _val;
    std::unique_ptr<AbstractNode> _assign;
};

#endif
