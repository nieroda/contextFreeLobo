
#include <iostream>
#include <boost/tokenizer.hpp>
#include <string>
#include <memory>

#include "Tokenizer.hpp"
#include "Token.hpp"
#include "astBuilder.hpp"
#include "FunctionMap.hpp"


#include "CompilerContext.hpp"

int main() {

    std::unique_ptr<Tokenizer> tokens = std::make_unique<Tokenizer>("data.txt");
    std::shared_ptr<FunctionMap> fMap = std::make_shared<FunctionMap>();

    // CompilerContext *c = new CompilerContext();

    // auto tok = tokens->getToken();

    // while ( !tok->isEOF() ) {
    //     std::cout << "Token: " << tok->getTok() << std::endl;
    //     tok = tokens->getToken();
    // }

    auto astBuilder = std::make_unique<ASTBuilder>(std::move(tokens), fMap);
    // auto ast = astBuilder->statements();
    // SymbolTable symTab;
    // ast->evaluate(symTab);
    // ast->dumpAST("");


    return 0;

}

/*

<program> -> <function_call> | <function_definition>
<function_call> -> callLobo<|<id>|>( <arith_expr>* )
<function_definition> -> nomaHacks<|<id>|>( <id>* ) << <statements> >>

*/

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
