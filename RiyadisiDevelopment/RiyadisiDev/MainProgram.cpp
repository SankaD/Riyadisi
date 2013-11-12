#include "MainProgram.h"

using namespace std;
using namespace cv;

const short int MainProgram::WAIT_PERIOD_PER_FRAME = 30;

void MainProgram::run()
{
	Log::log ( "Program started" );
    firstRun = true;
    frameCount = 0;
	
	ofstream dataFile;
	dataFile.open ("Resources/Data Files/test.txt");
	short isDrowsy = 0;
	
    while ( true ) {
        frame = imageManager.acquireImage ( frame );
		frameCount++;
		
        processImage();
		
        // Detection
        FaceFeature *faceFeature = featureManager.getFeatureCollection()->getNext();

        Rect faceRoi;

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
            featureManager.findFeatures ( grayFrame, faceFeature, faceRoi );
        }
		
		//dataFile<<featureManager.time<<endl;
        Rect nose = faceFeature->getRelativeRect ( faceFeature->getNose()->getFeatureRect() );
        Rect leftEye = faceFeature->getRelativeRect ( faceFeature->getLeftEye()->getFeatureRect() );
        Rect rightEye = faceFeature->getRelativeRect ( faceFeature->getRightEye()->getFeatureRect() );
        Rect mouth = faceFeature->getRelativeRect ( faceFeature->getMouth()->getFeatureRect() );

		//calculate nodding off level
        noddingOffLevel = noddingOffDetector.noddingOffDetect(*faceFeature);
		std::cout<<  "----------------------------------Nodding off level = "<< noddingOffLevel <<endl;

		//calculate gaze score
        gazeDetector.setCurrentGaze ( faceFeature->getGazeData() );
        gazeScore = gazeDetector.getDistractionScore();

		//calculate PERCLOS
        int frameNum = frameCount % 30;
        if ( frameNum == 0 ) {
            featureManager.perclos /= 30;
            percloscore = featureManager.perclos;
            featureManager.perclos = 0;
        }

		//calculate yawning frequency
		if( faceFeature->getMouth()->isAvailable() ) {
			yawning = yawningDetector.detectYawning( faceFeature );
			cout<<"----- Yawning:" << yawning<<endl;
		}

		//calculate head orientation
		if( frameCount == 1) 
			headRotationDetector.setStartPoints( Point(leftEye.x + leftEye.width/2, leftEye.y + leftEye.height/2), Point(rightEye.x + rightEye.width/2, rightEye.y + rightEye.height/2), Point(nose.x + nose.width/2, nose.y + nose.height/2) );
		if( faceFeature->getLeftEye()->isAvailable() && faceFeature->getRightEye()->isAvailable() && faceFeature->getNose()->isAvailable()) {
			headRotAngles =  headRotationDetector.calculateRotation( faceFeature );
			cout<<"Head orientation: "<<headRotAngles[0]<<" "<<headRotAngles[1]<<" "<<headRotAngles[2]<<endl;
		}

        // drawing image
        Point2f leftPupil = faceFeature->getLeftEye()->getPupil()->getCenterPoint();
        Point2f rightPupil = faceFeature->getRightEye()->getPupil()->getCenterPoint();

        leftPupil = faceFeature->getLeftEye()->getRelativePoint ( leftPupil );
        rightPupil = faceFeature->getRightEye()->getRelativePoint ( rightPupil );

        leftPupil = faceFeature->getRelativePoint ( leftPupil );
        rightPupil = faceFeature->getRelativePoint ( rightPupil );
		       
        if ( faceFeature->isAvailable() ) {
			Rect face = faceFeature->getFeatureRect();
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
            if ( faceFeature->getLeftEye()->getPupil()->isAvailable()
                    && faceFeature->getRightEye()->getPupil()->isAvailable() ) {
                line ( frame, leftPupil, rightPupil, Scalar ( 255, 255, 255 ) );
            }
			
        }
        CvFont font = fontQt ( "Times", -5, Scalar ( 255, 255, 0 ), 100 );

		//display parameters
        ostringstream distractedText ;
        ostringstream perclosText ;
		ostringstream noddingText;
        distractedText << "Distraction Level : " << gazeScore;
        perclosText << "perclos Level : " << percloscore;
		noddingText << "Nodding off : " << noddingOffLevel;
        string drowsinessText = "Drowsiness Level";
        
		addText ( frame, distractedText.str(), Point ( 10, 10 ), font );
        addText ( frame, drowsinessText, Point ( 10, 30 ), font );
        addText ( frame, noddingText.str(), Point ( 10, 50 ), font );
        addText ( frame, perclosText.str(), Point ( 10, 70 ), font );
        imshow ( "image", frame );

		//for writing data file
		int key = waitKey ( 30 );
		if ( key == ' ') isDrowsy = 1-isDrowsy;
					
		//dataFile << percloscore << " " << noddingOffLevel << " " << gazeScore << " " << headmovement << " " << yawning << " " << isDrowsy << endl;
   	
	}
	dataFile.close();
}

MainProgram::MainProgram() {
    isAlertOn = false;
    trainingMode = false;
    imageManager = ImageManager ( ImageSourceType::File, "Testing/Videos/me_with_ir.wmv" );
    //imageManager = ImageManager ( ImageSourceType::File, "Testing/Videos/video 12.wmv" );

    if ( !imageManager.isOpened() ) {
        throw exception ( "Program was unable to load the image source" );
    }

	percloscore = 0.0;
	noddingOffLevel = 0.0;
	yawning = 0.0;
	gazeScore = 0.0;
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
        /* Mat mat;
         imshow ( "Window", mat );*/
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