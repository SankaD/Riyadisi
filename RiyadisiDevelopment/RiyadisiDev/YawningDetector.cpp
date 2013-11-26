#include "YawningDetector.h"
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

YawningDetector::YawningDetector ( void )
{
	//alpha = 0.8;
	prevH = 0;
	cSum = 0.0;
}


YawningDetector::~YawningDetector ( void )
{

}

float YawningDetector::detectYawning ( FaceFeature *faceFeature )
{
	/*Mat mouth = faceFeature->getImage()( faceFeature->getMouth()->getFeatureRect() );
	Mat binaryImage;
	string yawningStatus = "";

	threshold(mouth, binaryImage, 35, 255, CV_THRESH_BINARY);
	imshow("test", binaryImage);*/
	
	Rect mouth = faceFeature->getMouth()->getFeatureRect();
	float value = mouth.height - prevH;
	float yawningScore = value * 0.2 + cSum * 0.8;
	
	prevH = mouth.height;
	cSum = yawningScore;

	return yawningScore;
}
