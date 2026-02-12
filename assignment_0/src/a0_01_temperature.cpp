#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>

#include "rm_a0/a0_01_temperature.hpp"
namespace rm_a0 {
  double CelsiusToFahrenheit(double celsius){
    double F = 0.0;
    F = celsius*9.0/5.0 + 32.0;
    return F;
  }
  std::string FormatFahrenheit(double fahrenheit){
    std::ostringstream oss;
    oss<<std::fixed<<std::setprecision(2)<<fahrenheit;
    return oss.str();
  }
  std::string SolveTemperature(const std::string& celsius_str,bool& ok){
    std::cout << "进入 SolveTemperature" << std::endl;
    ok = false;
    std::string F_str="";
    std::ostringstream os;
    try{
      double celsius = std::stod(celsius_str); //转换为double类型
      double F=CelsiusToFahrenheit(celsius);
      ok = true;
      F_str = FormatFahrenheit(F);
      os<<F_str<<"\n";
      return os.str();
    }catch(const std::exception& e){
      ok = false;
      std::cout <<"异常："<< e.what() <<ok<< std::endl;
      return "";
    }catch(...){
      ok = false;
      std::cout<<"有未知异常"<<ok<<std::endl;
      return "";
    }
  }
}
int main() {
  double celsius = 0.0;
  if (!(std::cin >> celsius)) {
    return 0;
  }
  std::cout << rm_a0::FormatFahrenheit(rm_a0::CelsiusToFahrenheit(celsius));
  return 0;
}
