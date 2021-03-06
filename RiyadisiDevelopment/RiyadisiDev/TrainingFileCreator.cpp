#include "TrainingFileCreator.h"


TrainingFileCreator::TrainingFileCreator ( void ) {

}


TrainingFileCreator::~TrainingFileCreator ( void ) {
}

void TrainingFileCreator::trainUsingFile ( string fileName ) {
    try {
        int fileCount ;
        ifstream listFileStream ( fileName );

        if ( listFileStream.is_open() ) {
            // get the file count from the top of the file
            listFileStream >> fileCount;
            //fileCount << listFileStream;

            string videoFileName = "";
            //train using the video files list known from the provided file
            for ( int i = 0; i < fileCount; i++ ) {

                listFileStream >> videoFileName;
                try {
                    Log::log ( "Using file : " + videoFileName );
                    stringstream stringStream;
                    stringStream << "data/data/" << ( i + 1 ) << ".data";
                    trainUsingVideo ( videoFileName, stringStream.str() );
                } catch ( exception ex ) {
                    Log::log ( LogStatus::Error, ex.what()  );
                }
            }
            listFileStream.close();
        } else {
            Log::log ( LogStatus::Error, "File was not opened" );
        }
    } catch ( exception ex ) {
        Log::log ( LogStatus::Error, ex.what()  );
    }
}
bool isDrowsy ;
bool isDistracted ;

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

    isDrowsy = false;
    isDistracted = false;
    alertStatus = false;

    while ( true ) {
        frame = imageManager.acquireImage ( frame );

        ticksForFrame =  getTickCount() - ticks;
        ticks = getTickCount();

        key = waitKey ( 30 );
        if ( imageManager.isVideoEnded() ) {
            return;
        }

        // if the used press 'c', abort
        if ( key == 'c' ) {
            break;
        } else if ( key == ' ' ) {
            alertStatus = !alertStatus;
        } else if ( key ==  '1' ) {
            isDrowsy = true;
        } else if (  key == '2' ) {
            isDistracted = true;
        } else if (  key == '3' ) {
            isDrowsy = true;
            isDistracted = true;
        } else if (  key == '0' ) {
            isDrowsy = false;
            isDistracted = false;
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

            featureManager.findFeatures ( grayFrame, faceFeature, faceRoi );

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

                if ( faceRoi.width + faceRoi.x > grayFrame.cols ) {
                    faceRoi.width = grayFrame.cols - faceRoi.x;
                }
                if ( faceRoi.height + faceRoi.y > grayFrame.rows ) {
                    faceRoi.height = grayFrame.rows - faceRoi.y;
                }
            } else {
                // if there was no previous frame take the whole image as ROI
                faceRoi.x = 0;
                faceRoi.y = 0;
                faceRoi.width = grayFrame.cols;
                faceRoi.height = grayFrame.rows;
            }

            featureManager.findFeatures ( grayFrame, faceFeature, faceRoi );
        }
        Rect nose = faceFeature->getRelativeRect ( faceFeature->getNose()->getFeatureRect() );
        Rect leftEye = faceFeature->getRelativeRect ( faceFeature->getLeftEye()->getFeatureRect() );
        Rect rightEye = faceFeature->getRelativeRect ( faceFeature->getRightEye()->getFeatureRect() );
        Rect mouth = faceFeature->getRelativeRect ( faceFeature->getMouth()->getFeatureRect() );

        noddingOffLevel = noddingOffDetector.noddingOffDetect ( *faceFeature, imageManager.getFrameNumber() );
        //noddingOffDetector.collectTraningData ( *faceFeature );

        gazeDetector.setCurrentGaze ( faceFeature->getGazeData() );
        gazeScore = gazeDetector.getDistractionScore();

        percloseScore = featureManager.perclos;

        //calculate yawning frequency
        if ( faceFeature->getMouth()->isAvailable() ) {
            yawningScore = yawningDetector.detectYawning ( faceFeature );
        }

        //calculate head orientation
        if ( imageManager.getFrameNumber() < 20 ) {
            headRotationDetector.updateGroundPosition ( faceFeature );
        }
        if ( faceFeature->getLeftEye()->isAvailable() && faceFeature->getRightEye()->isAvailable() && faceFeature->getNose()->isAvailable() ) {
            headRotAngles =  headRotationDetector.calculateRotation ( faceFeature );
        }

        outputFile << percloseScore << " "
                   << noddingOffLevel << " "
                   << gazeScore.horizontal << " "
                   << gazeScore.vertical << " "
                   << yawningScore << " "
                   << headRotAngles[0] << " "
                   << headRotAngles[1] << " "
                   << headRotAngles[2] << " "
                   << ( isDrowsy  ? 1 : 0 ) << " "
                   << ( isDistracted ? 1 : 0 )
                   << endl;


        drawTexts ( frame, ticksForFrame );

        cv::imshow ( "image", frame );
    }
    outputFile.close();
}
void TrainingFileCreator::drawTexts ( Mat &frame, long int ticksForFrame ) {
    CvFont fontYellow = fontQt ( "Times", -5, Scalar ( 255, 255, 0 ), 100 );
    CvFont fontRed = fontQt ( "Times", -5, Scalar ( 255, 0, 0 ), 100 );
    CvFont fontAlert = fontQt ( "Times", 12, Scalar ( 255, 0, 255 ), 200 );

    ostringstream gazeText ;
    ostringstream perclosText ;
    ostringstream frameTimeText;
    ostringstream noddingOffText;
    ostringstream yawningText;
    ostringstream headRotationText;

    ostringstream frameCountText;

    frameTime = ( ticksForFrame / (  getTickFrequency() ) ) * 1000;

    gazeText			<< "Gaze Level        : " << gazeScore.horizontal << " , " << gazeScore.vertical;
    perclosText			<< "perclos Level     : " << percloseScore;
    frameTimeText		<< "Frame Time        : " << frameTime;
    noddingOffText		<< "Nodding Off Rate  : " << noddingOffLevel;
    yawningText			<< "Yawning Rate	  : " << yawningScore;
    headRotationText	<< "Head Rotation     : " ;

    if ( headRotAngles.size() > 0 ) {
        headRotationText << headRotAngles[0] << ", " << headRotAngles[1] << ", " << headRotAngles[2];
    }

    frameCountText		<< "Frame Number :"		<< imageManager.getFrameNumber();

    string drowsinessText	= ":: Drowsiness Measures  ::";
    string distractionText =  ":: Distraction Measures ::";
    string alertText		= "Alert the driver  : ";

    string drowsiText = "Drowsy : ";
    string distractText = "Distracted : ";
    drowsiText += ( isDrowsy ? "Yes" : "No" );
    distractText += ( isDistracted ? "Yes" : "No" );

    if ( alertStatus ) {
        alertText += "Yes";
    } else {
        alertText += "No";
    }

    addText ( frame, drowsinessText, Point ( 10, 10 ), fontYellow );
    addText ( frame, perclosText.str(), Point ( 10, 30 ), fontYellow );
    addText ( frame, noddingOffText.str(), Point ( 10, 50 ), fontYellow );
    addText ( frame, yawningText.str(), Point ( 10, 70 ), fontYellow );

    addText ( frame, distractionText, Point ( 10, 100 ), fontYellow );
    addText ( frame, gazeText.str(), Point ( 10, 120 ), fontYellow );
    addText ( frame, headRotationText.str(), Point ( 10, 140 ), fontYellow );


    addText ( frame, frameTimeText.str(), Point ( frame.cols * 3 / 4 , 10 ), fontRed );
    addText ( frame, frameCountText.str(), Point ( frame.cols * 3 / 4, 30 ), fontRed );
    //addText ( frame, alertText, Point ( 200, 20 ), fontAlert );
    addText ( frame, drowsiText, Point ( 200, 20 ), fontAlert );
    addText ( frame, distractText, Point ( 200, 50 ), fontAlert );
}