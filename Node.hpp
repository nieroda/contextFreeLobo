#ifndef __AST__NODE_HPP
#define __AST__NODE_HPP

#include "Token.hpp"

class SymbolTable {};

class AbstractNode {
public:
    AbstractNode(std::shared_ptr<Token> tok): _tok{tok} {}
    virtual int evaluate(SymbolTable &symTab) = 0;
    virtual ~AbstractNode() = default;
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

    virtual int evaluate(SymbolTable &symTab);
    virtual ~ExprNode() = default; 

private:
    std::unique_ptr<AbstractNode> _left, _right;
};

#endif