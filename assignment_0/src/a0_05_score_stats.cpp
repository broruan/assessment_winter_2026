#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>

#include "rm_a0/a0_05_score_stats.hpp"


namespace rm_a0{
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

}
int main() {
  std::ostringstream oss;
  oss << std::cin.rdbuf();

  bool ok = false;
  std::string out = rm_a0::SolveScoreStats(oss.str(), ok);
  if (!ok) {
    return 0;
  }

  std::cout << out;

  return 0;
}
