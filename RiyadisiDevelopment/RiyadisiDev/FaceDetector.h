#pragma once
#include "Detector.h"

class FaceDetector: public Detector {
public:
    FaceDetector ( void );
    ~FaceDetector ( void );
    virtual vector<Rect> optimizeDetection ( vector<Rect> data );
private:
    string faceCascadeName;
};