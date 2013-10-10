#include "FaceFeatureManager.h"

#include <time.h>

FaceFeatureManager::FaceFeatureManager ( void )
{

}
FaceFeatureManager::~FaceFeatureManager ( void )
{
}

void FaceFeatureManager::findFeatures ( Mat image, FaceFeature *faceFeature, Rect faceROI, Rect leftEyeROI, Rect rightEyeROI, Rect mouthROI )
{
    Mat relatedImage = image ( faceROI );

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

    cout << "Finding eyes" << endl;
    faces = faceDetector.detect ( downsampledImage );

    if ( faces.size() == 0 ) {
        cout << "No faces found" << endl;
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

    cout << "Finding Eyes" << endl;
    //------------ handle the eye regions
    Rect leftEye, rightEye;
    vector<Rect> eyes;
    //eyes = eyeDetector.detect ( ( faceFeature->getImage() )  );

    //detect left eye
    //if(leftEyeROI.area() == 0){
    leftEyeROI.x = 0;
    leftEyeROI.y = faceImage.rows/4;
    leftEyeROI.width = faceImage.cols / 2;
    leftEyeROI.height = faceImage.rows / 4;
    //}
    eyes = eyeDetector.detect ( faceImage ( leftEyeROI ) );
	
    if ( eyes.size() > 0 ) {
        leftEye = eyes[0];
		leftEye.x += leftEyeROI.x;
        leftEye.y += leftEyeROI.y;

        faceFeature->getLeftEye()->setFeatureRect ( leftEye );
        faceFeature->getLeftEye()->setAvailable ( true );
		//imshow("test", faceImage ( leftEye ));
    }
	
    //detect right eye
    //if(rightEyeROI.area() == 0){
    rightEyeROI.x = faceImage.cols / 2;
    rightEyeROI.y = faceImage.rows/4;
    rightEyeROI.width = faceImage.cols / 2;
    rightEyeROI.height = faceImage.rows / 4;
    //}
    eyes = eyeDetector.detect ( faceImage ( rightEyeROI ) );

    if ( eyes.size() > 0 ) {
        rightEye = eyes[0];
        rightEye.x += rightEyeROI.x;
        rightEye.y += rightEyeROI.y;

        faceFeature->getRightEye()->setFeatureRect ( rightEye );
        faceFeature->getRightEye()->setAvailable ( true );
    }

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
    Rect mouth;
    //if(mouthROI.area() == 0){
    mouthROI.x = 0;
    mouthROI.y = faceImage.rows * 2 / 3;
    mouthROI.width = faceImage.cols;
    mouthROI.height = faceImage.rows / 3;
    //}
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
    //Rect nose;
    //vector<Rect> noseResults = noseDetector.detect ( faceFeature->getImage() );

    ////selecting the best rectangle for nose
    //if ( noseResults.size() > 0 ) {
    //    nose = noseResults[0];
    //    faceFeature->getNose()->setFeatureRect ( nose );
    //    faceFeature->getNose()->setAvailable ( true );
    //}

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
    cout << "Finished finding features" << endl;
}

FeatureCollection *FaceFeatureManager::getFeatureCollection()
{
    return &features;
}