#ifndef DETECTOR_HPP
#define DETECTOR_HPP

#include <iostream>
#include <string>
namespace de{
    class SolveProblem {
        public:
            SolveProblem(const std::string& path) : path_(path){
            };
            ~SolveProblem(){
            }
            cv::Mat solvepnp(cv::Mat& img);
            cv::Mat drawCircle();

        private:
            std::string path_;
            std::vector<cv::Point2f> points;
            float radius;

    };

    //相机内参矩阵
    cv::Mat cameraMatrix = (cv::Mat_<double> (3,3) << 1284.547433507284, 0.0, 651.7508235222139, 0.0, 1284.2364120767988, 526.5637803861928, 0.0, 0.0, 1.0);
    //相机畸变系数
    cv::Mat distCoeffs = (cv::Mat_<double> (5,1) << -0.37358321087789575, 0.17992488578084675, -0.0003940895801771612, -0.0007097534681170694, 0.0);
}




#endif