#ifndef __AST__NODE_HPP
#define __AST__NODE_HPP

#include "Token.hpp"
#include "SymbolTable.hpp"

#include "llvm/IR/Value.h"
#include "CompilerContext.hpp"

class AbstractNode {
public:
    AbstractNode(std::shared_ptr<Token> tok): _tok{tok} {}
    virtual int evaluate(SymbolTable &symTab) = 0;
    virtual ~AbstractNode() = default;

    virtual llvm::Value *codegen(CompilerContext *) = 0;
    std::shared_ptr<Token> getBaseClassToken() { return _tok; }

    virtual void dumpAST(std::string, CompilerContext *) = 0;


private:
    std::shared_ptr<Token> _tok;
};

class ExprNode: public AbstractNode {
public:

    ExprNode(
        std::unique_ptr<AbstractNode> left,
        std::unique_ptr<AbstractNode> right,
        std::shared_ptr<Token> tok
    ): 
        _left{std::move(left)}, 
        _right{std::move(right)},
        AbstractNode(tok)
    {}

    ExprNode(
        std::shared_ptr<Token> tok
    ): AbstractNode(tok) {}

    virtual llvm::Value *codegen(CompilerContext *);
    virtual int evaluate(SymbolTable &symTab);
    virtual ~ExprNode() = default; 
    virtual void dumpAST(std::string, CompilerContext *);

//rip
public:
    std::unique_ptr<AbstractNode> _left, _right;
};

class IntNode: public AbstractNode {
public:
    IntNode(std::shared_ptr<Token> tok): AbstractNode(tok) {}
    virtual ~IntNode() = default;

    virtual llvm::Value *codegen(CompilerContext *);
    virtual int evaluate(SymbolTable &);
    virtual void dumpAST(std::string, CompilerContext *);
};

#endif
