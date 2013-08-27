#pragma once

#include "Face.h"
#include "Utility.h"
#include "Pupil.h"

class Gaze {

private:
    Circle leftEye;
    Circle rightEye;

public:
    Gaze ( void );
    ~Gaze ( void );
    void setGaze ( Circle leftEye, Circle rightEye );
    float getPupilDistance();
};
