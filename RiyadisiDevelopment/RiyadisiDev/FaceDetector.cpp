#include "FaceDetector.h"

using namespace std;
using namespace cv;

FaceDetector::FaceDetector ( void ) :
    Detector ( "Resources/Cascades/HaarCascades/haarcascade_frontalface_alt.xml" )
{

}

FaceDetector::~FaceDetector ( void )
{

}

vector<Rect> FaceDetector::optimizeDetection ( vector<Rect> data )
{
    vector<Rect> optimizedResults;

    return optimizedResults;
}
