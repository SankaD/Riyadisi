#pragma once
#include "Detector.h"

class ProfileFaceDetector: public Detector {
public:
    ProfileFaceDetector ( void );
    ~ProfileFaceDetector ( void );
    virtual vector<Rect> optimizeDetection ( vector<Rect> data );
private:
    string faceCascadeName;
};