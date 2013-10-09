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

void point ( Mat img, Point2f point, Scalar color );

int main ( int argc, char **argv )
{
    CvCapture *capture;
    Mat frame, grayFrame;
    FaceFeatureManager featureManager;
    bool firstRun = true;
    int frameCount = 0;

    // capture = cvCaptureFromAVI ( "Testing/Videos/me_with_ir.wmv" );
    capture = cvCaptureFromAVI ( "Testing/Videos/video 12.wmv" );

    if ( capture ) {
        while ( true ) {
            frame = cvQueryFrame ( capture );
            frameCount++;

            int key = waitKey ( WAIT_PERIOD_PER_FRAME );// waiting for the key input. also determines operated frame rate.

            if ( key == 'c' ) {
                break;
            }
            cout << "Frame count : " << frameCount << endl;

            cvtColor ( frame, grayFrame, CV_BGR2GRAY );
            equalizeHist ( grayFrame, grayFrame );

            time_t t = clock();

            FaceFeature *faceFeature = featureManager.getFeatureCollection()->getNext() ;

            faceFeature->clearFeature();

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

            Point2f leftPupil = faceFeature->getLeftEye()->getPupil()->getCenterPoint();
            Point2f rightPupil = faceFeature->getRightEye()->getPupil()->getCenterPoint();

            leftPupil = faceFeature->getLeftEye()->getRelativePoint ( leftPupil );
            rightPupil = faceFeature->getRightEye()->getRelativePoint ( rightPupil );

            leftPupil = faceFeature->getRelativePoint ( leftPupil );
            rightPupil = faceFeature->getRelativePoint ( rightPupil );

            //rectangle ( frame, nose , Scalar ( 0, 255, 255 ) );
            rectangle ( frame, faceFeature->getFeatureRect(), Scalar ( 255, 0, 255 ) );
            rectangle ( frame, leftEye , Scalar ( 0, 255, 0 ) );
            rectangle ( frame, rightEye , Scalar ( 0, 255, 0 ) );

            line ( frame, leftPupil, rightPupil, Scalar ( 255, 255, 255 ) );
            point ( frame, leftPupil, Scalar ( 255, 0, 0 ) );
            point ( frame, rightPupil, Scalar ( 255, 0, 0 ) );

            imshow ( "image", frame );
        }
    }
}
void point ( Mat img, Point2f point, Scalar color )
{
    line ( img, Point2f ( point.x + 10, point.y ), Point2f ( point.x - 10, point.y ), color );
    line ( img, Point2f ( point.x , point.y + 10 ), Point2f ( point.x, point.y - 10 ), color );
    circle ( img, point, 8, color );
}