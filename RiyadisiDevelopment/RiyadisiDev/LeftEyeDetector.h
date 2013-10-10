#pragma once
#include "Detector.h"

class LeftEyeDetector: public Detector {
public:
    LeftEyeDetector();
    ~LeftEyeDetector();
    vector<Rect> optimizeDetection ( vector<Rect> data );
private:
    string eyeCascadeName;
};