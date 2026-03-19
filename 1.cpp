#include <opencv2/opencv.hpp>
#include <iostream>

#define ROTATE(img, angle) \
   cv::warpAffine(img, img, \
       cv::getRotationMatrix2D(cv::Point2f(img.cols/2, img.rows/2), angle, 1.0), \
       img.size())

int main() {
   cv::Mat original = cv::imread("C:\\Users\\danil\\Downloads\\Telegram Desktop\\cat2.jpg");

   if (original.empty()) {
       std::cout << "Ошибка!" << std::endl;
       return -1;
   }

   cv::imshow("0. Исходник", original);

   cv::Mat gray;
   cv::cvtColor(original, gray, cv::COLOR_BGR2GRAY);
   cv::imshow("1. Серое (из исходника)", gray);

   cv::Mat blurred;
   cv::GaussianBlur(original, blurred, cv::Size(15, 15), 0);
   cv::imshow("2. Расфокус (из исходника)", blurred);

   cv::Mat small;
   cv::resize(original, small, cv::Size(), 0.5, 0.5);
   cv::imshow("3. Уменьшенное (из исходника)", small);

   cv::Mat rotated = original.clone();
   ROTATE(rotated, 45);
   cv::imshow("4. Повернутое (из исходника)", rotated);
   
   cv::Mat lines;
   cv::Canny(original, lines, 50, 150);
   cv::imshow("5. Серые линии (из исходника)", lines);

   cv::waitKey(0);

   return 0;
}