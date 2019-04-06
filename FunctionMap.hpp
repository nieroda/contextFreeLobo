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

    void dumpAST(std::string tab) {

        std::cout << "FuncDEFN START" << std::endl;

        for (auto &item: _table) {
            item.second->dumpAST(tab);
            std::cout << "\n\n";
        }

        std::cout << "FuncDEF END\n\n" << std::endl;

    }


private:
    std::map<std::string, std::shared_ptr<FunctionDefinition>> _table;
};

#endif
