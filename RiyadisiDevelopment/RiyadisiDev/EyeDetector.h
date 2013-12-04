#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "EyeGlassDetector.h"
#include "LeftEyeDetector.h"
#include "RightEyeDetector.h"
#include <fstream>

using namespace cv;
using namespace std;

class EyeDetector {
public:
    EyeDetector ( void );
    ~EyeDetector ( void );
    vector<Rect> detect ( Mat frame );
	void EyeDetector::updateMinSizes( Size roi );
private:
	EyeGlassDetector eyeGlassDetector;
	LeftEyeDetector leftEyeDetector;
	RightEyeDetector rightEyeDetector;
	Rect optimizeDetection ( vector<Rect> data );
	//ofstream dataFile;
};