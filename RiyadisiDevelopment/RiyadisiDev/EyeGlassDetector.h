#pragma once
#include "Detector.h"

class EyeGlassDetector: public Detector {
public:
    EyeGlassDetector();
    ~EyeGlassDetector();
    virtual vector<Rect> optimizeDetection ( vector<Rect> data );
private:
    string eyeCascadeName;
};