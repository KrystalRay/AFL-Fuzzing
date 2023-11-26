#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
//假设我们需要插入的函数是svp_simple_001_001_isr_1
using namespace llvm;

namespace {
  struct InsertFooInMainPass : public FunctionPass {
    static char ID;
    InsertFooInMainPass() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      // 只对名为 "main" 的函数进行操作
      if (F.getName() != "main")
        return false;

      Module *M = F.getParent();
      LLVMContext &Context = M->getContext();

      // 获取或创建 foo 函数的声明
      FunctionCallee FooFunc = M->getOrInsertFunction("svp_simple_001_001_isr_1", Type::getVoidTy(Context));

      // 遍历 main 函数的每个基本块
      for (BasicBlock &BB : F) {
        IRBuilder<> Builder(&BB, BB.begin());
        Builder.CreateCall(FooFunc, {}); // 在基本块开始处插入对 foo 的调用
      }

      return true; // 返回 true，表示函数被修改
    }
  };
}

char InsertFooInMainPass::ID = 0;
static RegisterPass<InsertFooInMainPass> X("insert-foo-in-main", "Insert foo() in main() Function Pass", false, false);
