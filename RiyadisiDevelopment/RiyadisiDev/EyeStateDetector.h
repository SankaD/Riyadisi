


#include "eyeStateHeaders/engine.h"
#include "eyeStateHeaders/mat.h"
#define  BUFSIZE 256

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/photo/photo.hpp";
#include "opencv2/features2d/features2d.hpp";
#include <opencv2/ml/ml.hpp>

#include <iostream>
#include <stdio.h>
#include <fstream>

#include "LeftEyeDetector.h"
#include "RightEyeDetector.h"
#include "FaceDetector.h"
#include "FeatureCollection.h"
#include "FaceFeature.h"

using namespace cv;
using namespace std;

class EyeStateDetector {
private:
    /// stores the perclos scores in a cyclic array
	float scores[FEATURE_ARRAY_LENGTH];
    int currentIndex;
public :

    float calculateEyeState( Mat eye,FileStorage fs);
    void processImage( Mat image);
	float getPerclosScore( FaceFeature *faceFeature, String eyeType, FileStorage fs);
	float setScore(double eyestate);
	EyeStateDetector ( void );
    ~EyeStateDetector ( void );

};


