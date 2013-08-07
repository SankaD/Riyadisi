#pragma once
#include "Detector.h"

class EyeDetector: public Detector {
public:
    EyeDetector();
    ~EyeDetector();
    vector<Rect> optimizeDetection ( vector<Rect> data );
private:
    string eyeCascadeName;
};