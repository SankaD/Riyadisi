#include "FaceFeatureManager.h"
#include <time.h>

FaceFeatureManager::FaceFeatureManager ( void ) {
    fs=FileStorage("eye_state_bpca",FileStorage::READ);

}
FaceFeatureManager::~FaceFeatureManager ( void ) {
}

void FaceFeatureManager::findFeatures ( Mat image, FaceFeature *faceFeature, Rect faceROI, Rect leftEyeROI, Rect rightEyeROI, Rect mouthROI ) {
    try {
		Mat relatedImage = image( faceROI ).clone();

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
		if ( eyes[0].area() > 0 ) {
			leftEye = eyes[0];
			faceFeature->getLeftEye()->setFeatureRect ( leftEye );
			faceFeature->getLeftEye()->setAvailable ( true );
            perclos = eyeStateDetector.getPerclosScore ( faceImage ( leftEye ), fs );
			
			preeyeState=perclos;

		}
		else perclos=preeyeState;

		if ( eyes[1].area() > 0 ) {
			rightEye = eyes[1];
			faceFeature->getRightEye()->setFeatureRect ( rightEye );
			faceFeature->getRightEye()->setAvailable ( true );
            perclos = eyeStateDetector.getPerclosScore ( faceImage ( rightEye ), fs );
			
			preeyeState=perclos;
		}
		else perclos=preeyeState;

        
        //------------ handle the mouth region
        Rect mouth;
		
		if(faceFeature->getLeftEye()->isAvailable() && faceFeature->getRightEye()->isAvailable()){
			mouthROI.x = leftEye.x;
			mouthROI.y = faceImage.rows * 2 / 3;
			mouthROI.width = (rightEye.x + rightEye.width - leftEye.x);
			mouthROI.height = faceImage.rows / 3;

			mouth = mouthDetector.detect ( faceImage ( mouthROI ) );

			if ( mouth.area() > 0 ) {
				mouth.x += mouthROI.x;
				mouth.y += mouthROI.y;

				faceFeature->getMouth()->setFeatureRect ( mouth );
				faceFeature->getMouth()->setAvailable ( true );
			}
		} 

        //------------ handle the nose region
        Rect nose, noseROI;
		vector<Rect> noseResults;

		//selecting the best rectangle for nose
		if(faceFeature->getLeftEye()->isAvailable() && faceFeature->getRightEye()->isAvailable()){
			noseROI.x = leftEye.x + leftEye.width/2;
			noseROI.y = faceImage.rows/2;
			noseROI.width = (rightEye.x + rightEye.width/2) - (leftEye.x + leftEye.width/2);
			noseROI.height = faceImage.rows / 4;

			noseResults = noseDetector.detect ( faceImage ( noseROI ) );

			if ( noseResults.size() > 0 ) {
				nose = noseResults[0];
				nose.x += noseROI.x;
				nose.y += noseROI.y;

				faceFeature->getNose()->setFeatureRect ( nose );
				faceFeature->getNose()->setAvailable ( true );
			}
		}

        //------------ handler the pupil regions
        if ( faceFeature->getRightEye()->isAvailable() ) {
            Pupil pupil = pupilDetector.detectPupil ( faceImage ( rightEye ) );
            if ( pupil.getPupilLocation().getRadius() > 0 ) {
                faceFeature->getRightEye()->getPupil()->setAvailable ( true );
                faceFeature->getRightEye()->getPupil()->setCenterPoint ( pupil.getPupilLocation().getCenter() );
            }
        }
        if ( faceFeature->getLeftEye()->isAvailable() ) {
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