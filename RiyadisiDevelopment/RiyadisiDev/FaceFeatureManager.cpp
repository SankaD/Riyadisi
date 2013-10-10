#include "FaceFeatureManager.h"

#include <time.h>

FaceFeatureManager::FaceFeatureManager ( void )
{

}
FaceFeatureManager::~FaceFeatureManager ( void )
{
}

void FaceFeatureManager::findFeatures ( Mat image, FaceFeature *faceFeature, Rect roi )
{
    Mat relatedImage = image ( roi );

    // handle the face region
    vector<Rect> faces;
    cout << "Finding features" << endl;
    // downsampling for increased performance
    Mat downsampledImage;

    //pyrDown ( relatedImage, downsampledImage, Size ( ( relatedImage.cols  ) / DOWNSAMPLE_CONSTANT, ( relatedImage.rows  ) / DOWNSAMPLE_CONSTANT ) );
    downsampledImage = relatedImage.clone();

    cout << "Finding eyes" << endl;
    faces = faceDetector.detect ( downsampledImage );

    if ( faces.size() == 0 ) {
        cout << "No faces found" << endl;
        return;
    }

    Rect face = faces[0];// this should be changed to the largest identified face

    // rescaling into the original size
    //face.x *= DOWNSAMPLE_CONSTANT ;
    //face.y *= DOWNSAMPLE_CONSTANT ;
    //face.height *= DOWNSAMPLE_CONSTANT;
    //face.width *= DOWNSAMPLE_CONSTANT;

    //compensate for the roi
    Mat faceImage = relatedImage ( face );

    face.x += roi.x;
    face.y += roi.y;

    faceFeature->setAvailable ( true );
    faceFeature->setFeatureRect ( face );
    faceFeature->setImage ( faceImage ) ;

    cout << "Finding Eyes" << endl;
    //------------ handle the eye regions
    Rect leftEye, rightEye;
    vector<Rect> eyes;
    eyes = eyeDetector.detect ( ( faceFeature->getImage() )  );

    float midX =  faceFeature->getFeatureRect().width  / 2;
    if ( eyes.size() > 0 ) {

        if ( eyes[0].x + eyes[0].width / 2 < midX ) {
            leftEye = eyes[0];
            faceFeature->getLeftEye()->setFeatureRect ( leftEye );
            // faceFeature.getLeftEye().setFeatureRect ( leftEye );
            faceFeature->getLeftEye()->setAvailable ( true );
        } else {
            rightEye = eyes[0];
            faceFeature->getRightEye()->setFeatureRect ( rightEye );
            faceFeature->getRightEye()->setAvailable ( true );
        }

        if ( eyes.size() > 1 ) {
            if ( eyes[1].x + eyes[1].width / 2 > midX ) {
                rightEye = eyes[1];
                faceFeature->getRightEye()->setFeatureRect ( rightEye );
                faceFeature->getRightEye()->setAvailable ( true );
            } else {
                leftEye = eyes[1];
                faceFeature->getLeftEye()->setFeatureRect ( leftEye );
                faceFeature->getLeftEye()->setAvailable ( true );
            }
        }
    }

    //------------ handle the mouth region

    cout << "Finding nose" << endl;
    //------------ handle the nose region
    Rect nose;
    vector<Rect> noseResults = noseDetector.detect ( faceFeature->getImage() );

    //selecting the best rectangle for nose
    if ( noseResults.size() > 0 ) {
        nose = noseResults[0];
        faceFeature->getNose()->setFeatureRect ( nose );
        faceFeature->getNose()->setAvailable ( true );
    }

    cout << "Finding pupils" << endl;
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