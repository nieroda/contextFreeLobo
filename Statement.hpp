#ifndef __AST__STATEMENT__
#define __AST__STATEMENT__

#include <vector>
#include <string>

#include "SymbolTable.hpp"

class AbstractStatement {
public:
    virtual void evaluate(SymbolTable &) = 0;

};

class GroupedStatements: public AbstractStatement {
    
public:
    GroupedStatements() = default;
    ~GroupedStatements() = default;

    virtual void evaluate(SymbolTable &);
    void addStatement(std::unique_ptr<AbstractStatement> stmt);


private:
    std::vector<std::unique_ptr<AbstractStatement>> _statements;
};

class PrintStatement: public AbstractStatement {

public:
    PrintStatement(std::string identifier): _identifier{identifier} {}
    ~PrintStatement() = default;

    virtual void evaluate(SymbolTable &);

private:
    std::string _identifier;
};

#endif