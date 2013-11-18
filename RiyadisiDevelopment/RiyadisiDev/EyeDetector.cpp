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
	
	leftEye = optimizeDetection( eyeGlassDetector.detect ( faceImage( leftEyeROI ) ), faceImage( leftEyeROI ) );
	if(leftEye.area() == 0){
		leftEye = optimizeDetection( leftEyeDetector.detect ( faceImage( leftEyeROI ) ), faceImage( leftEyeROI ) );
	} 
	leftEye.x += leftEyeROI.x;
    leftEye.y += leftEyeROI.y;
	eyes.push_back( leftEye );

	//detect right eye
    rightEyeROI.x = faceImage.cols / 2;
    rightEyeROI.y = faceImage.rows / 4;
    rightEyeROI.width = faceImage.cols / 2;
    rightEyeROI.height = faceImage.rows / 4;
	
	rightEye = optimizeDetection( eyeGlassDetector.detect ( faceImage( rightEyeROI ) ), faceImage( rightEyeROI ) );

	if(rightEye.area() == 0){
		rightEye = optimizeDetection( rightEyeDetector.detect ( faceImage( rightEyeROI ) ), faceImage( rightEyeROI ) );
	} 
	rightEye.x += rightEyeROI.x;
    rightEye.y += rightEyeROI.y;
	eyes.push_back( rightEye );

	
	return eyes;
}

Rect EyeDetector::optimizeDetection ( vector<Rect> data, Mat image ) 
{
	/*Mat erodeElement = getStructuringElement ( MORPH_RECT, Size ( 3, 3 ), Point ( 1, 1 ) );
	Mat dilateElement = getStructuringElement ( MORPH_RECT, Size ( 3, 3 ), Point ( 2, 2 ) );
	Mat eye;*/
	Rect optimizedResult(0, 0, 0, 0);
	
	//for(int i=0; i < data.size(); i++) {
	if(data.size() > 0) {
		/*eye = image(data[0]).clone();
		threshold(eye, eye, 30, 255, THRESH_BINARY );
		erode ( eye, eye, erodeElement );
		dilate( eye, eye, dilateElement );

		erode ( eye, eye, erodeElement );
		dilate( eye, eye, dilateElement );
		
		imshow ( "image_eye", eye );*/

		optimizedResult = data[0];
	}

	return optimizedResult;
}

EyeDetector::EyeDetector ( void )
{
	
	dataFile.open ("Testing/Images/eye_testing/cum_sum.txt");
}

EyeDetector::~EyeDetector ( void )
{

}
