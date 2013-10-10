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
    //equalizeHist ( eyeTemp, eyeTemp );
    //imshow ( "equalized image", eyeTemp );



    threshold ( eyeTemp, eyeTemp, 50, 255, CV_THRESH_BINARY ); // low value needed for pupil detection.
    //imshow ( "eye threshold", eyeTemp );

    Mat erodeElement = getStructuringElement ( MORPH_RECT, Size ( 3, 3 ), Point ( 1, 1 ) );
    Mat dilateElement = getStructuringElement ( MORPH_RECT, Size ( 3, 3 ), Point ( 2, 2 ) );
    //dilate ( eyeTemp, eyeTemp, dilateElement );
    erode ( eyeTemp, eyeTemp, erodeElement );
    //imshow ( "transformed image", eyeTemp );

    vector<vector<Point>> contours;

    Canny ( eyeTemp.clone(), eyeTemp, cannyThreshold, cannyThreshold * cannyRatio, 3, true );
    findContours ( eyeTemp.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );
    //drawContours ( eyeTemp, contours, -1, Scalar ( 255, 255, 255 ), -1 );

    /* vector<vector<Point>> contours_poly ( contours.size() );
     vector<Rect> boundRect ( contours.size() );*/

    cvtColor ( eyeTemp.clone(), eyeTemp, CV_GRAY2BGR );

    imshow ( "eye", eyeTemp );

    double area = 0, maxArea = 0;
    int maxAreaIndex = -1;
    float radiusTemp;
    Point2f centerTemp;
    for ( int i = 0; i < contours.size(); i++ ) {
        area = contourArea ( contours[i] );

        minEnclosingCircle ( contours[i], centerTemp, radiusTemp );
        if ( area > maxArea
                && centerTemp.y < eyeTemp.rows * 0.75
                && centerTemp.y > eyeTemp.rows * 0.25 ) {
            maxAreaIndex = i;
            maxArea = area;
        }
    }
    cout << "Max Area : " << maxArea << endl;

    //vector<Point> contourCollection;
    //for ( int i = 0; i < contours[maxAreaIndex].size(); i++ ) {
    //    contourCollection.push_back ( contours[maxAreaIndex][i] );
    //}
//for ( int i = 0; i < contours.size(); i++ ) {
//    for ( int j = 0; j < contours[i].size(); j++ ) {
//        // consider the points only in the middle of the eye.
//        if ( contours[i][j].y < eye.rows * 0.75 && contours[i][j].y > eye.rows * 0.25 ) {
//            contourCollection.push_back ( contours[i][j] );
//        }
//    }
//}

    Point2f center;
    float radius = 0;

    if ( maxAreaIndex > -1 && contours[maxAreaIndex].size() > 0 ) {
        minEnclosingCircle ( contours[maxAreaIndex], center, radius );
        Circle c;
        c.setCenter ( center );
        c.setRadius ( radius );
        pupil.setPupilLocation ( c );

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