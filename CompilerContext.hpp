#ifndef __COMPILER_CONTEXT__
#define __COMPILER_CONTEXT__

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"

class CompilerContext {
public:
llvm::LLVMContext TheContext;
llvm::IRBuilder<> Builder{TheContext};
std::unique_ptr<llvm::Module> TheModule;
std::map<std::string, llvm::Value *> NamedValues;
};

#endif
