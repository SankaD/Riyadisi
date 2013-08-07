#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

#include "EyeDetector.h"
#include "FaceDetector.h"

using namespace std;
using namespace cv;

int main ( int argc, char** argv )
{
    EyeDetector eyeDetector;
    FaceDetector faceDetector;

    CvCapture* capture;
    Mat frame, grayFrame, regionOfFrame;

    vector<Rect> results, eyeResults;

    capture = cvCaptureFromCAM ( 0 );

    if ( capture ) {
        while ( true ) {
            frame = cvQueryFrame ( capture );

            int key = waitKey ( 10 );

            if ( key == 'c' ) {
                break;
            }
            cvtColor ( frame, grayFrame, CV_BGR2GRAY );

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

            imshow ( "Window", frame );
        }
    }
}
