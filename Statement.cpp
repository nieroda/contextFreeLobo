#include <iostream>
#include <algorithm>
#include "Statement.hpp"



void GroupedStatements::evaluate(SymbolTable &symTab) {
    for_each(_statements.begin(), _statements.end(), [&](auto &&stmt) {
        stmt->evaluate(symTab);
    });
    
}

void GroupedStatements::printInstrs(llvm::LLVMContext *context) {
   for_each(_statements.begin(), _statements.end(), [&](auto &&stmt) {
       stmt->printInstrs(context);
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

// END GS

// START PS

void PrintStatement::evaluate(SymbolTable &symTab) {
    std::cout << symTab.getItem(_identifier) << std::endl;
}

// https://stackoverflow.com/questions/35526075/llvm-how-to-implement-print-function-in-my-language
void PrintStatement::codegen(CompilerContext *c) {
    //todo
}

void PrintStatement::printInstrs(llvm::LLVMContext *context) {
       //todo
}

// END PS

//Start AS 

void AssignmentStatement::evaluate(SymbolTable &symTab) {
    symTab.addItem(_val, _assign->evaluate(symTab));
}


void AssignmentStatement::codegen(CompilerContext *c) {
    c->NamedValues[_val] = llvm::ConstantInt::get(c->TheContext, llvm::APInt(32, 3, false));
}

void AssignmentStatement::printInstrs(llvm::LLVMContext *context) {
	_assign->printInstr(context);
       //todo
}

// END AS
