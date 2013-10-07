#pragma once

#include "FeatureCollection.h"

FeatureCollection::FeatureCollection ( )
{
    counter = 0;
    size = 0;
    start = 0;
    //featureArray = new FaceFeature[FEATURE_ARRAY_LENGTH];

}
FeatureCollection::~FeatureCollection()
{
    // delete [] featureArray;
}

FaceFeature *FeatureCollection::getFeature ( int indexFromCurrent )
{
    int index = 0;
    if (  indexFromCurrent  > size || indexFromCurrent >= FEATURE_ARRAY_LENGTH ) {
        // if there are not enough elements in the array
        throw new exception ( "Index out of bound" );
    }

    index = ( counter + FEATURE_ARRAY_LENGTH - indexFromCurrent ) % FEATURE_ARRAY_LENGTH;
    return  &featureArray[index] ;
}
FaceFeature *FeatureCollection::getNext()
{
    counter = ( counter + 1 ) % FEATURE_ARRAY_LENGTH;

    if ( size < FEATURE_ARRAY_LENGTH ) {
        size++;
    }

    if ( counter == start ) {
        start++;
    }

    return  &featureArray[counter] ;
}
int FeatureCollection::getSize()
{
    return size;
}