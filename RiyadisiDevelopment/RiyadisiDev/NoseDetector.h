#pragma once

#include "Detector.h"

class NoseDetector: public Detector {
public:
    NoseDetector();
    ~NoseDetector();
    vector<Rect> optimizeDetection ( vector<Rect> data );
private :
    string noseCascadeName;
};