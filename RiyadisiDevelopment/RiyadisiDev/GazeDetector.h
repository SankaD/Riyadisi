#pragma once
#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Gaze.h"
#include "Detector.h"

using namespace std;
using namespace cv;

class GazeDetector: public Detector {
public:
    GazeDetector ( void );
    ~GazeDetector ( void );
    vector<Rect> optimizeDetection ( vector<Rect> data );
    vector<Rect> detect ( Mat frame, Rect regionOfInterest );
    Gaze calculateGaze ( Mat frame, Rect regionOfInterest );
};
