#include "TrainingFileCreator.h"


TrainingFileCreator::TrainingFileCreator ( void ) {

}


TrainingFileCreator::~TrainingFileCreator ( void ) {
}

void TrainingFileCreator::trainUsingFile ( string fileName ) {
    try {
        int fileCount = 0;
        ifstream listFileStream ( fileName );

        if ( listFileStream.is_open() ) {
            // get the file count from the top of the file
            listFileStream >> fileCount;

            string videoFileName = "";
            //train using the video files list known from the provided file
            for ( int i = 0; i < fileCount; i++ ) {

                listFileStream >> videoFileName;
                try {
                    Log::log ( "Using file : " + videoFileName );
                    trainUsingVideo ( videoFileName, i + ".data" );
                } catch ( exception ex ) {
                    Log::log ( ex.what()  );
                }
            }
            listFileStream.close();
        } else {
            Log::log ( "File was not opened" );
        }
    } catch ( exception ex ) {
        Log::log (  ex.what()  );
    }
}

void TrainingFileCreator::trainUsingVideo ( string inputFileName, string outputFileName ) {
    imageManager = ImageManager ( ImageSourceType::File, inputFileName );
    int key = 0;
    bool firstRun = true;
    Mat frame, grayFrame;
    long int ticks = 0, ticksForFrame = 0;

    namedWindow ( "image", CV_WINDOW_AUTOSIZE );

    ofstream outputFile ( outputFileName );
    if ( !outputFile.is_open() ) {
        throw new exception ( "Output file couldn't be opened" );
    }

    while ( ! imageManager.isVideoEnded() ) {
        frame = imageManager.acquireImage ( frame );

        ticksForFrame =  getTickCount() - ticks;
        ticks = getTickCount();

        key = waitKey ( 30 );

        // if the used press 'c', abort
        if ( key == 'c' ) {
            break;
        } else if ( key == ' ' ) {
            alertStatus = !alertStatus;
        }

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

        gazeDetector.setCurrentGaze ( faceFeature->getGazeData() );
        gazeScore = gazeDetector.getDistractionScore();

        percloseScore = featureManager.perclos;

        //calculate yawning frequency
        if ( faceFeature->getMouth()->isAvailable() ) {
            yawningScore = yawningDetector.detectYawning ( faceFeature );
        }

        //calculate head orientation
        if ( imageManager.getFrameNumber() == 1 ) {
            headRotationDetector.setStartPoints ( Point ( leftEye.x + leftEye.width / 2, leftEye.y + leftEye.height / 2 ), Point ( rightEye.x + rightEye.width / 2, rightEye.y + rightEye.height / 2 ), Point ( nose.x + nose.width / 2, nose.y + nose.height / 2 ) );
        }
        if ( faceFeature->getLeftEye()->isAvailable() && faceFeature->getRightEye()->isAvailable() && faceFeature->getNose()->isAvailable() ) {
            headRotAngles =  headRotationDetector.calculateRotation ( faceFeature );
        }

        // drawing image
        /* Point2f leftPupil = faceFeature->getLeftEye()->getPupil()->getCenterPoint();
         Point2f rightPupil = faceFeature->getRightEye()->getPupil()->getCenterPoint();

         leftPupil = faceFeature->getLeftEye()->getRelativePoint ( leftPupil );
         rightPupil = faceFeature->getRightEye()->getRelativePoint ( rightPupil );

         leftPupil = faceFeature->getRelativePoint ( leftPupil );
         rightPupil = faceFeature->getRelativePoint ( rightPupil );

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
         }*/

        outputFile << percloseScore << " "
                   << noddingOffLevel << " "
                   << gazeScore << " "
                   << yawningScore << " "
                   << headRotAngles[0] << " "
                   << headRotAngles[1] << " "
                   << headRotAngles[2] << " "
                   << ( alertStatus  ? 1 : 0 )
                   << endl;

        drawTexts ( frame, ticksForFrame );

        cv::imshow ( "image", frame );
    }
    outputFile.close();
}
void TrainingFileCreator::drawTexts ( Mat &frame, long int ticksForFrame ) {
    CvFont fontYellow = fontQt ( "Times", -5, Scalar ( 255, 255, 0 ), 100 );
    CvFont fontRed = fontQt ( "Times", -5, Scalar ( 255, 0, 0 ), 100 );
    CvFont fontAlert = fontQt ( "Times", -2, Scalar ( 100, 100, 255 ), 100 );

    ostringstream distractedText ;
    ostringstream perclosText ;
    ostringstream frameTimeText;
    ostringstream noddingOffText;
    ostringstream yawningText;
    ostringstream headRotationText;

    distractedText		<< "Gaze Level        : " << gazeScore;
    perclosText			<< "perclos Level     : " << percloseScore;
    frameTimeText		<< "Frame Time        : " << imageManager.getFrameNumber();
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