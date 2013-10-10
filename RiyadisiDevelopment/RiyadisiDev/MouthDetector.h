#pragma once

#include "Detector.h"

class MouthDetector: public Detector {
public:
    MouthDetector();
    ~MouthDetector();
    vector<Rect> optimizeDetection ( vector<Rect> data );
private :
    string mouthCascadeName;
};