#include "Node.hpp"
#include <iostream>

#include "llvm/ADT/APInt.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/raw_os_ostream.h"
#include "llvm/IR/Constants.h"
#include "llvm/Passes/PassBuilder.h"
#include <map>
int ExprNode::evaluate(SymbolTable &symTab) {

    int left =  _left-> evaluate(symTab);
    int right = _right->evaluate(symTab);

    auto tok = getBaseClassToken();

    if ( tok->isSubtraction()  )
        return left - right;
    else if ( tok->isAddition() )
        return left + right;
    else if ( tok->isMultiplication() )
        return left * right;
    else if ( tok->isDivision() )
        return left / right;
    else if ( tok->isModOp() )
        return left % right;
    else {
        std::cout << "Unknown Token: " << tok->getTok() << " in ExprNode::evaluate()";
        std::cout << "Returning random value" << std::endl;
        return 0;
    }

}

llvm::Value *ExprNode::codegen(CompilerContext *c) {

    llvm::Value *L = _left->codegen(c);
    llvm::Value *R = _right->codegen(c);

    auto tok = getBaseClassToken();

    if ( tok->isSubtraction()  )
        return c->Builder.CreateSub(L, R, "subtmp");
    else if ( tok->isAddition() )
        return c->Builder.CreateAdd(L, R, "addtmp");
    else if ( tok->isMultiplication() )
        return c->Builder.CreateMul(L, R, "multmp");
    return nullptr;
}

void ExprNode::dumpAST(std::string tab, CompilerContext *c) {
    std::cout << tab << "ExprNode: " << this << std::endl;
    _left->dumpAST(tab + "\t", c);
    _right->dumpAST(tab + "\t", c);
    (_left->codegen(c))->print(llvm::errs());
    (_right->codegen(c))->print(llvm::errs());
}

llvm::Value *IntNode::codegen(CompilerContext *c) {
  // auto tok = getBaseClassToken();
   std::string::size_type sz;
   auto value = std::stoi(getBaseClassToken()->getTok(), &sz); 
   double val = value * 1.0;
   return llvm::ConstantFP::get(c->TheContext, llvm::APFloat(val));
}

int IntNode::evaluate(SymbolTable &symTab) {

    std::string value = getBaseClassToken()->getTok();

    if (isalpha(value[0])) { //hacky
        return symTab.getItem(value);
    }

    return std::stoi(getBaseClassToken()->getTok());
}

void IntNode::dumpAST(std::string tab, CompilerContext *c) {
    std::cout << tab << "IntNode: " << this << " " << getBaseClassToken()->getTok() << std::endl;
    std::cout << "\n" << tab;
    codegen(c)->print(llvm::errs());
    std::cout << "\n";

}
