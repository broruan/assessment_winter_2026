#include <cctype>
#include <iostream>
#include <string>
#include <sstream>

#include "rm_a0/a0_04_vowel_count.hpp"
namespace rm_a0{
std::size_t CountVowels(const std::string& line) {
    std::size_t count = 0;
    // TODO: 完成下面函数的实现
    for(int i=0;i<line.length();i++){
        if(a0_04_detail::IsVowelChar(line[i])) count++;
    }
    return count;
  }
std::string SolveVowelCount(const std::string& input, bool& ok) {
    std::istringstream in(input);
    std::string line;
    if (!std::getline(in, line)) {
        ok = false;
        return "";
    }
    ok = true;
    std::ostringstream out;
    out << CountVowels(line) << "\n";
    return out.str();
}


}
namespace a0_04_detail{
  bool IsVowelChar(unsigned char c) {
    // TODO: 完成下面函数的实现
    (void)c;
    int a=0;
    unsigned char vowe[11]={'a','e','i','o','u','A','E','I','O','U','b'};
    for(unsigned char *i=vowe;i!=&vowe[10];i++){
        if(*i==c){
          a=1;
          break;
        }
        else{
          a=0;
        }
    }
    return a?true:false;
  }
}

int main() {
  std::string line;
  if (!std::getline(std::cin, line)) {
    return 0;
  }

  std::cout << rm_a0::CountVowels(line) << "\n";

  return 0;
}
