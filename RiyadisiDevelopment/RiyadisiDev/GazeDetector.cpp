#include "GazeDetector.h"

using namespace cv;
using namespace std;

GazeDetector::GazeDetector ( void ) {
    for ( int i = 0; i < FEATURE_ARRAY_LENGTH; i++ ) {
        scores[i].horizontal = 0;
        scores[i].vertical = 0;
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

double oldHScore = 0, oldVScore = 0;

DirectedGaze GazeDetector::calculateScore ( Gaze gaze ) {
    double hScore = oldHScore, vScore = oldVScore;
    DirectedGaze directedGaze ;
    double score = oldHScore;

    if ( gaze.isAvailable() ) {
        double leftEyeScore, rightEyeScore;
        double leftEyeHScore, rightEyeHScore;

        if ( gaze.getLeftPupil().x > 0.0 ) {
            score = calculateScoreForEye ( gaze.getLeftEye(), gaze.getLeftPupil(), 'l' );
        } else if ( gaze.getRightPupil().x > 0.0 ) {
            score = calculateScoreForEye ( gaze.getRightEye(), gaze.getRightPupil() , 'r' );
        }

        //leftEyeHScore = calculateScoreForEye ( gaze.getLeftEye(), gaze.getLeftPupil(), 'l', 'v' );
        //rightEyeHScore = calculateScoreForEye ( gaze.getRightEye(), gaze.getRightPupil(), 'r', 'v' );

        //vScore = ( leftEyeHScore > rightEyeHScore ) ? leftEyeHScore : rightEyeHScore;

        // need a method which would compensate when a measure from one eye is not available.
        //hScore =   ( abs ( leftEyeScore ) >  abs ( rightEyeScore ) ) ? leftEyeScore : rightEyeScore;
        //hScore = ( leftEyeScore + rightEyeScore ) / 2;

        oldHScore = score;
        oldVScore = vScore;
    }

    directedGaze.horizontal = score;
    directedGaze.vertical = vScore;

    return directedGaze;
}
double GazeDetector::calculateScoreForEye ( Rect eye, Point2f pupil, char eyeSide, char direction ) {
    double horizontalScore = 0, verticalScore = 0;
    double score = 0;

    if ( eye.width != 0 ) {
        if ( direction == 'h' ) {
            if ( eyeSide == 'l' ) {
                score =   ( pupil.x / eye.width ) - defaultLeftRatio;
            } else if ( eyeSide == 'r' ) {
                score = defaultRightRatio - ( ( eye.width - pupil.x ) / eye.width );
                // score *= -1;
            }
        } else if ( direction == 'v' ) {
            score = ( pupil.y / eye.height ) - defaultTopRatio;
        }
    }
    score *= 4;

    return score;
}

DirectedGaze GazeDetector::getDistractionScore() {
    double distractedAmount;

    double score = 0;
    DirectedGaze gaze;
    double hScore = 0, vScore = 0;
    scores[currentIndex] = calculateScore ( getGaze ( 0 ) );

    hScore = scores[ ( currentIndex - 1 + FEATURE_ARRAY_LENGTH ) % FEATURE_ARRAY_LENGTH].horizontal * 0.3
             + scores[currentIndex].horizontal * 0.7 ;
    /*vScore = scores[ ( currentIndex - 1 + FEATURE_ARRAY_LENGTH ) % FEATURE_ARRAY_LENGTH].vertical * 0.6
             + scores[currentIndex].vertical * 0.4 ;*/
    scores[currentIndex].horizontal = hScore;
    scores[currentIndex].vertical = vScore;

    gaze.horizontal = hScore;
    gaze.vertical = vScore;

    return gaze;
}
Gaze GazeDetector::getGaze ( int gazeFromCurrent ) {
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