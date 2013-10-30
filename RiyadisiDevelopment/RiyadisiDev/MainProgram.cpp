#pragma once
//opencv includes
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>

//standard c++ includes
#include <iostream>
#include <time.h>

//project related includes
#include "FaceFeatureManager.h"
#include "NoddingOffDetector.h"
#include "GazeDetector.h"

using namespace std;
using namespace cv;

///<summary>
///Represents the image source type
///</summary>
enum ImageSourceType {
    Camera, File
};

const short int WAIT_PERIOD_PER_FRAME = 30;

///<summary>
///Retrieves images from a given video source
///</summary>
class ImageManager {
public:

    ImageManager ( ImageSourceType sourceType, string fileName = "", int cameraID = 0 );
    ~ImageManager();
    Mat &acquireImage ();
    Mat &acquireImage ( Mat &image );
    bool isOpened();
private:
    VideoCapture capture;
};

class MainProgram {
public:
    const static short int WAIT_PERIOD_PER_FRAME;
    void run();
private:
};

const short int MainProgram::WAIT_PERIOD_PER_FRAME = 30;

void MainProgram::run()
{
    ImageManager imageManager ( ImageSourceType::File, "" );
    if ( !imageManager.isOpened() ) {
        throw exception ( "Program was unable to load the image source" );
    }

    FaceFeatureManager featureManager;
    NoddingOffDetector noddingOffDetector;
    GazeDetector gazeDetector;

    Mat frame, grayFrame;
    long int frameCount;// for keeping the frame count
    int key;// for the key pressed by the user
    time_t time = clock();// used to keep the time in the system
    bool firstRun = true;

    while ( true ) {
        frame = imageManager.acquireImage ( frame );
        frameCount++;

        key = waitKey ( WAIT_PERIOD_PER_FRAME );

        // if the used press 'c', abort
        if ( key == 'c' ) {
            break;
        }

        // processing the image
        cvtColor ( frame, grayFrame, CV_BGR2GRAY );
        equalizeHist ( grayFrame, grayFrame );

        // Detection
        FaceFeature *faceFeature = featureManager.getFeatureCollection()->getNext();

        Rect faceRoi, leftEyeRoi, rightEyeRoi, mouthRoi;

        faceFeature->clearFeature();

        // initial run, needs to be managed seperately.
        if ( firstRun ) {
            // initial ROI is the whole image.
            faceRoi.x = 0;
            faceRoi.y = 0;
            faceRoi.width = grayFrame.cols;
            faceRoi.height = grayFrame.rows;

            featureManager.findFeatures ( grayFrame, faceFeature, faceRoi, leftEyeRoi, rightEyeRoi, mouthRoi );

            firstRun = false;
        } else {
            FaceFeature *previous = featureManager.getFeatureCollection()->getFeature ( 1 );

            // take a portion of the previous image using the previously detected face and other features.
            if ( previous->isAvailable() ) {
                faceRoi = previous->getFeatureRect();
                faceRoi.x = faceRoi.x - faceRoi.width / 2;
                faceRoi.y = faceRoi.y - faceRoi.height / 2;

                if ( faceRoi.x < 0 ) {
                    faceRoi.x = 0;
                }
                if ( faceRoi.y < 0 ) {
                    faceRoi.y = 0;
                }

                faceRoi.width = faceRoi.width * 2;
                faceRoi.height = faceRoi.height * 2;

                if ( faceRoi.width > grayFrame.cols ) {
                    faceRoi.width = grayFrame.cols - faceRoi.x;
                }
                if ( faceRoi.height > grayFrame.rows ) {
                    faceRoi.height = grayFrame.rows - faceRoi.y;
                }

                // handling the left eye region of interest
                if ( previous->getLeftEye()->isAvailable() ) {
                    leftEyeRoi = previous->getLeftEye()->getFeatureRect();
                    leftEyeRoi.x = leftEyeRoi.x - leftEyeRoi.width / 2;
                    leftEyeRoi.y = leftEyeRoi.y - leftEyeRoi.height / 2;
                    if ( leftEyeRoi.x < 0 ) { leftEyeRoi.x = 0; }
                    if ( leftEyeRoi.y < 0 ) { leftEyeRoi.y = 0; }

                    leftEyeRoi.width = leftEyeRoi.width * 2;
                    leftEyeRoi.height = leftEyeRoi.height * 2;
                    if ( leftEyeRoi.width > grayFrame.cols ) {
                        leftEyeRoi.width = grayFrame.cols;
                    }
                    if ( leftEyeRoi.height > grayFrame.rows ) {
                        leftEyeRoi.height = grayFrame.rows;
                    }
                }

                // handling the right eye ROI
                if ( previous->getRightEye()->isAvailable() ) {
                    rightEyeRoi = previous->getRightEye()->getFeatureRect();
                    rightEyeRoi.x = rightEyeRoi.x - rightEyeRoi.width / 2;
                    rightEyeRoi.y = rightEyeRoi.y - rightEyeRoi.height / 2;
                    if ( rightEyeRoi.x < 0 ) { rightEyeRoi.x = 0; }
                    if ( rightEyeRoi.y < 0 ) { rightEyeRoi.y = 0; }

                    rightEyeRoi.width = rightEyeRoi.width * 2;
                    rightEyeRoi.height = rightEyeRoi.height * 2;
                    if ( rightEyeRoi.width > grayFrame.cols ) {
                        rightEyeRoi.width = grayFrame.cols;
                    }
                    if ( rightEyeRoi.height > grayFrame.rows ) {
                        rightEyeRoi.height = grayFrame.rows;
                    }
                }

                // handling the mouth ROI
                if ( previous->getMouth()->isAvailable() ) {
                    mouthRoi = previous->getMouth()->getFeatureRect();
                    mouthRoi.x = mouthRoi.x - mouthRoi.width / 2;
                    mouthRoi.y = mouthRoi.y - mouthRoi.height / 2;
                    if ( mouthRoi.x < 0 ) { mouthRoi.x = 0; }
                    if ( mouthRoi.y < 0 ) { mouthRoi.y = 0; }

                    mouthRoi.width = mouthRoi.width * 2;
                    mouthRoi.height = mouthRoi.height * 2;
                    if ( mouthRoi.width > grayFrame.cols ) {
                        mouthRoi.width = grayFrame.cols;
                    }
                    if ( mouthRoi.height > grayFrame.rows ) {
                        mouthRoi.height = grayFrame.rows;
                    }
                }
            } else {
                // if there was no previous frame take the whole image as ROI
                faceRoi.x = 0;
                faceRoi.y = 0;
                faceRoi.width = grayFrame.cols;
                faceRoi.height = grayFrame.rows;
            }
            featureManager.findFeatures ( grayFrame, faceFeature, faceRoi, leftEyeRoi, rightEyeRoi, mouthRoi );
        }
    }
}
ImageManager::ImageManager ( ImageSourceType sourceType, string filename, int cameraID )
{
    if ( sourceType == ImageSourceType::File ) {
        capture = VideoCapture ( filename );
    } else {
        capture = VideoCapture ( cameraID );
    }
}
Mat &ImageManager::acquireImage()
{
    Mat image;
    return acquireImage ( image );
}
Mat &ImageManager::acquireImage ( Mat &image )
{
    capture >> image;
    return image;
}
bool ImageManager::isOpened()
{
    return capture.isOpened();
}
ImageManager::~ImageManager()
{
}