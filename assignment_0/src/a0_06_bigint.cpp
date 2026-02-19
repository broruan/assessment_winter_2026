#include <iostream>
#include <sstream>

#include "rm_a0/a0_06_bigint.hpp"

namespace rm_a0{
BigInt operator+(const BigInt &a, const BigInt &b) {
    BigInt res("");
    auto len_a=a.digits_.size(),len_b=b.digits_.size();
    int sum=0;
    for(int i=0;i<std::max(len_a,len_b);i++){
        if(i<len_a) sum += a.digits_[i];
        if(i<len_b) sum += b.digits_[i];
        res.digits_.push_back(sum%10);
        sum /= 10;
    }
    if(sum>0) res.digits_.push_back(sum);
    return res;
    };
BigInt::BigInt(const std::string &s) {
    for(int i=s.length()-1;i>=0;i--){
        this->digits_.push_back(s[i]-'0');
    };
}
std::ostream &operator<<(std::ostream &os, const BigInt &x){
    if(x.digits_[x.digits_.size()-1]==0) {
        os<<'0';
        return os;
    }
    for(auto i=x.digits_.rbegin();i!=x.digits_.rend();++i){
        os<<*i;
    }
    return os;
}


std::string SolveBigIntAdd(const std::string& input, bool& ok) {
    std::istringstream in(input);
    std::string a;
    std::string b;
    std::ostringstream out;
    ok = true;
    if (!std::getline(in, a)) {
        ok = false;
        return "0";
    }
    if (!std::getline(in, b)) {
        ok = false;
        return "0";
    }

    try{
        BigInt big_a(a),big_b(b);
        BigInt res = big_a + big_b;
        ok = true;
        out<<res<<'\n';
    }catch(...){
        ok = false;
    }
    return out.str();
}
}

int main() {
  std::ostringstream oss;
  oss << std::cin.rdbuf();

  bool ok = false;
  std::string out = rm_a0::SolveBigIntAdd(oss.str(), ok);
  if (!ok) {
    return 0;
  }

  std::cout << out;
  return 0;
}
