//#include "stdafx.h"

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2\objdetect\objdetect.hpp>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture capture;
    Mat frame;

    capture.open ( 0 );
    if ( capture.isOpened() ) {
        while ( true ) {
            capture >> frame;
            if ( !frame.empty() ) {
                imshow ( "Window", frame );
            } else {
                printf ( " --(!) No captured frame -- Break!" );
                break;
            }

            int c = waitKey ( 10 );
            if ( ( char ) c == 'c' ) {
                break;
            }
        }
    }
}