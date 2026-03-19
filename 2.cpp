#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace cv;
using namespace std;

int main() {
   setlocale(LC_ALL, "Rus");
   Mat canvas(600, 800, CV_8UC3, Scalar(0, 0, 0));
   int x = 20;
   while (true) {
       canvas.setTo(Scalar(0, 0, 0));
       line(canvas, Point(0, 0), Point(799, 599), Scalar(255, 0, 0), 3);
       rectangle(canvas, Point(100, 100), Point(300, 250), Scalar(0, 255, 0), 2);
       circle(canvas, Point(400, 300), 100, Scalar(0, 0, 255), -1);
       ellipse(canvas, Point(400, 300), Size(150, 70), 30, 0, 360, Scalar(0, 255, 255), 2);

       vector<Point> pts = { Point(500,100), Point(600,150), Point(650,250),
                            Point(550,300), Point(450,200) };
       polylines(canvas, pts, true, Scalar(255, 255, 0), 2);
       if (x == 600) {
           x -=580;
       }
       x += 3;
       putText(canvas, "Tolstov D.L. group 22PM",
           Point(x, 580),
           FONT_HERSHEY_SIMPLEX,
           1.0,
           Scalar(255, 255, 255),
           2);
       imshow("Move", canvas);
       if (waitKey(30) == 27) break;
   }
   return 0;
}