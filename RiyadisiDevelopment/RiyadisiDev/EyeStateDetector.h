

#include "eyeStateHeaders/engine.h"
#include "eyeStateHeaders/mat.h"
#define  BUFSIZE 256

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

#include "LeftEyeDetector.h"
#include "RightEyeDetector.h"
#include "FaceDetector.h"

using namespace cv;
using namespace std;

class EyeStateDetector {
private:
    /// stores the face locations
    
public :

    float calculateEyeState(Mat eye);

};


