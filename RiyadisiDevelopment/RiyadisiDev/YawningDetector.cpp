#include "YawningDetector.h"
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

YawningDetector::YawningDetector ( void ) {
    //alpha = 0.8;
    prevH = 0;
    cSum = 0.0;
}


YawningDetector::~YawningDetector ( void ) {

}

float YawningDetector::detectYawning ( FaceFeature *faceFeature ) {
    Rect mouth = faceFeature->getMouth()->getFeatureRect();
	float value = 2 * mouth.height/ ( faceFeature->getRightEye()->getCenterPoint().x - faceFeature->getLeftEye()->getCenterPoint().x );
    float yawningScore = value * 0.2 + cSum * 0.8;

	if( yawningScore > 1.0 )
		yawningScore = 0.998;

    cSum = yawningScore;

    return yawningScore;
}
