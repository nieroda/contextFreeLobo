#ifndef __CMP_SYMTAB_HPP
#define __CMP_SYMTAB_HPP

#include <map>
#include <string>
#include <memory>
#include <algorithm>

// #include "FunctionMap.hpp"
class FunctionMap;

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

    void addFunctionMap(FunctionMap *fMap) {
        _fMap = fMap;
    }

    FunctionMap *getFuncMap() { return _fMap; }

private:
    std::map<std::string, int> _table;
    FunctionMap * _fMap;
};

#endif


// #include "llvm/IR/LLVMContext.h"
// #include "llvm/IR/IRBuilder.h"
// #include "llvm/IR/Module.h"


// llvm::ConstantInt::get(context, llvm::APInt(/*nbits*/32, value, /*bool*/is_signed));


// llvm::ConstantInt::get(context, llvm::APInt(/*nbits*/32, value, /*bool*/is_signed));

// get (IntegerType *Ty, uint64_t V, bool isSigned=false)

// llvm::ConstantInt::get()

// std::map<std::string, llvm::Value *> NamedValues;

// static ConstantInt * 	get (LLVMContext &Context, const APInt &V)

// llvm::ConstantInt::get(context, llvm::APInt(/*nbits*/32, /*val*/ 5, /*signed*/false));