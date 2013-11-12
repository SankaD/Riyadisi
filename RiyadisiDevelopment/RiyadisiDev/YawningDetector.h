#pragma once
#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "FaceFeature.h"

#define NO_OF_FRAMES 5
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
	void setInitialMouthHeight( int height );
private:
	int currentIndex;
	float mouthHeights[ARRAY_LENGTH];
};
