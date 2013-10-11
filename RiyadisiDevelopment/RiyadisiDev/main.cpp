#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2\photo\photo.hpp";
#include "opencv2\features2d\features2d.hpp";

#include <iostream>
#include <stdio.h>
#include <time.h>

#include "FaceFeatureManager.h"
#include "NoddingOffDetector.h"
#include "GazeDetector.h"

const short int WAIT_PERIOD_PER_FRAME = 30;

using namespace std;
using namespace cv;

void point ( Mat img, Point2f point, Scalar color );

int main ( int argc, char **argv )
{
    CvCapture *capture;
    Mat frame, grayFrame;
    FaceFeatureManager featureManager;
    NoddingOffDetector noddingOffDetector;
    GazeDetector gazeDetector;

    bool firstRun = true;
    int frameCount = 0;

    //capture = cvCaptureFromCAM ( 0 );
    //capture = cvCaptureFromAVI ( "Testing/Videos/me_with_ir.wmv" );
    capture = cvCaptureFromAVI ( "Testing/Videos/video 12.wmv" );
    //capture = cvCaptureFromAVI ( "Testing/Videos/Motion 1.wmv" );

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
            Rect faceROI, leftEyeROI, rightEyeROI, mouthROI;

            faceFeature->clearFeature();

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


                    if ( previous->getLeftEye()->isAvailable() ) {
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

                    if ( previous->getRightEye()->isAvailable() ) {
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

                    if ( previous->getMouth()->isAvailable() ) {
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

            bool isNoddingOff = noddingOffDetector.noddingOffDetect ( *faceFeature );
            if ( isNoddingOff ) {
                std::cout <<  "Driver is nodding off" << endl;
            }

            // gaze calculations
            gazeDetector.setCurrentGaze ( faceFeature->getGazeData() );
            float gazeScore = gazeDetector.getDistractionScore();

            // drawing image
            Point2f leftPupil = faceFeature->getLeftEye()->getPupil()->getCenterPoint();
            Point2f rightPupil = faceFeature->getRightEye()->getPupil()->getCenterPoint();

            leftPupil = faceFeature->getLeftEye()->getRelativePoint ( leftPupil );
            rightPupil = faceFeature->getRightEye()->getRelativePoint ( rightPupil );

            leftPupil = faceFeature->getRelativePoint ( leftPupil );
            rightPupil = faceFeature->getRelativePoint ( rightPupil );

            //rectangle ( frame, nose , Scalar ( 0, 255, 255 ) );
            if ( faceFeature->isAvailable() ) {
                rectangle ( frame, faceFeature->getFeatureRect(), Scalar ( 255, 0, 255 ) );
                rectangle ( frame, leftEye , Scalar ( 0, 255, 0 ) );
                rectangle ( frame, rightEye , Scalar ( 0, 255, 0 ) );

                rectangle ( frame, mouth , Scalar ( 0, 255, 255 ) );

                if ( faceFeature->getLeftEye()->getPupil()->isAvailable() ) {
                    point ( frame, leftPupil, Scalar ( 255, 0, 0 ) );
                }
                if ( faceFeature->getRightEye()->getPupil()->isAvailable() ) {
                    point ( frame, rightPupil, Scalar ( 255, 0, 0 ) );
                }
                if ( faceFeature->getLeftEye()->getPupil()->isAvailable()
                        && faceFeature->getRightEye()->getPupil()->isAvailable() ) {
                    line ( frame, leftPupil, rightPupil, Scalar ( 255, 255, 255 ) );
                }
            }
            CvFont font = fontQt ( "Times", -5, Scalar ( 255, 255, 0 ), 100 );

            ostringstream distractedText ;
            distractedText << "Distraction Level : " << gazeScore;
            string drowsinessText = "Drowsiness Level";
            string noddingText = "Nodding off : ";

            if ( isNoddingOff ) {
                noddingText += "True";
            } else {
                noddingText += "False";
            }

            addText ( frame, distractedText.str(), Point ( 10, 10 ), font );
            addText ( frame, drowsinessText, Point ( 10, 30 ), font );
            addText ( frame, noddingText, Point ( 10, 50 ), font );

            imshow ( "image", frame );
            /* while ( true && frameCount == 45 ) {
                 key = waitKey ( 30 );
                 if ( key == ' ' ) {
                     break;
                 }
             }*/
        }
    }
}
void point ( Mat img, Point2f point, Scalar color )
{
    line ( img, Point2f ( point.x + 10, point.y ), Point2f ( point.x - 10, point.y ), color );
    line ( img, Point2f ( point.x , point.y + 10 ), Point2f ( point.x, point.y - 10 ), color );
    circle ( img, point, 8, color );
}