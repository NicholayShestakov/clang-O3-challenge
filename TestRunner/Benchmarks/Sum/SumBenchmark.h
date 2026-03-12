#ifndef TESTRUNNER_BENCHMARKS_SUMBENCHMARK_H
#define TESTRUNNER_BENCHMARKS_SUMBENCHMARK_H

#include "../BenchRunner.h"
#include <llvm/Support/Error.h>
#include "llvm/Support/raw_ostream.h"

namespace tr {
template<const char *BenchFuncName, int InitSizeC, unsigned ExpectedResC>
class SumBenchmark : public BenchmarkBase {
public:
  SumBenchmark(FunctionStorage &Storage)
      : InitFunc(Storage.lookupFunc<int(int)>("init")),
        BenchFunc(Storage.lookupFunc<unsigned()>(BenchFuncName)),
        ShutdownFunc(Storage.lookupFunc<void()>("deinit")) {}

  bool init() override {
    return InitFunc(InitSize);
  }

  bool run() override {
    unsigned Res = BenchFunc();
    if (Res != ExpectedRes) {
      llvm::errs() << "Got unexpected result: expected "
            << llvm::format("%u", ExpectedRes) << ", got "
            << llvm::format("%u", Res) << "\n";
      return false;
    }
    return true;
  }

  void shutdown() override {
    ShutdownFunc();
  }

private:
  std::function<int(int)> InitFunc;
  std::function<unsigned()> BenchFunc;
  std::function<void()> ShutdownFunc;

  static constexpr int InitSize = InitSizeC;
  static constexpr unsigned ExpectedRes = ExpectedResC;
};
} // namespace tr

#endif // TESTRUNNER_BENCHMARKS_SUMBENCHMARK_H
