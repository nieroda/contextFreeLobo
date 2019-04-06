
#include <iostream>
//#include <boost/tokenizer.hpp>
#include <string>

//#include "Tokenizer.hpp"
//#include "Token.hpp"
//#include "astBuilder.hpp"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/raw_os_ostream.h"
#include "llvm/IR/Constants.h"
#include "llvm/Passes/PassBuilder.h"
#include <map>

// explicit char_separator(const Char* dropped_delims,
//                         const Char* kept_delims = "",
//                         empty_token_policy empty_tokens = drop_empty_tokens)

int main() {
    llvm::LLVMContext TheContext;
    llvm::LLVMContext NathansContext;

    std::map <std::string, llvm::Value *> NamedValues;

    auto num = llvm::ConstantInt::get(TheContext, llvm::APInt(32, 3, false));
    llvm::APInt value = num->getValue();
    std::ostream & objOstream = std::cout;
    llvm::raw_os_ostream out =  llvm::raw_os_ostream(objOstream);
    value.print(out,false);
    std::cout << " " << std::endl;

    NamedValues["hello"] = num;

    auto left = llvm::ConstantFP::get(TheContext, llvm::APFloat(3.0));
    auto right = llvm::ConstantFP::get(TheContext, llvm::APFloat(4.0));
    auto s = llvm::ConstantFP::get(NathansContext, llvm::APFloat(1.0));

    llvm::IRBuilder<> Builder{TheContext};

    auto build = Builder.CreateAdd(left,right, "addtmp");
    auto nextgen = Builder.CreateSub(s, build, "subtmp");
    //auto leftBuilder = Builder.CreateRet(left);
    //auto test = Builder.CreateRet(build);
    build->print(llvm::errs(), true);
    std::cout << " " << std::endl;
    nextgen->print(llvm::errs(),true);
    std::cout << " " << std::endl;
    nextgen->printAsOperand(llvm::errs(),true);
    //test->print(llvm::errs());
    //std::cout << " " << std::endl;
    //left->print(llvm::errs());
    //std::cout << " " << std::endl;
    //build->print(llvm::errs());

    //std::cout << " " << std::endl;


    //llvm::IntegerType *x = new llvm::IntegerType(TheContext, y);
    //llvm::Value *v = new llvm::Value(x); 
    /*
    std::unique_ptr<Tokenizer> tokens = std::make_unique<Tokenizer>("data.txt");
    auto astBuilder = std::make_unique<ASTBuilder>(std::move(tokens));
    auto ast = astBuilder->statements();
    SymbolTable symTab;
    ast->evaluate(symTab); */
    return 0;
}

/*
Token: foo
Token: =
Token: 1
Token: bar
Token: =
Token: 50
Token: print
Token: bar
Token: >
Token: =
Token: <
Token: =
Token: <
Token: >
*/
