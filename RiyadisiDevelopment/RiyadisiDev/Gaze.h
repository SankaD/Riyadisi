#pragma once

#include "Circle.h"
#include <opencv2\objdetect\objdetect.hpp>

class Gaze {

private:
    Rect leftEye;
    Rect rightEye;
    Point2f leftPupil;
    Point2f rightPupil;
    Point3f gazePoint;
    bool available;

public:
    Gaze ( void );
    ~Gaze ( void );
    Rect getLeftEye();
    void setLeftEye ( Rect eye );
    Rect getRightEye();
    void setRightEye ( Rect eye );
    Point2f getLeftPupil();
    void setLeftPupil ( Point2f pupil );
    Point2f getRightPupil();
    void setRightPupil ( Point2f pupil );
    bool isAvailable();
    void setAvailable ( bool availability );
    float getPupilDistance();
};
