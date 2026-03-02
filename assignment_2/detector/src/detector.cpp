#include <iostream>
#include <opencv2/opencv.hpp>
#include "detector.hpp"
#include <vector>
#include <cmath>

namespace de{
    cv::Mat SolveProblem::solvepnp(cv::Mat& img ) {
         //3D世界坐标点，小弹丸尺寸 ：16.8mm±0.2mm
        std::vector<cv::Point3f> objects;
        objects.push_back(cv::Point3f(0,0,0));//中心
        objects.push_back(cv::Point3f(0,-0.0084,0));//上方
        objects.push_back(cv::Point3f(0.0084,0,0));//右方
        objects.push_back(cv::Point3f(0,0.0084,0));//下方
        //2D图像坐标点
        cv::Mat revc,tevc,R;
        // cv::Mat ob=(cv::Mat_<double> (3,1) << 0,0,0);


        for(size_t i=0;i<this->points.size();i++){
            std::vector<cv::Point2f> image;
            image.push_back(this->points[i]);
            image.push_back(cv::Point2f(this->points[i].x,this->points[i].y - this->radius));
            image.push_back(cv::Point2f(this->points[i].x + this->radius,this->points[i].y));
            image.push_back(cv::Point2f(this->points[i].x,this->points[i].y + this->radius));
            cv::solvePnP(objects,image,cameraMatrix,distCoeffs,revc,tevc,false,cv::SOLVEPNP_AP3P);
            // cv::Rodrigues(revc,R);
            double distance = std::sqrt(tevc.at<double>(0)*tevc.at<double>(0) + tevc.at<double>(1)*tevc.at<double>(1) + tevc.at<double>(2)*tevc.at<double>(2));
            cv::putText(img,std::to_string(distance)+" m",cv::Point2f(image[1].x-10,image[1].y-10),cv::FONT_ITALIC,0.8,cv::Scalar(0,0,255),2);
        }
        return img;
    }
    cv::Mat SolveProblem::drawCircle(){
        cv::Mat img = cv::imread(this->path_);

        //通道分离
        std::vector<cv::Mat> channel;
        cv::split(img,channel);
        cv::Mat g=channel[1],b=channel[0],
                img_spl=g-b,
                dst,close,gray,hist,thresh,gauss;
        std::vector<cv::Vec3f> circles;


        //  //使用grabcut背景分离
        cv::Rect rect = cv::selectROI("选择目标",img,false,false);
        cv::Mat roi = img_spl(rect);//深拷贝用.clone()
        // cv::Mat result,mask,bgModel,fgModel;
        // cv::grabCut(img,mask,rect,bgModel,fgModel,10,cv::GC_INIT_WITH_RECT);
        // result = (mask==cv::GC_FGD) | (mask==cv::GC_PR_FGD);

        //去噪
        cv::GaussianBlur(roi,gauss,cv::Size(3,3),0,0);//没什么用

        // //直方图均衡
        // cv::cvtColor(img_spl,gray,cv::COLOR_BGR2GRAY);
        cv::equalizeHist(img_spl,hist);//噪点更多了

        //二值化
        cv::threshold(gauss,thresh,15,255,cv::THRESH_BINARY);
        // //膨胀
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3));
        cv::morphologyEx(thresh,close,cv::MORPH_DILATE,kernel);
        //canny检测
        cv::Canny(thresh,dst,75,150);//预验证Hough圆变换的Canny
        //霍夫圆变换
        cv::HoughCircles(close,circles,cv::HOUGH_GRADIENT,1,50,150,10,25,70);
        std::cout<<circles.size()<<std::endl;
        for(std::size_t i=0;i<circles.size();i++){
            cv::Point center(circles[i][0]+rect.x,circles[i][1]+rect.y);
            this->radius = circles[i][2];
            this->points.push_back(cv::Point2f(circles[i][0]+rect.x,circles[i][1]+rect.y));
            cv::circle(img,center,circles[i][2],cv::Scalar(0,255,0),5);
            cv::circle(img,center,1,cv::Scalar(0,0,255),2,-1);


        }
        return img;
    }

}

int main(int argc,char** argv){
    
    de::SolveProblem solve1("./imgs/test1.jpg"),solve2("./imgs/test2.jpg");
    cv::Mat test1 = solve1.drawCircle(),t1;
    cv::Mat test2 = solve2.drawCircle(),t2;
    t1 = solve1.solvepnp(test1);
    t2 = solve2.solvepnp(test2);
    // cv::imshow("高斯",gauss);
    // cv::imshow("直方图均衡化",hist);
    // cv::imshow("grabcut结果图",result);
    cv::imwrite("./imgs/result1.jpg",t1);
    cv::imwrite("./imgs/result2.jpg",t2);
    // cv::imshow("二值化",thresh);
    // cv::imshow("通道分离",img_spl);
    // cv::imshow("Canny检测",dst);
    // cv::imshow("膨胀",close);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;


}