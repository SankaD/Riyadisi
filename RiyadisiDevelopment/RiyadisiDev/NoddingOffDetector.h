#pragma once

#include "FaceFeature.h"
#include "FeatureCollection.h"
#include "FaceNod.h"

using namespace cv;
using namespace std;

class NoddingOffDetector {
private:
    /// stores the face locations
    FaceNod faceArray[FEATURE_ARRAY_LENGTH];
public :
    FaceNod getRect ( int indexFromCurrent );
    void setCurrentRect ( FaceNod rectangle );
    float calculateNoddingOffProbability();
	bool noddingOffDetect(FaceFeature feature);

};
