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
	//capture = cvCaptureFromCAM(1);

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
			Rect faceROI, leftEyeROI, rightEyeROI, mouthROI;

            if ( firstRun ) {
                //Rect r ;
                faceROI.x = 0;
                faceROI.y = 0;
                faceROI.width = grayFrame.cols;
                faceROI.height = grayFrame.rows;

                featureManager.findFeatures ( grayFrame , faceFeature, faceROI, leftEyeROI, rightEyeROI, mouthROI );

                firstRun = false;
            } else {
                FaceFeature *previous = featureManager.getFeatureCollection()->getFeature ( 1 );
                //Rect r ;
                if ( previous->isAvailable() ) {
                    faceROI = previous->getFeatureRect();
                    faceROI.x = faceROI.x - faceROI.width / 2;
                    faceROI.y = faceROI.y - faceROI.height / 2;
                    if ( faceROI.x < 0 ) { faceROI.x = 0; }
                    if ( faceROI.y < 0 ) { faceROI.y = 0; }

                    faceROI.width = faceROI.width * 2;
                    faceROI.height = faceROI.height * 2;
                    if ( faceROI.width > grayFrame.cols ) {
                        faceROI.width = grayFrame.cols - faceROI.x;
                    }
                    if ( faceROI.height > grayFrame.rows ) {
                        faceROI.height = grayFrame.rows - faceROI.y;
                    }


					if(previous->getLeftEye()->isAvailable()) {
						leftEyeROI = previous->getLeftEye()->getFeatureRect();
						leftEyeROI.x = leftEyeROI.x - leftEyeROI.width / 2;
						leftEyeROI.y = leftEyeROI.y - leftEyeROI.height / 2;
						if ( leftEyeROI.x < 0 ) { leftEyeROI.x = 0; }
						if ( leftEyeROI.y < 0 ) { leftEyeROI.y = 0; }

						leftEyeROI.width = leftEyeROI.width * 2;
						leftEyeROI.height = leftEyeROI.height * 2;
						if ( leftEyeROI.width > grayFrame.cols ) {
							leftEyeROI.width = grayFrame.cols;
						}
						if ( leftEyeROI.height > grayFrame.rows ) {
							leftEyeROI.height = grayFrame.rows;
						}
					} 
					
					if(previous->getRightEye()->isAvailable()) {
						rightEyeROI = previous->getRightEye()->getFeatureRect();
						rightEyeROI.x = rightEyeROI.x - rightEyeROI.width / 2;
						rightEyeROI.y = rightEyeROI.y - rightEyeROI.height / 2;
						if ( rightEyeROI.x < 0 ) { rightEyeROI.x = 0; }
						if ( rightEyeROI.y < 0 ) { rightEyeROI.y = 0; }

						rightEyeROI.width = rightEyeROI.width * 2;
						rightEyeROI.height = rightEyeROI.height * 2;
						if ( rightEyeROI.width > grayFrame.cols ) {
							rightEyeROI.width = grayFrame.cols;
						}
						if ( rightEyeROI.height > grayFrame.rows ) {
							rightEyeROI.height = grayFrame.rows;
						}
					} 
					
					if(previous->getMouth()->isAvailable()) {
						mouthROI = previous->getMouth()->getFeatureRect();
						mouthROI.x = mouthROI.x - mouthROI.width / 2;
						mouthROI.y = mouthROI.y - mouthROI.height / 2;
						if ( mouthROI.x < 0 ) { mouthROI.x = 0; }
						if ( mouthROI.y < 0 ) { mouthROI.y = 0; }

						mouthROI.width = mouthROI.width * 2;
						mouthROI.height = mouthROI.height * 2;
						if ( mouthROI.width > grayFrame.cols ) {
							mouthROI.width = grayFrame.cols;
						}
						if ( mouthROI.height > grayFrame.rows ) {
							mouthROI.height = grayFrame.rows;
						}
					} 
                } else {
                    faceROI.x = 0;
                    faceROI.y = 0;
                    faceROI.width = grayFrame.cols;
                    faceROI.height = grayFrame.rows;
	            }
                featureManager.findFeatures ( grayFrame , faceFeature, faceROI, leftEyeROI, rightEyeROI, mouthROI );
            }

            cout << "FullTime : " << ( clock() - t ) << endl;
            cout << "---------------------------------" << endl;

            Rect nose = faceFeature->getRelativeRect ( faceFeature->getNose()->getFeatureRect() );
            Rect leftEye = faceFeature->getRelativeRect ( faceFeature->getLeftEye()->getFeatureRect() );
            Rect rightEye = faceFeature->getRelativeRect ( faceFeature->getRightEye()->getFeatureRect() );
			Rect mouth = faceFeature->getRelativeRect ( faceFeature->getMouth()->getFeatureRect() );

            //rectangle ( frame, nose , Scalar ( 0, 255, 255 ) );
            rectangle ( frame, faceFeature->getFeatureRect(), Scalar ( 255, 0, 255 ) );
            rectangle ( frame, leftEye , Scalar ( 0, 255, 0 ) );
            rectangle ( frame, rightEye , Scalar ( 0, 255, 0 ) );
			rectangle ( frame, mouth , Scalar ( 0, 255, 255 ) );
			
            imshow ( "image", frame );


        }
    }
}