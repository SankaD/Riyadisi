#pragma once
#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Gaze.h"

using namespace std;
using namespace cv;
/*
    Usage: This class detects the gaze when an image of the eyes is given
*/
class GazeDetector {
public:
    GazeDetector ( void );
    ~GazeDetector ( void );
    Gaze detectGaze ( Mat rightEye, Mat leftEye );
    Circle detectPupil ( Mat eye );
};
