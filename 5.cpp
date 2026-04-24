#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

string identifyShape(const vector<Point>& outline) {
    double outlineLength = arcLength(outline, true);

    vector<Point> simplified;
    approxPolyDP(outline, simplified, 0.02 * outlineLength, true);

    int cornerCount = simplified.size();

    Rect surroundingBox = boundingRect(outline);
    double sideRatio = (double)surroundingBox.width / surroundingBox.height;

    double shapeArea = contourArea(outline);
    double boxArea = surroundingBox.width * surroundingBox.height;
    double fullness = shapeArea / boxArea;

    if (cornerCount == 4) {
        if (sideRatio > 0.9 && sideRatio < 1.1 && fullness > 0.75)
            return "Square";
    }

    if (cornerCount == 3 || cornerCount == 4) {
        if (fullness < 0.6)
            return "Triangle";
    }

    if (cornerCount > 7) {
        double fullLength = arcLength(outline, true);
        double roundness = 4 * 3.1415 * shapeArea / (fullLength * fullLength);

        if (roundness > 0.85)
            return "Circle";
    }

    return "Unknown";
}

int main() {
    VideoCapture videoInput("C:\\Users\\danil\\Downloads\\video.mkv");

    double framesPerSec = videoInput.get(CAP_PROP_FPS);
    int frameWidth = videoInput.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = videoInput.get(CAP_PROP_FRAME_HEIGHT);

    VideoWriter videoOutput("output_video.avi",
        VideoWriter::fourcc('M', 'J', 'P', 'G'),
        framesPerSec,
        Size(frameWidth, frameHeight));

    if (!videoOutput.isOpened()) {
        cout << "Ошибка создания видео для записи\n";
        return -1;
    }

    Mat currentFrame, greyImage, edgesMap, contoursView;

    while (true) {
        videoInput >> currentFrame;
        if (currentFrame.empty()) break;

        cvtColor(currentFrame, greyImage, COLOR_BGR2GRAY);
        GaussianBlur(greyImage, greyImage, Size(5, 5), 0);
        Canny(greyImage, edgesMap, 30, 100);
        dilate(edgesMap, edgesMap, Mat(), Point(-1, -1), 2);

        vector<vector<Point>> detectedContours;
        findContours(edgesMap, detectedContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        contoursView = Mat::zeros(currentFrame.size(), CV_8UC3);
        drawContours(contoursView, detectedContours, -1, Scalar(0, 255, 255), 2);

        for (auto& eachContour : detectedContours) {
            double contourAreaValue = contourArea(eachContour);

            if (contourAreaValue < 500) continue;

            string shapeName = identifyShape(eachContour);
            if (shapeName == "Unknown") continue;

            Rect boundingRectangle = boundingRect(eachContour);
            rectangle(currentFrame, boundingRectangle, Scalar(0, 255, 0), 2);

            Point centralPoint(boundingRectangle.x + boundingRectangle.width / 2,
                boundingRectangle.y + boundingRectangle.height / 2);

            putText(currentFrame, shapeName,
                Point(centralPoint.x - 40, centralPoint.y),
                FONT_HERSHEY_SIMPLEX, 0.6,
                Scalar(0, 0, 255), 2);
        }

        videoOutput.write(currentFrame);

        imshow("Result", currentFrame);
        imshow("Contours after Canny", contoursView);

        if (waitKey(30) == 27) break;
    }

    videoInput.release();
    videoOutput.release();
    destroyAllWindows();

    return 0;
}