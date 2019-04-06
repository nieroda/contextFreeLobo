#include "Node.hpp"
#include <iostream>
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

using namespace llvm;
static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
static std::map<std::string, Value *> NamedValues;

Value *LogError(const char *Str) {
  LogError(Str);
  return nullptr;
}

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

int IntNode::evaluate(SymbolTable &symTab) {
    return std::stoi(getBaseClassToken()->getTok());
}

/*
Value *ExprNode::codegen {	
    Value *v = NameValues[Name];
    if (!V)
        LogErrorV("Unknown Variable Name");
    return V;
};

Value *IntNode::codegen {
    return ConstantFP::gen(TheContext, APFloat(Val));	
}:*/
