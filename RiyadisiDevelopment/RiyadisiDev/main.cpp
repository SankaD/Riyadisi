#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2\photo\photo.hpp";
#include "opencv2\features2d\features2d.hpp";

#include <iostream>
#include <stdio.h>

#include "EyeDetector.h"
#include "FaceDetector.h"

using namespace std;
using namespace cv;

void detectIris ( Mat eye, Mat frame );
void detectPupil ( Mat eye, Mat frame );

int main ( int argc, char **argv )
{
    EyeDetector eyeDetector;
    FaceDetector faceDetector;

    CvCapture *capture;
    Mat frame, grayFrame, regionOfFrame;
    Mat eyeLeft, eyeRight, eyeTempLeft, eyeTempRight;

    vector<Rect> results, eyeResults;

    capture = cvCaptureFromAVI ( "G://temp/me_with_ir.wmv" );
    //capture = cvCaptureFromCAM ( -1 );

    int counter = 0;

    if ( capture ) {
        while ( true ) {
            frame = cvQueryFrame ( capture );

            int key = waitKey ( 30 );
            //cout << counter++ << "\n";

            if ( key == 'c' ) {
                break;
            }

            cvtColor ( frame, grayFrame, CV_BGR2GRAY );
            equalizeHist ( grayFrame, grayFrame );

            results =  faceDetector.detect ( grayFrame  );

            for ( int i = 0; i < results.size(); i++ ) {

                rectangle ( frame, Point ( results[i].x, results[i].y ),
                            Point ( results[i].x + results[i].width, results[i].y + results[i].height ),
                            Scalar ( 255, 255, 255 ), 1, 1, 0 );

                // Region of interest
                regionOfFrame = grayFrame ( Rect ( results[i].x, results[i].y, results[i].width, results[i].height ) );

                eyeResults = eyeDetector.detect ( regionOfFrame );

                for ( int j = 0; j < eyeResults.size(); j++ ) {
                    rectangle ( frame, Point ( results[i].x + eyeResults[j].x, results[i].y + eyeResults[j].y ),
                                Point ( results[i].x + eyeResults[j].x + eyeResults[j].width, results[i].y + eyeResults[j].y + eyeResults[j].height ),
                                Scalar ( 255, 255, 0 ), 1, 1, 0 );
                }
            }

            if ( results.size() > 0 ) {
                regionOfFrame = frame ( results[0] );
                Size s;
                Point p;
                regionOfFrame.locateROI ( s, p );
                //cout << p << "\n";

                if ( eyeResults.size() > 1 ) {
                    Point eyePoint1, eyePoint2;
                    regionOfFrame ( eyeResults[0] ).locateROI ( s, eyePoint1 );
                    regionOfFrame ( eyeResults[1] ).locateROI ( s, eyePoint2 );

                    if ( eyePoint1.x > eyePoint2.x ) {
                        eyeLeft = regionOfFrame ( eyeResults[0] );
                        eyeRight = regionOfFrame ( eyeResults[1] );
                    } else {
                        eyeLeft = regionOfFrame ( eyeResults[1] );
                        eyeRight = regionOfFrame ( eyeResults[0] );
                    }

                    detectPupil ( eyeLeft, frame );
                    detectPupil ( eyeRight, frame );
                }
            }

            imshow ( "Window", regionOfFrame );
        }
    }
    return 0;
}

// preprocess
Mat preprocessingEye ( Mat eye )
{
    Mat frame = eye.clone();
    Mat tempEye;
    Mat mask;

    //equalizeHist ( frame, frame );

    threshold ( frame, mask, 240, 255, CV_THRESH_TRUNC );
    inpaint ( frame.clone(), mask, tempEye, 4, INPAINT_NS );

    resize ( mask.clone(), mask, Size(), 6, 6, INTER_LINEAR );
    imshow ( "inmask", mask );

    resize ( tempEye, tempEye, Size(), 6, 6, INTER_LINEAR );
    imshow ( "testing3", tempEye );

    return eye;
}

