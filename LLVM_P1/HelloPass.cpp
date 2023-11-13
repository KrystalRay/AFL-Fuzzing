#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "hello"
namespace {
    struct Hello : public FunctionPass {
        static char ID;
        Hello() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            Module *M = F.getParent();
            
            FunctionCallee printfFunc = getPrintfFunction(*M);

            for (auto &BB : F) {
                IRBuilder<> builder(&BB, BB.begin());
                builder.SetInsertPoint(&BB, BB.begin());
                Value *formatStr = builder.CreateGlobalStringPtr("Hello from LLVM Pass!\n");
                builder.CreateCall(printfFunc, {formatStr});
            }

            return true;
        }

        FunctionCallee getPrintfFunction(Module &M) {
            LLVMContext &context = M.getContext();
            FunctionType *printfType = FunctionType::get(IntegerType::getInt32Ty(context), PointerType::get(IntegerType::getInt8Ty(context), 0), true);
            Function *printfFunc = Function::Create(printfType, Function::ExternalLinkage, "printf", &M);
            return printfFunc;
        }
    };
}

char Hello::ID = 0;
static RegisterPass<Hello> X("hello123", "Hello World Pass");
