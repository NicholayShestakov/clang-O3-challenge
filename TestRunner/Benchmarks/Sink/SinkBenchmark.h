#ifndef TESTRUNNER_BENCHMARKS_SINKBENCHMARK_H
#define TESTRUNNER_BENCHMARKS_SINKBENCHMARK_H

#include <cstdlib>
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/Error.h>

#include "../BenchRunner.h"

namespace tr {
class SinkBenchmark : public BenchmarkBase {
public:
  SinkBenchmark(FunctionStorage &Storage)
      : BenchFunc(Storage.lookupFunc<double(int *, unsigned)>("sink")) {
    generateInput(InputSize);
  }

  bool run() override;

private:
  std::vector<int> Input;
  double ExpectedResult;
  std::function<double(int *, unsigned)> BenchFunc;

  static constexpr unsigned InputSize = 10000;

  void generateInput(unsigned Size);
};
} // namespace tr

#endif // TESTRUNNER_BENCHMARKS_SINKBENCHMARK_H
