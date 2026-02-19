#include "rm_a0/a0_lib.hpp"

#include "rm_a0/a0_01_temperature.hpp"
#include "rm_a0/a0_02_leap_year.hpp"
#include "rm_a0/a0_03_range_sum.hpp"
#include "rm_a0/a0_04_vowel_count.hpp"
#include "rm_a0/a0_05_score_stats.hpp"
#include "rm_a0/a0_06_bigint.hpp"
#include "rm_a0/a0_07_log_analyzer.hpp"
#include "rm_a0/a0_08_raii_handle.hpp"

#include <cctype>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

namespace rm_a0 {

// ==================== A0-01 Temperature ====================
// TODO: 完成下面函数的实现
double CelsiusToFahrenheit(double celsius) {
    double F = 0.0;
    F = celsius*9.0/5.0 + 32.0;
    return F;
}
// 这里是格式化输出的函数
std::string FormatFahrenheit(double fahrenheit) {
    std::ostringstream oss;
    oss<<std::fixed<<std::setprecision(2)<<fahrenheit;
    return oss.str();
}

std::string SolveTemperature(const std::string& input, bool& ok) {
    ok = false;
    std::string F_str="";
    std::ostringstream os;
    try{

           // 解析输入的温度值
      double celsius = std::stod(input); //转换为double类型
      double F=CelsiusToFahrenheit(celsius);
      ok = true;
      F_str = FormatFahrenheit(F);
      os<<F_str<<"\n";
      return os.str();
    }catch(const std::exception& e){
      ok = false;
      return "";
    }catch(...){
      ok = false;
      return "";
    }
  }


// ==================== A0-02 Leap Year ====================
// TODO: 完成下面函数的实现
bool IsLeapYear(int year) {
    if(year%400==0 || (year%4==0 && year%100!=0)) return true;
    else{
        return false;
    }
}
// TODO: 完成下面函数的实现,不要新增行数，只修改返回值
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

// ==================== A0-03 Range Sum ====================
// TODO: 完成下面函数的实现
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

// ==================== A0-04 Vowel Count ====================

namespace {
    namespace a0_04_detail {

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

    } // namespace a0_04_detail
} // namespace

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

// ==================== A0-05 Score Stats ====================

ScoreStatsResult ComputeScoreStats(const std::string& input, bool& ok) {
    ok = false;

    std::string input_cp=input;
    // TODO: 完成下面函数的实现
    std::replace(input_cp.begin(),input_cp.end(),'\n',' ');
    std::istringstream in(input_cp);

    std::string name,n_str,score_str;
    std::getline(in,n_str,' ');
    int n,score;
    ScoreStatsResult res;

    try{
        n=std::stoi(n_str);
        if(n==0) ok = false;
        else{
            struct students{
                std::string name;
                int score;
            };
            students stu[n];

        //写入数据
            for(int i=0;i<n;i++){
                std::getline(in,name,' ');
                stu[i].name = name;
                std::getline(in,score_str,' ');
                score = std::stoi(score_str);
                stu[i].score = score;

            }

        //计算平均分和最高分
            int f=0,index,max=0;
            for(int i=0;i<n;i++){
                f += stu[i].score;
                if(stu[i].score>max) {
                    max = stu[i].score;
                    index = i;
                }
            }
        
            res.avg=f/n;
            ok = true;
            
            res.top_name = stu[index].name;
            res.top_score = stu[index].score; 
        }


    }catch(...){
        ok = false;
    }



    
    return res;
}

std::string SolveScoreStats(const std::string& input, bool& ok) {
    auto res = ComputeScoreStats(input, ok);
    if (!ok) {
        return "";
    }

    std::ostringstream out;
    out << "top=" << res.top_name << " " << res.top_score << "\n";
    out << "avg=" << std::fixed << std::setprecision(2) << res.avg << "\n";
    return out.str();
}

// ==================== A0-06 BigInt ====================

// TODO: 参考hpp完成类实现
/*
at a0_06_bigint.hpp:
class BigInt {
public:
  BigInt();

  // Constructs from a non-negative decimal string.
  explicit BigInt(const std::string &s);

  friend BigInt operator+(const BigInt &a, const BigInt &b);
  friend std::ostream &operator<<(std::ostream &os, const BigInt &x);

private:
  // Little-endian digits, each 0..9.
  std::vector<int> digits_;
};
*/
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

// ==================== A0-07 Log Analyzer ====================
/*
at a0_07_log_analyzer.hpp:
struct LogStats {
  long long info = 0;
  long long warn = 0;
  long long error = 0;
  double avg_ms = 0.0;
  std::string max_level;
  long long max_ms = 0;
};
*/
LogStats AnalyzeLogFile(const std::string& path, bool& ok) {
    return {};
}

std::string SolveLogAnalyzer(const std::string& input, bool& ok) {
    std::istringstream in(input);
    std::string path;
    if (!std::getline(in, path)) {
        ok = false;
        return {};
    }
    if (path.empty()) {
        ok = false;
        return "FAIL\n";
    }

    bool file_ok = false;
    LogStats s   = AnalyzeLogFile(path, file_ok);
    if (!file_ok) {
        ok = false;
        return "FAIL\n";
    }

    ok = true;
    std::ostringstream out;
    out << "INFO=" << s.info << "\n";
    out << "WARN=" << s.warn << "\n";
    out << "ERROR=" << s.error << "\n";
    out << "avg=" << std::fixed << std::setprecision(2) << s.avg_ms << "\n";
    out << "max=" << s.max_level << " " << s.max_ms << "\n";
    return out.str();
}

// ==================== A0-08 RAII Handle ====================

// TODO: 参考hpp完成类实现
/*
at a0_08_raii_handle.hpp:
class FileHandle {
public:
  FileHandle() = default;
  FileHandle(const char *path, const char *mode);
  ~FileHandle();

  FileHandle(const FileHandle &) = delete;
  FileHandle &operator=(const FileHandle &) = delete;

  FileHandle(FileHandle &&other) noexcept;
  FileHandle &operator=(FileHandle &&other) noexcept;

  bool valid() const;
  FILE *get() const;

private:
  FILE *fp_ = nullptr;
};
*/

bool CopyFile(const std::string& in_path, const std::string& out_path) {

    return true;
}

std::string SolveRaiiCopy(const std::string& input, bool& ok) {
    std::istringstream in(input);
    std::string in_path;
    std::string out_path;
    if (!(in >> in_path >> out_path)) {
        ok = false;
        return {};
    }

    if (CopyFile(in_path, out_path)) {
        ok = true;
        return "OK\n";
    }

    ok = false;
    return "FAIL\n";
}

// ==================== A0-09 Text Pipeline====================

std::vector<std::string> RunTextPipeline(const std::string& pipeline, const std::vector<std::string>& lines, bool& ok) {
    (void)pipeline;
    (void)lines;
    ok = false;
    return {};
}

// ==================== A0-10 Rule Engine ====================

std::vector<long long> RunRuleEngine(
    const std::vector<std::string>& rule_specs,
    const std::vector<Event>& events,
    long long& total_any,
    bool& ok
) {
    (void)rule_specs;
    (void)events;
    total_any = 0;
    ok        = false;
    return {};
}

// ==================== A0-11 Command Dispatcher====================

std::string RunCommandDispatcher(const std::string& full_stdin, bool& ok) {
    (void)full_stdin;
    ok = false;
    return "FAIL\n";
}

} // namespace rm_a0
