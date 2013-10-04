#include "PupilDetector.h"

PupilDetector::PupilDetector ( void )
{
}
PupilDetector::~PupilDetector ( void )
{
}
Pupil PupilDetector::detectPupil ( Mat eye )
{
    Mat eyeTemp; // matrices for internal calculations
    int cannyThreshold = 10;
    float cannyRatio = 3;
    Pupil pupil;

    //--- Preprocessing steps ---//
    //cvtColor ( eye, eyeTemp, CV_BGR2GRAY );
    eyeTemp = eye.clone();

    //--- detecting the pupil ---//
    threshold ( eyeTemp, eyeTemp, 50, 225, CV_THRESH_BINARY ); // low value needed for pupil detection.

    equalizeHist ( eyeTemp, eyeTemp );

    vector<vector<Point>> contours;

    Canny ( eyeTemp.clone(), eyeTemp, cannyThreshold, cannyThreshold * cannyRatio, 3, true );
    findContours ( eyeTemp.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );
    //drawContours ( eyeTemp, contours, -1, Scalar ( 255, 255, 255 ), -1 );

    vector<vector<Point>> contours_poly ( contours.size() );
    vector<Rect> boundRect ( contours.size() );

    cvtColor ( eyeTemp.clone(), eyeTemp, CV_GRAY2BGR );

    vector<Point> contourCollection;
    for ( int i = 0; i < contours.size(); i++ ) {
        for ( int j = 0; j < contours[i].size(); j++ ) {
            contourCollection.push_back ( contours[i][j] );
        }
    }

    Point2f center;
    float radius;

    if ( contourCollection.size() > 0 ) {
        minEnclosingCircle ( contourCollection, center, radius );
        Circle c;
        c.setCenter ( center );
        c.setRadius ( radius );
    }
    return pupil;
}

void PupilDetector::drawPupil ( Mat frame, Pupil pupil )
{
    Point2f center = pupil.getPupilLocation().getCenter();
    Point2f pNorth ( center.x, center.y - 2 );
    Point2f pSouth ( center.x, center.y + 2 );
    Point2f pEast ( center.x + 2, center.y );
    Point2f pWest ( center.x - 2, center.y );

    line ( frame, pNorth, pSouth, Scalar ( 255, 255, 0 ) );
    line ( frame, pWest, pEast, Scalar ( 255, 255, 0 ) );

}