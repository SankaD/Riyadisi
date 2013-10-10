#include "GazeDetector.h"
#include "Circle.h"
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

GazeDetector::GazeDetector ( void )
{
    for ( int i = 0; i < FEATURE_ARRAY_LENGTH; i++ ) {
        scores[i] = 0;
    }
    currentIndex = 0;
}


GazeDetector::~GazeDetector ( void )
{
}

/**
    eyes should be provided as GRAY images
*/
Gaze GazeDetector::detectGaze ( FaceFeature faceFeature )
{
    Gaze gaze;

    Rect leftEyeRect = faceFeature.getLeftEye()->getFeatureRect();
    Rect rightEyeRect = faceFeature.getRightEye()->getFeatureRect();
    Point2f leftPupil =  faceFeature.getLeftEye()->getPupil()->getCenterPoint();
    Point2f rightPupil = faceFeature.getRightEye()->getPupil()->getCenterPoint();



    return gaze;
}
float GazeDetector::calculateScore ( Gaze gaze )
{
    float score = 0;
    if ( gaze.isAvailable() ) {
        float leftEyeScore, rightEyeScore;

        leftEyeScore = calculateScoreForEye ( gaze.getLeftEye(), gaze.getLeftPupil() );
        rightEyeScore = calculateScoreForEye ( gaze.getRightEye(), gaze.getRightPupil() );

        score = leftEyeScore + rightEyeScore;
    }
    cout << " Score : " << score << endl;
    return score;
}
float GazeDetector::calculateScoreForEye ( Rect eye, Point2f pupil )
{
    float score = 0;

    if ( eye.width != 0 )
    { score = ( eye.width / 2 - pupil.x ) / eye.width; }
    score *= 100;

    return score;
}

float GazeDetector::getDistractionScore()
{
    float distractedAmount;

    float score = 0;
    scores[currentIndex] = calculateScore ( getGaze ( 0 ) );
    // for ( int i = 0; i < FEATURE_ARRAY_LENGTH; i++ ) {
    score += scores[ ( currentIndex - 1 + FEATURE_ARRAY_LENGTH ) % FEATURE_ARRAY_LENGTH] * 0.8 + scores[currentIndex] ;
    //  }
    scores[currentIndex] = score;

    return abs ( score );
}
Gaze GazeDetector::getGaze ( int gazeFromCurrent )
{
    Gaze gaze;
    /*if  ( gazeFromCurrent > size ) {
        return gaze;
    }*/
    return gazeArray[ ( currentIndex - gazeFromCurrent + FEATURE_ARRAY_LENGTH ) % FEATURE_ARRAY_LENGTH];
}
void GazeDetector::setCurrentGaze ( Gaze gaze )
{

    currentIndex = ( currentIndex + 1 + FEATURE_ARRAY_LENGTH ) % FEATURE_ARRAY_LENGTH;
    gazeArray[currentIndex].setAvailable ( gaze.isAvailable() );
    gazeArray[currentIndex].setLeftEye ( gaze.getLeftEye() );
    gazeArray[currentIndex].setLeftPupil ( gaze.getLeftPupil() );
    gazeArray[currentIndex].setRightEye ( gaze.getRightEye() );
    gazeArray[currentIndex].setRightPupil ( gaze.getRightPupil() );

}