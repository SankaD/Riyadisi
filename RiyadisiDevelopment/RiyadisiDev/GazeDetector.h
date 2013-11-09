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

/*
    Usage: This class detects the gaze when an image of the eyes is given
*/
class GazeDetector {
private:
    int currentIndex, startIndex, size;
    Gaze gazeArray[FEATURE_ARRAY_LENGTH];
    float scores[FEATURE_ARRAY_LENGTH];
    Gaze getGaze ( int gazeFromCurrent );
    ///<summary>
    ///Calculates a score for the gaze at a given instance
    ///</summary>
    float calculateScore ( Gaze gaze );
    float calculateScoreForEye ( Rect eye, Point2f pupil , char eyeSide );
    float defaultLeftRatio, defaultRightRatio, defaultTopRatio;
public:
    GazeDetector ( void );
    ~GazeDetector ( void );
    void setCurrentGaze ( Gaze gaze );
    Gaze detectGaze ( FaceFeature faceFeature );
    float getDistractionScore();
    void trainDefaultValues ( FaceFeature faceFeature );
};
