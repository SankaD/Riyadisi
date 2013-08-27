#include "GazeDetector.h"
#include "Pupil.h"
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;
Circle detectPupil ( Mat eye );

GazeDetector::GazeDetector ( void )
{
}


GazeDetector::~GazeDetector ( void )
{
}

/**
    eyes should be provided as GRAY images
*/
//Gaze GazeDetector::detectGaze ( Mat rightEye, Mat leftEye )
//{
//    rightEye = rightEye.clone();
//    leftEye = leftEye.clone();
//
//    Circle rightPupil, leftPupil;
//
//    rightPupil = detectPupil ( rightEye );
//    leftPupil = detectPupil ( leftEye );
//
//    return
//}
/**
Detect the pupil of a given eye. Eye should be provided in GRAY profile.
*/
Circle detectPupil ( Mat eye )
{
    int cannyThreshold = 10;
    float cannyRatio = 3;
    int thresholdValue = 50;

    Mat eyeTemp;
    eye = eye.clone();

    threshold ( eye, eye, thresholdValue, 255, CV_THRESH_BINARY );

    equalizeHist ( eye, eye );

    Mat element = getStructuringElement ( MORPH_CROSS, Size ( 3, 3 ) );
    morphologyEx ( eye.clone(), eyeTemp, MORPH_ERODE, element, Point ( -1, -1 ), 1 );

    vector<vector<Point>> contours;

    Canny ( eyeTemp.clone(), eyeTemp, cannyThreshold, cannyThreshold * cannyRatio, 3, true );
    findContours ( eyeTemp.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );
    drawContours ( eyeTemp, contours, -1, Scalar ( 255, 255, 255 ), -1 );

    Point2f center;
    float radius;

    vector<Point> contourCollection;
    for ( int i = 0; i < contours.size(); i++ ) {
        for ( int j = 0; j < contours[i].size(); j++ ) {
            contourCollection.push_back ( contours[i][j] );
        }
    }

    if ( contourCollection.size() > 0 ) {
        minEnclosingCircle ( contourCollection, center, radius );

        if ( eyeTemp.rows > 2 * radius ) {
            circle ( eye, center, radius, Scalar ( 0, 0, 255 ), 1, 8, 0 );
            line ( eye, Point ( center.x - 2, center.y ), Point ( center.x + 2, center.y ), Scalar ( 0, 255, 0 ) );
            line ( eye, Point ( center.x , center.y - 2 ), Point ( center.x , center.y + 2 ), Scalar ( 0, 255, 0 ) );
        }
    }
    Circle circle;
    circle.x = center.x;
    circle.y = center.y;
    circle.radius = radius;

    return circle;
}
