#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>

#include "rm_a0/a0_07_log_analyzer.hpp"
namespace rm_a0{
  LogStats AnalyzeLogFile(const std::string& path, bool& ok) {
    LogStats res;
    std::string line,word;
    long long I=0,W=0,E=0,sum=0;
    ok = true;
    std::ifstream file(path);
    if(!file.is_open()) {
        ok = false;
        return res;
    }
    try{
        while(getline(file,line)){
            std::stringstream l(line);
            while(l>>word){
                if(word=="INFO") {
                    I++;
                    continue;;
                }
                else if(word=="WARN") {
                    W++;
                    continue;;
                }

                else if(word=="ERROR") {
                    E++;
                    continue;
                }
                sum += std::stoll(word);
                if(std::stoll(word)>res.max_ms){
                    res.max_ms=std::stoll(word);
                    if(res.info!=I) res.max_level = "INFO";
                    else if(res.warn!=W) res.max_level = "WARN";
                    else if(res.error!=E) res.max_level = "ERROR";
                }
                res.info = I;
                res.warn = W;
                res.error = E;

            }

        }
        res.avg_ms = sum/(I+W+E);
    }catch(...){
        ok = false;
    }
    return res;
}
std::string SolveLogAnalyzer(const std::string& input, bool& ok) {
    std::istringstream in(input);
    std::string path;
    if (!std::getline(in, path)) {
        ok = false;
        return "FAIL\n";
    }
    if (path.empty()) {
        ok = false;
        return "FAIL\n";
    }

    bool file_ok = false;
    ok = true;
    try{
        LogStats s   = AnalyzeLogFile(path, file_ok);
        if (!file_ok) {
            ok = false;
            return "FAIL\n";
    }
        std::ostringstream out;
        out << "INFO=" << s.info << "\n";
        out << "WARN=" << s.warn << "\n";
        out << "ERROR=" << s.error << "\n";
        out << "avg=" << std::fixed << std::setprecision(2) << s.avg_ms << "\n";
        out << "max=" << s.max_level << " " << s.max_ms << "\n";
        return out.str();
    }catch(...){
        ok = false;
        return "FAIL\n";
    }

}
}

int main() {
  std::string path;
  if (!std::getline(std::cin, path)) {
    return 0;
  }

  bool ok = false;
  std::string out = rm_a0::SolveLogAnalyzer(path + "\n", ok);
  std::cout << out;

  return 0;
}
