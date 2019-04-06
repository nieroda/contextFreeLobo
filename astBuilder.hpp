#ifndef __astBuilder_HPP
#define __astBuilder_HPP

#include "Tokenizer.hpp"
#include "Statement.hpp"
#include "Node.hpp"
#include "Token.hpp"

#include "FunctionDef.hpp"
#include "FunctionMap.hpp"

class ASTBuilder {

public:
    ASTBuilder(std::unique_ptr<Tokenizer> tokens, std::shared_ptr<FunctionMap> fMap):
        _tokens{std::move(tokens)},
        _functionMap{fMap}
    {}

    std::unique_ptr<AbstractStatement> program();
    std::unique_ptr<AbstractStatement> functionCall();
    void functionDef();

    std::unique_ptr<
        std::vector<
            std::unique_ptr<AbstractNode>
            >
        > functionCallList();

    std::vector<std::string> collectFunctionArgNames();

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
    std::shared_ptr<FunctionMap> _functionMap;
};

#endif