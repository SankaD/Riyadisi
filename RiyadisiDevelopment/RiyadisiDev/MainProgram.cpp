#include "MainProgram.h"

using namespace std;
using namespace cv;

const short int MainProgram::WAIT_PERIOD_PER_FRAME = 30;

void MainProgram::run() {
    Log::log ( "Program started" );
    firstRun = true;
    frameCount = 0;

    long int ticks = 0, ticksForFrame = 0;

    while ( true ) {
        frame = imageManager.acquireImage ( frame );
        frameCount++;

        ticksForFrame =  getTickCount() - ticks;
        ticks = getTickCount();

        key = waitKey ( WAIT_PERIOD_PER_FRAME );

        // if the used press 'c', abort
        if ( key == 'c' ) {
            break;
        }

        processImage();

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

        double noddingOffLevel = 0.0;
        noddingOffLevel = noddingOffDetector.noddingOffDetect ( *faceFeature );
        //cout<<  "----------------------------------Nodding off level = "<< noddingOffLevel <<endl;

        gazeDetector.setCurrentGaze ( faceFeature->getGazeData() );
        gazeScore = gazeDetector.getDistractionScore();

        //   int frameNum = frameCount % 6;

        /*if ( frameNum == 0 ) {
            featureManager.perclos /= 30;
            percloseScore = featureManager.perclos;
            featureManager.perclos = 0;
        }*/
        percloseScore = featureManager.perclos;

        //calculate yawning frequency
        if ( faceFeature->getMouth()->isAvailable() ) {
            yawningScore = yawningDetector.detectYawning ( faceFeature );
        }

        //calculate head orientation
        if ( frameCount == 1 ) {
            headRotationDetector.setStartPoints ( Point ( leftEye.x + leftEye.width / 2, leftEye.y + leftEye.height / 2 ), Point ( rightEye.x + rightEye.width / 2, rightEye.y + rightEye.height / 2 ), Point ( nose.x + nose.width / 2, nose.y + nose.height / 2 ) );
        }
        if ( faceFeature->getLeftEye()->isAvailable() && faceFeature->getRightEye()->isAvailable() && faceFeature->getNose()->isAvailable() ) {
            headRotAngles =  headRotationDetector.calculateRotation ( faceFeature );
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
            rectangle ( frame, nose , Scalar ( 255, 255, 0 ) );

            if ( faceFeature->getLeftEye()->getPupil()->isAvailable() ) {
                point ( frame, leftPupil, Scalar ( 255, 0, 0 ) );
            }
            if ( faceFeature->getRightEye()->getPupil()->isAvailable() ) {
                point ( frame, rightPupil, Scalar ( 255, 0, 0 ) );
            }
            /*if ( faceFeature->getLeftEye()->getPupil()->isAvailable()
                    && faceFeature->getRightEye()->getPupil()->isAvailable() ) {
                line ( frame, leftPupil, rightPupil, Scalar ( 255, 255, 255 ) );
            }*/
        }
        bool alert =  decisionEngine.shouldAlert ( percloseScore, 0, gazeScore, 0, 0 );

        namedWindow ( "image", CV_WINDOW_AUTOSIZE );

        drawTexts ( frame, ticksForFrame );

        imshow ( "image", frame );
    }
    Log::log ( "Program ended" );
}
MainProgram::MainProgram() {
    isAlertOn = false;
    trainingMode = false;
    //imageManager = ImageManager ( ImageSourceType::File, "Testing/Videos/me_with_ir.wmv" );
    //imageManager = ImageManager ( ImageSourceType::File, "Testing/Videos/video 12.wmv" );
	imageManager = ImageManager ( ImageSourceType::Camera, "", 0);

    if ( !imageManager.isOpened() ) {
        throw exception ( "Program was unable to load the image source" );
    }

    gazeScore = 0;
    percloseScore = 0;
    noddingOffLevel = 0;
    yawningScore = 0;
    alertStatus = false;
}
void MainProgram::processImage() {
    // processing the image
    cvtColor ( frame, grayFrame, CV_BGR2GRAY );
    equalizeHist ( grayFrame, grayFrame );
}
void MainProgram::trainingRun() {
    Log::log ( "Training Started" );
    try {
        int key = 0;
        cout << "Should the model be created new ? y/n" << endl;

        key = waitKey ( 10000 );//doesn't work without a highgui component
        key = 'y';
        if ( key == 'y' || key == 'Y' ) {
            decisionEngine.trainEngine ( "data/trainingData.data" );
        } else {
            decisionEngine.trainEngine ();
        }
    } catch ( exception e ) {
        Log::log ( e.what() );
    }
    Log::log ( "Training ended" );
}
void MainProgram::drawTexts ( Mat &frame, long int ticksForFrame ) {
    CvFont fontYellow = fontQt ( "Times", -5, Scalar ( 255, 255, 0 ), 100 );
    CvFont fontRed = fontQt ( "Times", -5, Scalar ( 255, 0, 0 ), 100 );
    CvFont fontAlert = fontQt ( "Times", -2, Scalar ( 100, 100, 255 ), 100 );

    ostringstream distractedText ;
    ostringstream perclosText ;
    ostringstream frameTimeText;
    ostringstream noddingOffText;
    ostringstream yawningText;
    ostringstream headRotationText;

    frameTime = ( ticksForFrame / (  getTickFrequency() ) ) * 1000;

    distractedText		<< "Gaze Level        : " << gazeScore;
    perclosText			<< "perclos Level     : " << percloseScore;
    frameTimeText		<< "Frame Time        : " << frameTime;
    noddingOffText		<< "Nodding Off Rate  : " << noddingOffLevel;
    yawningText			<< "Yawning Rate	  : " << yawningScore;
    headRotationText	<< "Head Rotation	  : " << headRotAngles[0] << ", " << headRotAngles[1] << ", " << headRotAngles[2];

    string drowsinessText	= "Drowsiness Level : ";
    string alertText		= "Alert the driver  : ";

    if ( alertStatus ) {
        alertText += "Yes";
    } else {
        alertText += "No";
    }
    addText ( frame, distractedText.str(), Point ( 10, 10 ), fontYellow );
    addText ( frame, drowsinessText, Point ( 10, 30 ), fontYellow );
    addText ( frame, noddingOffText.str(), Point ( 10, 50 ), fontYellow );
    addText ( frame, perclosText.str(), Point ( 10, 70 ), fontYellow );
    addText ( frame, headRotationText.str(), Point ( 10, 90 ), fontYellow );
    addText ( frame, yawningText.str(), Point ( 10, 110 ), fontYellow );
    addText ( frame, frameTimeText.str(), Point ( frame.cols * 3 / 4 , 10 ), fontRed );
    addText ( frame, alertText, Point ( 10, 140 ), fontAlert );
}