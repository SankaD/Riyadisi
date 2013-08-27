#pragma once

#include <iostream>
#include <opencv2\objdetect\objdetect.hpp>
#include "Eye.h"

using namespace std;
using namespace cv;

class Face {
public:
    Face ( void );
    ~Face ( void );
private:
    Eye leftEye;
    Eye rightEye;
    Rect nose;
};