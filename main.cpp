
#include <iostream>
#include <boost/tokenizer.hpp>
#include <string>

#include "Tokenizer.hpp"
#include "Token.hpp"


// explicit char_separator(const Char* dropped_delims,
//                         const Char* kept_delims = "",
//                         empty_token_policy empty_tokens = drop_empty_tokens)



int main() {

    std::unique_ptr<Tokenizer> tok = std::make_unique<Tokenizer>("data.txt");

    // auto token = tok->getToken();

    // while ( !token->isEOF() ) {

    //     std::cout << "Token: " << token->getTok() << std::endl;
    //     token = tok->getToken();

    // }

    /* Tests */
    auto token = tok->getToken();




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