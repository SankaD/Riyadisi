#pragma once

#include <opencv2\objdetect\objdetect.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

class FaceNod {
private:
    Rect face;
    bool available;
    time_t timestamp;

public :
    Rect getFace();
    void setFace ( Rect face );
    bool isAvailable();
    void setAvailable ( bool availability );
    time_t getTimestamp();
    void setTimestamp ( time_t time );
};