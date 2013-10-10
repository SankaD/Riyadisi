
#include "RightEyeDetector.h"

using namespace std;
using namespace cv;

RightEyeDetector::RightEyeDetector ( void ) :
    Detector ( "Resources/Cascades/HaarCascades/haarcascade_mcs_righteye.xml" )
{
    scale = 1.1;
    minSize = Size ( 30, 30 );
    //downsampling??
}


vector<Rect> RightEyeDetector::optimizeDetection ( vector<Rect> data )
{
    vector<Rect> optimizedResults;
    // if the number of eyes detected within a face is greater than 2
    if ( data.size() > 2 ) {

    }
    return optimizedResults;
}

RightEyeDetector::~RightEyeDetector()
{

}


