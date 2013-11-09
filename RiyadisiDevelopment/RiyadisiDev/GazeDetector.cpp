#include "GazeDetector.h"
#include "Circle.h"
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

GazeDetector::GazeDetector ( void ) {
    for ( int i = 0; i < FEATURE_ARRAY_LENGTH; i++ ) {
        scores[i] = 0;
    }
    defaultLeftRatio = 0.5;
    defaultRightRatio = 0.5;
    defaultTopRatio = 0.5;
    currentIndex = 0;
}


GazeDetector::~GazeDetector ( void ) {
}

/**
    eyes should be provided as GRAY images
*/
Gaze GazeDetector::detectGaze ( FaceFeature faceFeature ) {
    Gaze gaze;

    Rect leftEyeRect = faceFeature.getLeftEye()->getFeatureRect();
    Rect rightEyeRect = faceFeature.getRightEye()->getFeatureRect();
    Point2f leftPupil =  faceFeature.getLeftEye()->getPupil()->getCenterPoint();
    Point2f rightPupil = faceFeature.getRightEye()->getPupil()->getCenterPoint();

    return gaze;
}
float GazeDetector::calculateScore ( Gaze gaze ) {
    float score = 0;
    if ( gaze.isAvailable() ) {
        float leftEyeScore, rightEyeScore;

        leftEyeScore = calculateScoreForEye ( gaze.getLeftEye(), gaze.getLeftPupil(), 'l' );
        rightEyeScore = calculateScoreForEye ( gaze.getRightEye(), gaze.getRightPupil() , 'r' );

        // need a method which would compensate when a measure from one eye is not available.
        score = ( ( ( leftEyeScore > 0 ) ? leftEyeScore : ( -1 * leftEyeScore ) )
                  > ( ( rightEyeScore > 0 ) ? rightEyeScore : ( -1 * rightEyeScore ) ) )
                ? leftEyeScore : rightEyeScore;
    }
    //cout << " Score : " << score << endl;
    return score;
}
float GazeDetector::calculateScoreForEye ( Rect eye, Point2f pupil, char eyeSide ) {
    float horizontalScore = 0, verticalScore = 0;
    float score = 0;

    if ( eye.width != 0 ) {
        if ( eyeSide == 'l' ) {
            horizontalScore = defaultLeftRatio -  pupil.x / eye.width;
        } else if ( eyeSide == 'r' ) {
            horizontalScore = defaultRightRatio -  pupil.x / eye.width;
        }

        if ( eye.height > 0 ) {
            verticalScore = defaultTopRatio - pupil.y / eye.height;

        }
        score = horizontalScore * horizontalScore + verticalScore * verticalScore;
    }
    score *= 100;

    return score;
}

float GazeDetector::getDistractionScore() {
    float distractedAmount;

    float score = 0;
    scores[currentIndex] = calculateScore ( getGaze ( 0 ) );

    score = scores[ ( currentIndex - 1 + FEATURE_ARRAY_LENGTH ) % FEATURE_ARRAY_LENGTH] * 0.8 + scores[currentIndex] * 0.2 ;
    scores[currentIndex] = score;

    return abs ( score );
}
Gaze GazeDetector::getGaze ( int gazeFromCurrent ) {
    Gaze gaze;
    /*if  ( gazeFromCurrent > size ) {
        return gaze;
    }*/
    return gazeArray[ ( currentIndex - gazeFromCurrent + FEATURE_ARRAY_LENGTH ) % FEATURE_ARRAY_LENGTH];
}
void GazeDetector::setCurrentGaze ( Gaze gaze ) {

    currentIndex = ( currentIndex + 1 + FEATURE_ARRAY_LENGTH ) % FEATURE_ARRAY_LENGTH;
    gazeArray[currentIndex].setAvailable ( gaze.isAvailable() );
    gazeArray[currentIndex].setLeftEye ( gaze.getLeftEye() );
    gazeArray[currentIndex].setLeftPupil ( gaze.getLeftPupil() );
    gazeArray[currentIndex].setRightEye ( gaze.getRightEye() );
    gazeArray[currentIndex].setRightPupil ( gaze.getRightPupil() );

}
void GazeDetector::trainDefaultValues ( FaceFeature faceFeature ) {
    Rect leftEye = Rect ( 0, 0, 0, 0 );
    Rect rightEye = Rect ( 0, 0, 0, 0 );
    Point2f leftPupil = Point2f ( 0, 0 );
    Point2f rightPupil = Point2f ( 0, 0 );

    if ( faceFeature.getLeftEye()->isAvailable() ) {
        leftEye = faceFeature.getLeftEye()->getFeatureRect();
        if ( faceFeature.getLeftEye()->getPupil()->isAvailable() ) {
            leftPupil = faceFeature.getLeftEye()->getPupil()->getCenterPoint();
            defaultLeftRatio = defaultLeftRatio * DEFAULT_RATIO
                               +   ( leftPupil.x / leftEye.width ) * ( 1 - DEFAULT_RATIO );
        }
    }
    if ( faceFeature.getRightEye()->isAvailable() ) {
        Rect rightEye = faceFeature.getRightEye()->getFeatureRect();

        if ( faceFeature.getRightEye()->getPupil()->isAvailable() ) {
            Point2f rightPupil = faceFeature.getRightEye()->getPupil()->getCenterPoint();

            defaultRightRatio = defaultRightRatio * DEFAULT_RATIO
                                +  (  rightPupil.x / rightEye.width )  * ( 1 - DEFAULT_RATIO );
        }
    }
    if ( leftEye.height + rightEye.height > 0 ) {
        defaultTopRatio = defaultTopRatio * DEFAULT_RATIO +
                          ( (  leftPupil.y + rightPupil.y ) / ( leftEye.height + rightEye.height ) ) * ( 1 - DEFAULT_RATIO );
    }
}