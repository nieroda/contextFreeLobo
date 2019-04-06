
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

    CompilerContext *c = new CompilerContext();

    // auto tok = tokens->getToken();

    // while ( !tok->isEOF() ) {
    //     std::cout << "Token: " << tok->getTok() << std::endl;
    //     tok = tokens->getToken();
    // }

    auto astBuilder = std::make_unique<ASTBuilder>(std::move(tokens), fMap);

    auto ast = astBuilder->program();

    // fMap->dumpAST("");
    // ast->dumpAST("");


    // auto ast = astBuilder->statements();
    SymbolTable symTab;
    symTab.addFunctionMap(fMap.get());
    // ast->evaluate(symTab);
    ast->dumpAST("", c);


    return 0;
}
