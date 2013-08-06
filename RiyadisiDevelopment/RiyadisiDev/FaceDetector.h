#pragma once
#include "Detector.h"

class FaceDetector: public Detector {
public:
    FaceDetector ( void );
    ~FaceDetector ( void );
private:
    string faceCascadeName;
};