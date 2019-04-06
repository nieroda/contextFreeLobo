#include "astBuilder.hpp"
#include "FunctionDef.hpp"

#include <iostream>
#include <memory>

std::unique_ptr<AbstractStatement> ASTBuilder::program() {

    auto tok = _tokens->getToken();

    auto stmts = std::make_unique<GroupedStatements>();

    while ( tok->isCallLobo() || tok->isNomaHacks() || !tok->isEOF()) {

        if ( tok->isCallLobo() ) {
            _tokens->ungetToken();
            stmts->addStatement(functionCall());
        }

        if ( tok->isNomaHacks() ) {
             _tokens->ungetToken();
             functionDef();
            //stmts->addStatement(functionDef());
        }

        tok = _tokens->getToken();

    }

    return stmts;
}

std::unique_ptr<AbstractStatement> ASTBuilder::functionCall() {

    auto tok = _tokens->getToken();

    if ( !tok->isCallLobo() ) {
        std::cout << "ERROR FunctionCall" << std::endl;
        exit(1); 
    }

    tok = _tokens->getToken();

    if ( !tok->isLT() ) {
        std::cout << "ERROR FunctionCall" << std::endl;
        exit(1); 
    }

    tok = _tokens->getToken();

    if ( !tok->isIdentifier() ) {
        std::cout << "ERROR FunctionCall" << std::endl;
        exit(1);
    }

    std::string functionName = tok->getTok();

    tok = _tokens->getToken();

    if ( !tok->isGT() ) {
        std::cout << "ERROR FunctionCall" << std::endl;
        exit(1);
    }

    tok = _tokens->getToken();

    if ( !tok->isLParen() ) {
        std::cout << "ERROR FunctionCall" << std::endl;
        exit(1);
    }

    // get list
    // std::cout << "Before DYL" << std::endl;
    auto list = functionCallList();
    // std::cout << "After DYL" << std::endl;


    tok = _tokens->getToken();

    if ( !tok->isRParen() ) {
        std::cout << "ERROR FunctionCall" << std::endl;
        exit(1);
    }

    tok = _tokens->getToken();

    if ( !tok->isSemiC() ) {
        std::cout << "ERROR FunctionCall" << std::endl;
        exit(1);
    }

    return std::make_unique<FunctionCall>(functionName, std::move(list));

}

std::unique_ptr<std::vector<std::unique_ptr<AbstractNode>>> ASTBuilder::functionCallList() {

    auto vect = std::make_unique<std::vector<std::unique_ptr<AbstractNode>>>();

    auto tok = _tokens->getToken();

    while ( !tok->isRParen() ) {

        _tokens->ungetToken();
        // std::cout << "In Loop token is: " << tok->getTok() << std::endl;
        vect->push_back(arithExpr());

        tok = _tokens->getToken();
    }

    _tokens->ungetToken();

    return vect;
}

void ASTBuilder::functionDef() {

    // std::cout << "functionDef" << std::endl;

    auto tok = _tokens->getToken();

    if ( !tok->isNomaHacks() ) {
        std::cout << "ERROR FunctionDef" << std::endl;
        exit(1);
    }

    tok = _tokens->getToken();

    if ( !tok->isLT() ) {
        std::cout << "ERROR FunctionCall" << std::endl;
        exit(1); 
    }

    tok = _tokens->getToken();

    if ( !tok->isIdentifier() ) {
        std::cout << "ERROR FunctionCall" << std::endl;
        exit(1);
    }

    std::string funcName = tok->getTok();

    tok = _tokens->getToken();

    if ( !tok->isGT() ) {
        std::cout << "ERROR FunctionCall" << std::endl;
        exit(1); 
    }

    tok = _tokens->getToken();

    if ( !tok->isLParen() ) {
        std::cout << "ERROR FunctionCall" << std::endl;
        exit(1); 
    }

    std::vector<std::string> funcArgNames = collectFunctionArgNames();

    tok = _tokens->getToken();

    if ( !tok->isRParen() ) {
        std::cout << "ERROR FunctionCall" << std::endl;
        exit(1); 
    }

    tok = _tokens->getToken(); // <
    tok = _tokens->getToken(); // < (2 late 2 check)

    // std::cout << "Before Error" << std::endl;

    auto stmts = statements();

    // std::cout << "After Error" << std::endl;

    tok = _tokens->getToken(); // <
    tok = _tokens->getToken(); // <

    auto fDef = std::make_shared<FunctionDefinition>(funcName, funcArgNames, std::move(stmts));
    _functionMap->addFunction(funcName, fDef);
}

