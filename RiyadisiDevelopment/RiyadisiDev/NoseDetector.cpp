#pragma once

#include "NoseDetector.h"

NoseDetector::NoseDetector ( void ) :
    Detector ( "Resources/Cascades/HaarCascades/haarcascade_mcs_nose.xml" )
{
	scale = 1.25;
	minSize = Size(30, 30);
}

NoseDetector::~NoseDetector()
{
}

vector<Rect> NoseDetector::optimizeDetection ( vector<Rect> data )
{
    return data;
}
