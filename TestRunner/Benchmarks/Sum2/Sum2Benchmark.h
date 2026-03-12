#ifndef TESTRUNNER_BENCHMARKS_SUM2BENCHMARK_H
#define TESTRUNNER_BENCHMARKS_SUM2BENCHMARK_H

#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/Error.h>

#include "../Sum/SumBenchmark.h"
#include "../BenchRunner.h"

namespace tr {
inline const char Sum2Name[] = "sum_2";
class Sum2Benchmark : public SumBenchmark<Sum2Name, 100000, 4294865760> {
public:
  template <typename LookupFuncTy>
  Sum2Benchmark(LookupFuncTy &&LookupFunc)
      : SumBenchmark(std::forward<LookupFuncTy>(LookupFunc)) {}
};
} // namespace tr

#endif // TESTRUNNER_BENCHMARKS_SUM2BENCHMARK_H
