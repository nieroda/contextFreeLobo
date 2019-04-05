#ifndef __TOKENIZER__HPP
#define __TOKENIZER__HPP


#include <boost/tokenizer.hpp>
#include <string>
#include <vector>
#include <fstream>

#include "Token.hpp"

class Tokenizer {
    public:
        Tokenizer(std::string);


        void ungetToken();
        std::shared_ptr<Token> getToken();

    private:
        std::vector<std::shared_ptr<Token>> _tokens;
        int currentPosition{0};

};

#endif