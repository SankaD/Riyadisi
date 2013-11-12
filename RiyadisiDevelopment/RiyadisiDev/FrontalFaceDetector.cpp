#include "FrontalFaceDetector.h"

using namespace std;
using namespace cv;

FrontalFaceDetector::FrontalFaceDetector ( void ) :
    Detector ( "Resources/Cascades/HaarCascades/haarcascade_frontalface_alt.xml" )
{
	scale = 1.5;
	minSize = Size(50, 50);
}

FrontalFaceDetector::~FrontalFaceDetector ( void )
{

}

vector<Rect> FrontalFaceDetector::optimizeDetection ( vector<Rect> data )
{
   return data;
}
