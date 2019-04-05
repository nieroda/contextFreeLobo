#include <iostream>

#include "Statement.hpp"



void GroupedStatements::evaluate(SymbolTable &symTab) {
    for_each(_statements.begin(), _statements.end(), [&](auto &&stmt) {
        stmt->evaluate(symTab);
    });
}

void GroupedStatements::addStatement(std::unique_ptr<AbstractStatement> stmt) {
    _statements.push_back(std::move(stmt));
}

// END GS

// START PS

void PrintStatement::evaluate(SymbolTable &symTab) {
    std::cout << symTab.getItem(_identifier) << std::endl;
}

// END PS

//Start AS 

void AssignmentStatement::evaluate(SymbolTable &symTab) {
    symTab.addItem(_val, _toAssign);
}

// END AS