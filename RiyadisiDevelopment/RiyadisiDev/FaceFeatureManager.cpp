#include "FaceFeatureManager.h"
#include "FaceDetector.h"
#include "EyeDetector.h"
#include "PupilDetector.h"
#include "NoseDetector.h"
#include <time.h>

FaceFeatureManager::FaceFeatureManager ( void )
{

}
FaceFeatureManager::~FaceFeatureManager ( void )
{
}

void FaceFeatureManager::findFeatures ( Mat image, FaceFeature &faceFeature )
{
    FaceDetector faceDetector;
    EyeDetector eyeDetector;
    PupilDetector pupilDetector;
    NoseDetector noseDetector;

    // handle the face region
    vector<Rect> faces;

    // downsampling for increased performance
    Mat downsampledImage;

    pyrDown ( image, downsampledImage, Size ( ( image.cols  ) / DOWNSAMPLE_CONSTANT, ( image.rows  ) / DOWNSAMPLE_CONSTANT ) );

    faces = faceDetector.detect ( downsampledImage );

    if ( faces.size() == 0 ) {
        return;
    }

    Rect face = faces[0];// this should be changed to the largest identified face

    // rescaling into the original size
    face.x *= DOWNSAMPLE_CONSTANT ;
    face.y *= DOWNSAMPLE_CONSTANT ;
    face.height *= DOWNSAMPLE_CONSTANT;
    face.width *= DOWNSAMPLE_CONSTANT;

    Mat faceImage = image ( face );
    faceFeature.setAvailable ( true );
    faceFeature.setFeatureRect ( face );
    faceFeature.setImage ( faceImage ) ;


    //------------ handle the eye regions
    Rect leftEye, rightEye;
    vector<Rect> eyes;
    eyes = eyeDetector.detect (   ( faceFeature.getImage() )  );

    float midX =  faceFeature.getFeatureRect().width  / 2;
    if ( eyes.size() > 0 ) {

        if ( eyes[0].x + eyes[0].width / 2 < midX ) {
            leftEye = eyes[0];
            faceFeature.getLeftEye().setFeatureRect ( leftEye );
            // faceFeature.getLeftEye().setFeatureRect ( leftEye );
            faceFeature.getLeftEye().setAvailable ( true );
        } else {
            rightEye = eyes[0];
            faceFeature.getRightEye().setFeatureRect ( rightEye );
            faceFeature.getRightEye().setAvailable ( true );
        }

        if ( eyes.size() > 1 ) {
            if ( eyes[1].x + eyes[1].width / 2 > midX ) {
                rightEye = eyes[1];
                faceFeature.getRightEye().setFeatureRect ( rightEye );
                faceFeature.getRightEye().setAvailable ( true );
            } else {
                leftEye = eyes[1];
                faceFeature.getLeftEye().setFeatureRect ( leftEye );
                faceFeature.getLeftEye().setAvailable ( true );
            }
        }
    }

    //------------ handle the mouth region

    //------------ handle the nose region
    Rect nose;
    vector<Rect> noseResults = noseDetector.detect ( faceFeature.getImage() );

    //selecting the best rectangle for nose
    if ( noseResults.size() > 0 ) {
        nose = noseResults[0];
        faceFeature.getNose().setFeatureRect ( nose );
        faceFeature.getNose().setAvailable ( true );
    }

    //------------ handler the pupil regions
    if ( faceFeature.getRightEye().isAvailable() ) {
        Pupil pupil = pupilDetector.detectPupil ( faceImage ( rightEye ) );
        faceFeature.getRightEye().getPupil().setCenterPoint ( pupil.getPupilLocation().getCenter() );
    }
    if ( faceFeature.getLeftEye().isAvailable() ) {
        Pupil pupil = pupilDetector.detectPupil ( faceImage ( leftEye ) );
        faceFeature.getLeftEye().getPupil().setCenterPoint ( pupil.getPupilLocation().getCenter() );
    }
    // return faceFeature;
}

FeatureCollection FaceFeatureManager::getFeatureCollection()
{
    return features;
}