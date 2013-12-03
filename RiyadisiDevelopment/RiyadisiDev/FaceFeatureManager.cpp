#include "FaceFeatureManager.h"
#include <time.h>

FaceFeatureManager::FaceFeatureManager ( void ) {
   // fs = FileStorage ( "eye_state_bpca", FileStorage::READ );
	fs=FileStorage("eye_state_sobel_bpca",FileStorage::READ);

}
FaceFeatureManager::~FaceFeatureManager ( void ) {
}

void FaceFeatureManager::findFeatures ( Mat image, FaceFeature *faceFeature, Rect faceROI, Rect leftEyeROI, Rect rightEyeROI, Rect mouthROI ) {
    try {
        Mat relatedImage = image ( faceROI ).clone();

        // handle the face region
        Log::log ( "Finding features" );

        Log::log ( "Finding faces" );
        Rect face = faceDetector.detect ( relatedImage );

        if ( face.area() == 0 ) {
            Log::log ( "No faces found" );
            return;
        }

        //compensate for the roi
        Mat faceImage = relatedImage ( face );

        face.x += faceROI.x;
        face.y += faceROI.y;

        faceFeature->setAvailable ( true );
        faceFeature->setFeatureRect ( face );
        faceFeature->setImage ( faceImage ) ;

        Log::log ( "Finding Eyes" );
        //------------ handle the eye regions
        Rect leftEye, rightEye;
        vector<Rect> eyes;
        eyes = eyeDetector.detect ( faceImage );
        int temp;
		double perclosr,perclosl;
        if ( eyes[0].area() > 0 ) {
            leftEye = eyes[0];
            faceFeature->getLeftEye()->setFeatureRect ( leftEye );
            faceFeature->getLeftEye()->setAvailable ( true );
            perclosl = eyeStateDetector.getPerclosScore ( faceFeature, "left", fs );

            preeyeState = perclosl;

        } else {
            perclosl = preeyeState;
        }

        if ( eyes.size() > 1 ) {
            rightEye = eyes[1];
            faceFeature->getRightEye()->setFeatureRect ( rightEye );
            faceFeature->getRightEye()->setAvailable ( true );
            perclosr = eyeStateDetector.getPerclosScore ( faceFeature, "right", fs );

            preeyeState = perclosr;
        } else {
            perclosr = preeyeState;
        }

		perclos=max(perclosl,perclosr);
        //------------ handle the nose region
        Rect nose, noseROI;
        vector<Rect> noseResults;


        // reducing the search area for a nose
        if ( faceFeature->isAvailable() ) {
            noseROI = faceFeature->getFeatureRect();
            noseROI.x =  noseROI.width / 4;
            noseROI.y =  noseROI.height / 4;
            noseROI.width = noseROI.width / 2;
            noseROI.height = noseROI.height / 2;

			Mat noseImage = faceImage ( noseROI );
			noseResults = noseDetector.detect ( noseImage );

            if ( noseResults.size() > 0 ) {
                nose = noseResults[0];

                //selecting the best rectangle for nose

                nose.x += noseROI.x;
                nose.y += noseROI.y;

                faceFeature->getNose()->setFeatureRect ( nose );
                faceFeature->getNose()->setAvailable ( true );

                Rect tempNoseROI;
                tempNoseROI.x = nose.x + nose.width / 4;
                tempNoseROI.y = nose.y;
                tempNoseROI.width = nose.width / 2;
                tempNoseROI.height = nose.height;

                Mat tempNose = faceImage ( tempNoseROI );
                equalizeHist ( tempNose, tempNose );
                threshold ( tempNose, tempNose, 200, 255, CV_THRESH_BINARY );

                Canny ( tempNose.clone(), tempNose, 200, 255 );
                Point2f noseCenter;
                float radius;
                vector<vector<Point>> contours;
                findContours ( tempNose.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );

                double area = 0, maxArea = 0;
                int maxAreaIndex = -1;
                float radiusTemp;
                Point2f centerTemp;
                vector<Point> points;
                for ( int i = 0; i < contours.size(); i++ ) {
                    points.insert ( points.end(), contours[i].begin(), contours[i].end() );
                }
                minEnclosingCircle ( points, noseCenter, radius );
                line ( tempNose, Point ( noseCenter.x, noseCenter.y + 5 ), Point ( noseCenter.x, noseCenter.y - 5 ), Scalar ( 255, 255, 0 ) );

                //imshow ( "Nose", tempNose );
            }
        }
        

		//------------ handle the mouth region
        Rect mouth;

        if ( faceFeature->getLeftEye()->isAvailable() && faceFeature->getRightEye()->isAvailable() ) {
			int mouthCenter = faceFeature->getLeftEye()->getCenterPoint().y + face.height * 0.36;
			
			mouthROI.x = faceFeature->getLeftEye()->getCenterPoint().x;
			mouthROI.width = faceFeature->getRightEye()->getCenterPoint().x - faceFeature->getLeftEye()->getCenterPoint().x;
			mouthROI.y = mouthCenter - mouthROI.width/6;
			mouthROI.height = mouthROI.width/3;
			
			if( mouthROI.y < (nose.y + nose.height) )
			{
				mouthROI.y = nose.y + nose.height;
			}
			//imshow ( "Mouth", faceImage ( mouthROI ) );

			/*mouthROI.x = faceFeature->getLeftEye()->getFeatureRect().x;
			mouthROI.width = faceFeature->getRightEye()->getFeatureRect().x+faceFeature->getRightEye()->getFeatureRect().width-faceFeature->getLeftEye()->getFeatureRect().x;
			mouthROI.y = face.height *2/3;
			mouthROI.height = face.height/3;*/
			mouth = mouthDetector.detect ( faceImage ( mouthROI ) );

            if ( mouth.area() > 0 ) {
                mouth.x += mouthROI.x;
                mouth.y += mouthROI.y;

                faceFeature->getMouth()->setFeatureRect ( mouth );
                faceFeature->getMouth()->setAvailable ( true );
            }
        }


        //------------ handler the pupil regions
		if ( faceFeature->getRightEye()->isAvailable() && faceFeature->getRightEye()->isEyeOpen() ) {
            Pupil pupil = pupilDetector.detectPupil ( faceImage ( rightEye ) );
            if ( pupil.getPupilLocation().getRadius() > 0 ) {
                faceFeature->getRightEye()->getPupil()->setAvailable ( true );
                faceFeature->getRightEye()->getPupil()->setCenterPoint ( pupil.getPupilLocation().getCenter() );
            }
        }
        if ( faceFeature->getLeftEye()->isAvailable() && faceFeature->getRightEye()->isEyeOpen() ) {
            Pupil pupil = pupilDetector.detectPupil ( faceImage ( leftEye ) );
            if ( pupil.getPupilLocation().getRadius() > 0 ) {
                faceFeature->getLeftEye()->getPupil()->setAvailable ( true );
                faceFeature->getLeftEye()->getPupil()->setCenterPoint ( pupil.getPupilLocation().getCenter() );
            }
        }
        Log::log ( "Finished finding features" );
    } catch ( exception ex ) {
        Log::log ( ex.what() );
    }
}

FeatureCollection *FaceFeatureManager::getFeatureCollection() {
    return &features;
}