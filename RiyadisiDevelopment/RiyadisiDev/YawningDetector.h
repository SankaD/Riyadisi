#pragma once
#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "FaceFeature.h"

#define ARRAY_LENGTH 6

using namespace std;
using namespace cv;

/*
    Usage: This class detects the gaze when an image of the eyes is given
*/
class YawningDetector {
public:
    YawningDetector ( void );
    ~YawningDetector ( void );
    float detectYawning ( FaceFeature *faceFeature );	
private:
	float cSum;
	int prevH;
	float alpha;
};
