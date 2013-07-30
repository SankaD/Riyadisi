#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "Neuron.h"

#include <iostream>
#include <stdio.h>


using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay ( Mat frame );

/** Global variables */
String face_cascade_name = "Resources/Cascades/HaarCascades/haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "Resources/Cascades/HaarCascades/haarcascade_eye_tree_eyeglasses.xml";
String mouth_cascade_name = "Resources/Cascades/HaarCascades/haarcascade_mcs_mouth.xml";

CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
CascadeClassifier mouth_cascade;

string window_name = "Capture - Face detection";
RNG rng ( 12345 );

/** @function main */
int main ( int argc, const char** argv )
{
    CvCapture* capture;
    Mat frame, dstFrame;

    //-- 1. Load the cascades
    if ( !face_cascade.load ( face_cascade_name ) ) {
        printf ( "--(!)Error loading\n" );
        return -1;
    };
    if ( !eyes_cascade.load ( eyes_cascade_name ) ) {
        printf ( "--(!)Error loading\n" );
        return -1;
    };
    if ( !mouth_cascade.load ( mouth_cascade_name ) ) {
        printf ( "--(!)Error loading\n" );
    }

    //-- 2. Read the video stream
    capture = cvCaptureFromCAM ( -1 );
    if ( capture ) {
        while ( true ) {
            frame = cvQueryFrame ( capture );

            //-- 3. Apply the classifier to the frame
            if ( !frame.empty() ) {
                detectAndDisplay ( frame );

            } else {
                printf ( " --(!) No captured frame -- Break!" );
                break;
            }

            int c = waitKey ( 30 );
            if ( ( char ) c == 'c' ) {
                break;
            }
        }
    }
    return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay ( Mat frame )
{
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor ( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist ( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale ( frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size ( 30, 30 ) );

    for ( int i = 0; i < faces.size(); i++ ) {
        Point center ( faces[i].x + faces[i].width * 0.5, faces[i].y + faces[i].height * 0.5 );
        //ellipse ( frame, center, Size ( faces[i].width * 0.5, faces[i].height * 0.5 ), 0, 0, 360, Scalar ( 255, 0, 255 ), 4, 8, 0 );
        rectangle ( frame, Point ( faces[i].x, faces[i].y ), Point ( faces[i].x + faces[i].width, faces[i].y + faces[i].height ),
                    Scalar ( 255, 255, 255 ), 1, 1, 0 );

        Mat faceROI = frame_gray ( faces[i] );

        std::vector<Rect> eyes;
        std::vector<Rect> mouth;

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale ( faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size ( 30, 30 ) );

        for ( int j = 0; j < eyes.size(); j++ ) {
            /* Point center ( faces[i].x + eyes[j].x + eyes[j].width * 0.5, faces[i].y + eyes[j].y + eyes[j].height * 0.5 );
             int radius = cvRound ( ( eyes[j].width + eyes[j].height ) * 0.25 );*/

            rectangle ( frame, Point ( faces[i].x + eyes[j].x , faces[i].y + eyes[j].y ),
                        Point ( faces[i].x + eyes[j].x + eyes[j].width , faces[i].y + eyes[j].y + eyes[j].height ), Scalar ( 255, 0, 0 ),
                        1, 1, 0 );
        }

        //-- In each face, detect mouth
        mouth_cascade.detectMultiScale ( faceROI, mouth, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size ( 30, 30 ) );

        for ( int j = 0; j < mouth.size(); j++ ) {
            rectangle ( frame, Point ( faces[i].x + mouth[j].x, faces[i].y + mouth[j].y ),
                        Point ( faces[i].x + mouth[j].x + mouth[j].width, faces[i].y + mouth[j].y + mouth[j].height ), Scalar ( 0, 255, 0 ),
                        1, 1, 0 );
        }
    }
    //-- Show what you got
    imshow ( window_name, frame );
    Neuron n = Neuron();
}