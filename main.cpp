
#include <iostream>
#include <boost/tokenizer.hpp>
#include <string>
#include <memory>

#include "Tokenizer.hpp"
#include "Token.hpp"
#include "astBuilder.hpp"


#include "CompilerContext.hpp"
// explicit char_separator(const Char* dropped_delims,
//                         const Char* kept_delims = "",
//                         empty_token_policy empty_tokens = drop_empty_tokens)




int main() {

    std::unique_ptr<Tokenizer> tokens = std::make_unique<Tokenizer>("data.txt");
    
    // llvm::LLVMContext TheContext;
    // llvm::IRBuilder<> Builder(TheContext);
    // std::unique_ptr<llvm::Module> TheModule;
    // std::map<std::string, llvm::Value *> NamedValues;

    CompilerContext *c = new CompilerContext();

    auto astBuilder = std::make_unique<ASTBuilder>(std::move(tokens));
    auto ast = astBuilder->statements();
    SymbolTable symTab;
    // ast->evaluate(symTab);
    ast->dumpAST("");


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

// clang++ -g -O3 toy.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -o toy
//  g++ -std=c++17 -lboost_system main.cpp Tokenizer.cpp astBuilder.cpp Statement.cpp Node.cpp  `llvm-config --cxxflags --ldflags --system-libs --libs core` -o interp && ./interp

//  g++ -lboost_system main.cpp Tokenizer.cpp astBuilder.cpp Statement.cpp Node.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -std=c++17 && ./a.out
