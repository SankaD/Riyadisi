#pragma once

#include "FeatureCollection.h"

FeatureCollection::FeatureCollection ( )
{
    counter = 0;
    size = 0;
}
void FeatureCollection::addFeature ( FaceFeature feature )
{
    featureArray[counter] = feature;
    counter = ( counter + 1 ) % FEATURE_ARRAY_LENGTH;
    if ( size < FEATURE_ARRAY_LENGTH ) {
        size++;
    }
}
FaceFeature FeatureCollection::getFeature ( int indexFromCurrent )
{
    int index = 0;
    if (  indexFromCurrent >= size ) {// if there are not enough elements in the array
        throw new exception ( "Index out of bound" );
    }
    index = ( counter + FEATURE_ARRAY_LENGTH - indexFromCurrent ) % FEATURE_ARRAY_LENGTH;
    return featureArray[index];
}