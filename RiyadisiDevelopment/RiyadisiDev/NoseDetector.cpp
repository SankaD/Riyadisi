#pragma once

#include "NoseDetector.h"

NoseDetector::NoseDetector ( void ) :
    Detector ( "Resources/Cascades/HaarCascades/haarcascade_mcs_nose.xml" )
{
}
NoseDetector::~NoseDetector()
{
}

vector<Rect> NoseDetector::optimizeDetection ( vector<Rect> data )
{
    vector<Rect> optimizedResults;
    // if the number of eyes detected within a face is greater than 2
    if ( data.size() > 2 ) {

    }
    return optimizedResults;
}
