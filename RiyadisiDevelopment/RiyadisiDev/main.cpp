#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2\photo\photo.hpp";
#include "opencv2\features2d\features2d.hpp";

#include <iostream>
#include <stdio.h>
#include <time.h>

#include "FaceFeatureManager.h"

const short int WAIT_PERIOD_PER_FRAME = 30;

using namespace std;
using namespace cv;

int main ( int argc, char **argv )
{
    CvCapture *capture;
    Mat frame, grayFrame;
    FaceFeatureManager featureManager;
    bool firstRun = true;

    capture = cvCaptureFromAVI ( "Testing/Videos/me_with_ir.wmv" );

    if ( capture ) {
        while ( true ) {
            frame = cvQueryFrame ( capture );

            int key = waitKey ( WAIT_PERIOD_PER_FRAME );// waiting for the key input. also determines operated frame rate.

            if ( key == 'c' ) {
                break;
            }

            cvtColor ( frame, grayFrame, CV_BGR2GRAY );
            equalizeHist ( grayFrame, grayFrame );

            time_t t = clock();

            FaceFeature *faceFeature = featureManager.getFeatureCollection()->getNext() ;

            if ( firstRun ) {
                Rect r ;
                r.x = 0;
                r.y = 0;
                r.width = grayFrame.cols;
                r.height = grayFrame.rows;

                featureManager.findFeatures ( grayFrame , faceFeature, r );

                firstRun = false;
            } else {
                FaceFeature *previous = featureManager.getFeatureCollection()->getFeature ( 1 );
                Rect r ;
                if ( previous->isAvailable() ) {
                    r = previous->getFeatureRect();
                    r.x = r.x - r.width / 2;
                    r.y = r.y - r.height / 2;
                    if ( r.x < 0 ) { r.x = 0; }
                    if ( r.y < 0 ) { r.y = 0; }

                    r.width = r.width * 2;
                    r.height = r.height * 2;
                    if ( r.width > grayFrame.cols ) {
                        r.width = grayFrame.cols - r.x;
                    }
                    if ( r.height > grayFrame.rows ) {
                        r.height = grayFrame.rows - r.y;
                    }
                } else {
                    r.x = 0;
                    r.y = 0;
                    r.width = grayFrame.cols;
                    r.height = grayFrame.rows;
                }
                featureManager.findFeatures ( grayFrame , faceFeature, r );
            }

            cout << "FullTime : " << ( clock() - t ) << endl;
            cout << "---------------------------------" << endl;

            Rect nose = faceFeature->getRelativeRect ( faceFeature->getNose()->getFeatureRect() );
            Rect leftEye = faceFeature->getRelativeRect ( faceFeature->getLeftEye()->getFeatureRect() );
            Rect rightEye = faceFeature->getRelativeRect ( faceFeature->getRightEye()->getFeatureRect() );

            rectangle ( frame, nose , Scalar ( 0, 255, 255 ) );
            rectangle ( frame, faceFeature->getFeatureRect(), Scalar ( 255, 0, 255 ) );
            rectangle ( frame, leftEye , Scalar ( 0, 255, 0 ) );
            rectangle ( frame, rightEye , Scalar ( 0, 255, 0 ) );

            imshow ( "image", frame );


        }
    }
}