#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2\photo\photo.hpp";
#include "opencv2\features2d\features2d.hpp";

#include <iostream>
#include <stdio.h>

#include "EyeDetector.h"
#include "FaceDetector.h"
#include "GazeDetector.h"
#include "PupilDetector.h"

// define constants here
const short int WAIT_PERIOD_PER_FRAME = 30;

using namespace std;
using namespace cv;

void detectIris ( Mat eye, Mat frame );
void detectPupil ( Mat eye, Mat frame );

int main ( int argc, char **argv )
{
    // required detectors are here
    EyeDetector eyeDetector;
    FaceDetector faceDetector;
    GazeDetector gazeDetector;
    PupilDetector pupilDetector;

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

            int key = waitKey ( WAIT_PERIOD_PER_FRAME );// waiting for the key input. also determines operated frame rate.

            if ( key == 'c' ) {
                break;
            }

            cvtColor ( frame, grayFrame, CV_BGR2GRAY );
            equalizeHist ( grayFrame, grayFrame );

            // downsampling to increase performance
            Mat downsampledFrame;
            int downsamplingConstant = 2;

            pyrDown ( grayFrame, downsampledFrame, Size ( ( grayFrame.cols + 1 ) / downsamplingConstant, ( grayFrame.rows + 1 ) / downsamplingConstant ) );

            results =  faceDetector.detect ( downsampledFrame  );

            for ( int i = 0; i < results.size(); i++ ) {
                //multiplying to cope with the downsampling of the source image
                results[i].height = results[i].height * downsamplingConstant;
                results[i].width = results[i].width * downsamplingConstant;
                results[i].x = results[i].x * downsamplingConstant;
                results[i].y = results[i].y * downsamplingConstant;

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

                    Pupil leftPupil, rightPupil;

                    leftPupil = pupilDetector.detectPupil ( eyeLeft );
                    rightPupil = pupilDetector.detectPupil ( eyeRight );

                    //cout << leftPupil.getPupilLocation().getCenter() << endl;

                    pupilDetector.drawPupil ( frame, leftPupil );
                    pupilDetector.drawPupil ( frame, rightPupil );
                }
            }

            imshow ( "Window", regionOfFrame );
        }
    }
    return 0;
}