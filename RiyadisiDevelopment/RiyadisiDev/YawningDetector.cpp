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
    float value = mouth.height - prevH;
    float yawningScore = value * 0.2 + cSum * 0.8;

    prevH = mouth.height;
    cSum = yawningScore;

    return yawningScore;
}
