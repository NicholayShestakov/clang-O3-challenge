#include "SinkBenchmark.h"

#include <llvm/ADT/Sequence.h>

#include <math.h>
#include <random>

using namespace llvm;

static double expectedResult(const llvm::ArrayRef<int> Input) {
  double Res = 0;
  for (int i = 0; i < Input.size(); i++) {
    double PartialRes = sin(Input[i]) * cos(Input[i]);
    if (Input[i] < 0)
      Res += PartialRes;
    Res += Input[i];
  }
  return Res;
}

static bool DoubleEq(double X, double Y, double Eps = 1e-9) {
  return fabs(X - Y) < Eps;
}

namespace tr {
void SinkBenchmark::generateInput(unsigned Size) {
  static std::random_device RD;
  std::mt19937 Gen(RD());
  std::uniform_int_distribution<> Distr;

  Input.reserve(Size);
  for (auto I : llvm::seq(Size))
    Input.push_back(Distr(Gen));
  ExpectedResult = expectedResult(Input);
}

bool SinkBenchmark::run() {
  double Res = BenchFunc(Input.data(), Input.size());
  if (!DoubleEq(Res, ExpectedResult)) {
    errs() << "Got unexpected result: expected " << ExpectedResult << ", got "
           << Res << "\n";
    return false;
  }
  return true;
}
} // namespace tr
