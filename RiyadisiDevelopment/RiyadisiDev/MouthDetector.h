#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

class MouthDetector {
public:
    MouthDetector();
    ~MouthDetector();
	Rect detect( Mat mouthROI );
	vector<vector<Point>> getContourMap( Mat image);
private:
	Rect minEnclosingRectangle( vector<Point> data );
	void drawTemplate ( vector<Mat> imageList );
	Mat mouthTemplate;
	int calculateThreshold( Mat image );
};