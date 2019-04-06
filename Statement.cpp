#include <iostream>
#include <algorithm>
#include "Statement.hpp"



void GroupedStatements::evaluate(SymbolTable &symTab) {
    for_each(_statements.begin(), _statements.end(), [&](auto &&stmt) {
        stmt->evaluate(symTab);
    });
    
}

void GroupedStatements::addStatement(std::unique_ptr<AbstractStatement> stmt) {
    _statements.push_back(std::move(stmt));
}

void GroupedStatements::codegen(CompilerContext *c) {
    for_each(_statements.begin(), _statements.end(), [&](auto &&stmt) {
        stmt->codegen(c);
    });


    // Function *callee = c->TheModule->

}

void GroupedStatements::dumpAST(std::string tab) {
    std::cout << tab << "GroupedStatements: " << this << std::endl;
    for_each(_statements.begin(), _statements.end(), [&](auto &&stmt) {
        stmt->dumpAST(tab + "\t");
    });
}

// END GS

// START PS

void PrintStatement::evaluate(SymbolTable &symTab) {
    std::cout << symTab.getItem(_identifier) << std::endl;
}

// https://stackoverflow.com/questions/35526075/llvm-how-to-implement-print-function-in-my-language
void PrintStatement::codegen(CompilerContext *c) {
    //todo
}

void PrintStatement::dumpAST(std::string tab) {
    std::cout << tab << "PrintStatement: " << this << "\t" << _identifier  << std::endl;
}

// END PS

//Start AS 

void AssignmentStatement::evaluate(SymbolTable &symTab) {
    symTab.addItem(_val, _assign->evaluate(symTab));
}


void AssignmentStatement::codegen(CompilerContext *c) {
    c->NamedValues[_val] = llvm::ConstantInt::get(c->TheContext, llvm::APInt(32, 3, false));
}

void AssignmentStatement::dumpAST(std::string tab) {
    std::cout << tab << "AssignmentStatement: " << this << "\t" << _val << " =" << std::endl;
    _assign->dumpAST(tab + "\t");
}

// END AS

void FunctionCall::codegen(CompilerContext *c) {}

void FunctionCall::evaluate(SymbolTable &symTab) {

    auto func = symTab.getFuncMap()->getFunction(_functionName);

    //Bring Function Arguments Into Scope
    if (func->_functionArgNames.size() != _functionArgs->size()) {
        std::cout << "There is a problem" << std::endl;
    }

    for (int i = 0; i < func->_functionArgNames.size(); i++) {
        symTab.addItem(func->_functionArgNames[i], _functionArgs[i]->evaluate(symTab));
    }

}

void FunctionCall::dumpAST(std::string tab) {
    std::cout << tab << "FunctionCall: " << _functionName << " " << this << std::endl;
    for_each(_functionArgs->begin(), _functionArgs->end(), [&](auto &node) {
        node->dumpAST(tab + "\t");
    });
}