
#include "LeftEyeDetector.h"

using namespace std;
using namespace cv;

LeftEyeDetector::LeftEyeDetector (  ) :
    Detector ( "Resources/Cascades/HaarCascades/haarcascade_mcs_lefteye.xml" ) {
    scale = 1.1;
    minSize = Size ( 30,  30 );
    donwsampleConst = 2;
}


vector<Rect> LeftEyeDetector::optimizeDetection ( vector<Rect> data ) {
    vector<Rect> optimizedResults;
    // if the number of eyes detected within a face is greater than 2
    if ( data.size() > 2 ) {

    }
    return optimizedResults;
}

LeftEyeDetector::~LeftEyeDetector() {

}

