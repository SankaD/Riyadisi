#pragma once
#include <iostream>
#include <opencv2\objdetect\objdetect.hpp>

using namespace std;
using namespace cv;

class Eye {
public :
    Eye ( void );
    ~Eye ( void );
    void setInnerPoint();
    Point2f getInnerPoint();
    void setOuterPoint();
    Point2f getOuterPoint();
private:
    Rect pupil;
    Point2f innerPoint, outerPoint;
};