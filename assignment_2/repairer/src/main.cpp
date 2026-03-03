#include <opencv2/opencv.hpp>
#include <iostream>


int main() {
    cv::Mat src = cv::imread("./imgs/noisy.jpg");
    if (src.empty()) {
        std::cout << "无法读取图片" << std::endl;
        return -1;
    }

    cv::Mat dst1,dst2;

    //非局部均值滤波

    // 第三个参数 h: 10 (值越大去噪越狠，但越像油画)
    // 第四个参数 hColor: 10 (针对彩色噪声的强度，通常与 h 相同)
    // 第五个参数 templateWindowSize: 7 (建议值)
    // 第六个参数 searchWindowSize: 21 (建议值，更大的窗口会更慢，但对大面积噪声有帮助)

    cv::fastNlMeansDenoisingColored(src, dst1, 6, 6, 7, 21);


    //中值滤波
    cv::medianBlur(src,dst2,3);


    cv::imshow("原图", src);
    cv::imshow("非局部均值降噪", dst1);
    cv::imshow("中值降噪", dst2);

    cv::imwrite("./imgs/result1.png", dst1);
    cv::imwrite("./imgs/result2.png", dst2);

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}