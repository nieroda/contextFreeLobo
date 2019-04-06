#include "Node.hpp"
#include <iostream>

#include "llvm/ADT/APInt.h"

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
    return llvm::ConstantFP::get(c->TheContext, llvm::APFloat(3.));
}

llvm::Value *IntNode::codegen(CompilerContext *c) {
    return llvm::ConstantFP::get(c->TheContext, llvm::APFloat(3.));
}

int IntNode::evaluate(SymbolTable &symTab) {
    return std::stoi(getBaseClassToken()->getTok());
}

