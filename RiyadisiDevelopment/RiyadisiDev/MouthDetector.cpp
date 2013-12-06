#include "MouthDetector.h"

using namespace std;
using namespace cv;

MouthDetector::MouthDetector ( void ) :
    Detector ( "Resources/Cascades/HaarCascades/haarcascade_mcs_mouth.xml" )
{
	scale = 1.5;
	minSize = Size(10, 10);
	donwsampleConst = 2;
}

MouthDetector::~MouthDetector ( void )
{

}

vector<Rect> MouthDetector::optimizeDetection ( vector<Rect> data )
{
   return data;
}
