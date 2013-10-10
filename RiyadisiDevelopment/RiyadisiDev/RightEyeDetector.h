#pragma once
#include "Detector.h"

class RightEyeDetector: public Detector {
public:
    RightEyeDetector();
    ~RightEyeDetector();
    vector<Rect> optimizeDetection ( vector<Rect> data );
private:
    string eyeCascadeName;
};