std::vector<std::string> ASTBuilder::collectFunctionArgNames() {

    auto tok = _tokens->getToken();

    std::vector<std::string> argNames;

    while ( !tok->isRParen() ) {

        if ( tok->isComma() ) { tok = _tokens->getToken(); }

        argNames.push_back(tok->getTok());

        tok = _tokens->getToken();
    }

    _tokens->ungetToken();
    return argNames;

}

std::unique_ptr<GroupedStatements> ASTBuilder::statements() {

    auto tok = _tokens->getToken();

    auto stmts = std::make_unique<GroupedStatements>();

    while ( !tok->isGT() ) {
        _tokens->ungetToken();
        stmts->addStatement(statement());
        tok = _tokens->getToken();
    }

    _tokens->ungetToken();
    return stmts;
}

std::unique_ptr<AbstractStatement> ASTBuilder::statement() {

    auto tok = _tokens->getToken();

    // std::cout << "ASTBuilder::statement(): " << tok->getTok() << std::endl;

    if ( tok->isKeywordPrint() ) {
        _tokens->ungetToken();
        return print();
    } else {
        _tokens->ungetToken();
        return assign();
    }
}

std::unique_ptr<AssignmentStatement> ASTBuilder::assign() {

    // std::cout << "ASSIGN" << std::endl;
    auto tok = _tokens->getToken();

    // std::cout << "ASsign First Token: " << tok->getTok() << std::endl;
    // std::cout << "ASTBuilder::assign(): " << tok->getTok() << std::endl;

    if ( !tok->isIdentifier() ) {
        std::cout << "Error ASTBuilder::assign()..token is " << tok->getTok() << std::endl;
        exit(1);
    }

    std::string identifier = tok->getTok();

    tok = _tokens->getToken();

    // std::cout << "ASsign Second Token: " << tok->getTok() << std::endl;


    if ( !tok->isAssign() ) {
        std::cout << "Error ASTBuilder::assign()..token is " << tok->getTok() << std::endl;
        exit(1);
    }

    auto expr = arithExpr();

    return std::make_unique<AssignmentStatement>(
        identifier,
        std::move(expr)
    );
}

std::unique_ptr<PrintStatement> ASTBuilder::print() {

    auto tok = _tokens->getToken();

    if ( !tok->isKeywordPrint() ) {
        std::cout << "Error ASTBuilder::print()" << std::endl;
        exit(1);
    }

    tok = _tokens->getToken();

    if ( !tok->isIdentifier() ) {
        std::cout << "Error ASTBuilder::print()" << std::endl;
        exit(1);
    }

    return std::make_unique<PrintStatement>(tok->getTok());

}

std::unique_ptr<AbstractNode> ASTBuilder::arithExpr() {

    auto left = arithTerm();
    auto tok = _tokens->getToken();

    while ( tok->isAddition() || tok->isSubtraction() ) {
        auto treeNode = std::make_unique<ExprNode>(tok);
        treeNode->_left = arithTerm();
        treeNode->_right = std::move(left);
        left = std::move(treeNode);

        tok = _tokens->getToken();
    }

    _tokens->ungetToken();
    return left;

}

std::unique_ptr<AbstractNode> ASTBuilder::arithTerm() {

    auto left = arithPrimary();
    auto tok = _tokens->getToken();

    while ( tok->isMultiplication() || tok->isDivision() || tok->isModOp() ) {
        auto treeNode = std::make_unique<ExprNode>(tok);
        treeNode->_left = arithPrimary();
        treeNode->_right = std::move(left);
        left = std::move(treeNode);

        tok = _tokens->getToken();
    }

    _tokens->ungetToken();
    return left;

}

std::unique_ptr<AbstractNode> ASTBuilder::arithPrimary() {

    auto tok = _tokens->getToken();

    if ( tok->isLParen() ) {

        auto nestedNode = arithExpr();

        tok = _tokens->getToken();

        if ( !tok->isRParen() ) {
            std::cout << "Error ASTBuilder::arithPrimary()" << std::endl;
            exit(1);
        }
        return nestedNode;

    } else {
        _tokens->ungetToken();
        return arithFactor();
    }
}

std::unique_ptr<AbstractNode> ASTBuilder::arithFactor() {

    // Need error checking here

    auto tok = _tokens->getToken();
    // std::cout << "Factor get token: " << tok->getTok() << std::endl;

    // std::cout << "ArithFactor: " << tok->getTok() << std::endl;

    return std::make_unique<IntNode>(tok);

}