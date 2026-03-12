#include "BenchRunner.h"
#include <chrono>
#include <numeric>

using namespace llvm;
using namespace tr;

std::optional<double> BenchRunner::run(unsigned NumIters, unsigned IterDuration) {
  using ClockTy = std::chrono::high_resolution_clock;
  auto TimeLimit = std::chrono::seconds(IterDuration);

  if (!Bench.init())
    return std::nullopt;

  std::vector<double> Scores;
  for (unsigned Iter = 0; Iter < NumIters; Iter++) {
    outs() << "Iteration #" << Iter + 1 << ": ";
    auto IterStart = ClockTy::now();
    unsigned NumTimesCalled = 0;
    while (true) {
      NumTimesCalled++;
      if (!Bench.run()) {
        Bench.shutdown();
        return std::nullopt;
      }
      if (ClockTy::now() - IterStart >= TimeLimit)
        break;
    }
    auto ElapsedTime = ClockTy::now() - IterStart;
    auto ElapsedTimeMS =
        std::chrono::duration_cast<std::chrono::milliseconds>(ElapsedTime)
            .count();
    auto Score = static_cast<double>(NumTimesCalled) * 1000 / ElapsedTimeMS;
    Scores.push_back(Score);
    outs() << format("%15.1lf", Score) << " ops/s\n";
  }
  Bench.shutdown();

  double Avg =
      std::accumulate(Scores.begin(), Scores.end(), 0.0) / Scores.size();
  return Avg;
}
