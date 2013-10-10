#include "GazeDetector.h"
#include "Circle.h"
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

GazeDetector::GazeDetector ( void )
{
}


GazeDetector::~GazeDetector ( void )
{
}

/**
    eyes should be provided as GRAY images
*/
Gaze GazeDetector::detectGaze ( FaceFeature faceFeature )
{
    Gaze gaze;

    Rect leftEyeRect = faceFeature.getLeftEye()->getFeatureRect();
    Rect rightEyeRect = faceFeature.getRightEye()->getFeatureRect();
    Point2f leftPupil =  faceFeature.getLeftEye()->getPupil()->getCenterPoint();
    Point2f rightPupil = faceFeature.getRightEye()->getPupil()->getCenterPoint();



    return gaze;
}