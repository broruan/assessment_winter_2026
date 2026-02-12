#include <iostream>
#include <sstream>

#include "rm_a0/a0_03_range_sum.hpp"

namespace rm_a0{
  long long RangeSum(long long l, long long r) {
    (void)l;
    (void)r;
    long long result;
    result = (l+r)*(r-l+1)/2;
    return result;
  }
  std::string SolveRangeSum(const std::string& input, bool& ok) {
    std::istringstream in(input);
    long long l = 0;
    long long r = 0;
    if (!(in >> l >> r)) {
        ok = false;
        return "";
    }
    ok = true;
    std::ostringstream out;
    out << RangeSum(l, r) << "\n";
    return out.str();
  }


}

int main() {
  long long l = 0;
  long long r = 0;
  if (!(std::cin >> l >> r)) {
    return 0;
  }

  std::cout << rm_a0::RangeSum(l, r) << "\n";

  return 0;
}
