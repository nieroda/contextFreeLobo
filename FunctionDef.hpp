#ifndef __FUNCTION_DEF
#define __FUNCTION_DEF

#include <string>
#include <vector>

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


private:
    std::string _functionName;
    std::vector<std::string> _functionArgNames;
    std::unique_ptr<GroupedStatements> _functionBody;
};

#endif