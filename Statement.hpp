#ifndef __AST__STATEMENT__
#define __AST__STATEMENT__

class SymbolTable {};

class AbstractStatement {
public:
    virtual void evaluate(SymbolTable &symTab) = 0;

private:

}

#endif