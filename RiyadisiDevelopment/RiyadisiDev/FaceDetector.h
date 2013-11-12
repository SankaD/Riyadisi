#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

#include "FrontalFaceDetector.h"
#include "ProfileFaceDetector.h"

using namespace cv;
using namespace std;

class FaceDetector {
public:
    FaceDetector ( void );
    ~FaceDetector ( void );
    Rect detect ( Mat frame );
private:
	FrontalFaceDetector fontalFaceDetector;
	ProfileFaceDetector profileFaceDetector;
	vector<Rect> optimizeDetection ( vector<Rect> data );
};