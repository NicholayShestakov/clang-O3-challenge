#ifndef TESTRUNNER_BENCHMARKS_SUM1BENCHMARK_H
#define TESTRUNNER_BENCHMARKS_SUM1BENCHMARK_H

#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/Error.h>

#include "../Sum/SumBenchmark.h"
#include "../BenchRunner.h"

namespace tr {
inline const char Sum1Name[] = "sum_1";
class Sum1Benchmark : public SumBenchmark<Sum1Name, 100000, 4294865392> {
public:
  template <typename LookupFuncTy>
  Sum1Benchmark(LookupFuncTy &&LookupFunc)
      : SumBenchmark(std::forward<LookupFuncTy>(LookupFunc)) {}
};
} // namespace tr

#endif // TESTRUNNER_BENCHMARKS_SUM1BENCHMARK_H
