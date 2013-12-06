#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "FaceFeature.h"
#include "MouthDetector.h"
#include <iostream>

using namespace cv;
using namespace std;

class MouthHoleDetector {
public:
    MouthHoleDetector();
    ~MouthHoleDetector();
	Rect detect( FaceFeature* faceFeature );
	vector<vector<Point>> getContourMap( Mat image);
private:
	Rect minEnclosingRectangle( vector<Point> data );
	void applyMorphOperations ( Mat* image ) ;
	Mat mouthTemplate;
	int calculateThreshold( Mat image );
	void updateTemplate( Mat imageList );
	Mat erodeElement, dilateElement;
	int timer;
	MouthDetector mouthDetector;
};