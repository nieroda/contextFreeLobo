#include "Tokenizer.hpp"

#include <streambuf>
#include <iostream>


Tokenizer::Tokenizer(std::string fileName) {

    static auto dropped_delims = " \n\t\r";
    static auto kept_delims = "/%+-=";

    std::ifstream fileStream(fileName);
    std::string fileHolder;

    fileStream.seekg(0, std::ios::end);   
    fileHolder.reserve(fileStream.tellg());
    fileStream.seekg(0, std::ios::beg);

    fileHolder.assign(
        (std::istreambuf_iterator<char>(fileStream)),
        std::istreambuf_iterator<char>()
    );

    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;

    boost::char_separator<char> sep(
        dropped_delims, kept_delims /* boost::keep_empty_tokens */);
    tokenizer tokens(fileHolder, sep);

    auto tok_iter = tokens.begin();

    _tokens.reserve(200);

    for (tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
        _tokens.emplace_back(new Token(*tok_iter));
    }
    _tokens.emplace_back(new Token("EOF"));
}

std::shared_ptr<Token> Tokenizer::getToken() {

    if (currentPosition > _tokens.size())
        return nullptr;
    return _tokens.at(currentPosition++);
}

void Tokenizer::ungetToken() {
    if (currentPosition == 0)
        return;
    currentPosition--;
}


