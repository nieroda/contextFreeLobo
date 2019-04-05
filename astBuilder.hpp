#ifndef __astBuilder_HPP
#define __astBuilder_HPP

#include "Tokenizer.hpp"
#include "Statement.hpp"
#include "Node.hpp"
#include "Token.hpp"

class ASTBuilder {

public:
    ASTBuilder(std::unique_ptr<Tokenizer> tokens):
        _tokens{std::move(tokens)}
    {}

    std::unique_ptr<GroupedStatements> statements();
    std::unique_ptr<AbstractStatement> statement();
    std::unique_ptr<AssignmentStatement> assign();
    std::unique_ptr<PrintStatement> print();

    std::unique_ptr<AbstractNode> arithExpr();
    std::unique_ptr<AbstractNode> arithTerm();
    std::unique_ptr<AbstractNode> arithPrimary();
    std::unique_ptr<AbstractNode> arithFactor();


private:
    std::unique_ptr<Tokenizer> _tokens;
};

#endif