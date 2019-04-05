
#include <iostream>
#include <boost/tokenizer.hpp>
#include <string>

#include "Tokenizer.hpp"
#include "Token.hpp"
#include "astBuilder.hpp"


// explicit char_separator(const Char* dropped_delims,
//                         const Char* kept_delims = "",
//                         empty_token_policy empty_tokens = drop_empty_tokens)



int main() {

    std::unique_ptr<Tokenizer> tokens = std::make_unique<Tokenizer>("data.txt");
    
    auto astBuilder = std::make_unique<ASTBuilder>(std::move(tokens));
    auto ast = astBuilder->statements();
    SymbolTable symTab;
    ast->evaluate(symTab);


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