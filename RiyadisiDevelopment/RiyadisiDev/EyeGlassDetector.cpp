
#include "EyeGlassDetector.h"

using namespace std;
using namespace cv;

EyeGlassDetector::EyeGlassDetector ( void ) :
    Detector ( "Resources/Cascades/HaarCascades/haarcascade_eye_tree_eyeglasses.xml" )
{
	scale = 1.25;
	minSize = Size(30, 30);
}


vector<Rect> EyeGlassDetector::optimizeDetection ( vector<Rect> data )
{
    return data;
}

EyeGlassDetector::~EyeGlassDetector()
{

}


