#ifndef __CMP_SYMTAB_HPP
#define __CMP_SYMTAB_HPP

#include <map>
#include <string>

//Assuming all accesses are defined accesses -- beef up later

class SymbolTable {
public:
    SymbolTable() = default;
    ~SymbolTable() = default;

    void addItem(std::string varName, int value) {
        _table[varName] = value;
    }

    int getItem(std::string varName) {
        return _table[varName];
    }

    bool isDefined(std::string varName) {
        //Do later
        return true;
    }


private:
    std::map<std::string, int> _table;
};

#endif