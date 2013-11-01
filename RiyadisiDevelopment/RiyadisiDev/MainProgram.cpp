#include "MainProgram.h"

using namespace std;
using namespace cv;

const short int MainProgram::WAIT_PERIOD_PER_FRAME = 30;

void MainProgram::run()
{
    ImageManager imageManager ( ImageSourceType::File, "Testing/Videos/me_with_ir.wmv" );
    if ( !imageManager.isOpened() ) {
        throw exception ( "Program was unable to load the image source" );
    }

    Mat frame, grayFrame;
    long int frameCount=0;// for keeping the frame count
    int key;// for the key pressed by the user
    time_t time = clock();// used to keep the time in the system
    bool firstRun = true;

    FaceFeatureManager featureManager;
    NoddingOffDetector noddingOffDetector;
    GazeDetector gazeDetector;

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
        Rect nose = faceFeature->getRelativeRect ( faceFeature->getNose()->getFeatureRect() );
        Rect leftEye = faceFeature->getRelativeRect ( faceFeature->getLeftEye()->getFeatureRect() );
        Rect rightEye = faceFeature->getRelativeRect ( faceFeature->getRightEye()->getFeatureRect() );
        Rect mouth = faceFeature->getRelativeRect ( faceFeature->getMouth()->getFeatureRect() );

        bool isNoddingOff = noddingOffDetector.noddingOffDetect ( *faceFeature );
        if ( isNoddingOff ) {
            cout << "Driver is Nodding off" << endl;
        }

        gazeDetector.setCurrentGaze ( faceFeature->getGazeData() );
        float gazeScore = gazeDetector.getDistractionScore();

        int frameNum = frameCount % 30;
        double percloscore = 0;
        if ( frameNum == 0 ) {
            featureManager.perclos /= 30;
            percloscore = featureManager.perclos;
            featureManager.perclos = 0;
        }

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
        ostringstream perclosText ;
        distractedText << "Distraction Level : " << gazeScore;
        perclosText << "perclos Level : " << percloscore;
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
        addText ( frame, perclosText.str(), Point ( 10, 70 ), font );
        imshow ( "image", frame );
    }
}
MainProgram::MainProgram()
{
    isAlertOn = false;
}