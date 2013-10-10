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
    virtual ~Detector ( void );
    std::vector<Rect> detect ( Mat frame );
    CascadeClassifier getClassifier();
    void setCascadeFileName ( string filename );
    virtual vector<Rect> optimizeDetection ( vector<Rect> data ) = 0 ;
protected:
	float scale;
	Size minSize;
private:
    string cascadeName;
    CascadeClassifier cascade;
};