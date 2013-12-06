#include "PupilDetector.h"

PupilDetector::PupilDetector ( void ) {
    //count = 0;
}

PupilDetector::~PupilDetector ( void ) {
}

Pupil PupilDetector::detectPupil ( Mat eye ) {
    Mat eyeTemp; // matrices for internal calculations
    int cannyThreshold = 10;
    float cannyRatio = 3;
    Pupil pupil;

    //--- Preprocessing steps ---//
    eyeTemp = eye.clone();

    //imshow ( "eyeTemp", eyeTemp );
    //--- detecting the pupil ---//
    threshold ( eyeTemp, eyeTemp, 20, 255, CV_THRESH_BINARY ); // low value needed for pupil detection.

    Mat erodeElement = getStructuringElement ( MORPH_RECT, Size ( 3, 3 ), Point ( 1, 1 ) );
    Mat dilateElement = getStructuringElement ( MORPH_RECT, Size ( 3, 3 ), Point ( 2, 2 ) );
    erode ( eyeTemp, eyeTemp, erodeElement );

    vector<vector<Point>> contours;

    Canny ( eyeTemp.clone(), eyeTemp, cannyThreshold, cannyThreshold * cannyRatio, 3, true );
    findContours ( eyeTemp.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );

    cvtColor ( eyeTemp.clone(), eyeTemp, CV_GRAY2BGR );

    double area = 0, maxArea = 0;
    int maxAreaIndex = -1;
    float radiusTemp;
    Point2f centerTemp;
    for ( int i = 0; i < contours.size(); i++ ) {
        area = contourArea ( contours[i] );

        minEnclosingCircle ( contours[i], centerTemp, radiusTemp );
        if ( area > maxArea
                && centerTemp.y < eyeTemp.rows * 1.0
                && centerTemp.y > eyeTemp.rows * 0.0 ) {
            maxAreaIndex = i;
            maxArea = area;
        }
    }

    Point2f center;
    float radius = 0;

    if ( maxAreaIndex > -1 && contours[maxAreaIndex].size() > 0 ) {
        minEnclosingCircle ( contours[maxAreaIndex], center, radius );
        Circle c;
        c.setCenter ( center );
        c.setRadius ( radius );
        pupil.setPupilLocation ( c );

    }

    // temp code -- start
    //Rect borders = getExactEyeBorders ( eye );
    //cout << borders.x << " " << borders.y << " " << borders.width << " " << borders.height << endl;

    // temp code -- finish

    return pupil;
}

void PupilDetector::drawPupil ( Mat frame, Pupil pupil ) {
    Point2f center = pupil.getPupilLocation().getCenter();
    Point2f pNorth ( center.x, center.y - 2 );
    Point2f pSouth ( center.x, center.y + 2 );
    Point2f pEast ( center.x + 2, center.y );
    Point2f pWest ( center.x - 2, center.y );

    line ( frame, pNorth, pSouth, Scalar ( 255, 255, 0 ) );
    line ( frame, pWest, pEast, Scalar ( 255, 255, 0 ) );

}
Rect PupilDetector::getExactEyeBorders ( Mat eye ) {
    Mat tempEye = eye.clone();
    Rect border;

    equalizeHist ( tempEye, tempEye );
    GaussianBlur ( tempEye.clone(), tempEye, Size ( 5, 5 ), 5 );
    //threshold ( tempEye.clone(), tempEye, 100, 255, CV_THRESH_TOZERO );
    Mat out;
    Canny ( tempEye, out, 50, 200 );

    //imshow ( "Eye", out );

    return border;
}