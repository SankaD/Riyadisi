#pragma once
#include <iostream>
#include <opencv2\objdetect\objdetect.hpp>
#include "Pupil.h"

using namespace std;
using namespace cv;

enum EyeType {
    LEFT, RIGHT
};

class Eye {
public :
    Eye ( void );
    ~Eye ( void );
    void setInnerPoint ( Point2f point );
    Point2f getInnerPoint();
    void setOuterPoint ( Point2f point );
    Point2f getOuterPoint();
    EyeType getEyeType();
    void setEyeType ( EyeType type );
    void setPupil ( Pupil pupil );
    Pupil getPupil();
private:
    Pupil pupil;
    Point2f innerPoint, outerPoint;
    EyeType type;
};