// works with IR
void detectPupil ( Mat eye, Mat frame )
{
    //Mat testingMat, sharpenedImage;
    Mat eyeTemp;
    int cannyThreshold = 10;
    float cannyRatio = 3;

    // -----------------------------Preprocessing steps-----------------------
    // ----------removing glare from eye

    cvtColor ( eye, eyeTemp, CV_BGR2GRAY );

    //resize ( eyeTemp, testingMat, Size(), 6, 6, INTER_LINEAR );
    //imshow ( "testing1", testingMat );

    //equalizeHist ( testingMat, testingMat );

    //preprocessingEye ( eyeTemp );


    threshold ( eyeTemp, eyeTemp, 50, 225, CV_THRESH_BINARY );

    equalizeHist ( eyeTemp, eyeTemp );

    Mat element = getStructuringElement ( MORPH_CROSS, Size ( 3, 3 ) );
    //morphologyEx ( eyeTemp.clone(), eyeTemp, MORPH_DILATE, element, Point ( -1, -1 ), 1 );
    morphologyEx ( eyeTemp.clone(), eyeTemp, MORPH_ERODE, element, Point ( -1, -1 ), 1 );
    //resize ( eyeTemp, testingMat, Size(), 6, 6, INTER_LINEAR );
    //imshow ( "testing2", testingMat );

    // -----------------------------Detecting pupil---------------------------

    vector<vector<Point>> contours;

    Canny ( eyeTemp.clone(), eyeTemp, cannyThreshold, cannyThreshold * cannyRatio, 3, true );
    findContours ( eyeTemp.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );
    drawContours ( eyeTemp, contours, -1, Scalar ( 255, 255, 255 ), -1 );

    vector<vector<Point>> contours_poly ( contours.size() );
    vector<Rect> boundRect ( contours.size() );
    Point2f center ;
    float radius ;

    cvtColor ( eyeTemp.clone(), eyeTemp, CV_GRAY2BGR );

    vector<Point> contourCollection;
    for ( int i = 0; i < contours.size(); i++ ) {
        for ( int j = 0; j < contours[i].size(); j++ ) {
            contourCollection.push_back ( contours[i][j] );
        }
    }

    // drawing bounding circle for the identified closed contours.
    if ( contourCollection.size() > 0 ) {

        //approxPolyDP ( contours[i]  , contours_poly[i], arcLength ( contours[i], true ) * 1, true );
        //boundRect[i] = boundingRect ( contours_poly[i] );
        //minEnclosingCircle ( contours_poly[i], center[i], radius[i] );
        minEnclosingCircle ( contourCollection, center, radius );

        if ( eyeTemp.rows > 2 * radius ) {
            circle ( eye, center, radius, Scalar ( 0, 0, 255 ), 1, 8, 0 );
            line ( eye, Point ( center.x - 2, center.y ), Point ( center.x + 2, center.y ), Scalar ( 0, 255, 0 ) );
            line ( eye, Point ( center.x , center.y - 2 ), Point ( center.x , center.y + 2 ), Scalar ( 0, 255, 0 ) );
        }
    }

    // -----------------------------Postprocessing steps----------------------

    // checking the result
    //resize ( eyeTemp, eyeTemp, Size(), 6, 6, INTER_LINEAR );
    //imshow ( "eye preprocessing data", eyeTemp );

    //resize ( eye, eye, Size(), 6, 6, INTER_LINEAR );
    //imshow ( "eye pupil", eye );

}

// works with visible light
void detectIris ( Mat eye , Mat frame )
{
    Mat eyeTemp;

    // -----------------------------Preprocessing steps-----------------------
    // ----------removing glare from eye
    cvtColor ( eye.clone(), eyeTemp, CV_BGR2HSV );
    inRange ( eyeTemp, Scalar ( 0, 0, 0 ), Scalar ( 0, 0, 150 ), frame );
    cvtColor ( eyeTemp, eye, CV_HSV2BGR );

    // converting into required format
    cvtColor ( eye, eyeTemp, CV_BGR2GRAY );


    // -----------------------------Detecting iris---------------------------
    Canny ( eyeTemp, eyeTemp, 0, 30, 3, true );
    equalizeHist ( eyeTemp, eyeTemp );
    GaussianBlur ( eyeTemp, eyeTemp, Size ( 3, 3 ), 2, 2 );
    threshold ( eyeTemp, eyeTemp, 50, 225, CV_THRESH_TRUNC );
    equalizeHist ( eyeTemp, eyeTemp );

    vector<vector<Point>> contours;

    Canny ( eyeTemp.clone(), eyeTemp, 0, 30, 3, true );
    findContours ( eyeTemp.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE );


    vector<vector<Point>> contours_poly ( contours.size() );
    vector<Rect> boundRect ( contours.size() );
    vector<Point2f> center ( contours.size() );
    vector<float> radius ( contours.size() );

    // drawing bounding circle for the identified closed contours.
    for ( int i = 0; i < contours.size(); i++ ) {
        cout << "round : " << i << ", Contour Size : " << contours[i].size()
             << " arc length : " << arcLength ( contours[i], true ) << "\n";

        approxPolyDP ( contours[i]  , contours_poly[i], arcLength ( contours[i], true ) * 0.1, true );
        boundRect[i] = boundingRect (  contours_poly[i]  );
        minEnclosingCircle ( contours_poly[i], center[i], radius[i] );

        if ( eyeTemp.rows > 4 * radius[i] && eyeTemp.rows < 8 * radius[i]
                && center[i].y < eyeTemp.rows * ( 3.0 / 4 ) ) {

            circle ( eye, center[i], radius[i], Scalar ( 0, 0, 255 ), 1, 8, 0 );
            line ( eye, Point ( center[i].x - 2, center[i].y ), Point ( center[i].x + 2, center[i].y ), Scalar ( 0, 255, 0 ) );
            line ( eye, Point ( center[i].x , center[i].y - 2 ), Point ( center[i].x , center[i].y + 2 ), Scalar ( 0, 255, 0 ) );

            // only one iris per eye
            break;
        }
    }

    // -----------------------------Postprocessing steps----------------------

    // checking the result
    resize ( eye, eye, Size(), 6, 6, INTER_LINEAR );
    imshow ( "eye iris", eye );
}
void calculateGaze()
{
}