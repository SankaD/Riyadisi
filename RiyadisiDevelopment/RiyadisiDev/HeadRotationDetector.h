#pragma once
#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "FaceFeature.h"

#define PI 3.1415926

using namespace std;
using namespace cv;

/*
    Usage: This class detects the head orientation when an image of the eyes and nose are given
*/
class HeadRotationDetector {
private:
	Point pl, pr, pn;
	Point fl, fr, fn;
	float radian( float angle );
public:
    HeadRotationDetector ( void );
    ~HeadRotationDetector ( void );
    vector<float> calculateRotation ( FaceFeature *faceFeature );
	void setStartPoints ( Point p1, Point p2, Point p3 );
};