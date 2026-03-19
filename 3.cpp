#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main() {
    Mat  img = cv::imread("C:\\Users\\danil\\Downloads\\image_png.png");
    Mat hsv;
    cvtColor(img, hsv, COLOR_BGR2HSV);

    Mat mask1, mask2, mask;

    inRange(hsv, Scalar(82, 100, 100), Scalar(160, 255, 255), mask2);

    imshow("Mask", mask2);
    waitKey(0);
    return 0;
}