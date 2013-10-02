#pragma once
#include "Feature.h"
#include "FaceFeature.h";

///<summary>
///A collection of for Feature instances which implements as a fixed size collection.
///</summary>
class FeatureCollection {
private:
    int counter;
    int size;
    FaceFeature featureArray[FEATURE_ARRAY_LENGTH];
public:
    FeatureCollection ( );
    ///<summary>
    ///
    ///</summary>
    FaceFeature getFeature ( int indexFromCurrent );
    void addFeature ( FaceFeature feature );
};
