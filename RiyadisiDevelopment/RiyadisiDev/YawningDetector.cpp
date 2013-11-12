#include "YawningDetector.h"
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

YawningDetector::YawningDetector ( void )
{
	for ( int i = 0; i < ARRAY_LENGTH; i++ ) {
        mouthToFaceRatio[i] = 1;
    }
    currentIndex = ARRAY_LENGTH - 1;
}


YawningDetector::~YawningDetector ( void )
{
}

void YawningDetector::setInitialMouthHeight( float ratio ) {
	mouthToFaceRatio[currentIndex] = ratio;
	currentIndex--;
}

float YawningDetector::detectYawning ( FaceFeature *faceFeature )
{
	/*Mat mouth = faceFeature->getImage()( faceFeature->getMouth()->getFeatureRect() );
	Mat binaryImage;
	string yawningStatus = "";

	threshold(mouth, binaryImage, 35, 255, CV_THRESH_BINARY);
	imshow("test", binaryImage);*/
	float yawningScore = 0.0;
	Rect mouth = faceFeature->getMouth()->getFeatureRect();
	Rect face = faceFeature->getFeatureRect();
	float ratio = mouth.height;

	mouthToFaceRatio[currentIndex] = ratio;
	int curr, prev;
	for(int i=0; i < NO_OF_FRAMES; i++) {
		curr = (currentIndex + i) % ARRAY_LENGTH;
		prev = (currentIndex + i + 1) % ARRAY_LENGTH;
		yawningScore += ( mouthToFaceRatio[curr] - mouthToFaceRatio[prev] ) / mouthToFaceRatio[prev];
	}
	
	return yawningScore/NO_OF_FRAMES;
}
