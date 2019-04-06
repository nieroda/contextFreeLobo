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

    int left =  _left->evaluate(symTab);
    int right = _right->evaluate(symTab);

    auto tok = getBaseClassToken();

    llvm::LLVMContext *context = new llvm::LLVMContext();
		_left->printInstr(context, symTab);
		_right->printInstr(context, symTab);

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
	 std::cout << "left is: " << _left->evaluate(symTab) << std::endl;
	 std::cout << "right is: " << _right->evaluate(symTab) << std::endl;
	 float leftVal = 1.0 * _left->evaluate(symTab);
	 float rightVal = 1.0 * _right->evaluate(symTab);
	 std::cout << "Values are\n";
   std::cout << leftVal << rightVal << std::endl;
   auto left = llvm::ConstantFP::get(*c, llvm::APFloat(leftVal));
   auto right = llvm::ConstantFP::get(*c, llvm::APFloat(rightVal));
   llvm::IRBuilder<> Builder{*c};
   auto tok = getBaseClassToken();

   if ( tok->isSubtraction() ) {
			std::cout << "subtraction\n";
       auto build = Builder.CreateSub(left,right, "subTmp");
       //build->print(llvm::errs(), false);
	 }
   else if ( tok->isAddition() ) {
			std::cout << "additon\n";
			left->print(llvm::errs());
			right->print(llvm::errs());
       auto build = Builder.CreateAdd(left,right, "addtmp");
       //build->print(llvm::errs(), false);
	 }
  // std::cout << "\nPrinting exprNode value\n";

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
		 std::cout << " " << std::endl;
     num->print(llvm::errs());
};


int IntNode::evaluate(SymbolTable &symTab) {

    std::string value = getBaseClassToken()->getTok();

    if (isalpha(value[0])) { //hacky
        return symTab.getItem(value);
    }

    return std::stoi(getBaseClassToken()->getTok());
}

