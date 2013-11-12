#include "FaceFeatureManager.h"
#include "opencv2\features2d\features2d.hpp";


FaceFeatureManager::FaceFeatureManager ( void )
{
	fs=FileStorage("eye_state_pca",FileStorage::READ);
	preeyeState=0;
	
}
FaceFeatureManager::~FaceFeatureManager ( void )
{
}

void FaceFeatureManager::findFeatures ( Mat image, FaceFeature *faceFeature, Rect faceROI )
{
    Mat relatedImage = image ( faceROI );
	Rect mouthROI, noseROI;

    // handle the face region
    vector<Rect> faces;
    cout << "Finding features" << endl;
    // downsampling for increased performance
    Mat downsampledImage;

    //pyrDown ( relatedImage, downsampledImage, Size ( ( relatedImage.cols  ) / DOWNSAMPLE_CONSTANT, ( relatedImage.rows  ) / DOWNSAMPLE_CONSTANT ) );
    downsampledImage = relatedImage.clone();
    for ( int i = 0; i < DOWNSAMPLE_CONSTANT / 2; i++ ) {
        pyrDown ( downsampledImage, downsampledImage, Size ( ( downsampledImage.cols  ) / 2, ( downsampledImage.rows  ) / 2 ) );
    }
	
    cout << "Finding Face" << endl;
	time = clock();
    Rect face = faceDetector.detect ( downsampledImage );
	time = clock() - time;

    if ( face.area() == 0 ) {
        cout << "No faces found" << endl;
        return;
    }


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

    cout << "Finding Eyes" << endl;
    //------------ handle the eye regions
    Rect leftEye, rightEye;
	vector<Rect> eyes;
    eyes = eyeDetector.detect ( faceImage );
	int temp;
    if ( eyes[0].area() > 0 ) {
        leftEye = eyes[0];
		faceFeature->getLeftEye()->setFeatureRect ( leftEye );
        faceFeature->getLeftEye()->setAvailable ( true );
		temp=eyeStateDetector.calculateEyeState(faceImage( leftEye ),fs);
		perclos+=temp;
		preeyeState=temp;

	}
	else perclos=preeyeState;

	if ( eyes[1].area() > 0 ) {
		rightEye = eyes[1];
        faceFeature->getRightEye()->setFeatureRect ( rightEye );
        faceFeature->getRightEye()->setAvailable ( true );
		temp=eyeStateDetector.calculateEyeState(faceImage( rightEye ),fs);
		perclos+=temp;
		preeyeState=temp;
	}
	else perclos=preeyeState;

	
	//float midX =  faceFeature->getFeatureRect().width  / 2;
    //if ( eyes.size() > 0 ) {

    //    if ( eyes[0].x + eyes[0].width / 2 < midX ) {
    //        leftEye = eyes[0];
    //        faceFeature->getLeftEye()->setFeatureRect ( leftEye );
    //        // faceFeature.getLeftEye().setFeatureRect ( leftEye );
    //        faceFeature->getLeftEye()->setAvailable ( true );
    //    } else {
    //        rightEye = eyes[0];
    //        faceFeature->getRightEye()->setFeatureRect ( rightEye );
    //        faceFeature->getRightEye()->setAvailable ( true );
    //    }

    //    if ( eyes.size() > 1 ) {
    //        if ( eyes[1].x + eyes[1].width / 2 > midX ) {
    //            rightEye = eyes[1];
    //            faceFeature->getRightEye()->setFeatureRect ( rightEye );
    //            faceFeature->getRightEye()->setAvailable ( true );
    //        } else {
    //            leftEye = eyes[1];
    //            faceFeature->getLeftEye()->setFeatureRect ( leftEye );
    //            faceFeature->getLeftEye()->setAvailable ( true );
    //        }
    //    }
    //}

    //------------ handle the mouth region
	cout << "Finding Mouth" << endl;
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
	cout << "Finding Nose" << endl;
    Rect nose;
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
	cout << "Finding Pupils" << endl;
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
    cout << "Finished finding features" << endl;
}

FeatureCollection *FaceFeatureManager::getFeatureCollection()
{
    return &features;
}