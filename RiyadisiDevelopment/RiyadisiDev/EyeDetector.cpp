#include "EyeDetector.h"

vector<Rect> EyeDetector::detect ( FaceFeature* faceFeature ) {
    vector<Rect> eyes;
    Rect leftEyeROI, rightEyeROI, leftEye, rightEye;
	Mat faceImage = faceFeature->getImage();
	Orientation faceOrientation = faceFeature->getOrientation();
	
	try{
		//detect left eye
		switch( faceOrientation )
		{
		case FRONTAL:
				leftEyeROI.x = 0;
				leftEyeROI.y = faceImage.rows / 4;
				leftEyeROI.width = faceImage.cols / 2;
				leftEyeROI.height = faceImage.rows / 4;
				break;
		/*case LEFT_PROFILE:
				leftEyeROI.x = 0;
				leftEyeROI.y = 0;
				leftEyeROI.width = 0;
				leftEyeROI.height = 0;
				break;
		case RIGHT_PROFILE:
				leftEyeROI.x = faceImage.cols / 2;
				leftEyeROI.y = faceImage.rows / 4;
				leftEyeROI.width = faceImage.cols / 2;
				leftEyeROI.height = faceImage.rows / 4;
				break;*/
		default:
			leftEyeROI.x = 0;
			leftEyeROI.y = faceImage.rows / 4;
			leftEyeROI.width = faceImage.cols;
			leftEyeROI.height = faceImage.rows / 4;
		}
		//imshow("left_eye", faceImage( leftEyeROI ));
		updateMinSizes( Size(leftEyeROI.width, leftEyeROI.height) );

		leftEye = optimizeDetection ( eyeGlassDetector.detect ( faceImage ( leftEyeROI ) ) );
		if(leftEye.area() == 0)
		{
			leftEye = optimizeDetection( leftEyeDetector.detect ( faceImage( leftEyeROI ) ) );
		} 
	
		leftEye.x += leftEyeROI.x;
		leftEye.y += leftEyeROI.y;
		eyes.push_back ( leftEye );
		Log::log( "Left eye detected" );

		//detect right eye
		switch( faceOrientation )
		{
		case FRONTAL:
				rightEyeROI.x = faceImage.cols / 2;
				rightEyeROI.y = faceImage.rows / 4;
				rightEyeROI.width = faceImage.cols / 2;
				rightEyeROI.height = faceImage.rows / 4;
				break;
		/*case LEFT_PROFILE:
				rightEyeROI.x = 0;
				rightEyeROI.y = faceImage.rows / 4;
				rightEyeROI.width = faceImage.cols / 2;
				rightEyeROI.height = faceImage.rows / 4;
				break;
		case RIGHT_PROFILE:
				rightEyeROI.x = 0;
				rightEyeROI.y = 0;
				rightEyeROI.width = 0;
				rightEyeROI.height = 0;
				break;*/
		default:
			rightEyeROI.x = 0;
			rightEyeROI.y = faceImage.rows / 4;
			rightEyeROI.width = faceImage.cols;
			rightEyeROI.height = faceImage.rows / 4;
		}
		//imshow("right_eye", faceImage( rightEyeROI ));

		updateMinSizes( Size(rightEyeROI.width, rightEyeROI.height) );

		rightEye = optimizeDetection ( eyeGlassDetector.detect ( faceImage ( rightEyeROI ) ) );
		if(rightEye.area() == 0)
		{
			rightEye = optimizeDetection( rightEyeDetector.detect ( faceImage( rightEyeROI ) ) );
		}
	
		rightEye.x += rightEyeROI.x;
		rightEye.y += rightEyeROI.y;
		eyes.push_back( rightEye );
		/*if ( ! ( (leftEye.x + leftEye.width/2) < rightEye.x && (leftEye.x + leftEye.width/2) > (rightEye.x + rightEye.width) ) )
			eyes.push_back( rightEye );*/
		Log::log( "Right eye detected" );

	} catch ( exception ex ) {
        Log::log ( ex.what() );
    }
	return eyes;
}

Rect EyeDetector::optimizeDetection ( vector<Rect> data ) {

    Rect optimizedResult ( 0, 0, 0, 0 );

    if ( data.size() > 0 ) {
        optimizedResult = data[0];
    }

    return optimizedResult;
}

void EyeDetector::updateMinSizes( Size roi )
{

	Size newMinSizeSize(roi.width/8, roi.height/8 );

	eyeGlassDetector.setMinSize( newMinSizeSize );
	leftEyeDetector.setMinSize( newMinSizeSize );
	rightEyeDetector.setMinSize( newMinSizeSize );
}

EyeDetector::EyeDetector ( void ) 
{
	//dataFile.open ("Testing/Images/eye_testing/cum_sum.txt");
}

EyeDetector::~EyeDetector ( void ) 
{

}
