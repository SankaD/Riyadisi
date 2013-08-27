#pragma once

#include "Circle.h"

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
