#pragma once

#include "Circle.h"
#include <opencv2\objdetect\objdetect.hpp>

class Gaze {

private:
    Circle leftEye;
    Circle rightEye;
    Point3f gazePoint;

public:
    Gaze ( void );
    ~Gaze ( void );
    void setGaze ( Circle leftEye, Circle rightEye );
    float getPupilDistance();
};
