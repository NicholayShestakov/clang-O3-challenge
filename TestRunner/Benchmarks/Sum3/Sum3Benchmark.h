#ifndef TESTRUNNER_BENCHMARKS_SUM3BENCHMARK_H
#define TESTRUNNER_BENCHMARKS_SUM3BENCHMARK_H

#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/Error.h>

#include "../Sum/SumBenchmark.h"
#include "../BenchRunner.h"

namespace tr {
inline const char Sum3Name[] = "sum_3";
class Sum3Benchmark : public SumBenchmark<Sum3Name, 100000, 4294865760> {
public:
  template <typename LookupFuncTy>
  Sum3Benchmark(LookupFuncTy &&LookupFunc)
      : SumBenchmark(std::forward<LookupFuncTy>(LookupFunc)) {}
};
} // namespace tr

#endif // TESTRUNNER_BENCHMARKS_SUM3BENCHMARK_H
