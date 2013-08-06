#pragma once
#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

class Detector {
public:
    Detector ( void );
    Detector ( string cascadeName );
    ~Detector ( void );
    std::vector<Rect> detect ( Mat frame, Rect regionOfInterest );
    CascadeClassifier getClassifier();
    void setCascadeFileName ( string filename );
private:
    string cascadeName;
    CascadeClassifier cascade;
};