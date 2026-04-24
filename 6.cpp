#include <iostream>
#include <complex>
#include <opencv2/opencv.hpp>

int main() {

    cv::CascadeClassifier faceCascade;
    cv::CascadeClassifier eyeCascade;
    cv::CascadeClassifier smileCascade;

    if (!faceCascade.load("C:\\Users\\danil\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml")) {
        std::cerr << "Ошибка загрузки каскада лиц\n";
        return -1;
    }
    if (!eyeCascade.load("C:\\Users\\danil\\opencv\\sources\\data\\haarcascades\\haarcascade_eye.xml")) {
        std::cerr << "Ошибка загрузки каскада глаз\n";
        return -1;
    }
    if (!smileCascade.load("C:\\Users\\danil\\opencv\\sources\\data\\haarcascades\\haarcascade_smile.xml")) {
        std::cerr << "Ошибка загрузки каскада улыбок\n";
        return -1;
    }

    cv::Mat frame, gray;

    cv::VideoCapture cap("C:\\Users\\danil\\Downloads\\ZUA.mp4");

    while (cap.read(frame))
    {
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);

        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.1, 10, 0, cv::Size(60, 60));

        for (auto& face : faces) {

            cv::rectangle(frame, face, { 0, 255, 0 }, 2);


            cv::Mat faceROI_gray = gray(face);
            cv::Mat faceROI_color = frame(face);

            std::vector<cv::Rect> eyes;
            eyeCascade.detectMultiScale(faceROI_gray, eyes, 1.05, 8, 0, cv::Size(15, 15));

            for (auto& eye : eyes) {

                cv::rectangle(frame, cv::Rect(face.x + eye.x, face.y + eye.y, eye.width, eye.height), { 255, 0, 0 }, 2);
            }


            std::vector<cv::Rect> smiles;
            smileCascade.detectMultiScale(faceROI_gray, smiles, 1.1, 20, 0, cv::Size(30, 30));

            for (auto& smile : smiles) {

                cv::rectangle(frame, cv::Rect(face.x + smile.x, face.y + smile.y, smile.width, smile.height), { 0, 0, 255 }, 2);
            }
        }

        cv::imshow("Faces", frame);
        if (cv::waitKey(1) == 27) break;
    }

    return 0;
}