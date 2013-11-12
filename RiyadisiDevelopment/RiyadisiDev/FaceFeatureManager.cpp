#include "FaceFeatureManager.h"
#include <time.h>

FaceFeatureManager::FaceFeatureManager ( void ) {
    fs = FileStorage ( "eye_state_pca", FileStorage::READ );

}
FaceFeatureManager::~FaceFeatureManager ( void ) {
}

void FaceFeatureManager::findFeatures ( Mat image, FaceFeature *faceFeature, Rect faceROI, Rect leftEyeROI, Rect rightEyeROI, Rect mouthROI ) {
    try {
        Mat relatedImage = image ( faceROI );

        // handle the face region
        vector<Rect> faces;
        Log::log ( "Finding features" );

        // downsampling for increased performance
        Mat downsampledImage;

        downsampledImage = relatedImage.clone();
        for ( int i = 0; i < DOWNSAMPLE_CONSTANT / 2; i++ ) {
            pyrDown ( downsampledImage, downsampledImage, Size ( ( downsampledImage.cols  ) / 2, ( downsampledImage.rows  ) / 2 ) );
        }

        Log::log ( "Finding faces" );
        faces = faceDetector.detect ( downsampledImage );

        if ( faces.size() == 0 ) {
            Log::log ( "No faces found" );
            return;
        }

        Rect face = faces[0];// this should be changed to the largest identified face

        // rescaling into the original size
        face.x *= DOWNSAMPLE_CONSTANT ;
        face.y *= DOWNSAMPLE_CONSTANT ;
        face.height *= DOWNSAMPLE_CONSTANT;
        face.width *= DOWNSAMPLE_CONSTANT;

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
        //eyes = eyeDetector.detect ( ( faceFeature->getImage() )  );

        //detect left eye
        leftEyeROI.x = 0;
        leftEyeROI.y = faceImage.rows / 4;
        leftEyeROI.width = faceImage.cols / 2;
        leftEyeROI.height = faceImage.rows / 4;

        eyes = leftEyeDetector.detect ( faceImage ( leftEyeROI ) );

        if ( eyes.size() > 0 ) {
            leftEye = eyes[0];

            for ( int i = 1; i < eyes.size(); i++ ) {
                if ( leftEye.area() < eyes[i].area() ) {
                    leftEye = eyes[i];
                }
            }

            leftEye.x += leftEyeROI.x;
            leftEye.y += leftEyeROI.y;

            faceFeature->getLeftEye()->setFeatureRect ( leftEye );
            faceFeature->getLeftEye()->setAvailable ( true );
            perclos += eyeStateDetector.calculateEyeState ( faceImage ( leftEye ), fs );
        }

        //detect right eye
        rightEyeROI.x = faceImage.cols / 2;
        rightEyeROI.y = faceImage.rows / 4;
        rightEyeROI.width = faceImage.cols / 2;
        rightEyeROI.height = faceImage.rows / 4;

        eyes = rightEyeDetector.detect ( faceImage ( rightEyeROI ) );

        if ( eyes.size() > 0 ) {
            rightEye = eyes[0];

            for ( int i = 1; i < eyes.size(); i++ ) {
                if ( rightEye.area() < eyes[i].area() ) {
                    rightEye = eyes[i];
                }
            }

            rightEye.x += rightEyeROI.x;
            rightEye.y += rightEyeROI.y;

            faceFeature->getRightEye()->setFeatureRect ( rightEye );
            faceFeature->getRightEye()->setAvailable ( true );
            perclos += eyeStateDetector.calculateEyeState ( faceImage ( rightEye ), fs );
        }

        //------------ handle the mouth region
        Rect mouth;
        mouthROI.x = 0;
        mouthROI.y = faceImage.rows * 2 / 3;
        mouthROI.width = faceImage.cols;
        mouthROI.height = faceImage.rows / 3;

        vector<Rect> mouthResults = mouthDetector.detect ( faceImage ( mouthROI ) );

        //selecting the best rectangle for nose
        if ( mouthResults.size() > 0 ) {
            mouth = mouthResults[0];

            mouth.x += mouthROI.x;
            mouth.y += mouthROI.y;

            faceFeature->getMouth()->setFeatureRect ( mouth );
            faceFeature->getMouth()->setAvailable ( true );
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