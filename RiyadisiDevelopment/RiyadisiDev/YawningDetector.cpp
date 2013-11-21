#include "YawningDetector.h"
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

YawningDetector::YawningDetector ( void )
{
	alpha[0] = 0.1;
	alpha[1] = 0.4;
	alpha[2] = 0.5;
	for ( int i = 0; i < ARRAY_LENGTH; i++ ) {
        mouthToFaceRatio[i] = 1;
    }
    currentIndex = 0;
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
	for(int i=0; i < 3; i++) {
		curr = (currentIndex + i) % ARRAY_LENGTH;
		prev = (currentIndex + i - 1) % ARRAY_LENGTH;
		if( prev < 0 )
			prev = 0;
		if( ( mouthToFaceRatio[curr] - mouthToFaceRatio[prev] ) > 0 )
			yawningScore += alpha[i] *( mouthToFaceRatio[curr] - mouthToFaceRatio[prev] );
		else 
			yawningScore += 0;
	}
	currentIndex++;
	if(currentIndex == ARRAY_LENGTH)
		currentIndex = 0;

	return yawningScore/3;
}
