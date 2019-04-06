#ifndef __FUNCTION_DEF
#define __FUNCTION_DEF

#include <string>
#include <vector>
#include <iostream>
#include "CompilerContext.hpp"

class FunctionDefinition {

public:
    FunctionDefinition(
        std::string functionName,
        std::vector<std::string> functionArgNames,
        std::unique_ptr<GroupedStatements> functionBody
    ): _functionName{functionName},
       _functionArgNames{functionArgNames},
       _functionBody{std::move(functionBody)}
    {}

    void dumpAST(std::string tab, CompilerContext *c) {

        std::cout << tab << "FunctionDefinition: " << _functionName << "(";
        for_each(_functionArgNames.begin(), _functionArgNames.end(), [&](auto &item) {
            std::cout << item << ", ";
        });
        std::cout << std::endl;
        _functionBody->dumpAST(tab + "\t", c);


    }


private:
    std::string _functionName;
    std::vector<std::string> _functionArgNames;
    std::unique_ptr<GroupedStatements> _functionBody;
};

#endif
