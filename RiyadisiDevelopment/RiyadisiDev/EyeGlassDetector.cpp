
#include "EyeGlassDetector.h"

using namespace std;
using namespace cv;

EyeGlassDetector::EyeGlassDetector ( void ) :
    Detector ( "Resources/Cascades/HaarCascades/haarcascade_eye_tree_eyeglasses.xml" )
{
	scale = 1.1;
	minSize = Size(10, 10);
	donwsampleConst = 2;
}


vector<Rect> EyeGlassDetector::optimizeDetection ( vector<Rect> data )
{
    return data;
}

EyeGlassDetector::~EyeGlassDetector()
{

}


