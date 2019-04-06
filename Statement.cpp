#include <iostream>
#include <algorithm>
#include "Statement.hpp"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"


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

void GroupedStatements::dumpAST(std::string tab, CompilerContext *c) {
    std::cout << tab << "GroupedStatements: " << this << std::endl;
    for_each(_statements.begin(), _statements.end(), [&](auto &&stmt) {
        stmt->dumpAST(tab + "\t", c);
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

void PrintStatement::dumpAST(std::string tab, CompilerContext *c) {
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

void AssignmentStatement::dumpAST(std::string tab, CompilerContext *c) {
    std::cout << tab << "AssignmentStatement: " << this << "\t" << _val << " =" << std::endl;
    _assign->dumpAST(tab + "\t", c);
}

// END AS

void FunctionCall::codegen(CompilerContext *c) {
  // Make the function type:  double(double,double) etc.
  std::vector<llvm::Type*> Doubles(_functionArgs->size(),llvm::Type::getDoubleTy(c->TheContext));
  llvm::FunctionType *FT = llvm::FunctionType::get(llvm::Type::getDoubleTy(c->TheContext), Doubles, false);
  llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, _functionName, c->TheModule.get());

   // Set names for all arguments.
   unsigned Idx = 0;
   for (auto &Arg : F->args())
     Arg.setName("s");
   F->print(llvm::errs());
   //return F;
}

void FunctionCall::evaluate(SymbolTable &symTab) {
    /*
    auto func = symTab.getFuncMap()->getFunction(_functionName);

    //Bring Function Arguments Into Scope
    if (func->_functionArgNames.size() != _functionArgs->size()) {
        std::cout << "There is a problem" << std::endl;
    }

    for (int i = 0; i < func->_functionArgNames.size(); i++) {
        symTab.addItem(func->_functionArgNames[i], _functionArgs[i]->evaluate(symTab));
    }*/

}

void FunctionCall::dumpAST(std::string tab, CompilerContext *c) {
    std::cout << tab << "FunctionCall: " << _functionName << " " << this << std::endl;
    codegen(c);
    for_each(_functionArgs->begin(), _functionArgs->end(), [&](auto &node) {
        node->dumpAST(tab + "\t", c);
    });
}
