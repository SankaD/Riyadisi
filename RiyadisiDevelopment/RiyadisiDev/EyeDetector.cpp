#include "EyeDetector.h"

vector<Rect> EyeDetector::detect ( Mat faceImage )
{
    vector<Rect> eyes;
	Rect leftEyeROI, rightEyeROI, leftEye, rightEye;

	//detect left eye
    leftEyeROI.x = 0;
    leftEyeROI.y = faceImage.rows / 4;
    leftEyeROI.width = faceImage.cols / 2;
    leftEyeROI.height = faceImage.rows / 4;

	leftEye = optimizeDetection( eyeGlassDetector.detect ( faceImage ( leftEyeROI ) ) );
	if(leftEye.area() == 0){
		leftEye = optimizeDetection( leftEyeDetector.detect ( faceImage ( leftEyeROI ) ) );
	} 
	leftEye.x += leftEyeROI.x;
    leftEye.y += leftEyeROI.y;
	eyes.push_back( leftEye );

	//detect right eye
    rightEyeROI.x = faceImage.cols / 2;
    rightEyeROI.y = faceImage.rows / 4;
    rightEyeROI.width = faceImage.cols / 2;
    rightEyeROI.height = faceImage.rows / 4;

	rightEye = optimizeDetection( eyeGlassDetector.detect ( faceImage ( rightEyeROI ) ) );

	if(rightEye.area() == 0){
		rightEye = optimizeDetection( rightEyeDetector.detect ( faceImage ( rightEyeROI ) ) );
	} 
	rightEye.x += rightEyeROI.x;
    rightEye.y += rightEyeROI.y;
	eyes.push_back( rightEye );
	
	return eyes;
}

Rect EyeDetector::optimizeDetection ( vector<Rect> data ) 
{
	if( data.size() > 0 )
		return data[0];
	else 
		return Rect(0, 0, 0, 0);
}

EyeDetector::EyeDetector ( void )
{

}

EyeDetector::~EyeDetector ( void )
{

}
