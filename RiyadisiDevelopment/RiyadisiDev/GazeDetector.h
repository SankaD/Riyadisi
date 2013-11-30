#pragma once
#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Gaze.h"
#include "FaceFeature.h"
#include "FeatureCollection.h"

using namespace std;
using namespace cv;

#define DEFAULT_RATIO 0.9

///<summary>
///
///</summary>
struct DirectedGaze {
    double horizontal, vertical;
};
/*
    Usage: This class detects the gaze when an image of the eyes is given
*/
class GazeDetector {
private:
    int currentIndex, startIndex, size;
    Gaze gazeArray[FEATURE_ARRAY_LENGTH];
    DirectedGaze scores[FEATURE_ARRAY_LENGTH];
    Gaze getGaze ( int gazeFromCurrent );
    ///<summary>
    ///Calculates a score for the gaze at a given instance
    ///</summary>
    DirectedGaze calculateScore ( Gaze gaze );
    double calculateScoreForEye ( Rect eye, Point2f pupil , char eyeSide, char direction = 'h' );
    double defaultLeftRatio, defaultRightRatio, defaultTopRatio;
public:
    GazeDetector ( void );
    ~GazeDetector ( void );
    void setCurrentGaze ( Gaze gaze );
    Gaze detectGaze ( FaceFeature faceFeature );
    DirectedGaze getDistractionScore();
    void trainDefaultValues ( FaceFeature faceFeature );
};
