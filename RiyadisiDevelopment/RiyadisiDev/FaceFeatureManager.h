#pragma once
#include "Feature.h"
#include "FeatureCollection.h"
#include "FaceFeature.h"

///<summary>
/// This class identifies and manages the facial features within a sequence of images
///</summary>
class FaceFeatureManager {
public:
    FaceFeatureManager ( void );
    ~FaceFeatureManager ( void );

private:
    FeatureCollection features;
    FaceFeature findFeatures ( Mat image );
    NoseFeature findNoseFeature ( Mat image, Rect roi );
    EyeFeature findLeftEyeFeature ( Mat image, Rect roi );
    EyeFeature findRightEyeFeature ( Mat image, Rect roi );
    MouthFeature findMouthFeature ( Mat image, Rect roi );
    PupilFeature findPupilFeature ( Mat image, Rect roi );
};