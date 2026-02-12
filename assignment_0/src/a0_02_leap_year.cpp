#include <iostream>
#include <sstream>

#include "rm_a0/a0_02_leap_year.hpp"
namespace rm_a0{
  bool IsLeapYear(int year) {
    if(year%400==0 || (year%4==0 && year%100!=0)) return true;
    else{
        return false;
    }
  }
  std::string FormatLeapYearAnswer(bool is_leap_year) {
    (void)is_leap_year;
    return is_leap_year?"YES\n":"NO\n";
  }
  std::string SolveLeapYear(const std::string& input, bool& ok) {
    std::istringstream in(input);
    int year = 0;
    if (!(in >> year)) {  //从in中读取year
        ok = false;
        return "";
    }

    ok = true;
    return FormatLeapYearAnswer(IsLeapYear(year));
  }

}

int main() {
  int year = 0;
  if (!(std::cin >> year)) {
    return 0;
  }

  std::cout << rm_a0::FormatLeapYearAnswer(rm_a0::IsLeapYear(year));

  return 0;
}
