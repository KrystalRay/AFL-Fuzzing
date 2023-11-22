//This pass is used to Print each instruction in the LLIM-IR file. Using simple loop from Module layer to Instruction layer.

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

namespace{
    struct  Print_Instruction : public ModulePass{
        static char ID;
        Print_Instruction() :ModulePass(ID){}
        virtual bool runOnModule(Module &M)
        {
            for(auto& F : M)
            {
                for(auto& B : F)
                {
                    for(auto& I :B) errs() << I << "\n";
                }
            }
            return true;
        }
    };
}

char Print_Instruction::ID = 0;
static RegisterPass<Print_Instruction> X("PrtIns","Print each instruction in the IR file.");
