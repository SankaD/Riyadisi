#pragma once
#include "Feature.h"
#include "FeatureCollection.h"
#include "FaceFeature.h"

#define DOWNSAMPLE_CONSTANT 2

///<summary>
/// This class identifies and manages the facial features within a sequence of images
///</summary>
class FaceFeatureManager {
public:
    FaceFeatureManager ( void );
    ~FaceFeatureManager ( void );
    FeatureCollection *getFeatureCollection();
    FaceFeature *findFeatures ( Mat image );
    NoseFeature findNoseFeature ( Mat image, Rect roi );
    EyeFeature findLeftEyeFeature ( Mat image, Rect roi );
    EyeFeature findRightEyeFeature ( Mat image, Rect roi );
    MouthFeature findMouthFeature ( Mat image, Rect roi );
    PupilFeature findPupilFeature ( Mat image, Rect roi );
private:
    FeatureCollection *features;
};