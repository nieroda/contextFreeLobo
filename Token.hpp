#ifndef __TOKEN_HPP
#define __TOKEN_HPP

#include <string>

class Token {
public:
    Token(std::string tok): _tok{tok} {};
    ~Token() = default;

    std::string toPrint() { return _tok; }
    std::string getTok()  { return _tok; }

    bool isEOF()            { return _tok == "EOF"; }
    bool isGT()             { return _tok == ">";   }
    bool isGTE()            { return _tok == ">=";  }
    bool isLT()             { return _tok == "<";   }
    bool isLTE()            { return _tok == "<=";  }
    bool isEquality()       { return _tok == "==";  }
    bool isAssign()         { return _tok == "=";   }
    bool isSubtraction()    { return _tok == "-";   }
    bool isAddition()       { return _tok == "+";   }
    bool isMultiplication() { return _tok == "*";   }
    bool isDivision()       { return _tok == "/";   }
    bool isModOp()          { return _tok == "%";   }
    bool isLParen()         { return _tok == "(";   }
    bool isRParen()         { return _tok == ")";   }
    bool isSemiC()          { return _tok == ";";   }
    bool isComma()          { return _tok == ",";   }

    bool isCallLobo()       { return _tok == "callLobo"; }
    bool isNomaHacks()      { return _tok == "nomaHacks"; }

    bool isKeywordPrint()   { return _tok == "print"; }

    bool isKeyword ()   { return _tok == "print"; }
    bool isIdentifier() { return !isKeyword() && 
                                 !isEOF()     &&
                                 !isGT()      &&
                                 !isGTE()     &&
                                 !isLT()      &&
                                 !isLTE()     &&
                                 !isAssign()  &&
                                 !isSubtraction() &&
                                 !isAddition()    &&
                                 !isMultiplication() &&
                                 !isDivision() &&
                                 !isModOp()    && //yuck
                                 !isEquality(); }

private:
    std::string _tok;
};

#endif
