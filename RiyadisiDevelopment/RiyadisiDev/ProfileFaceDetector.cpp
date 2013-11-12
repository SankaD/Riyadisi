#include "ProfileFaceDetector.h"

using namespace std;
using namespace cv;

ProfileFaceDetector::ProfileFaceDetector ( void ) :
    Detector ( "Resources/Cascades/HaarCascades/haarcascade_profileface.xml" )
{
	scale = 1.5;
	minSize = Size(50, 50);
}

ProfileFaceDetector::~ProfileFaceDetector ( void )
{

}

vector<Rect> ProfileFaceDetector::optimizeDetection ( vector<Rect> data )
{
    return data;
}
