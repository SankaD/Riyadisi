#pragma once
#include "Feature.h"
#include "FaceFeature.h";
#include <list>

#define FEATURE_ARRAY_LENGTH  30

///<summary>
///A collection of for Feature instances which implements as a fixed size collection.
///</summary>
class FeatureCollection {
private:
    int counter;
    int size;
    int start;
    FaceFeature featureArray[FEATURE_ARRAY_LENGTH];

public:
    FeatureCollection ( );
    ~FeatureCollection();
    ///<summary>
    ///
    ///</summary>
    FaceFeature *getFeature ( int indexFromCurrent );
    //void addFeature ( FaceFeature feature );
    FaceFeature *FeatureCollection::getNext();
    int getSize();
};
