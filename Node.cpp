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

void ExprNode::printInstr(llvm::LLVMContext *c, SymbolTable &symTab) {
   std::cout << "Printing exprNode value\n";
};

llvm::Value *ExprNode::codegen(CompilerContext *c) {

    llvm::Value *L = _left->codegen(c);
    llvm::Value *R = _right->codegen(c);

    auto tok = getBaseClassToken();

    if ( tok->isSubtraction()  )
        return c->Builder.CreateSub(L, R, "subtmp");
        //return c->Builder.CreateFSub(L, R, "subtmp");
    else if ( tok->isAddition() )
        return c->Builder.CreateAdd(L, R, "addtmp");
        // return c->Builder.CreateFAdd(L, R, "addtmp");
    else if ( tok->isMultiplication() )
        return c->Builder.CreateMul(L, R, "multmp");
    // else if ( tok->isDivision() )
    //     return left / right;
    // else if ( tok->isModOp() )
    //     return left % right;
    return nullptr;

    // just + - *
    // return llvm::ConstantFP::get(c->TheContext, llvm::APFloat(3.));
}

llvm::Value *IntNode::codegen(CompilerContext *c) {
    return llvm::ConstantFP::get(c->TheContext, llvm::APFloat(3.));
}

void IntNode::printInstr(llvm::LLVMContext *context, SymbolTable &symTab) { 
     int value = evaluate(symTab);
     double val = value * 1.0;
     auto num = llvm::ConstantFP::get(*context, llvm::APFloat(val));

     std::cout << "Printing int value\n";
     num->print(llvm::errs());
};


int IntNode::evaluate(SymbolTable &symTab) {

    std::string value = getBaseClassToken()->getTok();

    if (isalpha(value[0])) { //hacky
        return symTab.getItem(value);
    }

    return std::stoi(getBaseClassToken()->getTok());
}

