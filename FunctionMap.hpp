#ifndef __FUNCTION_MAP_HPP
#define __FUNCTION_MAP_HPP

#include "FunctionDef.hpp"

//Assuming all accesses are defined accesses -- beef up later

class FunctionMap {
public:
    FunctionMap() = default;
    ~FunctionMap() = default;

    void addFunction(std::string varName, std::shared_ptr<FunctionDefinition> func) {
        _table[varName] = func;
    }

    std::shared_ptr<FunctionDefinition> getFunction(std::string varName) {
        return _table[varName];
    }

    bool isDefined(std::string varName) {
        //Do later
        return true;
    }


private:
    std::map<std::string, std::shared_ptr<FunctionDefinition>> _table;
};

#endif
