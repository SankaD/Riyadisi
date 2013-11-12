#pragma once
#include "Detector.h"

class FrontalFaceDetector: public Detector {
public:
    FrontalFaceDetector ( void );
    ~FrontalFaceDetector ( void );
    virtual vector<Rect> optimizeDetection ( vector<Rect> data );
private:
    string faceCascadeName;
};