#ifndef __TOKEN_HPP
#define __TOKEN_HPP

#include <string>

class Token {
public:
    Token(std::string tok): _tok{tok} {};
    ~Token() = default;

    std::string toPrint() { return _tok; }
    std::string getTok()  { return _tok; }

    bool isEOF()        { return _tok == "EOF"; }
    bool isGT()         { return _tok == ">";   }
    bool isGTE()        { return _tok == ">=";  }
    bool isLT()         { return _tok == "<";   }
    bool isLTE()        { return _tok == "<=";  }
    bool isAssign()     { return _tok == "==";  }
    bool isEquality()   { return _tok == "=";   }
    bool isKeyword ()   { return _tok == "print"; }
    bool isIdentifier() { return !isKeyword() && 
                                 !isEOF()     &&
                                 !isGT()      &&
                                 !isGTE()     &&
                                 !isLT()      &&
                                 !isLTE()     &&
                                 !isAssign()  &&
                                 !isEquality(); }

private:
    std::string _tok;
};

#endif