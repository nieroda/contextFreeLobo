#ifndef __CMP_SYMTAB_HPP
#define __CMP_SYMTAB_HPP

//#include "Statement.hpp"
class AbstractStatement;
class FunctionDefinition;
#include "Statement.hpp"

#include <map>
#include <string>
#include <iostream>

// class FunctionDefinition;

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

    void addFunction(std::string varName, std::shared_ptr<FunctionDefinition> func) {
        _funcTable[varName] = func;
    }

    std::shared_ptr<FunctionDefinition> getFunction(std::string varName) {
        return _funcTable[varName];
    }

    void dumpAST(std::string tab) {

        std::cout << "FuncDEFN START" << std::endl;

        for (auto &item: _funcTable) {
            item.second->dumpAST(tab);
            std::cout << "\n\n";
        }

        std::cout << "FuncDEF END\n\n" << std::endl;

    }

private:
    std::map<std::string, int> _table;
    std::map<std::string, std::shared_ptr<FunctionDefinition>> _funcTable;

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